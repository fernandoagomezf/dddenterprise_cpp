#include <stdexcept>
#include "domain/common/domainevent.hpp"

using std::hash;
using std::invalid_argument;
using std::string;
using vantage::domain::common::DomainEvent;

DomainEvent::DomainEvent(const string& context, const string& code)
    : ValueObject(), _context(context), _code(code) {
    if (context.empty()) {
        throw invalid_argument("Context cannot be empty.");
    }
    if (code.empty()) {
        throw invalid_argument("Code cannot be empty.");
    }
}

bool DomainEvent::equals(const ValueObject& other) const {
    const auto* ptr = dynamic_cast<const DomainEvent*>(&other);
    return ptr != nullptr 
        && (_context == ptr->_context) 
        && (_code == ptr->_code);
}

size_t DomainEvent::hashCode() const {
    return hash<string>{}(_context) ^ (hash<string>{}(_code) << 1);
}

string DomainEvent::toString() const {
    return "DomainEvent{context='" + _context + "', code='" + _code + "'}";
}