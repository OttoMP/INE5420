#include "canvas.h"

Canvas::Canvas()
    : scale(1),       // scales starts at 1 to indicate normal zoom
      x_dislocate(0), // dislocate parameters starts at 0
      y_dislocate(0),
      screen(Ponto(0,0), Ponto(0,100), Ponto(100,0))//
{
    this->update_conv_matrix();
}

Canvas::~Canvas()
{
}

/*  Function Get Last ID
 *  Function used when setting the id of polygons in display_file.
 *  When display_file is empty it returns 0. Otherwise it returns the
 *  id of the currently last object. If the display_file ever empties after
 *  the start of the application the id count resets
 */
int Canvas::get_last_id() {
    if(display_file.empty())
        return display_file.size();
    else
        return display_file.back().get_id();
}

/*  Function Get Last Name
 *  Function used to display in the log the name of the polygon
 */
std::string Canvas::get_last_name() {
    if(display_file.empty())
        return "";
    else
        return display_file.back().get_nome();
}

/*  Function Get Display File
 *
 */
std::list<Poligono> Canvas::get_display_file() {
    return this->display_file;
}

/*
 *
 */
void Canvas::set_display_file(std::list<Poligono> loaded_display_file) {
    this->display_file = loaded_display_file;
    this->update_scn_coord();
    queue_draw();
}

/*  Function Add Polygon
 *  Function used to add a new polygon to the display_file. It
 *  pushes the polygon sent as parameter to the end of the list
 */
void Canvas::add_poligono(Poligono pol) {
    pol.exec_update_scn(this->cart_to_scn);
    display_file.push_back(pol);
    queue_draw();
}

/*  Function Remove Polygon
 *  Function used to remove the especified polygon from the display_file
 */
void Canvas::rm_poligono(int id) {
    Poligono p = Poligono("deletar");
    p.set_id(id);
    display_file.remove(p);
    queue_draw();
}

/*  Drawing function
 *  Function used to draw all objects in the display_file in the screen.
 *  It first reads the scale and dislocate parameters to set the view accordingly
 *  then it iterates the display_file drawing each of the objects inside of it
 */
bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->scale(scale, scale);
    //drawing the coordinate lines
    cr->set_line_width(1);
    cr->set_source_rgb(0.0, 0.4, 0.8);
    Ponto p1 = this->cart_to_scn.exec_transform(Ponto(0,-1000));
    Ponto p2 = this->cart_to_scn.exec_transform(Ponto(0, 1000));

    cr->move_to(vp_transform_x(p1.get_x(),width), vp_transform_y(p1.get_y(),height));
    cr->line_to(vp_transform_x(p2.get_x(),width), vp_transform_y(p2.get_y(),height));

    p1 = this->cart_to_scn.exec_transform(Ponto(-1000,0));
    p2 = this->cart_to_scn.exec_transform(Ponto(1000,0));

    cr->move_to(vp_transform_x(p1.get_x(),width), vp_transform_y(p1.get_y(),height));
    cr->line_to(vp_transform_x(p2.get_x(),width), vp_transform_y(p2.get_y(),height));

  // draw red lines out from the center of the window
    cr->stroke();
    
    cr->set_source_rgb(0.0, 0.5, 0);
    
    cr->move_to(vp_transform_x(0.1,width), vp_transform_y(0,height));
    cr->line_to(vp_transform_x(-0.1,width), vp_transform_y(0,height));
    cr->move_to(vp_transform_x(0,width), vp_transform_y(0.1,height));
    cr->line_to(vp_transform_x(0,width), vp_transform_y(-0.1,height));
    
    cr->stroke();

//--------------------CLIPPING----------------------------
    // drawing subcanvas for clipping
    cr->set_source_rgb(0.0, 0.8, 0.0);

    cr->move_to(10,10);

    cr->line_to(10,(height/scale)-10);

    cr->line_to((width/scale)-10,(height/scale)-10);

    cr->line_to((width/scale)-10,10);

    cr->line_to(10,10);

    Ponto top_left(10,10);
    Ponto bottom_right((width/scale)-10,(height/scale)-10);

    cr->stroke();

    cr->set_source_rgb(0.8, 0.0, 0.0);
    for (auto i = display_file.begin(); i != display_file.end(); i++)
    {
        std::list<Ponto> pontos= i->draw(this->calc_distancia(screen.get_v(), Ponto(0,0)));
        if(pontos.size() == 2) {
            if(!inside_view(pontos.front(),
                            top_left, bottom_right,
                            height, width)) {
                continue;
            }
        }
        cr->set_line_width(i->get_brush_size());
        cr->move_to(vp_transform_x(pontos.back().get_x(), width),
                    vp_transform_y(pontos.back().get_y(), height));
        for (auto pt = pontos.begin(); pt != pontos.end(); pt++)
        {
            cr->line_to(vp_transform_x(pt->get_x(), width),
                        vp_transform_y(pt->get_y(), height));
        }
        if(i->get_filled())
            cr->fill();
        cr->stroke();
    }

    return true;
}

