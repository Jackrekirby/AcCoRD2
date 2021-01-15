#pragma once
#include "pch.h"

namespace accord
{
	class ActiveActorID
	{
	public:
		ActiveActorID(int id);

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