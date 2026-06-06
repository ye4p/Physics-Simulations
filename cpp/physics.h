#pragma once
#include <type_traits>
#include <cmath>

constexpr int TIME_INTERVAL = 1;
constexpr int X_BOUND = 100;
constexpr int Y_BOUND = 100;

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
private:
    T x;
    T y;

public:
    Vector();
    Vector(T x, T y) : x(x), y(y) {}
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

    T get_length()
    {
        return std::sqrt(x * x + y * y);
    }
};

class Body
{
private:
    Vector<int> position;
    Vector<int> velocity; // per second
    int mass;

public:
    Body();
    Body(Vector<int> p, Vector<int> s);
    void move();

    axis is_out_of_bounds();

    void handle_wall_collision(axis a);
};

class Molecule : public Body
{
private:
    int temperature; // In Celsius
public:
    Molecule();
    Molecule(int temp, Vector<int> p, Vector<int> s);
};

class HashMapWindow
{

private:
public:
    HashMapWindow(int num_of_particles, int particle_radius);
};