#pragma once
#include "pch.h"
// is it better to pass id's or grids? (can a grid be passed?)
namespace accord::microscopic
{
	using MoleculeID = int;
	using MoleculeIDs = std::vector<int>;
	class Region2;
	class Grid2;
	class Subvolume2;
	class NormalMolecule;

	class OneReactantSecondOrderReaction
	{
	public:
		OneReactantSecondOrderReaction(MoleculeID reactant, const MoleculeIDs& products);

		void Run(double current_time);
	private:
		Grid2* reactant_grid;
		MoleculeID reactant;
		MoleculeIDs products;
		double binding_radius;
		double unbinding_radius;
		void CalculateReactions(double current_time);

		void CompareMoleculesInSubvolume(Subvolume2& s1, double current_time);
	};

	class TwoReactantSecondOrderReaction
	{
	public:
		TwoReactantSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
			const MoleculeIDs& products, double binding_radius, double unbinding_radius, Region2* region);

		void Run(double current_time);
	private:
		Grid2* reactant_a_grid;
		MoleculeID reactant_a;
		MoleculeID reactant_b;
		MoleculeIDs products;
		double binding_radius;
		double unbinding_radius;

		void CalculateReactions(double current_time);

		void CompareMoleculesInSubvolumes(Subvolume2& s1, Subvolume2& s2, double current_time);

		bool AttemptToReactMolecules(const NormalMolecule& m1, const NormalMolecule& m2,
			Subvolume2& s1, Subvolume2& s2, double current_time);
	};

	// need to add base SecondOrderReactionClass
	// SecondOrderReactions class not necessary, move work into regions
	// rename add reactions into seperate types so can overload them
	class SecondOrderReactions
	{
	public:
		void AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products,
			double binding_radius, double unbinding_radius, Region2* region);

		void Run(double current_time);
	private:
		std::vector<OneReactantSecondOrderReaction> one_reactant_reactions;
		std::vector<TwoReactantSecondOrderReaction> two_reactant_reactions;

	};
}