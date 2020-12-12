#include "pch.h"
#include "relation_cylinder.h"
#include "relation_box.h"
#include "relation_sphere.h"
#include "vec1d.h"

namespace accord::shape::relation
{
	Cylinder::Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis)
		: basic::Cylinder(base_centre, radius, length, axis),
		base_face({ GetBase(), axis }, { GetCircleCentre(), radius }),
		top_face({ GetTop(), axis }, { GetCircleCentre(), radius }),
		projected_face({ GetCircleCentre(), radius }),
		projected_side_x(GenerateBoundingBox().FlattenInAxis(GetOtherAxes(GetAxis()).at(0))),
		projected_side_y(GenerateBoundingBox().FlattenInAxis(GetOtherAxes(GetAxis()).at(1)))
	{

	}

	Vec3d Cylinder::CalculateNearestPoint(const Vec3d& position) const
	{
		double longitudinal = Vec1d::Max(GetBase(), Vec1d::Min(position.GetAxis(GetAxis()), GetTop()));

		Vec2d transverse = Vec2d::Max(GetBaseCentre().GetPlane(GetAxis()) - GetRadius(),
			Vec2d::Min(position.GetPlane(GetAxis()), GetBaseCentre().GetPlane(GetAxis()) + GetRadius()));

		if (transverse.Size2() < GetRadius2())
		{
			return { longitudinal, transverse, GetAxis() };
		}
		else
		{
			return { longitudinal,
			GetCircleCentre() + (transverse - GetCircleCentre()).Normalise() * GetRadius(),
			GetAxis()
			};
		}

		
	}

	Vec3d Cylinder::CalculateFurthestPoint(const Vec3d& position) const
	{
		// find if the base or top of cylinder is furthest away from the position
		double longitudinal = GetBase() + GetLength() * 
			(Vec1d::Square(position.GetAxis(GetAxis()) - GetBase()) <
					Vec1d::Square(position.GetAxis(GetAxis()) - GetTop()));

		Vec2d transverse = Vec2d::Max(GetBaseCentre().GetPlane(GetAxis()) - GetRadius(),
			Vec2d::Min(position.GetPlane(GetAxis()), GetBaseCentre().GetPlane(GetAxis()) + GetRadius()));

		if (transverse.Size2() == 0) transverse.x = GetRadius();

		return { longitudinal,
			GetCircleCentre() - (transverse - GetCircleCentre()).Normalise() * GetRadius(),
			GetAxis()
		};
	}

	bool Cylinder::IsOverlapping(const Shape3D& other) const
	{
		return other.IsOverlapping(*this);
	}

	bool Cylinder::IsEnveloping(const Shape3D& other) const
	{
		return other.IsEnvelopedBy(*this);
	}

	bool Cylinder::IsEnvelopedBy(const Shape3D& other) const
	{
		return other.IsEnveloping(*this);
	}

	bool Cylinder::IsOverlapping(const Cylinder& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsOverlapping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsOverlapping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsOverlapping(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnveloping(const Cylinder& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnveloping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnveloping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnveloping(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnvelopedBy(const Cylinder& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnvelopedBy(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnvelopedBy(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnvelopedBy(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsOverlapping(const Box& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsOverlapping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsOverlapping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsOverlapping(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnveloping(const Box& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnveloping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnveloping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnveloping(other.FlattenInAxis(Axis3D::z))
		);
	}

	bool Cylinder::IsEnvelopedBy(const Box& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnvelopedBy(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnvelopedBy(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnvelopedBy(other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsOverlapping(const Sphere& other) const
	{
		return other.IsWithinOrOnBorder(CalculateNearestPoint(other.GetCentre()));
	}

	bool Cylinder::IsEnveloping(const Sphere& other) const
	{
		return (
			FlattenInAxis(Axis3D::x).IsEnveloping(other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y).IsEnveloping(other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z).IsEnveloping(other.FlattenInAxis(Axis3D::z))
		);
	}

	bool Cylinder::IsEnvelopedBy(const Sphere& other) const
	{
		return other.IsWithinOrOnBorder(CalculateFurthestPoint(other.GetCentre()));
	}

	const SurfaceShape& Cylinder::IsPartiallyNeighbouring(const Box& other) const
	{
		switch (GetAxis())
		{
		case Axis3D::x:
			if (base_face.IsPartiallyNeighbouring(other.GetFace(Face::nx)))
			{
				return other.GetFace(Face::nx).GetShape();
			}
			if (top_face.IsPartiallyNeighbouring(other.GetFace(Face::px)))
			{
				return other.GetFace(Face::px).GetShape();
			}
		case Axis3D::y:
			if (base_face.IsPartiallyNeighbouring(other.GetFace(Face::ny)))
			{
				return other.GetFace(Face::ny).GetShape();
			}
			if (top_face.IsPartiallyNeighbouring(other.GetFace(Face::py)))
			{
				return other.GetFace(Face::py).GetShape();
			}
		case Axis3D::z:
			if (base_face.IsPartiallyNeighbouring(other.GetFace(Face::nz)))
			{
				return other.GetFace(Face::nz).GetShape();
			}
			if (top_face.IsPartiallyNeighbouring(other.GetFace(Face::pz)))
			{
				return other.GetFace(Face::pz).GetShape();
			}
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	const SurfaceShape& Cylinder::IsFullyNeighbouring(const Box& other) const
	{
		switch (GetAxis())
		{
		case Axis3D::x:
			if (base_face.IsFullyNeighbouring(other.GetFace(Face::nx)))
			{
				return other.GetFace(Face::nx).GetShape();
			}
			if (top_face.IsFullyNeighbouring(other.GetFace(Face::px)))
			{
				return other.GetFace(Face::px).GetShape();
			}
		case Axis3D::y:
			if (base_face.IsFullyNeighbouring(other.GetFace(Face::ny)))
			{
				return other.GetFace(Face::ny).GetShape();
			}
			if (top_face.IsFullyNeighbouring(other.GetFace(Face::py)))
			{
				return other.GetFace(Face::py).GetShape();
			}
		case Axis3D::z:
			if (base_face.IsFullyNeighbouring(other.GetFace(Face::nz)))
			{
				return other.GetFace(Face::nz).GetShape();
			}
			if (top_face.IsFullyNeighbouring(other.GetFace(Face::pz)))
			{
				return other.GetFace(Face::pz).GetShape();
			}
		}
		LOG_CRITICAL("Unknown Axis3D type");
		throw std::exception();
	}

	const SurfaceShape& Cylinder::IsPartiallyNeighbouring(const Cylinder& other) const
	{
		if (base_face.IsPartiallyNeighbouring(other.top_face)) return other.top_face.GetShape();
		if (top_face.IsPartiallyNeighbouring(other.top_face)) return other.base_face.GetShape();
		return other.base_face.GetShape(); // WRONG
	}

	// not required
	const SurfaceShape& Cylinder::IsFullyNeighbouring(const Cylinder& other) const
	{
		if (base_face.IsFullyNeighbouring(other.top_face)) return other.top_face.GetShape();
		if (top_face.IsFullyNeighbouring(other.top_face)) return other.base_face.GetShape();
		return other.base_face.GetShape(); // WRONG
	}

	const SurfaceShape& Cylinder::FlattenInAxis(const Axis3D& axis) const
	{
		if (axis == GetAxis())
		{
			return projected_face;
		}
		else
		{
			std::array<Axis3D, 2> axes = GetOtherAxes(axis);
			if (axis == axes.at(0))
			{
				return projected_side_x;
			}
			else // if (axis == axes.at(1))
			{
				return projected_side_y;
			}
		}
	}

	Box Cylinder::GenerateBoundingBox() const
	{
		Vec3d origin(GetBase(), GetCircleCentre() - GetRadius(), GetAxis());
		Vec3d length(GetLength(), { 2 * GetRadius(), 2 * GetRadius() }, GetAxis());
		return { origin, length };
	}

	void Cylinder::ToJson(Json& j) const
	{
		j = static_cast<basic::Cylinder>(*this);
	}

	const Cylinder& Cylinder::GetShape() const
	{
		return *this;
	}

	void to_json(Json& j, const Cylinder& shape)
	{
		shape.ToJson(j);
	}
}
