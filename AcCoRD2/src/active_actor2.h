#pragma once
#include "pch.h"
#include "event5.h"
#include "object_ids.h"
#include "active_actor_id.h"
#include "active_actor_shape.h"

namespace accord
{
	namespace microscopic
	{
		class Region;
	}

	namespace mesoscopic
	{
		class Region;
	}

	class ActiveActorID;

	class ActiveActor2 : public Event5
	{
	public:
		ActiveActor2(double action_interval, double release_interval, MoleculeIDs release_molecules,
			int modulation_strength, std::vector<microscopic::Region*> micro_regions, std::vector<mesoscopic::Region*> meso_regions,
			std::unique_ptr<ActiveActorShape> shape, double start_time, int priority, const ActiveActorID& id);

		virtual void Run() = 0;

		Type GetType() const;

		const ActiveActorID& GetID() const;

		ActiveActorShape& GetShape();

		void ReleaseMolecules(int n_releases);

		// could return true if a new symbol needs to be generated
		bool SetNextReleaseTime(double elapsed_time);

		virtual void NextRealisation();

	private:
		std::vector<microscopic::Region*> micro_regions;
		std::vector<mesoscopic::Region*> meso_regions;
		std::unique_ptr<ActiveActorShape> shape;
		MoleculeIDs release_molecules;
		ActiveActorID id;
	protected:
		double action_interval;
		double last_action_time;
		double release_interval;
		double local_time;
		int modulation_strength;
		double start_time;
	};
}
