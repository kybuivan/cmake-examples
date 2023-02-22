///////////////////////////////////////////////////////////////////////////////
// Primitives.h
// ============
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

#ifndef GIL_PRIMITIVE_H
#define GIL_PRIMITIVE_H

#include <vector>
#include "Vectors.h"

namespace Gil
{

///////////////////////////////////////////////////////////////////////////////
// base class of all primitive classes
class Primitive
{
public:
    Primitive() {}
    virtual ~Primitive() {}

    virtual void printSelf() const = 0;

    void setPosition(const Vector3& p)  { position = p; }
    void setRotation(const Vector3& r)  { rotation = r; }
    void setColor(const Vector4& c)     { color = c; }

    const Vector3& getPosition() const  { return position; }
    const Vector3& getRotation() const  { return rotation; }
    const Vector4& getColor() const     { return color; }

protected:
    Vector3 position;
    Vector3 rotation;
    Vector4 color;

private:

};



///////////////////////////////////////////////////////////////////////////////
// plane on xz-plane
//  width: length on x-axis
// height: length on z-axis
// sliceCount: number of segments on each side
class Plane : public Primitive
{
public:
    Plane() : width(1), height(1) {}
    Plane(float w, float h) : width(w), height(h) {}
    virtual ~Plane();

protected:
    float width;
    float height;
private:

};



///////////////////////////////////////////////////////////////////////////////
// sphere
// radius: > 0
// sliceCount: >= 2
// stackCount: >= 2
class Sphere : public Primitive
{
public:
    Sphere();
    Sphere(float r, int sl, int st);
    virtual ~Sphere();

    void printSelf() const;

    void set(float r, int slices, int stacks);
    void setRadius(float r);
    void setSliceCount(int slices);
    void setStackCount(int stacks);

    float getRadius() const         { return radius; }
    int   getSliceCount() const     { return sliceCount; }
    int   getStackCount() const     { return stackCount; }

    int getVertexCount() const      { return (int)vertices.size(); }
    int getNormalCount() const      { return (int)normals.size(); }
    int getIndexCount() const       { return (int)indices.size(); }

    const float* getVertices() const        { return &vertices[0]; }
    const float* getNormals() const         { return &normals[0]; }
    const unsigned int* getIndices() const  { return &indices[0]; }

protected:
    float radius;
    int   sliceCount;
    int   stackCount;

private:
    // member functions
    void buildSphere();

    // member variables
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
};
}

#endif
