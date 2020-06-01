//
// Created by hrb on 20-3-13.
//

#include <iostream>
#include "opencv2/core.hpp"
#include "timer.h"

#ifdef ANDROID_BASALT
#include <android/log.h>
#endif

void Timer::start(std::string _name) {
    auto iter = elements.find(_name);
    if (iter == elements.end()) {
        std::cout << "create: " << _name << std::endl;
//        elements.insert(std::map<std::string, TimeData>::value_type(_name, TimeData()));
        elements.insert(std::make_pair(_name, TimeData()));

        iter = elements.find(_name);
    }

    assert(iter != elements.end());
    iter->second.time_start = cv::getTickCount();
}

void Timer::stop(std::string _name) {
    auto iter = elements.find(_name);
    if (iter == elements.end())
        return;

    iter->second.time_cost += (cv::getTickCount() - iter->second.time_start) / cv::getTickFrequency() * 1000;
}

void Timer::count(std::string _name) {
    auto iter = elements.find(_name);
    if (iter == elements.end())
        return;

    iter->second.use_cnt++;
    if (iter->second.time_cost < iter->second.time_min)
        iter->second.time_min = iter->second.time_cost;
    if (iter->second.time_cost > iter->second.time_max)
        iter->second.time_max = iter->second.time_cost;
    iter->second.time_sum += iter->second.time_cost;
    iter->second.time_cur = iter->second.time_cost;
    iter->second.time_cost = 0.0f;
}

void Timer::stopAndCount(std::string _name) {
    stop(_name);
    count(_name);
}

void Timer::count() {
    for (auto iter = elements.begin(); iter != elements.end(); ++iter) {
        iter->second.use_cnt++;
        if (iter->second.time_cost < iter->second.time_min)
            iter->second.time_min = iter->second.time_cost;
        if (iter->second.time_cost > iter->second.time_max)
            iter->second.time_max = iter->second.time_cost;
        iter->second.time_sum += iter->second.time_cost;
        iter->second.time_cur = iter->second.time_cost;
        iter->second.time_cost = 0.0f;
    }
}

void Timer::print(std::string _name) {
    auto iter = elements.find(_name);
    if (iter == elements.end())
        return;

    std::string name = iter->first;
    if (name.length() < 40) {
        name.append(40 - name.length(), ' ');
    }

    std::string time_min = std::to_string(iter->second.time_min);
    std::string time_max = std::to_string(iter->second.time_max);
    std::string time_mean = std::to_string(iter->second.time_sum / iter->second.use_cnt);
    std::string time_cur = std::to_string(iter->second.time_cur);
    time_min.resize(5);
    time_max.resize(5);
    time_mean.resize(5);
    time_cur.resize(5);

#ifdef ANDROID_BASALT
    __android_log_print(ANDROID_LOG_INFO, "basalt", "%s -> min: %s , max: %s, mean: %s, cur: %s ms  \n",
            name.c_str(), time_min.c_str(), time_max.c_str(), time_mean.c_str(), time_cur.c_str());
#else
    std::cout << name << " -> min:" << time_min << ", max:" << time_max << ", mean:" << time_mean << " cur: "
              << time_cur << " ms" << std::endl;
#endif

}

void Timer::print() {
    for (auto iter = elements.begin(); iter != elements.end(); ++iter) {
        std::string name = iter->first;
        if (name.length() < 40) {
            name.append(40 - name.length(), ' ');
        }

        std::string time_min = std::to_string(iter->second.time_min);
        std::string time_max = std::to_string(iter->second.time_max);
        std::string time_mean = std::to_string(iter->second.time_sum / iter->second.use_cnt);
        std::string time_sum = std::to_string(iter->second.time_sum);
        std::string time_cur = std::to_string(iter->second.time_cur);
        time_min.resize(5);
        time_max.resize(5);
        time_mean.resize(5);
        time_sum.resize(7);
        time_cur.resize(5);

#ifdef ANDROID_BASALT
        __android_log_print(ANDROID_LOG_INFO, "basalt", "%s -> min: %s , max: %s, mean: %s, cur: %s  ms  \n",
            name.c_str(), time_min.c_str(), time_max.c_str(), time_mean.c_str(), time_cur.c_str());
#else
        std::cout << name << " -> min:" << time_min << ", max:" << time_max << ", mean:" << time_mean << " cur: "
                  << time_cur << " ms" << std::endl;
#endif
    }
}