// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord
{
	class ActiveActorID
	{
	public:
		ActiveActorID(int id = 0);

		int operator () () const;

		// Define prefix increment operator.
		int operator++();

		// Define postfix increment operator.
		int operator++(int);

		// Define prefix decrement operator.
		int operator--();

		// Define postfix decrement operator.
		int operator--(int);

		operator int() const;

		static void SetNumIDs(int count);
	private:
		int id;
		static int count;

		void InRange();
	};
	
	using ActiveActorIDs = std::vector<ActiveActorID>;
}