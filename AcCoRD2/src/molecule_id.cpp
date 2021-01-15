#include "pch.h"
#include "molecule_id.h"

namespace accord
{
	MoleculeID::MoleculeID(int id)
		: id(id)
	{
		InRange();
	}

	int MoleculeID::operator() () const
	{
		return id;
	}

	// Define prefix increment operator.
	int MoleculeID::operator++()
	{
		id++;
		InRange();
		return id;
	}

	// Define postfix increment operator.
	int MoleculeID::operator++(int)
	{
		int temp = id;
		++id;
		InRange();
		return temp;
	}

	// Define prefix decrement operator.
	int MoleculeID::operator--()
	{
		id--;
		InRange();
		return id;
	}

	// Define postfix decrement operator.
	int MoleculeID::operator--(int)
	{
		int temp = id;
		--id;
		InRange();
		return temp;
	}

	MoleculeID::operator int() const
	{
		return id;
	}

	void MoleculeID::SetNumIDs(int count)
	{
		MoleculeID::count = count;
	}

	void MoleculeID::InRange()
		{
			if (id < 0 || id >= count)
			{
				LOG_CRITICAL("ID was set to {}, but 0 <= ID < {}.", id, count);
				throw std::exception();
			}
		}

	int MoleculeID::count = 0;
}