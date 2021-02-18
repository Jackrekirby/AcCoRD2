#pragma once
#include "pch.h"
#include "axis_3d.h"

namespace accord
{
    struct Vec3b {
    public:
        union
        {
            // vector can be access using x, y, z dimesions or as an array
            struct
            {
                bool x, y, z;
            };

            // must access array by enum. see enum_array
            std::enum_array<Axis3D, bool, 3> axis;
        };

        Vec3b(bool x, bool y, bool z);

        explicit Vec3b(bool s);

        Vec3b() = default;

        // returns the axis which is true. Requires exactly 1 axis to be true or will throw exception;
        Axis3D FindAxis() const;

        // the number of true dimensions
        int Sum() const;

        // returns true if all dimensions are true
        bool All() const;

        // returns true per dimension is both 'this' AND vector v are true for each dimension
        Vec3b operator && (const Vec3b& v) const;

        // returns true if any of the dimensions are true
        bool Any() const;

        // returns true per dimension is both 'this' AND/OR vector v are true for each dimension
        Vec3b operator || (const Vec3b& v) const;

        // log vector to output stream
        template<typename OStream>
        friend OStream& operator<<(OStream& os, const Vec3b& v)
        {
            return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        }
    };

    // convert vector data to json
    void to_json(Json& j, const Vec3b& v);

    // create a vector from json data
    void from_json(const Json& j, Vec3b& v);
}