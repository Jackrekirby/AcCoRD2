#pragma once
#include "object_ids.h"

namespace accord
{
	class ZerothOrderReaction
	{
	public:
		ZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions);

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		const RegionIDs& GetRegions() const;

	private:
		MoleculeIDs products;
		double reaction_rate;
		RegionIDs regions;
	};

	class FirstOrderReaction
	{
	public:
		FirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions);

		MoleculeID GetReactant() const;

		const MoleculeIDs& GetProducts() const;

		double GetRate() const;

		double GetTotalRate() const; 

		const RegionIDs& GetRegions() const;

	private:
		MoleculeID reactant;
		MoleculeIDs products;
		double reaction_rate;
		RegionIDs regions;
	};

	// in the future need to change RegionIDs to MicroscopicRegionIDs and MesoscopicRegionIDs
	class ReactionManager
	{
	public:
		static void Init(int num_of_molecule_types);

		// Zeroth Order Reaction
		static void AddZerothReaction(const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions);

		// First Order Reaction
		static void AddFirstReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, const RegionIDs& regions);

		static double GetSumOfRates(MoleculeID reactant);

		static const ZerothOrderReaction& GetZerothOrderReaction(RegionID id);

		static const FirstOrderReaction& GetFirstOrderReaction(RegionID id);

		static const std::vector<ZerothOrderReaction>& GetZerothOrderReactions();

		static const std::vector<FirstOrderReaction>& GetFirstOrderReactions();
	private:
		static std::vector<ZerothOrderReaction> zeroth_order_reactions;
		static std::vector<FirstOrderReaction> first_order_reactions;
		static std::vector<double> first_order_reaction_rates_per_molecule_type;
	};
}