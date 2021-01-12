#pragma once
#include "object_ids.h"
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
		static void AddZerothOrderReaction(const MoleculeIDs& products, double reaction_rate, 
			const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		// First Order Reaction
		static void AddFirstOrderReaction(MoleculeID reactant, const MoleculeIDs& products, double reaction_rate, 
			const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		static void AddSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
			const MoleculeIDs& products, double binding_radius, double unbinding_radius,
			double reaction_rate, const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		static void AddSecondOrderReaction(MoleculeID reactant_a,
			const MoleculeIDs& products, double binding_radius, double unbinding_radius, 
			double reaction_rate, const MicroRegionIDs& micro_regions, const MesoRegionIDs& meso_regions);

		static double GetSumOfRates(MoleculeID reactant);

		static const ZerothOrderReaction& GetZerothOrderReaction(ReactionID id);

		static const FirstOrderReaction& GetFirstOrderReaction(ReactionID id);

		static const SecondOrderReaction& GetSecondOrderReaction(ReactionID id);

		static const std::vector<ZerothOrderReaction>& GetZerothOrderReactions();

		static const std::vector<FirstOrderReaction>& GetFirstOrderReactions();

		static const std::vector<SecondOrderReaction>& GetSecondOrderReactions();
	private:
		static std::vector<ZerothOrderReaction> zeroth_order_reactions;
		static std::vector<FirstOrderReaction> first_order_reactions;
		static std::vector<double> first_order_reaction_rates_per_molecule_type;
		static std::vector<SecondOrderReaction> second_order_reactions;
	};
}