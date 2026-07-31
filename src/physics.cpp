#include "../include/physics.h"
#include <stdexcept>
#include <vector>
Body::Body() : position(Vector<int>()), velocity(Vector<int>()) {};

Body::Body(Vector<int> p, Vector<int> s, int mass) : position(p), velocity(s), mass(mass) {}

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

float Body::distance_between_centers(const Body &other)
{
    return std::sqrt((position.x - other.position.x) * (position.x - other.position.x) + (position.y - other.position.y) * (position.y - other.position.y));
}

bool Body::is_intersection(const Body &other)
{
    return (position.get_length() + other.position.get_length()) > distance_between_centers(other);
}

Vector<int> Body::calc_collision_point(const Body &other)
{
    // int max_x = std::max(position.x, other.position.x);
    // int min_x = std::min(position.x, other.position.x);
    // int max_y = std::max(position.y, other.position.y);
    // int min_y = std::min(position.y, other.position.y); Prob only need if I will have negative coordinates, which I don't at the moment
    return Vector(std::abs(position.x - other.position.x), std::abs(position.y - other.position.y));
}

Vector<int> Body::get_unit_direction_vector(const Body &other)
{
    return Vector((position.x - other.position.x) / (int)distance_between_centers(other), (position.y - other.position.y) / (int)distance_between_centers(other));
}

Molecule::Molecule() : Body(), temperature(0) {};
Molecule::Molecule(Vector<int> p, Vector<int> s, int mass, int temp) : Body(p, s, mass), temperature(temp) {}
bool Molecule::operator==(const Molecule &other) const
{
    return other.position == position;
}

bool Molecule::operator!=(const Molecule &other) const
{
    return other.position != position;
}

//
//   HASH MAP
//

// To check if particles are hitting each other, create hash map where each entry is the grid position (x,y) and in the value, is the list of particles
Grid::Grid(int particle_radius)
{
    int x_squares = X_BOUND / (particle_radius * 6);
    int y_squares = Y_BOUND / (particle_radius * 6);
    arr_size = x_squares * y_squares;
    arr = std::make_unique<ListNode *[]>(arr_size);
}

void Grid::insert(Molecule m)
{
    int x_sq = m.position.x % x_squares;
    int y_sq = m.position.y % y_squares;

    int sq = x_sq + y_sq * x_squares;
    if (!arr[sq])
    {
        arr[sq] = new ListNode(m);
    }
    else
    {
        ListNode *ptr = arr[sq]->next;
        while (!ptr->next)
        {
            ptr = ptr->next;
        }
        ptr->next = new ListNode(m);
    }
}

void Grid::remove(Molecule m)
{
    int x_sq = m.position.x % x_squares;
    int y_sq = m.position.y % y_squares;

    int sq = x_sq + y_sq * x_squares;

    if (!arr[sq])
    {
        throw std::runtime_error("Molecule was not found");
    }
    else
    {
        ListNode *ptr = arr[sq]->next;
        while (m != ptr->m)
        {
            ptr = ptr->next;
        }

        ListNode *next_ptr = ptr->next;
        if (!next_ptr->next)
        {
            ptr->next = nullptr;
        }
        else
        {
            ptr->next = next_ptr->next;
        }
    }
}

void Grid::move(Molecule &m, Vector<int> new_pos)
{
    remove(m);
    m.position = new_pos;
    insert(m);
}

Molecule &Grid::find(Vector<int> pos)
{
    int x_sq = pos.x % x_squares;
    int y_sq = pos.y % y_squares;

    int sq = x_sq + y_sq * x_squares;

    if (!arr[sq])
    {
        throw std::runtime_error("Molecule was not found");
    }
    else
    {
        return arr[sq]->m;
    }
}
