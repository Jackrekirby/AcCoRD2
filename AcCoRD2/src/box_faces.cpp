// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "pch.h"
#include "box_faces.h"

namespace accord::shape
{
	Face GetOppositeFace(Face face)
	{
		switch (face)
		{
		case Face::nx:
			return Face::px;
		case Face::ny:
			return Face::py;
		case Face::nz:
			return Face::pz;
		case Face::px:
			return Face::nx;
		case Face::py:
			return Face::ny;
		case Face::pz:
			return Face::nz;
		}
		LOG_CRITICAL("Unknown Face type");
		throw std::exception();
	}

	std::string EnumToString(Face face)
	{
		switch (face)
		{
		case Face::nx:
			return "negative x";
		case Face::ny:
			return "negative y";
		case Face::nz:
			return "negative z";
		case Face::px:
			return "positive x";
		case Face::py:
			return "positive y";
		case Face::pz:
			return "positive z";
		}
		LOG_CRITICAL("Unknown Face type");
		throw std::exception();
	}

	void to_json(Json& j, Face face)
	{
		j = EnumToString(face);
	}

	std::array<Face, 6> face_types = { Face::nx, Face::ny, Face::nz, Face::px, Face::py, Face::pz };
}