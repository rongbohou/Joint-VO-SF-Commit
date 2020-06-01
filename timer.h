//
// Created by hrb on 20-3-13.
//

#ifndef BASALT_BACKEND_TIMER_H
#define BASALT_BACKEND_TIMER_H

#include <unordered_map>
#include <map>
#include <float.h>

class Timer {
    struct TimeData {
        size_t use_cnt = 0;
        int64_t time_start = 0;
        double time_cost = 0.0f;
        double time_min = DBL_MAX;
        double time_max = 0.0f;
        double time_sum = 0.0f;
        double time_cur = 0.0f;
    };

public:
    void start(std::string _name);

    void stop(std::string _name);

    void count(std::string _name);

    void stopAndCount(std::string _name);

    void count();

    void print(std::string _name);

    void print();

private:
    std::map<std::string, TimeData> elements;
//    std::unordered_map<std::string, TimeData> elements;
};

#endif //BASALT_BACKEND_TIMER_H
