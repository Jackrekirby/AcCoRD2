#pragma once
#include "vec2d.h"

namespace accord::shape::basic
{
	class Box2D
	{
	public:
		Box2D(Vec2d origin, Vec2d length);

		void Move(const Vec2d& origin);

		void Resize(const Vec2d& length);

		const Vec2d& GetOrigin() const;

		const Vec2d& GetEnd() const;

		const Vec2d& GetLength() const;
		
		void ToJson(Json& j) const;

	private:
		Vec2d origin;
		Vec2d end;
		Vec2d length;
	};

	void to_json(Json& j, const Box2D& box);
}