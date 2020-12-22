#include "pch.h"
#include "microscopic_second_order_reaction.h"


namespace accord::microscopic
{
	void SecondOrderReactions::AddReaction(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products)
	{
		if (reactant_a == reactant_b)
		{
			one_reactant_reactions.emplace_back(reactant_a, products);
		}
		else
		{
			two_reactant_reactions.emplace_back(reactant_a, reactant_b, products);
		}
	}

	OneReactantSecondOrderReaction::OneReactantSecondOrderReaction
	(MoleculeID reactant, const MoleculeIDs& products)
	{

	}

	TwoReactantSecondOrderReaction::TwoReactantSecondOrderReaction
	(MoleculeID reactant_a, MoleculeID reactant_b, const MoleculeIDs& products)
	{

	}


	// avoid nested for loops!
	// need to make sure subsequence second order reactions do not react with same molecules
	// OneTypeSecondOrderReaction
	// TwoTypeSecondOrderReaction
	class SecondOrderReaction
	{
	public:
		// also have option for single reactant
		SecondOrderReaction(ID reactant_a, ID rectant_b, std::vector<Grid> products, Region* region)
			: reactant_a(reactant_a), rectant_b(rectant_b), products(products), region(region)
		{

		}


		void CalculateReactions()
		{
			Grid& grid_a = region->GetGrid(reactant_a);
			for (auto& subvolume_a : grid_a.GetSubvolumes())
			{
				// switch for GetRelativesOfType()
				for (auto& subvolume_b : subvolume_a.GetRelative(rectant_b).GetSubvolumes())
				{
					CompareMolecules(subvolume_a, *subvolume_b);
				}
			}
		}

		// for single subvolume molecule comparisons
		void CompareMolecules(Subvolume& s)
		{
			auto& molecules = s.GetNormalMolecules();
			auto begin = molecules.begin();
			auto end = molecules.end();
			int i = 1;
			for (auto molecule_a = begin; molecule_a != end; ++molecule_a)
			{
				for (auto molecule_b = begin + i; molecule_a != end; ++molecule_a)
				{
					if (CompareMolecules(*molecule_a, *molecule_b))
					{
						//reacted_list(reactant_a ID)
						// manager.at(reactant id).at(position_id) = true;
						// MarkMoleculeAsReacted()
					}
				}
				i++;
			}
		}




		// react molecules
		bool CompareMolecules(NormalMolecule& m1, NormalMolecule& m2)
		{
			// check if they react return true
			// if within radius
			// Grid grid_a.checkPath(m1.position, m2.position, bool& HITSURFACEFLAG)
			// if surface hit then return std::nullopt
			// if end = m2.position
		}

		// shoudl be called compare subvolumes
		void CompareMolecules(Subvolume& s1, Subvolume& s2)
		{
			//reacted list 1, 2
			std::vector<bool> reacted_molecules_a(s1.GetNormalMolecules().size());
			std::vector<bool> reacted_molecules_b(s1.GetNormalMolecules().size());
			int n_reactions = 0;

			// need to store list of which molecules have reacted
			// at end molecules which have not reacted can be copied across to new normal molecules list

			// no need to get recent molecules as recent list has been cleared by this point
			int ia = 0, ib = 0;
			for (auto& molecule_a : s1.GetNormalMolecules())
			{
				for (auto& molecule_b : s2.GetNormalMolecules())
				{
					// change position to GetPosition()
					// if molecule b has already reacted then skip to next molecule b.
					if (reacted_molecules_b.at(ib)) continue;
					if ((molecule_a.position - molecule_b.position).Size() < binding_radius)
					{
						// delete m1 and m2
						// create products
						// is it faster to just create a new vector (copy elements you want to keep)? YES

						for (auto& product : products)
						{
							// GetGrid(type)
							// path checking required
							region->GetGrids().at(product).AddNormalMolecule(Vec3d(0, 0, 0));
						}

						reacted_molecules_a.at(ia) = true;
						reacted_molecules_b.at(ib) = true;
						n_reactions++;
						// once molecule a has reacted skip to next molecule a;
						break;
					}
					ib++;
				}
				ib = 0;
				ia++;
			}


			std::vector<NormalMolecule> new_normal_molecules_a, new_normal_molecules_b;
			new_normal_molecules_a.reserve(s1.GetNormalMolecules().size() - n_reactions);
			new_normal_molecules_b.reserve(s2.GetNormalMolecules().size() - n_reactions);

			int ia = 0, ib = 0;
			for (auto& molecule_a : s1.GetNormalMolecules())
			{
				if (reacted_molecules_a.at(ia)) new_normal_molecules_a.emplace_back(molecule_a);
				ia++;
			}

			for (auto& molecule_b : s2.GetNormalMolecules())
			{
				if (reacted_molecules_b.at(ib)) new_normal_molecules_b.emplace_back(molecule_b);
				ib++;
			}

			s1.GetNormalMolecules() = new_normal_molecules_a;
			s2.GetNormalMolecules() = new_normal_molecules_b;
		}
	private:
		double binding_radius;
		double unbinding_radius; // is this required for all reactions?
		std::vector<ID> products;
		Region* region;
		ID reactant_a;
		ID rectant_b;
	};
}

}