/*  Funtion Zoom In
 *  Function used to set the zoom of the viewport.
 *  It changes the value of scale adding a factor sent as parameter
 */
void Canvas::zoom_in(double factor) {
    screen.scale(1/factor);
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}



/*  Funtion Zoom Out
 *  Function used to set the zoom of the viewport.
 *  It changes the value of scale subtracting a factor sent as parameter
 */
void Canvas::zoom_out(double factor) {
    screen.scale(factor);
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}

/*  Move Up Function
 *  Function used to change the view of the viewport, sending it up.
 *  It changes the value in the y_dislocate attribute by adding a step
 *  sent as parameter
 */
void Canvas::move_up(double step) {
    screen.translate(Ponto(0,-step));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}

/*  Move Down Function
 *  Function used to change the view of the viewport, sending it down.
 *  It changes the value in the y_dislocate attribute by subtracting a step
 *  sent as parameter
 */
void Canvas::move_down(double step) {
    screen.translate(Ponto(0,step));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}


/*  Move Right Function
 *  Function used to change the view of the viewport, sending it to the right.
 *  It changes the value in the x_dislocate attribute by subtracting a step
 *  sent as parameter
 */


void Canvas::move_right(double step) {	 	  	 	    	 	    		    	    	  	 	
    screen.translate(Ponto(-step,0));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}


/*  Move Left Function
 *  Function used to change the view of the viewport, sending it to the left.
 *  It changes the value in the x_dislocate attribute by adding a step
 *  sent as parameter
 */

void Canvas::move_left(double step) {
    screen.translate(Ponto(step,0));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}

/*
 *
 */
void Canvas::rotate(double angle)
{
    screen.rotate(angle);
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}

/*  Rotate Function
 *  Function used to rotate an object around itself by some angle
 */

void Canvas::rotate_object(int id, double angle) {
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().rotate(angle, (*pol).get_center());
           pol->exec_transform(m);
           pol->exec_update_scn(this->cart_to_scn);
           break;
        }
    }
    queue_draw();
}

/*  Rotate Function
 *  Function used to rotate an object around itself by some angle
 */

void Canvas::rotate_point(int id, double angle, Ponto centro) {
    Ponto novo_ponto = this->scn_to_cart.exec_transform(centro);
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().rotate(angle, novo_ponto);
           pol->exec_transform(m);
           pol->exec_update_scn(this->cart_to_scn);
           break;
        }
    }
    queue_draw();
}

void Canvas::rotate_center(int id, double angle) {
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().rotate(angle, Ponto(0,0));
           pol->exec_transform(m);
           pol->exec_update_scn(this->cart_to_scn);
           break;
        }
    }
    queue_draw();
}

/*  Move Function
 *  Function used to move an object around by some distance determined by a dot
 */

void Canvas::move_object(int id, Ponto distancia) {
    Ponto novo_ponto = this->scn_to_cart.exec_transform(distancia);
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().translate(novo_ponto);
           pol->exec_transform(m);
           pol->exec_update_scn(this->cart_to_scn);
           break;
        }
    }
    queue_draw();
}

/*  Resize Function
 *  Function used to Resize an object by some size
 */

void Canvas::resize_object(int id, Ponto size) {
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().scale(size, pol->get_center());
           pol->exec_transform(m);
           pol->exec_update_scn(this->cart_to_scn);
           break;
        }
    }
    queue_draw();
}

/*  Function Viewport transform X
 *  Function used to change a cartesian dot to viewport coordinates
 *  in the X axis
 */
double Canvas::vp_transform_x(double x, double width){
    return (x - (-1)) / (1-(-1)) * width;
}


/*  Function Viewport transform Y
 *  Function used to change a cartesian dot to viewport coordinates
 *  in the Y axis
 */
double Canvas::vp_transform_y(double y, double height){
    return (y - (1)) / (-1-(1)) * height;
}

