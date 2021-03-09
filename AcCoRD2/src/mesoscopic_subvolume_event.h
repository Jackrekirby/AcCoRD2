// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once

namespace accord::mesoscopic
{
	class SubvolumeQueue;

	class SubvolumeEvent
	{
	public:
		SubvolumeEvent();

		void LinkToQueue(SubvolumeQueue* queue, size_t queue_index);

		double GetTime() const;

		void UpdateTime(double delta_time);

		void SetTime(double new_time);

		bool ReactsBefore(const SubvolumeEvent& other);
	private:
		double time;
		size_t queue_index;
		SubvolumeQueue* queue;
	};
}