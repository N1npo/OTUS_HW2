#include <iostream>
#include "Tester.h"

class StringsTask : public ITask
{
public:
    std::string run(const string_buffer_t &buff) override
    {
        return std::to_string(buff[0].length());
    }
    const char *name() const override { return "Strings"; }
};

struct TicketsTask : public ITask
{
    using vector_t = std::vector<uint64_t>;

    const char* name() const override { return "Tickets"; }

    std::string run(const string_buffer_t &buff) override
    {
        int n = std::atoi(buff[0].c_str());
        auto result = calculate(n);
        return std::to_string(result);
    }

    uint64_t calculate(int n)
    {
        vector_t summs(10, 1); // for n=1
        uint64_t result = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            summs = get_next(summs);
        }

        for (auto sum : summs)
        {
            result += (sum * sum);
        }
        return result;
    }

    vector_t get_next(const vector_t &prev_summs)
    {
        size_t max = prev_summs.size() + 9;
        vector_t new_summs;
        new_summs.resize(max);
        for (size_t i = 0; i < max; ++i)
        {
            uint64_t q = 0;
            for (size_t j = 0; j <= 9; ++j)
            {

                if (j <= i and i - j <= prev_summs.size() - 1)
                {
                    q += prev_summs[i - j];
                }
            }
            new_summs[i] = q;
        }
        return new_summs;
    }
};

