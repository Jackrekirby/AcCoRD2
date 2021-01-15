#include "pch.h"
#include "passive_actor_id.h"

namespace accord
{
	PassiveActorID::PassiveActorID(int id)
		: id(id)
	{
		InRange();
	}

	int PassiveActorID::operator() () const
	{
		return id;
	}

	// Define prefix increment operator.
	int PassiveActorID::operator++()
	{
		id++;
		InRange();
		return id;
	}

	// Define postfix increment operator.
	int PassiveActorID::operator++(int)
	{
		int temp = id;
		++id;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int PassiveActorID::operator--()
	{
		id--;
		InRange();
		return id;
	}

	// Define postfix decrement operator.
	int PassiveActorID::operator--(int)
	{
		int temp = id;
		--id;
		InRange();
		return temp;
	}

	PassiveActorID::operator int() const
	{
		return id;
	}

	void PassiveActorID::SetNumIDs(int count)
	{
		PassiveActorID::count = count;
	}

	void PassiveActorID::InRange()
		{
			if (id < 0 || id >= count)
			{
				LOG_CRITICAL("ID was set to {}, but 0 <= ID < {}.", id, count);
				throw std::exception();
			}
		}

	int PassiveActorID::count = 0;
}