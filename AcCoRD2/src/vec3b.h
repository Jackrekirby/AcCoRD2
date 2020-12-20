#pragma once
#include "pch.h"
#include "axis_3d.h"

namespace accord
{
    struct Vec3b {
    public:
        union
        {
            struct
            {
                bool x, y, z;
            };

            std::enum_array<Axis3D, bool, 3> axis;
        };

        Vec3b(bool x, bool y, bool z);

        explicit Vec3b(bool s);

        Vec3b() = default;

        // May want GetAxis() GetPlane

        // returns the axis which is true. Requires exactly 1 axis to be true or will throw exception;
        Axis3D FindAxis() const;

        int Sum() const;

        bool All() const;

        Vec3b operator && (const Vec3b& v) const;

        bool Any() const;

        Vec3b operator || (const Vec3b& v) const;

        template<typename OStream>
        friend OStream& operator<<(OStream& os, const Vec3b& v)
        {
            return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        }
    };

    void to_json(Json& j, const Vec3b& v);

}