double Canvas::calc_angulo(Ponto a, Ponto b) //só funciona quando b é vertical arrumar depois
{

    double cima = a.get_x()*b.get_x() + a.get_y()*b.get_y();
    double baixo = sqrt(pow(a.get_x(),2) + pow(a.get_y(),2))*
        sqrt(pow(b.get_x(),2)+pow(b.get_y(),2));
    double temp = cima/baixo;
    if (a.get_x() >=0 && a.get_y() <0 || a.get_x()>0 && a.get_y()>0){
        return -abs(acos(temp)*180/M_PI);
    } else {
        return abs(acos(temp)*180/M_PI);
    }

}

double Canvas::calc_distancia(Ponto a, Ponto b)
{
    return sqrt(pow(a.get_x() - b.get_x(), 2) + pow(a.get_y() - b.get_y(), 2));
}

void Canvas::update_scn_coord()
{
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        pol->exec_update_scn(this->cart_to_scn);
    }
}

void Canvas::update_conv_matrix()
{
    double angulo = this->calc_angulo(screen.get_v(), Ponto(0,1));
    this->cart_to_scn = Matriz().translate(
                                           Ponto(
                                                 -screen.get_wc().get_x(),
                                                 -screen.get_wc().get_y()))
        .multiplication(Matriz().rotate(-angulo, Ponto(0,0)))
        .multiplication(Matriz().scale(
                                       Ponto(
                                             1/this->calc_distancia(screen.get_v(),Ponto(0,0)),
                                             1/this->calc_distancia(screen.get_u(),Ponto(0,0))),
                                             screen.get_wc()));

    this->scn_to_cart = Matriz().scale(Ponto(this->calc_distancia(screen.get_v(),Ponto(0,0)),
                this->calc_distancia(screen.get_u(),Ponto(0,0))),screen.get_wc())
        .multiplication(Matriz().rotate(angulo, Ponto(0,0)))
        .multiplication(Matriz().translate(Ponto(screen.get_wc().get_x(), screen.get_wc().get_y())));
}

/* Function Clipping Line
 * Function used to clip lines out of viewport
 * It uses the Liang-Barsky algorithm
 */
void Canvas::clipping_line(Poligono line, Ponto tl, Ponto br) {
    double xmin = tl.get_x();
    double ymin = tl.get_y();
    double xmax = br.get_x();
    double ymax = br.get_y();

    std::list<Ponto> line_p = line.draw(this->calc_distancia(screen.get_v(), Ponto(0,0)));

    double p1 = -(line_p.front().get_x() - line_p.back().get_x());
    double p2 = line_p.front().get_x() - line_p.back().get_x();
    double p3 = -(line_p.front().get_y() - line_p.back().get_y());
    double p4 = line_p.front().get_y() - line_p.back().get_y();

    double q1 = line_p.front().get_x() - xmin;
    double q2 = xmax - line_p.front().get_x();
    double q3 = line_p.front().get_y() - ymin;
    double q4 = ymax - line_p.front().get_y();

    if(p1 != 0)
        double r1 = q1/p1;
    if(p2 != 0)
        double r2 = q2/p2;
    if(p3 != 0)
        double r3 = q3/p3;
    if(p4 != 0)
        double r4 = q4/p4;

}

/* Function Clipping Polygon
 * Function used to clip polygons out of viewport
 * It uses the Weiler-Atherton algorithm
 */
void Canvas::clipping_poly(Poligono poly, double height, double width, double scale) {
/*    Ponto top_left(10, 10);
    Ponto bottom_left(10, (height/scale)-10;
    Ponto bottom_right((width/scale)-10, (height/scale)-10);
    Ponto top_right((width/scale)-10, 10);

    std::list<Ponto> window_corners = {top_left, top_right, bottom_right, bottom_left};
    std::list<Ponto> entrances = {};
    std::list<Ponto> poly_corners = poly.draw();

    for {auto p = poly_corners.begin(); p != poly_corners.end(); p++) {
        next = p++;
        if(!inside_view(p, top_left, bottom_right) && inside_view(next, top_left, bottom_right)) {
            entrances.push_back();
            window_corners.insert();
            poly_corners.insert();
        } else
    }*/
}

bool Canvas::inside_view(Ponto p,
                         Ponto tl, Ponto br,
                         double height, double width) {
    double xmin = tl.get_x();
    double ymin = tl.get_y();
    double xmax = br.get_x();
    double ymax = br.get_y();
    double x = vp_transform_x(p.get_x(), width);
    double y = vp_transform_y(p.get_y(), height);

    if(x < xmax && x > xmin && y < ymax && y > ymin) {
        return true;
    } else {
        return false;
    }
}
