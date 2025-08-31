#pragma once

namespace vantage::domain::core {
    struct ValueObject {
        ValueObject();
        ValueObject(const ValueObject& other);
        virtual ~ValueObject();
    };
}