#ifndef KEYSUMM_HPP
#define KEYSUMM_HPP
#include <string>

int sum(int a, int b);
struct Key_summ {
    void operator()(const std::pair<const int, std::string> key_value)
    {
        result_ = sum(result_, key_value.first);
        if (str.empty())
            str += key_value.second;
        else
            str += " " + key_value.second;
    }
    int result_ = 0;
    std::string str;
};

#endif
