#include "vec2b.h"

namespace accord::math
{
    Vec2b::Vec2b(bool x, bool y)
        : x(x), y(y)
    {

    }

    Vec2b::Vec2b(bool a)
        : x(a), y(a)
    {

    }

    Vec2b::Vec2b()
        : x(false), y(false)
    {
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