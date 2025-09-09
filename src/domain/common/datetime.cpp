#include <chrono>
#include <string>
#include <stdexcept>
#include <format>
#include "domain/common/datetime.hpp"

using std::invalid_argument;
using std::format;
using std::size_t;
using std::chrono::system_clock;
using std::chrono::hours;
using std::chrono::minutes;
using std::chrono::seconds;
using std::chrono::time_point;
using std::chrono::time_point_cast;
using std::chrono::sys_days;
using std::chrono::year;
using std::chrono::years;
using std::chrono::month;
using std::chrono::months;
using std::chrono::day;
using std::chrono::days;
using std::chrono::year_month_day;
using std::string;
using std::hash;
using vantage::domain::common::ValueObject;
using vantage::domain::common::DateTime;

DateTime::DateTime() 
    : _value(system_clock::now()) {

}

DateTime::DateTime(system_clock::time_point pt)
    : _value(pt) {

}

DateTime::DateTime(int yyyy, int mm, int dd)
    : _value(system_clock::time_point()) {
    ensure_date(yyyy, mm, dd);

    year y { yyyy };    
    month m { static_cast<unsigned int>(mm) };
    day d { static_cast<unsigned int>(dd) };
    sys_days pt { y/m/d };
    _value = pt + hours(0) + minutes(0) + seconds(0);
}

DateTime::DateTime(int yyyy, int mm, int dd, int hs, int ms, int ss)
    : _value(system_clock::time_point()) {
    ensure_date(yyyy, mm, dd);
    ensure_time(hs, ms, ss);

    year y { yyyy };
    month m { static_cast<unsigned int>(mm) };
    day d { static_cast<unsigned int>(dd) };
    sys_days pt { y/m/d };
    _value = pt + hours(hs) + minutes(ms) + seconds(ss);
}

DateTime DateTime::now() {
    DateTime dt {};
    return dt;
}

int DateTime::getYear() const {
    auto pt = time_point_cast<days>(_value);
    year_month_day ymd { pt };
    auto yyyy = static_cast<int>(ymd.year());
    return yyyy;
}

int DateTime::getMonth() const {
    auto pt = time_point_cast<days>(_value);
    year_month_day ymd { pt };
    auto mm = static_cast<unsigned int>(ymd.month());
    return static_cast<int>(mm);
}

int DateTime::getDay() const {
    auto pt = time_point_cast<days>(_value);
    year_month_day ymd { pt };
    auto dd = static_cast<unsigned int>(ymd.day());
    return static_cast<int>(dd);
}

int DateTime::getHour() const {
    auto pt = time_point_cast<days>(_value);
    auto afterDay = _value - pt;
    auto hs = duration_cast<hours>(afterDay);
    return hs.count();
}

int DateTime::getMinute() const {
    auto pt = time_point_cast<days>(_value);
    auto afterDay = _value - pt;
    auto afterHour = afterDay - hours(getHour());
    auto ms = duration_cast<minutes>(afterHour);
    return ms.count();
}

int DateTime::getSecond() const {
    auto pt = time_point_cast<days>(_value);
    auto afterDay = _value - pt;
    auto afterMinute = afterDay - hours(getHour()) - minutes(getMinute());
    auto ss = duration_cast<seconds>(afterMinute);
    return static_cast<int>(ss.count());
}

bool DateTime::equals(const ValueObject& other) const {
    auto ptr = dynamic_cast<const DateTime*>(&other);
    return ptr && _value == ptr->_value;
}

size_t DateTime::hashCode() const {
    return hash<int>()(getYear()) 
         ^ hash<int>()(getMonth()) 
         ^ hash<int>()(getDay()) 
         ^ hash<int>()(getHour()) 
         ^ hash<int>()(getMinute()) 
         ^ hash<int>()(getSecond());
}

int DateTime::compareTo(const DateTime& other) const {
    if (_value < other._value) return -1;
    if (_value > other._value) return 1;
    return 0;
}

string DateTime::toString() const {
    return format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}",
                  getYear(), getMonth(), getDay(),
                  getHour(), getMinute(), getSecond());
}

DateTime DateTime::addYears(int yy) const {
    auto pt = time_point_cast<days>(_value);
    year_month_day ymd { pt };
    year_month_day newYmd { ymd.year() + years(yy), ymd.month(), ymd.day() };
    sys_days newPt { newYmd };
    auto newValue = newPt + hours(getHour()) + minutes(getMinute()) + seconds(getSecond());
    DateTime result { newValue };
    return result;
}

DateTime DateTime::addMonths(int mm) const {
    auto pt = time_point_cast<days>(_value);
    year_month_day ymd { pt };
    year_month_day newYmd { ymd.year(), ymd.month() + months(mm), ymd.day() };
    sys_days newPt { newYmd };
    auto newValue = newPt + hours(getHour()) + minutes(getMinute()) + seconds(getSecond());
    DateTime result { newValue };
    return result;
}

DateTime DateTime::addDays(int dd) const {
    auto newValue = _value + days(dd);
    DateTime result { newValue };
    return result;
}

DateTime DateTime::addHours(int hs) const {
    auto newValue = _value + hours(hs);
    DateTime result { newValue };
    return result;
}

DateTime DateTime::addMinutes(int ms) const {
    auto newValue = _value + minutes(ms);
    DateTime result { newValue };
    return result;
}

DateTime DateTime::addSeconds(int ss) const {
    auto newValue = _value + seconds(ss);
    DateTime result { newValue };
    return result;
}

void DateTime::ensure_date(int yy, int mm, int dd) {
    if (mm < 1 || mm > 12) {
        throw invalid_argument("Month must be in range 1..12");
    }
    if (dd < 1 || dd > 31) {
        throw invalid_argument("Day must be in range 1..31");
    }
    year y { yy };
    month m { static_cast<unsigned int>(mm) };
    day d { static_cast<unsigned int>(dd) };
    year_month_day ymd { y/m/d };
    if (!ymd.ok()) {
        throw invalid_argument("The date provided is invalid");
    }
}

void DateTime::ensure_time(int hs, int ms, int ss) {
    if (hs < 0 || hs > 23) {
        throw invalid_argument("Hour must be in range 0..23");
    }
    if (ms < 0 || ms > 59) {
        throw invalid_argument("Minute must be in range 0..59");
    }
    if (ss < 0 || ss > 59) {
        throw invalid_argument("Second must be in range 0..59");
    }
}