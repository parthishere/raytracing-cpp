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

        auto seconds = elapsed / 1'000'000;
        auto milliseconds = (elapsed % 1'000'000) / 1000;
        auto microseconds = elapsed % 1000;


        printFormattedOutput(seconds, milliseconds, microseconds, elapsed);
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

    void printFormattedOutput(long long seconds, long long milliseconds, long long microseconds, long long elapsed)
    {
        const int width = 50;
        const std::string separator(width, '-');
        
        std::cout << '\n' << separator << '\n';
        std::cout << std::setw(width/2 + 7) << "ELAPSED TIME" << std::setw(width/2 - 7) << '\n';
        std::cout << separator << '\n';
        
        std::cout << std::left << std::setw(20) << "Seconds:" << std::right << std::setw(width - 23) << seconds << " s\n";
        std::cout << std::left << std::setw(20) << "Milliseconds:" << std::right << std::setw(width - 23) << milliseconds << " ms\n";
        std::cout << std::left << std::setw(20) << "Microseconds:" << std::right << std::setw(width - 23) << microseconds << " µs\n";
        
        std::cout << separator << '\n';
        std::cout << std::left << std::setw(20) << "Total Time:" << std::right << std::setw(width - 23) << elapsed << " µs\n";
        std::cout << std::left << std::setw(20) << "Total Time:" << std::right << std::setw(width - 23) << std::fixed << std::setprecision(3) << elapsed * 0.001 << " ms\n";
        std::cout << separator << '\n';
    }
};