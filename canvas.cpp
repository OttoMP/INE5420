#include "canvas.h"

Canvas::Canvas()
    : scale(1),       // scales starts at 1 to indicate normal zoom
      x_dislocate(-50), // dislocate parameters starts at 0
      y_dislocate(-50)  //
{
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
void Canvas::add_poligono(Poligono pol){
    //display_file.push_back(pol);
    Matriz m = Matriz().rotate(45, pol.get_center());

    pol.exec_transform(m);
    display_file.push_back(pol);
    queue_draw();
}

/*  Function Remove Polygon
 *  Function used to remove the especified polygon from the display_file
 */
void Canvas::rm_poligono(int id){
    for(auto i = display_file.begin(); i != display_file.end(); i++) {
       if(i->get_id() == id) {
           display_file.erase(i);
           break;
        }
    }
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

    cr->move_to(10, 10);
    cr->line_to(10, (height/scale)-10);
    cr->line_to((width/scale)-10, (height/scale)-10);
    cr->line_to((width/scale)-10, 10);
    cr->line_to(10, 10);

    Ponto top_left(vp_transform_x(10, width),
                   vp_transform_y(10, height));
    Ponto bottom_right(vp_transform_x((width/scale)-10, width),
                       vp_transform_y((height/scale)-10, height));

    cr->stroke();

//---------------------------------------------------------

    cr->set_source_rgb(0.8, 0.0, 0.0);
    for (auto i = display_file.begin(); i != display_file.end(); i++)
    {
        std::list<Ponto> pontos= i->draw();
        if(pontos.size() == 1) {
            if(!inside_view(pontos.front(), top_left, bottom_right)) {
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
        cr->line_to(vp_transform_x(i->get_center().get_x(), width),
                    vp_transform_y(i->get_center().get_y(), height));

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
    scale += factor;
    queue_draw();
}


/*  Funtion Zoom Out
 *  Function used to set the zoom of the viewport.
 *  It changes the value of scale subtracting a factor sent as parameter
 */
void Canvas::zoom_out(double factor) {
    scale -= factor;
    queue_draw();
}

/*  Move Up Function
 *  Function used to change the view of the viewport, sending it up.
 *  It changes the value in the y_dislocate attribute by adding a step
 *  sent as parameter
 */
void Canvas::move_up(double step) {
    y_dislocate += step;
    queue_draw();
}


/*  Move Down Function
 *  Function used to change the view of the viewport, sending it down.
 *  It changes the value in the y_dislocate attribute by subtracting a step
 *  sent as parameter
 */
void Canvas::move_down(double step) {
    y_dislocate -= step;
    queue_draw();
}


/*  Move Right Function
 *  Function used to change the view of the viewport, sending it to the right.
 *  It changes the value in the x_dislocate attribute by subtracting a step
 *  sent as parameter
 */
void Canvas::move_right(double step) {
    x_dislocate += step;
    queue_draw();
}


/*  Move Left Function
 *  Function used to change the view of the viewport, sending it to the left.
 *  It changes the value in the x_dislocate attribute by adding a step
 *  sent as parameter
 */

void Canvas::move_left(double step) {
    x_dislocate -= step;
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
           break;
        }
    }
    queue_draw();
}

/*  Rotate Function
 *  Function used to rotate an object around itself by some angle
 */

void Canvas::rotate_point(int id, double angle, Ponto centro) {
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().rotate(angle, centro);
           pol->exec_transform(m);
           break;
        }
    }
    queue_draw();
}

/*  Move Function
 *  Function used to move an object around by some distance determined by a dot
 */

void Canvas::move_object(int id, Ponto distancia) {
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        if(pol->get_id() == id) {
           Matriz m = Matriz().translate(distancia);
           pol->exec_transform(m);
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
    return (x - x_dislocate) / width * width;
}


/*  Function Viewport transform Y
 *  Function used to change a cartesian dot to viewport coordinates
 *  in the Y axis
 */
double Canvas::vp_transform_y(double y, double height){
    return (1-(y - y_dislocate)/height) * height;
}

/* Function Clipping Line
 * Function used to clip lines out of viewport
 * It uses the Liang-Barsky algorithm
 */
void clipping_line(Poligono line, Ponto tl, Ponto br) {
/*    double xmin = tl.get_x();
    double ymin = tl.get_y();
    double xmax = br.get_x();
    double ymax = br.get_y();

    std::vector<Ponto> line_p{ std::begin(line.draw()), std::end(line.draw) };

    double p1 = -(line_p[0].get_x() - line_p[1].get_x());
    double p2 = line_p[0].get_x() - line_p[1].get_x();
    double p3 = -(line_p[0].get_y() - line_p[1].get_y());
    double p4 = line_p[0].get_y() - line_p[1].get_y();

    double q1 = line_p[0],get_x() - xmin;
    double q2 = xmax - line_p[0].get_x();
    double q3 = line_p[0].get_y() - ymin;
    double q4 = ymax - line_p[0].get_y();

    if(p1 != 0)
        double r1 = q1/p1;
    if(p2 != 0)
        double r2 = q2/p2;
    if(p3 != 0)
        double r3 = q3/p3;
    if(p4 != 0)
        double r4 = q4/p4;
*/
}

/* Function Clipping Polygon
 * Function used to clip polygons out of viewport
 * It uses the Weiler-Atherton algorithm
 */
void clipping_poly(Poligono poly, double height, double width, double scale) {
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

bool Canvas::inside_view(Ponto p, Ponto tl, Ponto br) {
    double xmin = tl.get_x();
    double ymin = tl.get_y();
    double xmax = br.get_x();
    double ymax = br.get_y();

    if(p.get_x() < xmax && p.get_x() > xmin && p.get_y() < ymax && p.get_y() > ymin) {
        return true;
    } else {
        return false;
    }
}
