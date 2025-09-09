#pragma once

#include <string>
#include "valueobject.hpp"

namespace vantage::domain::common {
    using std::size_t;
    using std::string;
    using vantage::domain::common::ValueObject;

    class DomainEvent final : public ValueObject {
        public:
            explicit DomainEvent(const string& context, const string& code);
            ~DomainEvent() override = default;
            
            bool equals(const ValueObject& other) const override;
            size_t hashCode() const override;
            string toString() const override;

        private:
            string _context;
            string _code;
    };
}