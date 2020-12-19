#pragma once
#include "pch.h"
#include "basic_shape.h"

namespace accord::shape::basic
{
	class Box;

	class Shape3D : public Shape
	{
	public:
		virtual Box GenerateBoundingBox() const = 0;
	};
}