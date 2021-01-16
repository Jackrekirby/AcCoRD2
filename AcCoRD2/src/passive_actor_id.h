#pragma once
#include "pch.h"

namespace accord
{
	class PassiveActorID
	{
	public:
		PassiveActorID(int id = 0);

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
	
	using PassiveActorIDs = std::vector<PassiveActorID>;
}