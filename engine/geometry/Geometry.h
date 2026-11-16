#pragma once

#include <glad/glad.h>

class Geometry
{
public:
    virtual ~Geometry() = default;

    virtual void Bind() const = 0;
    virtual GLsizei GetIndexCount() const = 0;
};