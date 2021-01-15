#include "pch.h"
#include "active_actor_id.h"

namespace accord
{
	ActiveActorID::ActiveActorID(int id)
		: id(id)
	{
		InRange();
	}

	int ActiveActorID::operator() () const
	{
		return id;
	}

	// Define prefix increment operator.
	int ActiveActorID::operator++()
	{
		id++;
		InRange();
		return id;
	}

	// Define postfix increment operator.
	int ActiveActorID::operator++(int)
	{
		int temp = id;
		++id;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int ActiveActorID::operator--()
	{
		id--;
		InRange();
		return id;
	}

	// Define postfix decrement operator.
	int ActiveActorID::operator--(int)
	{
		int temp = id;
		--id;
		InRange();
		return temp;
	}

	ActiveActorID::operator int() const
	{
		return id;
	}

	void ActiveActorID::SetNumIDs(int count)
	{
		ActiveActorID::count = count;
	}

	void ActiveActorID::InRange()
		{
			if (id < 0 || id >= count)
			{
				LOG_CRITICAL("ID was set to {}, but 0 <= ID < {}.", id, count);
				throw std::exception();
			}
		}

	int ActiveActorID::count = 0;
}