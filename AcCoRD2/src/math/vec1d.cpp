#include "pch.h"

#include "vec1d.h"

namespace accord::math
{
	// intersection = origin + time * (end - origin)
	double Lerp(double origin, double end, double time)
	{
		return origin + time * (end - origin);
	}

	// time = (intersection - origin) / (end - origin);
	double InverseLerp(double origin, double end, double intersection)
	{
		return (intersection - origin) / (end - origin);
	}

	// mirrored_position = (2 * mirror_line - position);
	double MirrorPosition(double position, double mirror_line)
	{
		return (2 * mirror_line - position);
	}
}