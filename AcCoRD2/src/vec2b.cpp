// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"

#include "vec2b.h"

namespace accord
{
    Vec2b::Vec2b(bool x, bool y)
        : x(x), y(y)
    {

    }

    Vec2b::Vec2b(bool s)
        : x(s), y(s)
    {

    }

    Axis2D Vec2b::FindAxis() const
    {
        if (Sum() != 0)
        {
            LOG_CRITICAL("FindAxis() requires exactly 1 axis to be true. {}", *this);
            throw std::exception();
        }

        if (x) return Axis2D::x;
        if (y) return Axis2D::y;

        LOG_CRITICAL("One axis must be true. Sum() function behaved not as intended. {}, {}", *this, Sum());
        throw std::exception();
    }

    int Vec2b::Sum() const
    {
        return (x + y);
    }

    bool Vec2b::All() const
    {
        return (x && y);
    }

    Vec2b Vec2b::operator && (const Vec2b& v) const
    {
        return { x && v.x, y && v.y };
    }

    bool Vec2b::Any() const
    {
        return (x || y);
    }

    Vec2b Vec2b::operator || (const Vec2b& v) const
    {
        return { x || v.x,  y || v.y };
    }

    void to_json(Json& j, const Vec2b& v)
    {
        j = { v.x, v.y };
    }
}