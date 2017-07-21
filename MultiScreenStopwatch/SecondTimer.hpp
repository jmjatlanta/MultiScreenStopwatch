#pragma once

#include <stdio.h>
#include <chrono>
#include <wx/wx.h>

/**
 * a class that executes timer events
 **/

class SecondTimer : public wxTimer {
public:
	SecondTimer();
	~SecondTimer();
public:
	int StartTimer();
	int StopTimer();
	int ResetTimer();
	std::chrono::system_clock::time_point GetStartTime();
	std::chrono::seconds SecondsSinceStart();
	static std::string ToString(const std::chrono::seconds secs);
	static std::string ToString(const int minutes);
private:
	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point stopTime;
	bool isRunning;
};
