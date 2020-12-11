#include "pch.h"
#include "relation_cylinder.h"
#include "relation_box.h"
#include "relation_sphere.h"

namespace accord::shape::relation
{
	Cylinder::Cylinder(Vec3d base_centre, double radius, double length, Axis3D axis)
		: basic::Cylinder(base_centre, radius, length, axis),
		base_face({ GetBase(), axis }, { GetCircleCentre(), radius }),
		top_face({ GetTop(), axis }, { GetCircleCentre(), radius })
	{

	}

	bool Cylinder::IsOverlapping(const Shape3D& other) const
	{
		return (
			FlattenInAxis(Axis3D::x)->IsOverlapping(*other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y)->IsOverlapping(*other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z)->IsOverlapping(*other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnveloping(const Shape3D& other) const
	{
		return (
			FlattenInAxis(Axis3D::x)->IsEnveloping(*other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y)->IsEnveloping(*other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z)->IsEnveloping(*other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsEnvelopedBy(const Shape3D& other) const
	{
		return (
			FlattenInAxis(Axis3D::x)->IsEnvelopedBy(*other.FlattenInAxis(Axis3D::x)) &&
			FlattenInAxis(Axis3D::y)->IsEnvelopedBy(*other.FlattenInAxis(Axis3D::y)) &&
			FlattenInAxis(Axis3D::z)->IsEnvelopedBy(*other.FlattenInAxis(Axis3D::z))
			);
	}

	bool Cylinder::IsOverlapping(const Box& other) const
	{
		return IsOverlapping(static_cast<const Shape3D&>(other));
	}

	bool Cylinder::IsEnveloping(const Box& other) const
	{
		return IsEnveloping(static_cast<const Shape3D&>(other));
	}

	bool Cylinder::IsEnvelopedBy(const Box& other) const
	{
		return IsEnvelopedBy(static_cast<const Shape3D&>(other));
	}

	bool Cylinder::IsOverlapping(const Sphere& other) const
	{
		return IsOverlapping(static_cast<const Shape3D&>(other));
	}

	bool Cylinder::IsEnveloping(const Sphere& other) const
	{
		return IsEnveloping(static_cast<const Shape3D&>(other));
	}

	bool Cylinder::IsEnvelopedBy(const Sphere& other) const
	{
		return IsOverlapping(static_cast<const Shape3D&>(other));
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

	std::unique_ptr<SurfaceShape> Cylinder::FlattenInAxis(Axis3D axis) const
	{
		if (axis == GetAxis())
		{
			return std::make_unique<Circle>(GetCircleCentre(), GetRadius());
		}
		else
		{
			return GenerateBoundingBox().FlattenInAxis(axis);
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
