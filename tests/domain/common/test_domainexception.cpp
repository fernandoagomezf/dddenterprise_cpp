#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "domain/common/domainexception.hpp"

using namespace std::literals;
using vantage::domain::common::DomainException;

TEST_CASE("DomainException - constructor") {
    SUBCASE("Default constructor") {
        DomainException ex { };
        CHECK(ex.what() == "A problem occurred within the domain."s);
        CHECK(ex.context() == ""s);
        CHECK(ex.entity() == ""s);
        CHECK(ex.id() == ""s);
    }
    SUBCASE("Parametrized constructor") {
        DomainException ex("Custom error message", "UserContext", "UserEntity", "UserId");
        CHECK(ex.what() == "Custom error message"s);
        CHECK(ex.context() == "UserContext"s);
        CHECK(ex.entity() == "UserEntity"s);
        CHECK(ex.id() == "UserId"s);
    }
}

TEST_CASE("DomainException - accessors") {
    SUBCASE("Context accessor") {
        DomainException ex("Error with context", "OrderContext", "OrderEntity", "OrderId");
        CHECK(ex.context() == "OrderContext"s);
    }
    SUBCASE("Entity accessor") {
        DomainException ex("Error with entity", "OrderContext", "OrderEntity", "OrderId");
        CHECK(ex.entity() == "OrderEntity"s);
    }
    SUBCASE("ID accessor") {
        DomainException ex("Error with ID", "OrderContext", "OrderEntity", "OrderId");
        CHECK(ex.id() == "OrderId"s);
    }
}
