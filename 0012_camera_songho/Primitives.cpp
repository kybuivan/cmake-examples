///////////////////////////////////////////////////////////////////////////////
// Primitives.cpp
// ==============
// OpenGL primitives:
// Plane
// Cube
// Disk
// Sphere
// Torus
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2011-12-10
// UPDATED: 2011-12-10
///////////////////////////////////////////////////////////////////////////////

#include "Primitives.h"
#include <iostream>

using namespace Gil;



///////////////////////////////////////////////////////////////////////////////
// Plane
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Sphere
///////////////////////////////////////////////////////////////////////////////
Sphere::Sphere() : radius(1), sliceCount(10), stackCount(10)
{
    buildSphere();
}
Sphere::Sphere(float r, int sl, int st) : radius(r), sliceCount(sl), stackCount(st)
{
    if(radius < 0.0f)  radius = 0;
    if(sliceCount < 2) sliceCount = 2;
    if(stackCount < 2) stackCount = 2;
    buildSphere();
}
Sphere::~Sphere()
{
}

void Sphere::printSelf() const
{
    std::cout << "===== Sphere =====\n"
              << "   Position: " << position << "\n"
              << "   Rotation: " << rotation << "\n"
              << "      Color: " << color << "\n"
              << "     Radius: " << radius << "\n"
              << "Slice Count: " << sliceCount << "\n"
              << "Stack Count: " << stackCount << "\n"
              << std::endl;
}

void Sphere::set(float r, int sl, int st)
{
    radius = r;
    sliceCount = sl;
    stackCount = st;
    if(radius < 0.0f)  radius = 0;
    if(sliceCount < 2) sliceCount = 2;
    if(stackCount < 2) stackCount = 2;
    buildSphere();
}
void Sphere::setRadius(float r)
{
    radius = r;
    if(radius < 0.0f) radius = 0;
    buildSphere();
}
void Sphere::setSliceCount(int s)
{
    sliceCount = s;
    if(sliceCount < 2) sliceCount = 2;
    buildSphere();
}
void Sphere::setStackCount(int s)
{
    stackCount = s;
    if(stackCount < 2) stackCount = 2;
    buildSphere();
}

void Sphere::buildSphere()
{
    if(radius <= 0.0f) return;

    const float PI = 3.141592f;
    const float PI2 = PI * 2.0f;
    const float PI_HALF = PI * 0.5f;

    vertices.clear();
    normals.clear();
    indices.clear();

    float x, y, z;               // parameters
    float a = 0;                // angle for slices [0 ~ 2pi]
    float b = -PI_HALF;         // angle for stack  [-pi/2 ~ pi/2]
    float deltaA = PI2 / (sliceCount - 1);
    float deltaB = PI / (stackCount - 1);
    for(int i = 0; i <= stackCount; ++i)
    {
        b = PI / sliceCount * i - PI_HALF;
        for(int j = 0; j <= sliceCount; ++j)
        {
            a = j * PI2 / (sliceCount - 1);
        }
    }

}
