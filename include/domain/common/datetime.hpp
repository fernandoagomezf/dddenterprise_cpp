#pragma once 

#include <chrono>
#include <string>
#include "valueobject.hpp"

namespace vantage::domain::common {
    using std::chrono::system_clock;
    using std::size_t;
    using std::string;
    using vantage::domain::common::ValueObject;

    class DateTime final : public ValueObject {
        public:
            DateTime(int yyyy, int mm, int dd);
            DateTime(int yyyy, int mm, int dd, int hs, int ms, int ss);
            ~DateTime() override = default;
            
            int getYear() const;
            int getMonth() const;
            int getDay() const;
            int getHour() const;
            int getMinute() const;
            int getSecond() const;
            
            DateTime addYears(int years) const;
            DateTime addMonths(int months) const;
            DateTime addDays(int days) const;
            DateTime addHours(int hours) const;
            DateTime addMinutes(int minutes) const;
            DateTime addSeconds(int seconds) const;

            static DateTime now();

            bool equals(const ValueObject& other) const override;
            int compareTo(const DateTime& other) const;
            size_t hashCode() const override;
            string toString() const override;

        private:
            DateTime();
            DateTime(system_clock::time_point pt);
            static void ensure_date(int yy, int mm, int dd);
            static void ensure_time(int hs, int ms, int ss);

            system_clock::time_point _value;
    };
}