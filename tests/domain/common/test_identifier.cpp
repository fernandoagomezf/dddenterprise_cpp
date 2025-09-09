#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "domain/common/identifier.hpp"

using vantage::domain::common::Identifier;


TEST_CASE("Identifier - constructor") {
    SUBCASE("Create new Identifier") {
        Identifier id1 = Identifier::createNew();
        Identifier id2 = Identifier::createNew();
        CHECK(id1.equals(id1) == true);
        CHECK(id1.equals(id2) == false);
    }
}

TEST_CASE("Identifier - string representation") {
    SUBCASE("Convert Identifier to string") {
        Identifier id = Identifier::createNew();
        std::string str = id.toString();
        CHECK(str.length() == 36);
        CHECK(str[8] == '-');
        CHECK(str[13] == '-');
        CHECK(str[18] == '-');
        CHECK(str[23] == '-');
    }
}
TEST_CASE("Identifier - equality and hashing") {
    SUBCASE("Check equality") {
        Identifier id1 = Identifier::createNew();
        Identifier id2 = Identifier::createNew();
        Identifier id3 = id1;

        CHECK(id1.equals(id3) == true);
        CHECK(id1.equals(id2) == false);
    }
    SUBCASE("Check hashing equality") {
        Identifier id1 = Identifier::createNew();
        Identifier id2 = Identifier::createNew();
        Identifier id3 = id1;

        CHECK(id1.hashCode() == id3.hashCode());
        CHECK(id1.hashCode() != id2.hashCode());
    }
    SUBCASE("Check hash code consistency") {
        Identifier id = Identifier::createNew();
        size_t hash1 = id.hashCode();
        size_t hash2 = id.hashCode();
        CHECK(hash1 == hash2);
    }
}