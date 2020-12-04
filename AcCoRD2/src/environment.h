#pragma once

namespace accord
{
	class Environment
	{
	public:
		static double GetTime()
		{
			return time;
		}

		static double GetNumberOfMoleculeTypes()
		{
			return num_molecule_types;
		}
	private:
		static double time;
		static int num_molecule_types;
	};
}