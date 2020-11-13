#pragma once
#include "json.h"
#include <array>

namespace accord::math
{
    struct Vec3b {
    public:
        union
        {
            struct
            {
                bool x, y, z;
            };

            std::array<bool, 3> axis;
        };

        Vec3b(bool x, bool y, bool z);

        Vec3b(bool a);

        Vec3b();

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