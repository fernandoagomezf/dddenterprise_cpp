#pragma once

#include <memory>
#include <string>

namespace vantage::domain::common {
    class ValueObject {
        public:
            virtual ~ValueObject() = default;

            virtual bool equals(const ValueObject& other) const = 0;
            virtual std::size_t hash() const = 0;
            virtual std::string toString() const = 0;

            
    };
}