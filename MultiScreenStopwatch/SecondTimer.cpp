/**
 * @brief Implementation of the SecondTimer class
 *
 * A simple class that encapsulates a wxTimer, and fires
 * an event (approximately) every second.
 *
 **/
#include "SecondTimer.hpp"
#include <sstream>

/**
 * Default constructor
 **/
SecondTimer::SecondTimer() : wxTimer()
{
}

/**
 * Desstructor
 **/
SecondTimer::~SecondTimer()
{
}

/**
 * Starts the timer ticking
 * @returns 0
 */
int SecondTimer::StartTimer()
{
	startTime = std::chrono::system_clock::now();
	Start(1000);
	return 0;
}

/***
 * Stops the timer
 * @returns 0
 */
int SecondTimer::StopTimer()
{
	stopTime = std::chrono::system_clock::now();
	Stop();
	return 0;
}

/**
 * Resets the start time of the timer
 * @returns 0
 */
int SecondTimer::ResetTimer()
{
	startTime = std::chrono::system_clock::now();
	return 0;
}

/****
 * Returns the time the timer started
 * @returns a time_point of exactly when the timer started
 */
std::chrono::system_clock::time_point SecondTimer::GetStartTime() {
	return startTime;
}

/***
 * Returns the number of seconds the timer has been running
 * @returns a std::chrono::seconds object
 **/
std::chrono::seconds SecondTimer::SecondsSinceStart()
{
	std::chrono::system_clock::time_point current = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(current - startTime);
}

/**
 * converts a seconds object into a string of MM:SS
 * @returns a string in the format MM:SS
 */
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

/***
 * Converts an interger of minutes into a MM:SS string
 * @returns a formatted string in the format MM:00
 */
std::string SecondTimer::ToString(int minutes)
{
	std::stringstream ss;
	if (minutes < 10)
		ss << "0";
	ss << minutes;
	ss << ":00";
	return ss.str();
}
