#include "pch.h"
#include "mesoscopic_region_id.h"

namespace accord
{
	MesoscopicRegionID::MesoscopicRegionID(int id)
		: id(id)
	{
		InRange();
	}

	int MesoscopicRegionID::operator() () const
	{
		return id;
	}

	// Define prefix increment operator.
	int MesoscopicRegionID::operator++()
	{
		id++;
		InRange();
		return id;
	}

	// Define postfix increment operator.
	int MesoscopicRegionID::operator++(int)
	{
		int temp = id;
		++id;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int MesoscopicRegionID::operator--()
	{
		id--;
		InRange();
		return id;
	}

	// Define postfix decrement operator.
	int MesoscopicRegionID::operator--(int)
	{
		int temp = id;
		--id;
		InRange();
		return temp;
	}

	MesoscopicRegionID::operator int() const
	{
		return id;
	}

	void MesoscopicRegionID::SetNumIDs(int count)
	{
		MesoscopicRegionID::count = count;
	}

	void MesoscopicRegionID::InRange()
		{
			if (id < 0 || id >= count)
			{
				LOG_CRITICAL("ID was set to {}, but 0 <= ID < {}.", id, count);
				throw std::exception();
			}
		}

	int MesoscopicRegionID::count = 0;
}