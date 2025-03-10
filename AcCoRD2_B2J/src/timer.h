// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord
{
	// Used to measure the time taken to perform a section of code
	// The timer starts upon object construction and finishes when Stop() is called.
	class Timer
	{
	public:
		// Starts the timer. Timer runs until Stop() called
		Timer();

		// Stops timer and returns the number of seconds passed since timer construction, to the nearest millisecond.
		double Stop();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
	};
}