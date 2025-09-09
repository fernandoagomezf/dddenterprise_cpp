#pragma once

#include <stdexcept>
#include <string>

namespace vantage::domain::common {
    using std::runtime_error;
    using std::string;

    class DomainException : public runtime_error {
        public:
            DomainException();
            explicit DomainException(const string& message);
            DomainException(const string& message, const string& context, const string& entity, const string& id);
            virtual ~DomainException() = default;

            string context() const;
            string entity() const;
            string id() const;

        private:
            string _context;
            string _entity;
            string _id;
    };
}