#pragma once
#include "pch.h"

namespace accord::shape
{
	enum class Face : size_t
	{ // negative and positive direction x, y and z faces in reference to the box's centre
		nx, ny, nz, px, py, pz
	};

	Face GetOppositeFace(Face face);

	extern std::array<Face, 6> face_types;

	std::string EnumToString(Face face);

	void to_json(Json& j, Face face);

	template<typename OStream>
	OStream& operator<<(OStream& os, Face face)
	{
		return os << EnumToString(face);
	}


}