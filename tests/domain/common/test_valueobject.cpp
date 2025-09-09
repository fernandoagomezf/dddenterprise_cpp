#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "domain/common/valueobject.hpp"

using vantage::domain::common::ValueObject;

class TestValueObject : public ValueObject {
    public:
        TestValueObject(int value) : _value(value) {}

        bool equals(const ValueObject& other) const override {
            const auto* otherVO = dynamic_cast<const TestValueObject*>(&other);
            return otherVO && (_value == otherVO->_value);
        }

        std::size_t hashCode() const override {
            return std::hash<int>{}(_value);
        }

        std::string toString() const override {
            return "TestValueObject(" + std::to_string(_value) + ")";
        }

        int value() const {
            return _value;
        }

    private:
        int _value;
};

TEST_CASE("ValueObject - Constructor") {
    SUBCASE("Default constructor") {
        TestValueObject vo1(10);
        TestValueObject vo2(20);
        CHECK(vo1.value() == 10);
        CHECK(vo2.value() == 20);
    }
}

TEST_CASE("ValueObject - Equality") {
    SUBCASE("Equality - check two equal objects") {
        TestValueObject vo1(10);
        TestValueObject vo2(10);
        TestValueObject vo3(20);

        CHECK(vo1.equals(vo2) == true);
    }
    SUBCASE("Equality - check two different objects") {
        TestValueObject vo1(10);
        TestValueObject vo2(20);

        CHECK(vo1.equals(vo2) == false);
    }
}

TEST_CASE("ValueObject - Hashing") {
    SUBCASE("Hashing - check hash of equal objects") {
        TestValueObject vo1(10);
        TestValueObject vo2(10);

        CHECK(vo1.hashCode() == vo2.hashCode());
    }
    SUBCASE("Hashing - check hash of different objects") {
        TestValueObject vo1(10);
        TestValueObject vo2(20);

        CHECK(vo1.hashCode() != vo2.hashCode());
    }
}

TEST_CASE("ValueObject - toString") {
    SUBCASE("toString - check string representation") {
        TestValueObject vo(10);
        CHECK(vo.toString() == "TestValueObject(10)");
    }
}

