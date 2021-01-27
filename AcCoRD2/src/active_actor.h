#pragma once
#include "pch.h"
#include "event.h"
#include "active_actor_id.h"
#include "active_actor_shape.h"
#include "molecule_id.h"

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

	class ActiveActor : public Event
	{
	public:
		ActiveActor(double action_interval, double release_interval, const std::vector<int>& release_molecules,
			int modulation_strength, const std::vector<microscopic::Region*>& microscopic_regions, const std::vector<mesoscopic::Region*>& mesoscopic_regions,
			std::unique_ptr<ActiveActorShape> shape, double start_time, int priority, const ActiveActorID& id);

		virtual void Run() = 0;

		std::string LogEvent() const;

		const ActiveActorID& GetID() const;

		ActiveActorShape& GetShape();

		void ReleaseMolecules(int n_releases);

		// could return true if a new symbol needs to be generated
		bool SetNextReleaseTime(double elapsed_time);

		virtual void NextRealisation();

	private:
		std::vector<microscopic::Region*> microscopic_regions;
		std::vector<mesoscopic::Region*> mesoscopic_regions;
		std::unique_ptr<ActiveActorShape> shape;
		std::vector<int> release_molecules;
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
