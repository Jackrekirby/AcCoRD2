// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#include "json.h"

#include <iomanip> // for std::setw
#include <sstream> // for std::stringstream

namespace accord
{
	Json g_json;

	std::string JsonToString(const Json& j)
	{
		std::stringstream os;
		os << j;
		return os.str();
	}

	std::string JsonToPrettyString(const Json& j)
	{
		std::stringstream os;
		os << std::setw(4) << j;
		return os.str();
	}
}