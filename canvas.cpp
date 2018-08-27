#include "canvas.h"

Canvas::Canvas()
    : scale(1),       // scales starts at 1 to indicate normal zoom
      x_dislocate(-10), // dislocate parameters starts at 0
      y_dislocate(-10),
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
int Canvas::get_last_id() 
{
    if(display_file.empty())
        return display_file.size();
    else
        return display_file.back().get_id();
}

/*
 *
 */
std::string Canvas::get_last_name() {
    if(display_file.empty())
        return "";
    else
        return display_file.back().get_nome();
}	 	  	 	    	 	    		    	    	  	 	

/*  Function Add Polygon
 *  Function used to add a new polygon to the display_file. It
 *  pushes the polygon sent as parameter to the end of the list
 */
void Canvas::add_poligono(Poligono pol)
{
    pol.exec_update_scn(this->cart_to_scn);
    //pol.exec_transform(this->scn_to_cart);
    display_file.push_back(pol);
    queue_draw();
}

/*  Function Remove Polygon
 *  Function used to remove the especified polygon from the display_file
 */
void Canvas::rm_poligono(int id)
{
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
//-----------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------
  // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->scale(scale, scale);
    //drawing the coordinate lines
    cr->set_line_width(1);
    cr->set_source_rgb(0.0, 0.4, 0.8);

    cr->move_to(0, vp_transform_y(0, height));
    cr->line_to(width/scale, vp_transform_y(0, height));

    cr->move_to(-x_dislocate, 0);
    cr->line_to(-x_dislocate, height/scale);

  // draw red lines out from the center of the window
    cr->stroke();

//--------------------CLIPPING----------------------------
    // drawing subcanvas for clipping
    cr->set_source_rgb(0.0, 0.8, 0.0);

    cr->move_to(10, (height/scale)-10);
    cr->line_to((width/scale)-10, (height/scale)-10);

    cr->line_to((width/scale)-10, 10);
    cr->line_to(10, 10);
    cr->line_to(10, (height/scale)-10);

    cr->stroke();

//---------------------------------------------------------

    cr->set_source_rgb(0.8, 0.0, 0.0);
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {	 	  	 	    	 	    		    	    	  	 	
        std::list<Ponto> pontos= pol->draw();
        cr->set_line_width(pol->get_brush_size());
        cr->move_to(vp_transform_x(pontos.back().get_x(), width), vp_transform_y(pontos.back().get_y(), height));
        for (std::list<Ponto>::iterator pt = pontos.begin(); pt != pontos.end(); pt++)
        {
            cr->line_to(vp_transform_x(pt->get_x(), width), vp_transform_y(pt->get_y(), height));
        }
        cr->line_to(vp_transform_x(pol->get_center().get_x(), width), vp_transform_y(pol->get_center().get_y(), height));
    }

    cr->stroke();

    return true;
}

/*  Funtion Zoom In
 *  Function used to set the zoom of the viewport.
 *  It changes the value of scale adding a factor sent as parameter
 */
void Canvas::zoom_in(double factor) 
{
    screen.scale(Ponto(factor,factor));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}


/*  Funtion Zoom Out
 *  Function used to set the zoom of the viewport.
 *  It changes the value of scale subtracting a factor sent as parameter
 */
void Canvas::zoom_out(double factor) 
{
    screen.scale(Ponto(1/factor,1/factor));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}	 	  	 	    	 	    		    	    	  	 	

/*  Move Up Function
 *  Function used to change the view of the viewport, sending it up.
 *  It changes the value in the y_dislocate attribute by adding a step
 *  sent as parameter
 */
void Canvas::move_up(double step) 
{
    screen.translate(Ponto(0,step));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}


/*  Move Down Function
 *  Function used to change the view of the viewport, sending it down.
 *  It changes the value in the y_dislocate attribute by subtracting a step
 *  sent as parameter
 */
void Canvas::move_down(double step) 
{
    screen.translate(Ponto(0,-step));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}


/*  Move Right Function
 *  Function used to change the view of the viewport, sending it to the right.
 *  It changes the value in the x_dislocate attribute by subtracting a step
 *  sent as parameter
 */
void Canvas::move_right(double step) 
{	 	  	 	    	 	    		    	    	  	 	
    screen.translate(Ponto(step,0));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}


/*  Move Left Function
 *  Function used to change the view of the viewport, sending it to the left.
 *  It changes the value in the x_dislocate attribute by adding a step
 *  sent as parameter
 */

void Canvas::move_left(double step) 
{
    screen.translate(Ponto(-step,0));
    this->update_conv_matrix();
    this->update_scn_coord();
    queue_draw();
}

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

void Canvas::rotate_object(int id, double angle) 
{
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

void Canvas::rotate_point(int id, double angle, Ponto centro) 
{
    //Ponto novo_ponto = this->cart_to_scn.exec_transform(centro);
    Ponto novo_ponto = centro;
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

/*  Move Function
 *  Function used to move an object around by some distance determined by a dot
 */

void Canvas::move_object(int id, Ponto distancia) 
{	 	  	 	    	 	    		    	    	  	 	
    //Ponto novo_ponto = this->cart_to_scn.exec_transform(distancia);
    Ponto novo_ponto = distancia;
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

void Canvas::resize_object(int id, Ponto size)
{
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
double Canvas::vp_transform_x(double x, double width)
{	 	  	 	    	 	    		    	    	  	 	
    return (x - x_dislocate) / width * width;
}


/*  Function Viewport transform Y
 *  Function used to change a cartesian dot to viewport coordinates
 *  in the Y axis
 */
double Canvas::vp_transform_y(double y, double height)
{
    return (1-(y - y_dislocate)/height) * height;
}

double Canvas::calc_angulo(Ponto a, Ponto b) //só funciona quando b é vertical arrumar depois
{
    double coef_a = a.get_x()/a.get_y();
    double coef_b = b.get_x()/b.get_y();
    double temp = abs(1/(coef_a));
    return atan(temp)*180/M_PI;
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
    this->cart_to_scn = Matriz().translate(Ponto(-screen.get_wc().get_x(), -screen.get_wc().get_y()))
        .multiplication(Matriz().rotate(-angulo, Ponto(0,0)))
        .multiplication(Matriz().scale(
            Ponto(1/this->calc_distancia(screen.get_v(),Ponto(0,0)),
                1/this->calc_distancia(screen.get_u(),Ponto(0,0))),
            screen.get_wc()));
    this->scn_to_cart = Matriz().scale(Ponto(this->calc_distancia(screen.get_v(),Ponto(0,0)),
                this->calc_distancia(screen.get_u(),Ponto(0,0))),screen.get_wc())
        .multiplication(Matriz().rotate(angulo, Ponto(0,0)))
        .multiplication(Matriz().translate(Ponto(screen.get_wc().get_x(), screen.get_wc().get_y())));
}