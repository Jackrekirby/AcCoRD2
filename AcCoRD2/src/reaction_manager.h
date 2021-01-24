#pragma once
#include "zeroth_order_reaction.h"
#include "first_order_reaction.h"
#include "second_order_reaction.h"

namespace accord
{
	// in the future need to change MicroRegionIDs to MicroscopicRegionIDs and MesoscopicRegionIDs
	class ReactionManager
	{
	public:
		static void Init(int num_of_molecule_types);

		// Zeroth Order Reaction
		static void AddZerothOrderReaction(const std::vector<int>& products, double reaction_rate,
			const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions);

		// First Order Reaction
		static void AddFirstOrderReaction(const MoleculeID& reactant, const std::vector<int>& products, double reaction_rate,
			const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& meso_regions);

		static void AddSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b,
			const std::vector<int>& products, double binding_radius, double unbinding_radius,
			double reaction_rate, const MicroscopicRegionIDs& microscopic_regions, const MesoscopicRegionIDs& mesoscopic_regions);

		static void AddSecondOrderReaction(const MoleculeID& reactant_a, const std::vector<int>& products, double binding_radius,
			double unbinding_radius,  double reaction_rate, const MicroscopicRegionIDs& microscopic_regions, 
			const MesoscopicRegionIDs& mesoscopic_regions);

		static double GetSumOfRates(MoleculeID reactant);

		static const std::vector<ZerothOrderReaction>& GetZerothOrderReactions();

		static const std::vector<FirstOrderReaction>& GetFirstOrderReactions();

		static const std::vector<SecondOrderReaction>& GetSecondOrderReactions();
	private:
		static std::vector<ZerothOrderReaction> zeroth_order_reactions;
		static std::vector<FirstOrderReaction> first_order_reactions;
		static std::vector<SecondOrderReaction> second_order_reactions;

		static std::vector<double> first_order_reaction_rates_per_molecule_type;
	};
}