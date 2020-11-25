#pragma once
#include "pch.h"
#include "relation_box.h"
#include "collision_box.h"
#include "microscopic_grid.h"

// add Vec3d GenerateUniform(), GenerateNormal() ... 
// reactions cannot be added until all relationships have been added

namespace accord::microscopic
{
	using ID = int;
	class ZeroOrderReaction
	{

	};

	class FirstOrderReaction
	{

	};



	using OptionalCollision3D = std::optional<shape::collision::Collision3D>;
	

	class Box : public shape::relation::Box, public shape::collision::Box, public RegionShape
	{
	public:
		// can foresee multiple inheritance problem
		// make inheritance virtual ?
		// construct shape::basic::box ?
		Box(Vec3d origin, Vec3d length)
			: shape::relation::Box(origin, length), shape::collision::Box(origin, length)
		{

		}

		OptionalCollision3D CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const
		{
			return shape::collision::Box::CalculateExternalCollisionData(origin, end);
		}

		OptionalCollision3D CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const
		{
			return shape::collision::Box::CalculateInternalCollisionData(origin, end);
		}

		bool IsMoleculeInsideBorder(const Vec3d& position) const
		{
			return shape::basic::Box::IsWithinBorder(position);
		}
	};

	class RegionShape
	{
	public:
		virtual OptionalCollision3D CalculateExternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual OptionalCollision3D CalculateInternalCollisionData(const Vec3d& origin, const Vec3d& end) const = 0;

		virtual bool IsMoleculeInsideBorder(const Vec3d& position) const = 0;

		void move()
		{

		}
	};

	enum class SurfaceType
	{
		Reflecting, Adsorbing, Absorbing, None
	};

	class Region
	{
	public:
		Region(Vec3d origin, Vec3d length, std::vector<double> diffision_coefficients,
			std::vector<Vec3i> partitions, SurfaceType surface_type)
			: box(origin, length), surface_type(surface_type)
		{
			grids.reserve(Environment::GetNumberOfMoleculeTypes());
			for (int i = 0; i < Environment::GetNumberOfMoleculeTypes(); i++)
			{
				// for a non box shape you would need to do shape.GenerateBoundingBox()
				grids.emplace_back(origin, length, diffision_coefficients.at(i), partitions.at(i));
			}
		}

		RegionShape& GetRegionShape()
		{
			return box;
		}

		const SurfaceType& GetSurfaceType() const
		{
			return surface_type;
		}// probably will become GetSurface().GetType()

		// molecule_a < molecule_b
		// grid neighbours are for diffusion
		// subvolume neighbours are for bi-molecular reactions
		// no need to add subvolume neighbours for neighbouring regions where timestep is smaller
		void AddNeighbours(ID molecule_a, ID molecule_b)
		{
			grids.at(molecule_a).AddNeighbour(grids.at(molecule_b));
		}

		const double& GetTimeStep()
		{
			return time_step;
		}

		std::vector<Grid>& GetGrids()
		{
			return grids;
		}
	private:
		SurfaceType surface_type;
		std::vector<Grid> grids;
		Box box;

		double time_step;
		double local_simulation_time; // remove once added to event manager (GetEventTime())
		// surface: Adsorbing, Absorbing, Reflective, None
	};

	// avoid nested for loops!
	class SecondOrderReaction
	{
	public:
		SecondOrderReaction(ID reactant_a, ID rectant_b, std::vector<Grid> products, Region* region)
		{
			Grid& grid_a = region->GetGrids().at(reactant_a);
			for (auto& subvolume_a : grid_a.GetSubvolumes())
			{
				// switch for GetRelativesOfType()
				for (auto& subvolume_b : subvolume_a.GetRelative(rectant_b).GetSubvolumes())
				{
					
				}
			}
		}

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
	};
}
