#pragma once

#include <string>
#include "valueobject.hpp"

namespace vantage::domain::core {
    using std::size_t;
    using std::string;
    using vantage::domain::core::ValueObject;

    class DomainEvent final : public ValueObject {
        public:
            DomainEvent() = delete;
            explicit DomainEvent(const string& code);
            DomainEvent(const DomainEvent&) = default;
            ~DomainEvent() override = default;

            DomainEvent& operator=(const DomainEvent&) = default;
            DomainEvent(DomainEvent&&) = default;
            DomainEvent& operator=(DomainEvent&&) = default;
            
            bool equals(const ValueObject& other) const override;
            size_t hash() const override;
            string toString() const override;

        private:
            string _code;
    };
}