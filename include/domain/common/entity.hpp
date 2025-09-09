#pragma once

#include <string>
#include "domain/common/identifier.hpp"

namespace vantage::domain::common {
    using std::string;
    using vantage::domain::common::Identifier;
    
    class Entity {
        public:
            virtual ~Entity() = default;

            Identifier getId() const;

            virtual bool equals(const Entity& other) const;
            virtual size_t hashCode() const;
            virtual string toString() const;

        protected:
            Entity(Identifier id);

        private:
            Identifier _id;
    };
}
