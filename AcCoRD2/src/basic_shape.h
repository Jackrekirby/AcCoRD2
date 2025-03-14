// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord::shape::basic
{
	// a requirement of all basic shapes is that they can be outputted to json to aid debugging
	class Shape
	{
	public:
		//is called by to_json to allow for abstract calling and access to private variables
		virtual void ToJson(Json& j) const = 0;
	};

	// to_json is a function required by Nlohmann Json library to convert a class object to a json object
	void to_json(Json& j, const Shape& shape);
}