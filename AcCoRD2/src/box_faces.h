#pragma once
#include "pch.h"

namespace accord::shape
{
	enum class Face : size_t
	{ // negative and positive direction x, y and z faces in reference to the box's centre
		nx, ny, nz, px, py, pz
	};

	// returns the face on the opposite side to the face inputed. 
	// E.g. the face opposite to the positive x is negative x
	Face GetOppositeFace(Face face);

	// an array of all box face directions
	extern std::array<Face, 6> face_types;

	// convert face enum to string
	std::string EnumToString(Face face);

	// convert face enum to json
	void to_json(Json& j, Face face);

	// log face enum to output stream
	template<typename OStream>
	OStream& operator<<(OStream& os, Face face)
	{
		return os << EnumToString(face);
	}
}