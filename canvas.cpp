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
    // drawing subcanvas for clipping
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
//--------------------------------------------------------

    cr->set_source_rgb(0.8, 0.0, 0.0);
    for (auto i = display_file.begin(); i != display_file.end(); i++)
    {
        std::list<Poligono> to_draw_poly = {*i};

        std::list<Ponto> pontos = i->draw(this->calc_distancia(screen.get_v(), Ponto(0,0)));
        /*
        if(pontos.size() == 1) {
            // Clipping Dots
            if(!inside_view(pontos.front(),
                            top_left, bottom_right,
                            height, width)) {
                continue;
            } else {
                clipped_pontos = pontos;
            }
        } else */
        if(pontos.size() == 2) {
            // Clipping lines
            std::list<Ponto> clipped_line = clipping_line(pontos);
            if(clipped_line.size() == 0) {
                continue;
            }
            to_draw_poly.push_back(Poligono("clip", clipped_line));
        } else {
            //clipping_poly();
            to_draw_poly = clipping_poly(pontos);

            if(to_draw_poly.size() == 0) {
                continue;
            }
        }

        cr->set_line_width(i->get_brush_size());

        for(auto drawing_it = to_draw_poly.begin(); drawing_it != to_draw_poly.end(); drawing_it++) {
            pontos = drawing_it->get_pontos();
            cr->move_to(vp_transform_x(pontos.back().get_x(), width),
                        vp_transform_y(pontos.back().get_y(), height));

            for (auto pt = pontos.begin(); pt != pontos.end(); pt++)
            {
                cr->line_to(vp_transform_x(pt->get_x(), width),
                            vp_transform_y(pt->get_y(), height));
            }

            if(i->get_filled()) {
                cr->fill();
            }
            cr->stroke();
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
std::list<Ponto> Canvas::clipping_line(std::list<Ponto> line_p) {

    std::list<Ponto> clipped_dots;

    bool front_is_inside = inside_view(line_p.front());
    bool back_is_inside = inside_view(line_p.back());

    if(front_is_inside && back_is_inside) {
        return line_p;
    }

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

    if ((p1 == 0 && q1 < 0) || (p3 == 0 && q3 < 0)) {
        // line parallel to window
        return clipped_dots;
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
        // linha fora do canvas
        return clipped_dots;
    }

    if(!front_is_inside) {
    //double new_x_out_in = line_p.front().get_x() + max*p2;
    //double new_y_out_in = line_p.front().get_y() + max*p4;
        clipped_dots.push_back(Ponto(
                               line_p.front().get_x() + max*p2,
                               line_p.front().get_y() + max*p4));
    } else {
        clipped_dots.push_back(line_p.front());
    }

    if(!back_is_inside) {
    //double new_x_in_out = line_p.back().get_x() + max*p2;
    //double new_y_in_out = line_p.back().get_y() + max*p4;
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
    std::list<Poligono> clipped_poly = {};

    Ponto top_left(-0.9, 0.9);
    Ponto bottom_left(-0.9, -0.9);
    Ponto bottom_right(0.9, -0.9);
    Ponto top_right(0.9, 0.9);

    std::list<Ponto> window_corners = {top_left, top_right, bottom_right, bottom_left};
    std::list<Ponto> entrances = {}, artificials = {};

    bool all_inside = true, none_inside = true;

    for (auto p = poly_p.begin(); p != poly_p.end(); p++) {
        if(inside_view(*p)) {
            none_inside = false;
        } else {
            all_inside = false;
        }

        if(!none_inside && !all_inside) {
            break;
        }
    }

    if(all_inside) {
        clipped_poly.push_back(Poligono("cut", poly_p));
        return clipped_poly;
    }

    if(none_inside) {
        return clipped_poly;
    }

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

        if(clipped_line.size() == 0) {// || line == clipped_line) {
            continue;
        }

        if(!inside_view(k) && inside_view(l)) {
            change_corners(window_corners, clipped_line.front());

            entrances.push_back(clipped_line.front());
            artificials.push_back(clipped_line.front());
            poly_p.insert(next, clipped_line.front());
            p++;

        } else if(inside_view(k) && !inside_view(l)) {
            change_corners(window_corners, clipped_line.back());

            artificials.push_back(clipped_line.back());
            poly_p.insert(next, clipped_line.back());
            p++;

        } else if(!inside_view(k) && !inside_view(l)) {
            change_corners(window_corners, clipped_line.front());
            change_corners(window_corners, clipped_line.back());

            entrances.push_back(clipped_line.front());

            artificials.push_back(clipped_line.front());
            artificials.push_back(clipped_line.back());

            poly_p.insert(next, clipped_line.back());
            poly_p.insert(next, clipped_line.front());

            p++;
            p++;
        }
    }

//    for (auto e = entrances.begin(); e != entrances.end(); e++) {

    auto e = entrances.front();

    do {
        entrances.remove(e);
        std::list<Ponto> hold = {};

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

        auto visited = *artificial_iterator;

        artificial_iterator++;
        if(artificial_iterator == artificials.end()) {
            artificial_iterator = artificials.begin();
        }

        artificials.remove(visited);

        for (auto it = std::find(window_corners.begin(), window_corners.end(), hold.back());
             *it != *artificial_iterator;
             it++) {
            if(it == window_corners.end()) {
                it = window_corners.begin();
            }
            hold.push_back(*it);
        }
        hold.push_back(*artificial_iterator);

        visited = *artificial_iterator;
        artificials.remove(visited);

        auto visited_entrance = find(entrances.begin(), entrances.end(), visited);
        if(artificial_iterator != visited_entrance) {
            clipped_poly.push_back(Poligono("cut", hold));
        } else {
            e = visited;
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
        }
        window_corners.insert(it, k);
    }

    if(k.get_x() == xmax) {
        auto it = find(window_corners.begin(), window_corners.end(), top_right);
        auto n = *it;
        while(it != window_corners.end() && k.get_y() <= n.get_y()) {
            it++;
        }
        window_corners.insert(it, k);
    }

    if(k.get_y() == ymin) {
        auto it = find(window_corners.begin(), window_corners.end(), bottom_right);
        auto n = *it;
        while(it != window_corners.end() && k.get_x() <= n.get_x()) {
            it++;
        }
        window_corners.insert(it, k);
    }

    if(k.get_y() == ymax) {
        auto it = find(window_corners.begin(), window_corners.end(), top_left);
        auto n = *it;
        while(it != window_corners.end() && k.get_x() >= n.get_x()) {
            it++;
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

Ponto Canvas::intersect2d(std::list<Ponto>& window_corners, Ponto k, Ponto l) {
    double det, s, inter_x, inter_y;
    double xmin = -0.9;
    double ymin = -0.9;
    double xmax = 0.9;
    double ymax = 0.9;

    for (auto i = window_corners.begin(); i != window_corners.end(); i++) {
        auto j = i;
        j++;
        if(j == window_corners.end()) {
            auto j = window_corners.begin();
        }

        auto n = *i;
        auto m = *j;

        if(n.get_x() != xmin && n.get_x() != xmax &&
           n.get_y() != ymin && n.get_y() != ymax) {
            continue;
        }

        det = (n.get_x() - m.get_x()) * (l.get_y() - k.get_y())
            - (n.get_y() - m.get_y()) * (l.get_x() - k.get_x());

        if (det != 0.0) {
            s = ((n.get_x() - m.get_x()) * (m.get_y() - k.get_y())
               - (n.get_y() - m.get_y()) * (m.get_x() - k.get_x()))
               / det ;

            auto inter_x = k.get_x() + (l.get_x() - k.get_x()) * s;
            auto inter_y = k.get_y() + (l.get_y() - k.get_y()) * s;

            Ponto intersect(inter_x, inter_y);

            if((inter_x == xmin || inter_x == xmax) &&
               (inter_y >= ymin && inter_y <= ymax)) {

                    window_corners.insert(j, intersect);
                    return intersect;

            } else if((inter_y == ymin || inter_y == ymax) &&
                      (inter_x >= xmin && inter_x <= xmax)) {

                    window_corners.insert(j, intersect);
                    return intersect;

            }
        }
    }


    return Ponto(0,0);
}
