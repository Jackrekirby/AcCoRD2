#include "pch.h"
#include "event_id.h"

namespace accord
{
	EventID::EventID(int id)
		: id(id)
	{
		InRange();
	}

	int EventID::operator() () const
	{
		return id;
	}

	// Define prefix increment operator.
	int EventID::operator++()
	{
		id++;
		InRange();
		return id;
	}

	// Define postfix increment operator.
	int EventID::operator++(int)
	{
		int temp = id;
		++id;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int EventID::operator--()
	{
		id--;
		InRange();
		return id;
	}

	// Define postfix decrement operator.
	int EventID::operator--(int)
	{
		int temp = id;
		--id;
		InRange();
		return temp;
	}

	EventID::operator int() const
	{
		return id;
	}

	void EventID::SetNumIDs(int count)
	{
		EventID::count = count;
	}

	void EventID::InRange()
		{
			if (id < 0 || id >= count)
			{
				LOG_CRITICAL("ID was set to {}, but 0 <= ID < {}.", id, count);
				throw std::exception();
			}
		}

	int EventID::count = 0;
}