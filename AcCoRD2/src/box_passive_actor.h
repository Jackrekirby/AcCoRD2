#pragma once
#include "passive_actor.h"
#include "relation_box.h"

namespace accord
{
	class PassiveActorBoxShape : public PassiveActorShape, shape::relation::Box
	{
	public:
		PassiveActorBoxShape(shape::basic::Box box);

		bool IsMoleculeInsideBorder(const Vec3d& position) const;

		bool IsSubvolumeInsideBorder(const shape::relation::Box& box) const;

		bool IsSubvolumeOverlappingBorder(const shape::relation::Box& box) const;

		void ToJson(Json& j) const;
	};

	class BoxPassiveActor : public PassiveActor
	{
	public:
		BoxPassiveActor(shape::relation::Box box, const MoleculeIDs& molecule_ids,
			double start_time, int priority, double time_step,
			const PassiveActorID& id, bool record_positions, bool record_time);

		const PassiveActorBoxShape* const GetShape() const;
	private:
		PassiveActorBoxShape box;
	};
}