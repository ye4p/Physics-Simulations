#pragma once
#include <type_traits>
#include <cmath>
#include <array>
#include <memory>
#include <compare>

constexpr int TIME_INTERVAL = 1;
constexpr int X_BOUND = 1280;
constexpr int Y_BOUND = 720;

enum class axis
{
    none,
    x,
    y
};

// template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
template <typename T>
class Vector
{
public:
    T x;
    T y;

    Vector() : x(0), y(0) {};
    Vector(T x, T y) : x(x), y(y) {}

    operator==(const Vector<T> &other) const
    {
        return x == other.x && y == other.y;
    }
    operator!=(const Vector<T> &other) const
    {
        return x != other.x || y != other.y;
    }

    void set_x(T x_new)
    {
        x = x_new;
    }
    void set_y(T y_new)
    {
        y = y_new;
    }
    T get_x()
    {
        return x;
    }
    T get_y()
    {
        return y;
    }
    Vector operator+(const Vector &other)
    {
        return Vector(x + other.x, y + other.y);
    }
    Vector operator-(const Vector &other)
    {
        return Vector(x - other.x, y + other.y);
    }
    Vector operator*(const int factor)
    {
        return Vector(factor * x, factor * y);
    }

    T get_length() const
    {
        return std::sqrt(x * x + y * y);
    }
};

class ListNode
{
public:
    ListNode *next;
    Molecule m;
    ListNode() : next(nullptr), m(Molecule()) {};
    ListNode(Molecule m, ListNode *next = nullptr) : next(next), m(m) {};
};

class Body
{
public:
    Vector<int> position;
    Vector<int> velocity; // per second
    int mass;
    int radius = 10;

    Body();
    Body(Vector<int> p, Vector<int> s, int mass);
    void move();

    float distance_between_centers(const Body &other);
    bool is_intersection(const Body &other);
    Vector<int> calc_collision_point(const Body &other);
    axis is_out_of_bounds();
    void handle_wall_collision(axis a);
    Vector<int> get_unit_direction_vector(const Body &other);
};

class Molecule : public Body
{
private:
    int temperature; // In Celsius
public:
    Molecule();
    Molecule(Vector<int> p, Vector<int> s, int mass, int temp);

    bool operator==(const Molecule &other) const;
    bool operator!=(const Molecule &other) const;
};

class Grid
{

private:
    int x_squares;
    int y_squares;
    std::unique_ptr<ListNode *[]> arr; // Holds pointers to list nodes
    size_t arr_size;

public:
    Grid(int particle_radius);

    void insert(Molecule m);
    void remove(Molecule m);
    void move(Molecule &m, Vector<int> new_pos);
    Molecule &find(Vector<int> pos); // Finds if there are more molecules in the current grid square
};