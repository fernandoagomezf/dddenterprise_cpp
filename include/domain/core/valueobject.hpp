#pragma once

#include <memory>
#include <string>

namespace vantage::domain::core {
    class ValueObject {
        public:
            virtual ~ValueObject() = default;

            virtual bool equals(const ValueObject& other) const = 0;
            virtual std::size_t hash() const = 0;
            virtual std::string toString() const = 0;

            bool operator==(const ValueObject& other) const;
            bool operator!=(const ValueObject& other) const;

        protected:
            ValueObject() = default;
            ValueObject(const ValueObject&) = default;
            ValueObject& operator=(const ValueObject&) = default;
            ValueObject(ValueObject&&) = default;
            ValueObject& operator=(ValueObject&&) = default;
    };
}