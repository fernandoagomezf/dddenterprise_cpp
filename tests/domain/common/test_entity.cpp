#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "domain/common/identifier.hpp"
#include "domain/common/entity.hpp"

using vantage::domain::common::Identifier;
using vantage::domain::common::Entity;

class TestEntity : public Entity {
public:
    explicit TestEntity(const Identifier& id) : Entity(id) {}
};

TEST_CASE("Entity - identity and behavior") {
    Identifier id1 { Identifier::createNew() };
    Identifier id1_copy = id1;
    Identifier id2 { Identifier::createNew() };

    TestEntity e1(id1);
    TestEntity e1b(id1_copy);
    TestEntity e2(id2);

    SUBCASE("getId and id string") {
        CHECK(e1.getId().toString() == id1.toString());
        CHECK(e1.getId().toString() == e1b.getId().toString());
    }

    SUBCASE("equality and hashing") {
        CHECK(e1.equals(e1b));
        CHECK_FALSE(e1.equals(e2));
        CHECK(e1.hashCode() == e1b.hashCode());
    }

    SUBCASE("string representation") {
        CHECK_FALSE(e1.toString().empty());
        CHECK_FALSE(e1.getId().toString().empty());
    }

    SUBCASE("identity uniqueness") {
        Identifier a { Identifier::createNew() };
        Identifier b { Identifier::createNew() };
        CHECK(a.toString() != b.toString());

        TestEntity ea(a);
        TestEntity eb(b);

        CHECK_FALSE(ea.equals(eb));
        CHECK(ea.getId().toString() != eb.getId().toString());
    }
}