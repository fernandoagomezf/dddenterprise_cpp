#include "domain/core/domainexception.hpp"

using std::runtime_error;
using std::string;
using vantage::domain::core::DomainException;

DomainException::DomainException()
    : runtime_error("A problem occurred within the domain.") {
    _context = "Generic domain error";
}

DomainException::DomainException(const string& message)
    : runtime_error(message) {
    _context = "Generic domain error";
}

DomainException::DomainException(const string& message, const string& context)
    : runtime_error(message) {
    _context = context;
}

string DomainException::context() const {
    return _context;
}