//
// Created by mathew on 5/9/18.
//

#pragma once

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

class TimeReporter
{
	std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l> >> start = Clock::now();
	std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l> >> end = Clock::now();

public:
	void print_time(void (* function)(void));

	void begin();

	void finish();

	void print();
};

