#include "canvas.h"

Canvas::Canvas()
    : scale(1),       // scales starts at 1 to indicate normal zoom
      x_dislocate(0), // dislocate parameters starts at 0
      y_dislocate(0), /**/
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

/*  Function Get Last Name
 *  Function used to display in the log the name of the polygon
 */
std::string Canvas::get_last_name()
{
    if(display_file.empty())
        return "";
    else
        return display_file.back().get_nome();
}

/*  Function Get Display File
 *  Function called when the application is going to save
 *  the current set of canvas. Used in the write function inside DescritorObj
 */
std::list<Objeto> Canvas::get_display_file()
{
    return this->display_file;
}

/*  Function Load Display File
 *  Function called by the DescritorObj to set the canvas when reading a file
 */
void Canvas::load_display_file(std::list<Objeto> loaded_display_file)
{
    this->display_file = loaded_display_file;
    this->update_scn_coord();
    queue_draw();
}

/*  Function Add Polygon
 *  Function used to add a new polygon to the display_file. It
 *  pushes the polygon sent as parameter to the end of the list
 */
void Canvas::add_poligono(Poligono pol)
{
    pol.exec_update_scn(this->cart_to_scn);
    display_file.push_back(pol.to_objeto());
    std::cin.get();
}

void Canvas::add_curva(Curva2D curva)
{
    curva.exec_update_scn(this->cart_to_scn);
    display_file.push_back(curva.to_objeto());
    queue_draw();
}

/*  Function Remove Polygon
 *  Function used to remove the especified polygon from the display_file
 */
void Canvas::rm_objeto(int id) 
{
    Objeto o = Objeto();
    o.set_id(id);
    display_file.remove(o);
    queue_draw();
}

