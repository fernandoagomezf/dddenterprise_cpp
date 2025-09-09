#include "domain/common/entity.hpp"

using std::string;
using vantage::domain::common::Identifier;
using vantage::domain::common::Entity;

Entity::Entity(Identifier id)
    : _id(id) {

}

Identifier Entity::getId() const {
    return _id;
}

bool Entity::equals(const Entity& other) const {
    return _id.equals(other._id);
}

size_t Entity::hashCode() const {
    return _id.hashCode();
}

string Entity::toString() const {
    return "Entity(" + _id.toString() + ")";
}