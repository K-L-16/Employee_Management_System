#pragma once
#include<chrono>
using namespace std::chrono;
/*timer*/
class Timer
{
public:
	Timer(int64_t ms = 0);
	void startTimer();
	bool timeout();
	void setTime(int64_t ms);
	void killTimer();
public:

	static bool startTimer(int64_t ms, int id);
	inline static size_t maxTimerID() { return 20; };
private:
    int64_t m_ms;	
	time_point<high_resolution_clock> m_startime;
	time_point<high_resolution_clock> m_endtime;

	bool m_threadIsRun;	
};

class ElapsedTimer
{
public:
    ElapsedTimer();
    void reset();
    
    int64_t elapsed() const;
    int64_t elapsed_micro() const;
    int64_t elapsed_nano() const;
    //second
    int64_t elapsed_seconds() const;
    //min
    int64_t elapsed_minutes() const;
    //hour
    int64_t elapsed_hours() const;
private:
    time_point<high_resolution_clock> m_begin;
};

