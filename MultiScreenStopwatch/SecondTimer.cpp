/**
 * @brief Implementation of the SecondTimer class
 *
 * A simple class that encapsulates a wxTimer, and fires
 * an event (approximately) every second.
 *
 **/
#include "SecondTimer.hpp"
#include <sstream>
#include <time.h>

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
	std::chrono::hours hrs = std::chrono::duration_cast<std::chrono::hours>(temp);
	temp -= hrs;
	std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(temp);
	temp -= min;
	std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(temp);

	std::stringstream ss;
	if (hrs.count() > 0) {
		if (hrs > std::chrono::hours(10))
			ss << "0";
		ss << hrs.count() << ":";
	}
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

/***
 * Turns the current time into HH::MM:SS
 */
std::string SecondTimer::ToString() {
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm* tm = localtime(&t);
	// hour
	int hour = tm->tm_hour;
	if (hour > 12)
		hour -= 12;
	std::stringstream ss;
	if (tm->tm_hour < 10)
		ss << "0";
	ss << hour << ":";
	// minutes
	if (tm->tm_min < 10)
		ss << "0";
	ss << tm->tm_min << ":";
	//seconds
	if (tm->tm_sec < 10)
		ss << "0";
	ss << tm->tm_sec;
	return ss.str();
}
