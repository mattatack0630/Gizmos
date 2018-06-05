//
// Created by mathew on 5/9/18.
//

#include <chrono>
#include <iostream>
#include "TimeReporter.h"


void TimeReporter::print_time(void (*function)(void))
{
	auto start = Clock::now();

	function();

	auto end = Clock::now();

	auto diff = end - start;

	std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
}

void TimeReporter::begin()
{
	start = Clock::now();
}

void TimeReporter::finish()
{
	end = Clock::now();
}

void TimeReporter::print()
{
	auto diff = end - start;

	std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
}
