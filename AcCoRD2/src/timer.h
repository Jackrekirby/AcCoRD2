// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord
{
	// Used to measure the time taken to perform a section of code
	class Timer
	{
	public:
		// Starts the timer.
		Timer();

		// returns the number of seconds passed since timer created/reset, to the nearest millisecond.
		double GetTime();

		// starts / resets the start timer of the timer to the current time.
		void Reset();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
	};
}