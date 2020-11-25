#pragma once
#include "pch.h"
#include "relation_box.h"
#include "collision_box.h"
#include "microscopic_grid.h"

// add Vec3d GenerateUniform(), GenerateNormal() ... 
// reactions cannot be added until all relationships have been added
// CORRECTION: reactions can be added as ids but subvolumes cannot calculate relations yet.

// e.g. CalculateSubvolumeRelatives()
// RegionID
// ReactionID
// could even do MoleculeIDs for std::vector<MoleculeID>

// IN JSON {Relations: RegionID 1 Neighbour [1, 3, 5] / 'all'}

// could add Vec3d::GenerateRandom(double k = 0.5)?

// AddNeighbour(Region region, std::vector<MoleculeID> ids)
// AddHighPriorityRelative(Region region, std::vector<MoleculeID> ids)
// AddLowPriorityRelative(Region region, std::vector<MoleculeID> ids)

namespace accord::microscopic
{
	using ID = int;
	class ZeroOrderReaction
	{
		ZeroOrderReaction(std::vector<ID> products, Region* region)
		{
			// propensity = k * region.GetShape().GetVolume()
		}
	};

	class FirstOrderReaction
	{
		FirstOrderReaction(ID reactant_a, std::vector<ID> products, Region* region)
		{
			// propensity = k * region.at(reactant_a).GetNormalCount()
		}
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

		// second order reactions COULD be aware of pseudo surfaces
		// when you add a diffusion neighbour
		void AddNeighbours(Grid& grid, std::vector<ID> molecule_types)
		{
			// MTID = 1 3 4
			// e.g. MTID 1 needs to add 3 and 4 as reaction relatives
			// MTID 1 Grid needs to add MTID 1 as a diffision relative

			// NEED AddReactionNeighbour() AddDiffusionNeighbour()
			
			// due to overlap it is easier for a grid to add all overlapping reactions
			// as reaction neighbours and then check path after
			// some regions may not have those reactions 
			// do if(grid.region.has_reaction(reaction_ID))
			// could automatically check every region against every other for overlap.

			for (auto& type : molecule_types)
			{
				GetGrid(type).AddNeighbour(grid);
			}
		}

		// consider putting reaction neighbours functions in reaction manager
		// just add reaction and it can add neighbours and add reaction to manager (have as seperate)

		// reaction manager needed, could just pass reaction manager
		void AddReaction(ID reactant_a, ID rectant_b, std::vector<Grid> products)
		{

		}

		/// <summary>
		///
		/// </summary>
		/// <param name="molecule_type"></param>
		/// <param name="position"></param>
		void AddMolecule(ID molecule_type, const Vec3d& position)
		{
			auto a = CommentTest(5, { 0, 0, 0 });
		}

		/// <summary>
		/// This is a summary
		/// </summary>
		/// <param name="molecule_type"></param>
		/// <param name="position"></param>
		/// <returns>A Comment</returns>
		int CommentTest(ID molecule_type, const Vec3d& position)
		{

		}

		// for mesoscopic regions
		void AddMolecule(ID molecule_type, const Vec3d& position, double time)
		{
			GetGrid(molecule_type).AddRecentMolecule({ position, time });
		}

		// rely on reaction manager to sure only regions which allow this reaction call this
		// regions include itself
		void AddReactionNeighbours(ID reactant_a, ID reactant_b, std::vector<Region> regions)
		{
			// for Environment::GetMicroscopicRegions()
			// if region a and region b both have same reaction id add as reaction neighbours
			// For Grid(Reactant id).GetSubvolumes().addReactionNeighbour(Grid2(reactant2 id).GetSubvolumes() and vice versa
			// For Grid(Reactant2 id).GetSubvolumes().addReactionNeighbour(Grid2(reactant id).GetSubvolumes()
			// YOU MUST ADD NEIGHBOURS TO BOTH AS IF BOTH REACT AT THE SAME TIME AND THERE EVENT TIME IS RANDOM
			// THE ORDER OF EXECUTION IS UNKNOWN

			// OR for each region which has the same reaction check if overlap and if they do add
		}

		const double& GetTimeStep()
		{
			return time_step;
		}

		std::vector<Grid>& GetGrids()
		{
			return grids;
		}

		Grid& GetGrid(ID molecule_type)
		{
			return grids.at(molecule_type);
		}
	private:
		SurfaceType surface_type;
		std::vector<Grid> grids;
		Box box;

		SecondOrderReactionManager second_order_reaction_manager;

		double time_step;
		double local_simulation_time; // remove once added to event manager (GetEventTime())
		// surface: Adsorbing, Absorbing, Reflective, None
	};

	class SecondOrderReactionManager
	{
		// holds the reacted list to make sure reactants are not involved in multiple reactions
		// and new products do not react immediately
		std::vector<SecondOrderReaction> reactions;

		struct MoleculeType
		{
			std::vector<bool> has_reacted;
		};

		std::vector<MoleculeType> reacted_list;

		// or put inside molecule type and SecondOrderReaction can have a reference to each list.
		void MarkMoleculeAsReacted(ID molecule_type, size_t index)
		{
			reacted_list.at(molecule_type).has_reacted.at(index) = true;
		}
	};

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
