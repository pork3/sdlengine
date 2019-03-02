#ifndef UTILS_HPP_
#define UTILS_HPP_
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Chase Craig
 *	Last updated on: Feb. 24, 2019
 *
 *	Purpose:
 *      This header file is to define useful utility objects that can perform quick and redundant
 *            calculations.
 *
 *
 *
 */


#include <chrono>
using namespace std::chrono;
namespace Engine{
    class Utilities{
    public:
        static Utilities* &instance(){static Utilities* uti= new Utilities; return uti;}
        long long getMillisFrom(high_resolution_clock::time_point *then, high_resolution_clock::time_point *now){


            auto now_ms = time_point_cast<milliseconds>(*now);
            auto then_ms = time_point_cast<milliseconds>(*then);

            auto now_v = now_ms.time_since_epoch();
            auto then_v = then_ms.time_since_epoch();
            long long duration = now_v.count() - then_v.count();

            return duration;
        }

        /*
            This function will take a targetRate, and will return the delta time, in milliseconds that
                best corresponds to the rate.

            If the rate is 0 or negative, it will be treated as uncapped and hence it will return 0.
        */
        long long getMillisWaitTime(short rate){
            if(rate <= 0){
                return 0;
            }
            double drate = rate;
            double delta = 1000.0 / drate; //1000 since rate is in ____ per second, so we need millis.
            return static_cast<long long>(delta);
        }
    protected:
        Utilities(){};
    };
}
namespace Management{
    class OnlyOne{
    protected:
        OnlyOne()=default;
        virtual ~OnlyOne()=default;
        OnlyOne(const OnlyOne&)=delete;
        OnlyOne& operator=(const OnlyOne&)=delete;
        OnlyOne(OnlyOne&&)=delete;
        OnlyOne& operator=(OnlyOne&&)=delete;
    };
}

#endif // UTILS_HPP_
