#pragma once
/**
 * @brief header for the SecondTimer class
 *
 * A simple class that encapsulates a wxTimer, and fires
 * an event (approximately) every second.
 *
 **/

#include <stdio.h>
#include <chrono>
#include <wx/wx.h>

class SecondTimer : public wxTimer {
public:
	/**
	 * Default constructor
	 */
	SecondTimer();
	/**
	 * Default destructor
	 */
	~SecondTimer();
public:
	/**
	 * Starts the timer ticking
	 * @returns 0
	 */
	int StartTimer();
	/***
	 * Stops the timer
	 * @returns 0
	 */
	int StopTimer();
	/**
	 * Resets the start time of the timer
	 * @returns 0
	 */
	int ResetTimer();
	/****
	 * Returns the time the timer started
	 * @returns a time_point of exactly when the timer started
	 */
	std::chrono::system_clock::time_point GetStartTime();
	/***
	 * Returns the number of seconds the timer has been running
	 * @returns a std::chrono::seconds object
	 **/
	std::chrono::seconds SecondsSinceStart();
	/**
	 * converts a seconds object into a string of MM:SS
	 * @returns a string in the format MM:SS
	 */
	static std::string ToString(const std::chrono::seconds secs);
	/***
	 * Converts an interger of minutes into a MM:SS string
	 * @returns a formatted string in the format MM:00
	 */
	static std::string ToString(const int minutes);
private:
	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point stopTime;
};
