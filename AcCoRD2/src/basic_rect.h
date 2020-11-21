#pragma once
#include "vec2d.h"

namespace accord::shape::basic
{
	class Rect
	{
	public:
		Rect(Vec2d origin, Vec2d length);

		void Move(const Vec2d& origin);

		void Resize(const Vec2d& length);

		const Vec2d& GetOrigin() const;

		const Vec2d& GetEnd() const;

		const Vec2d& GetLength() const;

		Vec2d CalculateCentre() const;

		double CalculateArea() const;

		bool IsWithinBorder(const Vec2d& position) const;

		bool IsWithinOrOnBorder(const Vec2d& position) const;

		bool IsOnBorder(const Vec2d& position) const;
		
		void ToJson(Json& j) const;

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Rect& rect)
		{
			return os << fmt::format("origin = {}, length = {}, end = {}",
				rect.GetOrigin(), rect.GetLength(), rect.GetEnd());
		}

	private:
		Vec2d origin;
		Vec2d end;
		Vec2d length;
	};

	void to_json(Json& j, const Rect& rect);
}