/*  Drawing function
 *  Function used to draw all objects in the display_file on the screen.  It
 *  first reads the scale and dislocate parameters to set the view accordingly
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
// --------------Drawing the coordinate lines-------------

    cr->set_line_width(1);
    cr->set_source_rgb(0.0, 0.4, 0.8);
    Ponto p1 = this->cart_to_scn.exec_transform(Ponto(0,-1000));
    Ponto p2 = this->cart_to_scn.exec_transform(Ponto(0, 1000));

    cr->move_to(vp_transform_x(p1.get_x(),width),
                vp_transform_y(p1.get_y(),height));
    cr->line_to(vp_transform_x(p2.get_x(),width),
                vp_transform_y(p2.get_y(),height));

    p1 = this->cart_to_scn.exec_transform(Ponto(-1000,0));
    p2 = this->cart_to_scn.exec_transform(Ponto(1000,0));

    cr->move_to(vp_transform_x(p1.get_x(),width),
                vp_transform_y(p1.get_y(),height));
    cr->line_to(vp_transform_x(p2.get_x(),width),
                vp_transform_y(p2.get_y(),height));

    cr->stroke();

//--------------------CLIPPING----------------------------
    // drawing subcanvas for clipping debugging
    cr->set_source_rgb(0.0, 0.8, 0.0);

    cr->move_to(vp_transform_x(-0.9, width),
                vp_transform_y(0.9, height));

    cr->line_to(vp_transform_x(0.9, width),
                vp_transform_y(0.9, height));

    cr->line_to(vp_transform_x(0.9, width),
                vp_transform_y(-0.9, height));

    cr->line_to(vp_transform_x(-0.9, width),
                vp_transform_y(-0.9, height));

    cr->line_to(vp_transform_x(-0.9, width),
                vp_transform_y(0.9, height));

    cr->stroke();

//-----------------Drawing display file--------------------

    cr->set_source_rgb(0.8, 0.0, 0.0);
    for (auto i = display_file.begin(); i != display_file.end(); i++)
    {
        
        if (i->get_tipo() == 2)
        {
            Curva2D objeto = Curva2D(*i);
            std::list<Ponto> pontos = objeto.draw(1,-0.9, 0.9, -0.9, 0.9); // pega os pontos pra desenhar da curva

            cr->set_line_width(objeto.get_brush_size()); 

            cr->move_to(vp_transform_x(pontos.back().get_x(), width),
                        vp_transform_y(pontos.back().get_y(), height));

            for (auto pt = pontos.begin(); pt != pontos.end(); pt++)
            {
                cr->line_to(vp_transform_x(pt->get_x(), width),
                            vp_transform_y(pt->get_y(), height));
            }
            cr->stroke();
        }
        else if(i->get_tipo() == 1)
        {
            Poligono objeto = Poligono(*i);
            // Initialize a list of polygons to draw it will be needed in case the
            // clipping_poly() creates more polygons
            std::list<Poligono> to_draw_poly = {};

            // Analyzing what type of object we are drawing based in the number of
            // dots
            std::list<Ponto> pontos = objeto.get_pontos();
            if(pontos.size() == 1) {
                // Clipping Dots
                if(!inside_view(pontos.front())) {
                    continue;
                } else {
                    to_draw_poly.push_back(Poligono("clip",objeto.draw(
                                                              this->calc_distancia(
                                                                     screen.get_v(),
                                                                     Ponto(0,0)))));
                }
            } else
            if(pontos.size() == 2) {
                // Clipping Lines
                std::list<Ponto> clipped_line = clipping_line(
                                                    objeto.draw(this->calc_distancia(
                                                                   screen.get_v(),
                                                                   Ponto(0,0))));
                if(clipped_line.size() == 0) {
                    continue;
                }
                to_draw_poly.push_back(Poligono("clip", clipped_line));
            } else {
                // Clipping Polygons;
                to_draw_poly = clipping_poly(
                                   objeto.draw(this->calc_distancia(
                                                  screen.get_v(),
                                                  Ponto(0,0))));

                if(to_draw_poly.size() == 0) {
                    continue;
                }
            }

            // Drawing loop
            cr->set_line_width(objeto.get_brush_size());
            for(auto drawing_it = to_draw_poly.begin();
                drawing_it != to_draw_poly.end();
                drawing_it++) {

                // We call get_pontos() instead of draw() because after the
                // clipping the dots are already in window coordinates
                pontos = drawing_it->get_pontos();
                cr->move_to(vp_transform_x(pontos.back().get_x(), width),
                            vp_transform_y(pontos.back().get_y(), height));

                for (auto pt = pontos.begin(); pt != pontos.end(); pt++)
                {
                    cr->line_to(vp_transform_x(pt->get_x(), width),
                                vp_transform_y(pt->get_y(), height));
                }

                // Fill the polygon if needed
                if(objeto.get_filled()) {
                    cr->fill();
                }
                cr->stroke();
            }
        }

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

/*  Rotate Window Function
 *  Function called when rotating the viewport window
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

/*  Rotate Dot Function
 *  Function used to rotate an object around an arbitrary Dot inside window
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

/*  Rotate Center Function
 *  Function used to rotate an object around the center of window
 */
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

/*
 *
 */
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

/*
 *
 */
double Canvas::calc_distancia(Ponto a, Ponto b)
{
    return sqrt(pow(a.get_x() - b.get_x(), 2) + pow(a.get_y() - b.get_y(), 2));
}

/*
 *
 */
void Canvas::update_scn_coord()
{
    for (auto pol = display_file.begin(); pol != display_file.end(); pol++)
    {
        pol->exec_update_scn(this->cart_to_scn);
    }
}

