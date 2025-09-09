#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "domain/common/domainexception.hpp"

using namespace std::literals;
using vantage::domain::common::DomainException;

TEST_CASE("DomainException - Constructor") {
    SUBCASE("Default Constructor") {
        DomainException ex { };
        CHECK(ex.what() == "A problem occurred within the domain."s);
        CHECK(ex.context() == ""s);
        CHECK(ex.entity() == ""s);
        CHECK(ex.id() == ""s);
    }
    SUBCASE("Parametrized Constructor") {
        DomainException ex("Custom error message", "UserContext", "UserEntity", "UserId");
        CHECK(ex.what() == "Custom error message"s);
        CHECK(ex.context() == "UserContext"s);
        CHECK(ex.entity() == "UserEntity"s);
        CHECK(ex.id() == "UserId"s);
    }
}
