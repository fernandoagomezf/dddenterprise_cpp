
#include "domain/core/valueobject.hpp"

using vantage::domain::core::ValueObject;

bool ValueObject::operator==(const ValueObject& other) const {
    return equals(other);
}
            
bool ValueObject::operator!=(const ValueObject& other) const {
    return !equals(other);
}
