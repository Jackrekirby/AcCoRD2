#pragma once
#include "json.h"

#include <array>

namespace accord::math
{
    struct Vec2b {
    public:
        union
        {
            struct
            {
                bool x, y;
            };

            std::array<bool, 2> axis;
        };

        Vec2b(bool x, bool y);

        Vec2b(bool a);

        Vec2b();

        bool All() const;

        Vec2b operator && (const Vec2b& v) const;

        bool Any() const;

        Vec2b operator || (const Vec2b& v) const;

        template<typename OStream>
        friend OStream& operator<<(OStream& os, const Vec2b& v)
        {
            return os << "[" << v.x << ", " << v.y << "]";
        }
    };

    void to_json(Json& j, const Vec2b& v);
}