/*
 *
 */
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
std::list<Ponto> Canvas::clipping_line(std::list<Ponto> line_p) {

    // Initialize list to be returned
    std::list<Ponto> clipped_dots;

    bool front_is_inside = inside_view(line_p.front());
    bool back_is_inside = inside_view(line_p.back());

    // Verify if both dots are inside window, if true no clipping is needed
    if(front_is_inside && back_is_inside) {
        return line_p;
    }

    // Setting borders of window
    // using 0.9 because of the subcanvas
    double xmin = -0.9;
    double ymin = -0.9;
    double xmax = 0.9;
    double ymax = 0.9;

    // - delta x
    double p1 = -(line_p.back().get_x() - line_p.front().get_x());
    // delta x
    double p2 = -p1;
    // - delta y
    double p3 = -(line_p.back().get_y() - line_p.front().get_y());
    // delta y
    double p4 = -p3;

    // x1 - xmin
    double q1 = line_p.front().get_x() - xmin;
    // xmax - x1
    double q2 = xmax - line_p.front().get_x();
    // y1 - ymin
    double q3 = line_p.front().get_y() - ymin;
    // ymax - y1
    double q4 = ymax - line_p.front().get_y();

    // u1 = values lesser than 0
    // u2 = values greater than 0
    std::vector<double> u1, u2;
    u1.push_back(0);
    u2.push_back(1);

    // Verifying if line is parallel to window
    if(p1 == 0) {
        if(!front_is_inside && !back_is_inside) {
            return clipped_dots;
        }
    } else if(p3 == 0) {
        if(!front_is_inside && !back_is_inside) {
            return clipped_dots;
        }
    }

    if(p1 != 0) {
        double r1 = q1/p1;
        double r2 = q2/p2;
        if(p1 < 0) {
            u1.push_back(r1);
            u2.push_back(r2);
        } else {
            u1.push_back(r2);
            u2.push_back(r1);
        }
    }

    if(p3 != 0) {
        double r3 = q3/p3;
        double r4 = q4/p4;
        if(p3 < 0) {
            u1.push_back(r3);
            u2.push_back(r4);
        } else {
            u1.push_back(r4);
            u2.push_back(r3);
        }
    }

    auto max = *std::max_element(u1.begin(), u1.end());
    auto min = *std::min_element(u2.begin(), u2.end());

    if(max>min) {
        // line outside canvas
        return clipped_dots;
    }

    if(!front_is_inside) {
        clipped_dots.push_back(Ponto(
                               line_p.front().get_x() + max*p2,
                               line_p.front().get_y() + max*p4));
    } else {
        clipped_dots.push_back(line_p.front());
    }

    if(!back_is_inside) {
        clipped_dots.push_back(Ponto(
                               line_p.front().get_x() + min*p2,
                               line_p.front().get_y() + min*p4));
    } else {
        clipped_dots.push_back(line_p.back());
    }

    return clipped_dots;
}

/* Function Clipping Polygon
 * Function used to clip polygons out of viewport
 * It uses the Weiler-Atherton algorithm
 */
std::list<Poligono> Canvas::clipping_poly(std::list<Ponto> poly_p) {
    std::list<Poligono> clipped_poly;
    poly_p.pop_front();
    poly_p.pop_back();

    // Setting window's borders
    // using 0.9 because of the subcanvas
    Ponto top_left(-0.9, 0.9);
    Ponto bottom_left(-0.9, -0.9);
    Ponto bottom_right(0.9, -0.9);
    Ponto top_right(0.9, 0.9);

    std::list<Ponto> window_corners = {top_left, top_right, bottom_right, bottom_left};
    std::list<Ponto> entrances = {}, artificials = {};

    for (auto p = poly_p.begin(); p != poly_p.end(); p++) {
        auto next = p;
        next++;
        if(next == poly_p.end()) {
            next = poly_p.begin();
        }

        auto k = *p;
        auto l = *next;

        std::list<Ponto> line = {k,l};
        std::list<Ponto> clipped_line = clipping_line(line);

        if(clipped_line.size() == 0) {
            continue;
        }

        if(!inside_view(k) && inside_view(l)) {
            change_corners(window_corners, clipped_line.front());

            entrances.push_back(clipped_line.front());
            artificials.push_back(clipped_line.front());
            p++;
            poly_p.insert(p, clipped_line.front());
            p--;

        } else if(inside_view(k) && !inside_view(l)) {
            change_corners(window_corners, clipped_line.back());

            artificials.push_back(clipped_line.back());
            p++;
            poly_p.insert(p, clipped_line.back());
            p--;

        } else if(!inside_view(k) && !inside_view(l)) {
            change_corners(window_corners, clipped_line.front());
            change_corners(window_corners, clipped_line.back());

            entrances.push_back(clipped_line.front());

            artificials.push_back(clipped_line.front());
            artificials.push_back(clipped_line.back());

            p++;
            poly_p.insert(p, clipped_line.back());
            poly_p.insert(p, clipped_line.front());
            p--;

        }
    }

    // Verify if whole polygon is inside or outside window
    if(entrances.size() == 0) {
        if(!inside_view(poly_p.front())) {
            return clipped_poly;
        } else {
            clipped_poly.push_back(Poligono("cut", poly_p));
            return clipped_poly;
        }
    }

    auto e = entrances.front();
    std::list<Ponto> hold, visited_list;
    do {
        entrances.remove(e);
        visited_list.push_back(e);

        auto artificial_iterator = find(artificials.begin(), artificials.end(), e);

        artificial_iterator++;
        if(artificial_iterator == artificials.end()) {
            artificial_iterator = artificials.begin();
        }

        for (auto it = std::find(poly_p.begin(), poly_p.end(), e);
             *it != *artificial_iterator;
             it++) {
            if(it == poly_p.end()) {
                it = poly_p.begin();
            }
            hold.push_back(*it);
        }

        hold.push_back(*artificial_iterator);
        visited_list.push_back(*artificial_iterator);

        artificial_iterator++;
        if(artificial_iterator == artificials.end()) {
            artificial_iterator = artificials.begin();
        }

        //artificials.remove(visited_list.back());
        for (auto it = std::find(window_corners.begin(), window_corners.end(), hold.back());
             *it != *artificial_iterator;
             it++) {
            if(it == window_corners.end()) {
                it = window_corners.begin();
            }
            if(inside_list(artificials, *it) && *it != hold.back()) {
                artificial_iterator = find(artificials.begin(), artificials.end(), *it);
                break;
            }
            hold.push_back(*it);
        }
        hold.push_back(*artificial_iterator);

        visited_list.push_back(*artificial_iterator);
        //artificials.remove(*artificial_iterator);

        if(inside_list(entrances, visited_list.back())) {
            e = visited_list.back();
        } else {
            clipped_poly.push_back(Poligono("cut", hold));
            hold = {};
            if(!entrances.empty()) {
                e = entrances.front();
            }
        }
    } while(entrances.size() != 0);

    return clipped_poly;
}

