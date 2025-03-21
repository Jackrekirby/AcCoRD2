// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"

#include "vec3b.h"

namespace accord
{
    Vec3b::Vec3b(bool x, bool y, bool z)
        : x(x), y(y), z(z)
    {

    }

    Vec3b::Vec3b(bool s)
        : x(s), y(s), z(s)
    {

    }

    Axis3D Vec3b::FindAxis() const
    {
        if (Sum() != 1)
        {
            LOG_CRITICAL("FindAxis() requires exactly 1 axis to be true. {}", *this);
            throw std::exception();
        }

        if (x) return Axis3D::x;
        if (y) return Axis3D::y;
        if (z) return Axis3D::z;

        LOG_CRITICAL("One axis must be true. Sum() function behaved not as intended. {}, {}", *this, Sum());
        throw std::exception();
    }

    int Vec3b::Sum() const
    {
        return (x + y + z);
    }

    bool Vec3b::All() const
    {
        return (x && y && z);
    }

    Vec3b Vec3b::operator && (const Vec3b& v) const
    {
        return { x && v.x, y && v.y, z && v.z };
    }

    bool Vec3b::Any() const
    {
        return (x || y || z);
    }

    Vec3b Vec3b::operator || (const Vec3b& v) const
    {
        return { x || v.x,  y || v.y, z || v.z };
    }

    void to_json(Json& j, const Vec3b& v)
    {
        j = { v.x, v.y, v.z };
    }

    void from_json(const Json& j, Vec3b& v) {
        j.at(0).get_to(v.x);
        j.at(1).get_to(v.y);
        j.at(2).get_to(v.z);
    }

}