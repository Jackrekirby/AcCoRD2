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


	class SecondOrderReaction
	{
	public:
		SecondOrderReaction(const MoleculeIDs& products, double binding_radius, double unbinding_radius);

		virtual void CalculateReactions(double current_time) = 0;
	protected:
		MoleculeIDs products;
		double binding_radius;
		double unbinding_radius;

		void CompareMoleculesInSubvolumes(Subvolume2& s1, Subvolume2& s2, double current_time);

		bool AttemptToReactMolecules(const NormalMolecule& m1, const NormalMolecule& m2,
			Subvolume2& s1, Subvolume2& s2, double current_time);
	};

	class OneReactantSecondOrderReaction : public SecondOrderReaction
	{
	public:
		OneReactantSecondOrderReaction(MoleculeID reactant, const MoleculeIDs& products, 
			double binding_radius, double unbinding_radius, Region2* region);

		void CalculateReactions(double current_time);
	private:
		Grid2* reactant_grid;
		MoleculeID reactant;
		
		void CompareMoleculesInSubvolume(Subvolume2& s1, double current_time);
	};

	class TwoReactantSecondOrderReaction : public SecondOrderReaction
	{
	public:
		TwoReactantSecondOrderReaction(MoleculeID reactant_a, MoleculeID reactant_b,
			const MoleculeIDs& products, double binding_radius, double unbinding_radius, Region2* region);

		void CalculateReactions(double current_time);
	private:
		Grid2* reactant_a_grid;
		MoleculeID reactant_a;
		MoleculeID reactant_b;
	};
}