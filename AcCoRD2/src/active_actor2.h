#pragma once
#include "pch.h"
#include "event.h"
#include "object_ids.h"
#include "active_actor_shape.h"

namespace accord
{
	namespace microscopic
	{
		class Region;
	}

	class ActiveActor2 : public Event
	{
	public:
		ActiveActor2(double action_interval, double release_interval, MoleculeIDs release_molecules,
			int modulation_strength, std::vector<microscopic::Region*> regions, std::unique_ptr<ActiveActorShape> shape,
			double start_time, int priority, EventQueue* event_queue, ActiveActorID id);

		virtual void Run() = 0;

		Type GetType() const;

		EventID GetID() const;

		ActiveActorShape& GetShape();

		void ReleaseMolecules(int n_releases);

		// could return true if a new symbol needs to be generated
		bool SetNextReleaseTime(double elapsed_time);

	private:
		double local_time;
		double action_interval;
		double last_action_time;
		double release_interval;

		std::vector<microscopic::Region*> regions; // will need to change to generic region in the future
		std::unique_ptr<ActiveActorShape> shape;
		MoleculeIDs release_molecules;
		ActiveActorID id;
	protected:
		int modulation_strength;
	};
}
