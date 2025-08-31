#pragma once

#include <stdexcept>
#include <string>

namespace vantage::domain::core {
    using std::runtime_error;
    using std::string;

    class DomainException : public runtime_error {
        public:
            DomainException();
            explicit DomainException(const string& message);
            DomainException(const string& message, const string& context);
            virtual ~DomainException() = default;

            string context() const;

        private:
            string _context;
    };
}