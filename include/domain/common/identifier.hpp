#pragma once

#include "valueobject.hpp"

#include <array>

namespace vantage::domain::common {
    using std::size_t;
    using std::string;
    using std::array;
    using vantage::domain::common::ValueObject;

    class Identifier final : public ValueObject {
        public:
            ~Identifier() override = default;

            static Identifier createNew();

            bool equals(const ValueObject& other) const override;
            size_t hashCode() const override;
            string toString() const override;

        private:
            Identifier();
            static array<uint8_t, 16> createUUID();

            array<uint8_t, 16> _value;
    };
}