void Canvas::change_corners(std::list<Ponto>& window_corners, Ponto k) {
    double xmin = -0.9;
    double ymin = -0.9;
    double xmax = 0.9;
    double ymax = 0.9;

    Ponto top_left(-0.9, 0.9);
    Ponto bottom_left(-0.9, -0.9);
    Ponto bottom_right(0.9, -0.9);
    Ponto top_right(0.9, 0.9);

    if(k.get_x() == xmin) {
        auto it = find(window_corners.begin(), window_corners.end(), bottom_left);
        auto n = *it;
        while(it != window_corners.end() && k.get_y() >= n.get_y()) {
            it++;
            n = *it;
        }
        window_corners.insert(it, k);
    }

    if(k.get_x() == xmax) {
        auto it = find(window_corners.begin(), window_corners.end(), top_right);
        auto n = *it;
        while(it != window_corners.end() && k.get_y() <= n.get_y()) {
            it++;
            n = *it;
        }
        window_corners.insert(it, k);
    }

    if(k.get_y() == ymin) {
        auto it = find(window_corners.begin(), window_corners.end(), bottom_right);
        auto n = *it;
        while(it != window_corners.end() && k.get_x() <= n.get_x()) {
            it++;
            n = *it;
        }
        window_corners.insert(it, k);
    }

    if(k.get_y() == ymax) {
        auto it = find(window_corners.begin(), window_corners.end(), top_left);
        auto n = *it;
        while(it != window_corners.end() && k.get_x() >= n.get_x()) {
            it++;
            n = *it;
        }
        window_corners.insert(it, k);
    }
}

bool Canvas::inside_view(Ponto p) {
    double xmin = -0.9;
    double ymin = -0.9;
    double xmax = 0.9;
    double ymax = 0.9;
    double x = p.get_x();
    double y = p.get_y();

    if(x < xmax && x > xmin && y < ymax && y > ymin) {
        return true;
    } else {
        return false;
    }
}

bool Canvas::inside_list(std::list<Ponto> list, Ponto p) {

    auto iterator = find(list.begin(), list.end(), p);

    if(*iterator == p) {
        return true;
    } else {
        return false;
    }

}
