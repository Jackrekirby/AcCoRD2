#include "pch.h"
#include "microscopic_region_id.h"

namespace accord
{
	MicroscopicRegionID::MicroscopicRegionID(int id)
		: id(id)
	{
		InRange();
	}

	int MicroscopicRegionID::operator() () const
	{
		return id;
	}

	// Define prefix increment operator.
	int MicroscopicRegionID::operator++()
	{
		id++;
		InRange();
		return id;
	}

	// Define postfix increment operator.
	int MicroscopicRegionID::operator++(int)
	{
		int temp = id;
		++id;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int MicroscopicRegionID::operator--()
	{
		id--;
		InRange();
		return id;
	}

	// Define postfix decrement operator.
	int MicroscopicRegionID::operator--(int)
	{
		int temp = id;
		--id;
		InRange();
		return temp;
	}

	MicroscopicRegionID::operator int() const
	{
		return id;
	}

	void MicroscopicRegionID::SetNumIDs(int count)
	{
		MicroscopicRegionID::count = count;
	}

	void MicroscopicRegionID::InRange()
		{
			if (id < 0 || id >= count)
			{
				LOG_CRITICAL("ID was set to {}, but 0 <= ID < {}.", id, count);
				throw std::exception();
			}
		}

	int MicroscopicRegionID::count = 0;
}