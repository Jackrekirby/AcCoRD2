#pragma once

namespace accord
{
	// intersection = origin + time * (end - origin)
	double Lerp(double origin, double end, double time);

	// time = (intersection - origin) / (end - origin);
	double InverseLerp(double origin, double end, double intersection);

	// mirrored_position = (2 * mirror_line - position);
	double MirrorPosition(double a, double mirror_line);
}

