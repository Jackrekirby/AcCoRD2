#include "vec3b.h"

namespace accord::math
{
    Vec3b::Vec3b(bool x, bool y, bool z)
        : x(x), y(y), z(z)
    {

    }

    Vec3b::Vec3b(bool a)
        : x(a), y(a), z(a)
    {

    }

    Vec3b::Vec3b()
        : x(false), y(false), z(false)
    {

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

}