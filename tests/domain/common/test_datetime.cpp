// cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "domain/common/datetime.hpp"

#include <string>
#include <stdexcept>

using vantage::domain::common::DateTime;
using std::string;

TEST_CASE("DateTime - Constructor") {
    SUBCASE("Date only constructor sets date and zero time") {
        DateTime d1(2021, 6, 15);
        CHECK(d1.getYear() == 2021);
        CHECK(d1.getMonth() == 6);
        CHECK(d1.getDay() == 15);
        CHECK(d1.getHour() == 0);
        CHECK(d1.getMinute() == 0);
        CHECK(d1.getSecond() == 0);
    }

    SUBCASE("Full constructor sets date and time") {
        DateTime d2(2021, 6, 15, 13, 14, 15);
        CHECK(d2.getYear() == 2021);
        CHECK(d2.getMonth() == 6);
        CHECK(d2.getDay() == 15);
        CHECK(d2.getHour() == 13);
        CHECK(d2.getMinute() == 14);
        CHECK(d2.getSecond() == 15);
    }
}

TEST_CASE("DateTime - Invalid parameters") {    
    SUBCASE("Invalid month values") {
        CHECK_THROWS_AS(DateTime(2021, 0, 1), std::invalid_argument);
        CHECK_THROWS_AS(DateTime(2021, 13, 1), std::invalid_argument);
    }
    SUBCASE("Invalid day values") {
        CHECK_THROWS_AS(DateTime(2021, 1, 0), std::invalid_argument);
        CHECK_THROWS_AS(DateTime(2021, 1, 32), std::invalid_argument);
        CHECK_THROWS_AS(DateTime(2021, 2, 29), std::invalid_argument); 
    }
    SUBCASE("Invalid time values") {
        CHECK_THROWS_AS(DateTime(2021, 1, 1, 24, 0, 0), std::invalid_argument);
        CHECK_THROWS_AS(DateTime(2021, 1, 1, 0, 60, 0), std::invalid_argument);
        CHECK_THROWS_AS(DateTime(2021, 1, 1, 0, 0, 60), std::invalid_argument);
    }
}

TEST_CASE("DateTime - Equality and Hashing") {
    DateTime a(2020, 1, 2, 3, 4, 5);
    DateTime b(2020, 1, 2, 3, 4, 5);
    DateTime c(2020, 1, 2, 3, 4, 6); 

    SUBCASE("Equal objects compare equal and have same hash") {
        CHECK(a.equals(b) == true);
        CHECK(a.hashCode() == b.hashCode());
    }

    SUBCASE("Different objects compare not equal and hashes differ (likely)") {
        CHECK(a.equals(c) == false);
        CHECK(a.hashCode() != c.hashCode());
    }
}

TEST_CASE("DateTime - compareTo and add operations") {
    DateTime base(2020, 6, 15, 10, 0, 0);

    SUBCASE("addDays, addHours, addMinutes, addSeconds") {
        DateTime plusDay = base.addDays(1);
        DateTime minusDay = base.addDays(-1);
        CHECK(base.compareTo(plusDay) < 0);
        CHECK(base.compareTo(minusDay) > 0);

        DateTime plusHour = base.addHours(1);
        CHECK(base.compareTo(plusHour) < 0);

        DateTime plusMinute = base.addMinutes(1);
        CHECK(base.compareTo(plusMinute) < 0);

        DateTime plusSecond = base.addSeconds(1);
        CHECK(base.compareTo(plusSecond) < 0);
    }

    SUBCASE("addMonths and addYears") {
        DateTime plusMonth = base.addMonths(1);
        DateTime plusYear = base.addYears(1);
        CHECK(base.compareTo(plusMonth) < 0);
        CHECK(base.compareTo(plusYear) < 0);
    }
}

TEST_CASE("DateTime - toString and now") {
    SUBCASE("toString contains year and is non-empty") {
        DateTime d(2021, 12, 31, 23, 59, 59);
        string s = d.toString();
        CHECK(!s.empty());
        CHECK(s.find("2021") != string::npos);
    }

    SUBCASE("now returns a non-empty representation and is self-equal") {
        DateTime n = DateTime::now();
        string s = n.toString();
        CHECK(!s.empty());        
        CHECK(n.compareTo(n) == 0);
    }
}