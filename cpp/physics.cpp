#include "physics.h"

Body::Body() : position(Vector<int>()), velocity(Vector<int>()) {};

Body::Body(Vector<int> p, Vector<int> s) : position(p), velocity(s) {}

void Body::move()
{
    position.set_x(position.get_x() + velocity.get_x() * TIME_INTERVAL);
    position.set_y(position.get_y() + velocity.get_y() * TIME_INTERVAL);
}

axis Body::is_out_of_bounds()
{
    if (position.get_x() >= X_BOUND || position.get_x() <= 0)
        return axis::x;
    if (position.get_y() >= Y_BOUND || position.get_y() <= 0)
        return axis::y;
    return axis::none;
}

void Body::handle_wall_collision(axis a)
{
    if (a == axis::x)
    {
        velocity.set_y(-velocity.get_y());
    }
    else if (a == axis::y)
    {
        velocity.set_x(-velocity.get_x());
    }
}

Molecule::Molecule() : Body(), temperature(0) {};
Molecule::Molecule(int temp, Vector<int> p, Vector<int> s) : Body(p, s), temperature(temp) {}

// To check if particles are hitting each other, create hash map where each entry is the grid position (x,y) and in the value, is the list of particles

HashMapWindow::HashMapWindow(int num_of_particles, int particle_radius)
{
    int total_squares =
}