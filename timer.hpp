#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer()
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        stop();
    }
  
    
    void stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
        auto elapsed = (end - start);
        double ms = elapsed * 0.001;

        std::cout << elapsed << " us ( " << ms << "ms )" << '\n';
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

};