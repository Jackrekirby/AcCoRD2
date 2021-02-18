#pragma once
#include "vec2d.h"
#include "basic_shape.h"

namespace accord::shape::basic
{
	class Rect : public Shape
	{
	public:
		// construct a rectangle from its negative most vertex and its length along each dimension
		Rect(Vec2d origin, Vec2d length);

		// move the box relative to its origin
		void Move(const Vec2d& origin);

		// chaneg the length of the box along each dimension
		void Resize(const Vec2d& length);

		const Vec2d& GetOrigin() const;

		// returns origin + length
		const Vec2d& GetEnd() const;

		const Vec2d& GetLength() const;

		// returns origin + 0.5 * length
		Vec2d CalculateCentre() const;

		double CalculateArea() const;

		// returns true if a position is inside the surface of the rectangle
		bool IsWithinBorder(const Vec2d& position) const;

		// returns true if a position is inside on on the surface of the rectangle
		bool IsWithinOrOnBorder(const Vec2d& position) const;

		// returns true if a position lies exaclty on the surface of the rectangle
		bool IsOnBorder(const Vec2d& position) const;
		
		// converts rectangle data to json
		void ToJson(Json& j) const;

		// logs rectangle data to output stream
		template<typename OStream>
		friend OStream& operator<<(OStream& os, const Rect& rect)
		{
			return os << fmt::format("origin = {}, length = {}, end = {}",
				rect.GetOrigin(), rect.GetLength(), rect.GetEnd());
		}

	private:
		Vec2d origin;
		Vec2d end; // origin + length
		Vec2d length;
	};

	// converts rectangle data to json
	void to_json(Json& j, const Rect& rect);
}