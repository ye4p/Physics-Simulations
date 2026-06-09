#include "physics.h"
#include <iostream>
#include <vector>

float dt = .016;

struct World
{
    std::vector<Vector<float>> positions;
    void sync()
    {
        positions.resize(physics.vec.size());
        for (int i = 0; i < physics.vec.size() - 1; i++)
        {
            positions[i] = Vector((float)physics.vec[i].position.x,
                                  (float)physics.vec[i].position.y);
        }
    }
};

struct PhysicsEngine
{
    Grid grid = Grid(10);
    std::vector<Molecule> vec;
    void add_one_particle()
    {
        Molecule m = Molecule(Vector(100, 100), Vector(50, 50), 1, 1);
        vec.push_back(m);
    }
    void add_n_particles(int n)
    {
        for (int i = 0; i < n; i++)
        {
        }
    }
    void arrange_bodies_randomly()
    {
    }
};

std::vector<Vector<float>> get_positions()
{
    return world.positions;
}

static PhysicsEngine physics;
static World world;

int init()
{
    physics.add_one_particle();
    world.sync();
    return dt;
}

void update()
{
    //  Update actual physics of objects
    for (Molecule &m : physics.vec)
    {
        m.position.x += m.velocity.x * dt;
        m.position.y += m.velocity.y * dt;
    }

    //  Update data that is readable by rust
    world.sync();
}