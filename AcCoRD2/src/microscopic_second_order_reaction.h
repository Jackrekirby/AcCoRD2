#pragma once
#include "pch.h"
#include "molecule_id.h"

// is it better to pass id's or grids? (can a grid be passed?)
namespace accord::microscopic
{
	class Region;
	class Grid;
	class Subvolume;
	class NormalMolecule;

	class SecondOrderReaction
	{
	public:
		SecondOrderReaction(const std::vector<int>& products, double binding_radius, double unbinding_radius);

		virtual void CalculateReactions(double current_time) = 0;
	protected:
		std::vector<int> products;
		// variables only used if there is only 1 or 2 products
		MoleculeID product_a;
		MoleculeID product_b;

		int n_products;
		double binding_radius;
		double unbinding_radius;

		void CompareMoleculesInSubvolumes(Subvolume& s1, Subvolume& s2, double current_time);

		bool AttemptToReactMolecules(const NormalMolecule& m1, const NormalMolecule& m2,
			Subvolume& s1, Subvolume& s2, double current_time);

		int CalculateNumberOfProductMolecules(const std::vector<int>& products);

		void AssignProductsAB();
	};

	class OneReactantSecondOrderReaction : public SecondOrderReaction
	{
	public:
		OneReactantSecondOrderReaction(const MoleculeID& reactant, const std::vector<int>& products,
			double binding_radius, double unbinding_radius, Region* region);

		void CalculateReactions(double current_time);
	private:
		Grid* reactant_grid;
		MoleculeID reactant;
		
		void CompareMoleculesInSubvolume(Subvolume& s1, double current_time);
	};

	class TwoReactantSecondOrderReaction : public SecondOrderReaction
	{
	public:
		TwoReactantSecondOrderReaction(const MoleculeID& reactant_a, const MoleculeID& reactant_b,
			const std::vector<int>& products, double binding_radius, double unbinding_radius, Region* region);

		void CalculateReactions(double current_time);
	private:
		Grid* reactant_a_grid;
		MoleculeID reactant_a;
		MoleculeID reactant_b;
	};
}