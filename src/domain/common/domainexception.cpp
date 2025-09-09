#include "domain/common/domainexception.hpp"

using std::runtime_error;
using std::string;
using vantage::domain::common::DomainException;

DomainException::DomainException()
    : runtime_error("A problem occurred within the domain.") {
    _context = "";
    _entity = "";
    _id = "";   
}

DomainException::DomainException(const string& message)
    : runtime_error(message) {
    _context = "Generic domain error";
}

DomainException::DomainException(const string& message, const string& context, const string& entity, const string& id)
    : runtime_error(message) {
    _context = context;
    _entity = entity;
    _id = id;
}

string DomainException::context() const {
    return _context;
}

string DomainException::entity() const {
    return _entity;
}

string DomainException::id() const {
    return _id;
}