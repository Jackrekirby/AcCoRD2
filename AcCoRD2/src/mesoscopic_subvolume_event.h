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