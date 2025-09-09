#pragma once

#include <memory>
#include <string>

namespace vantage::domain::common {
    using std::size_t;
    using std::string;

    class ValueObject {
        public:
            virtual ~ValueObject() = default;

            virtual bool equals(const ValueObject& other) const = 0;
            virtual size_t hashCode() const = 0;
            virtual string toString() const = 0;
    };
}