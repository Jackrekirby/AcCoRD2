// The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
// Copyright 2021 Jack Kirby. All rights reserved. 
// For license details, read LICENSE.txt in the root AcCoRD2 directory

#pragma once
#include "pch.h"

namespace accord
{
	class Event;
	class EventQueue
	{
	public:
		EventQueue(size_t capacity);

		EventQueue();

		void Reserve(size_t capacity);

		size_t GetSize();

		void Add(Event* event);

		void IncreasePriority(size_t index);

		void DecreasePriority(size_t index);

		Event& Front();

		Event& GetEvent(size_t index);
	private:

		// an unsorted vector which holds pointers to the events
		std::vector<Event*> events;
		// the position map stores the location of the values as a binary heap
		std::vector<size_t> pm;
		// the inverse map stores the location of the indicies in the position map
		std::vector<size_t> im;

		// swaps two heap values in the position map, and updates the inverse map
		void Swap(size_t index_a, size_t index_b);

		void Swim(size_t index);

		void Sink(size_t index);

		template<typename OStream>
		friend OStream& operator<<(OStream& os, const EventQueue& event_queue)
		{
			os << "pm = [";
			for (auto& index : event_queue.pm)
			{
				os << index << ", ";
			}
			os << "]\n im = [";
			for (auto& index : event_queue.im)
			{
				os << index << ", ";
			}
			os << "]";
			return os;
		}
	};
}