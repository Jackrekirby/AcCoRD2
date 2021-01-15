#pragma once
#include "pch.h"

namespace accord
{
	class FixedRangeInt
	{
	public:
		FixedRangeInt(int value);

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

		static void SetRange(int min, int max);
	private:
		int value;
		static int min;
		static int max;

		void InRange();
	};

	class MoleculeID2 : public FixedRangeInt
	{
	public:
		MoleculeID2(int id)
			: FixedRangeInt(id)
		{

		}
	};

	class RegionID2 : public FixedRangeInt
	{
	public:
		RegionID2(int id)
			: FixedRangeInt(id)
		{

		}
	};
}