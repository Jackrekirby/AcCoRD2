#include "pch.h"
#include "fixed_range_int.h"


namespace accord
{
	FixedRangeInt::FixedRangeInt(int value)
		: value(value)
	{
		InRange();
	}

	int FixedRangeInt::operator() () const
	{
		return value;
	}

	// Define prefix increment operator.
	int FixedRangeInt::operator++()
	{
		value++;
		InRange();
		return value;
	}

	// Define postfix increment operator.
	int FixedRangeInt::operator++(int)
	{
		int temp = value;
		++value;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int FixedRangeInt::operator--()
	{
		value--;
		InRange();
		return value;
	}

	// Define postfix decrement operator.
	int FixedRangeInt::operator--(int)
	{
		int temp = value;
		--value;
		InRange();
		return temp;
	}

	FixedRangeInt::operator int() const
	{
		return value;
	}

	void FixedRangeInt::SetRange(int min, int max)
	{
		FixedRangeInt::min = min;
		FixedRangeInt::max = max;
	}

	void FixedRangeInt::InRange()
		{
			if (value < min || value > max)
			{
				LOG_CRITICAL("Value was set to {}, but {} <= Value <= {}.", value, min, max);
				throw std::exception();
			}
		}

	int FixedRangeInt::min = 0;
	int FixedRangeInt::max = 0;
}