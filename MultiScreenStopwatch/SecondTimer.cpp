/**
 * Implementation of the SecondTimer class
 **/
#include "SecondTimer.hpp"
#include <sstream>

/**
 * Default constructor
 **/
SecondTimer::SecondTimer() : wxTimer()
{
	isRunning = false;
}

/**
 * Desstructor
 **/
SecondTimer::~SecondTimer()
{
}

int SecondTimer::StartTimer()
{
	startTime = std::chrono::system_clock::now();
	isRunning = true;
	Start(1000);
	return 0;
}

int SecondTimer::StopTimer()
{
	stopTime = std::chrono::system_clock::now();
	Stop();
	return 0;
}

int SecondTimer::ResetTimer()
{
	startTime = std::chrono::system_clock::now();
	return 0;
}

std::chrono::system_clock::time_point SecondTimer::GetStartTime() {
	return startTime;
}

std::chrono::seconds SecondTimer::SecondsSinceStart()
{
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(current - startTime);
}

std::string SecondTimer::ToString(const std::chrono::seconds secs)
{
	std::chrono::seconds temp = secs;
	std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(temp);
	temp -= min;
	std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(temp);

	std::stringstream ss;
	if (min < std::chrono::minutes(10))
		ss << "0";
	ss << min.count() << ":";
	if (sec < std::chrono::seconds(10))
		ss << "0";
	ss << sec.count();
	return ss.str();
}

std::string SecondTimer::ToString(int minutes)
{
	std::stringstream ss;
	if (minutes < 10)
		ss << "0";
	ss << minutes;
	ss << ":00";
	return ss.str();
}
