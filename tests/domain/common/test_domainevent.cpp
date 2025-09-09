#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "domain/common/domainevent.hpp"

using vantage::domain::common::DomainEvent;

TEST_CASE("DomainEvent - Constructor") {
    SUBCASE("Valid parameters") {
        DomainEvent event("context", "code");
        CHECK(event.toString() == "DomainEvent{context='context', code='code'}");
    }
    SUBCASE("Invalid parameters") {
        CHECK_THROWS_AS(DomainEvent("", "code"), std::invalid_argument);
        CHECK_THROWS_AS(DomainEvent("context", ""), std::invalid_argument);
    }
}

TEST_CASE("DomainEvent - Equality") {
    SUBCASE("Equality - check two equal objects") {
        DomainEvent event1("context", "code");
        DomainEvent event2("context", "code");

        CHECK(event1.equals(event2) == true);
    }
    SUBCASE("Equality - check two different objects") {
        DomainEvent event1("context", "code");
        DomainEvent event2("context", "different_code");

        CHECK(event1.equals(event2) == false);
    }
}

TEST_CASE("DomainEvent - Hashing") {
    SUBCASE("Hashing - check hash of equal objects") {
        DomainEvent event1("context", "code");
        DomainEvent event2("context", "code");

        CHECK(event1.hashCode() == event2.hashCode());
    }
    SUBCASE("Hashing - check hash of different objects") {
        DomainEvent event1("context", "code");
        DomainEvent event2("context", "different_code");

        CHECK(event1.hashCode() != event2.hashCode());
    }
}

TEST_CASE("DomainEvent - toString") {
    SUBCASE("toString - check string representation") {
        DomainEvent event("context", "code");
        CHECK(event.toString() == "DomainEvent{context='context', code='code'}");
    }
}
