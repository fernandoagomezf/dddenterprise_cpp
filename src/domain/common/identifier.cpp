#include <random>
#include <sstream>
#include <iomanip>
#include "domain/common/identifier.hpp"

using std::array;
using std::hex;
using std::mt19937;
using std::ostringstream;
using std::random_device;
using std::setfill;
using std::setw;
using std::string;
using std::uniform_int_distribution;

using vantage::domain::common::Identifier;

Identifier::Identifier() 
    : _value(createUUID()) {
}

Identifier Identifier::createNew() {
    Identifier result {};
    return result;
}

array<uint8_t, 16> Identifier::createUUID() {
    static random_device random;
    static mt19937 generator(random());
    static uniform_int_distribution<uint32_t> distribution(0, 0xFFFFFFFF);

    array<uint8_t, 16> uuid;
    for (size_t i = 0; i < 16; i += 4) {
        uint32_t part = distribution(generator);
        uuid[i]     = static_cast<uint8_t>((part >> 24) & 0xFF);
        uuid[i + 1] = static_cast<uint8_t>((part >> 16) & 0xFF);
        uuid[i + 2] = static_cast<uint8_t>((part >> 8) & 0xFF);
        uuid[i + 3] = static_cast<uint8_t>(part & 0xFF);
    }
    
    uuid[6] = (uuid[6] & 0x0F) | 0x40;
    uuid[8] = (uuid[8] & 0x3F) | 0x80;

    return uuid;
}

bool Identifier::equals(const ValueObject& other) const {
    const auto* o = dynamic_cast<const Identifier*>(&other);
    return o && _value == o->_value;
}

size_t Identifier::hashCode() const  {
    size_t hash = 0;
    for (auto b : _value) {
        hash = (hash * 31) ^ b;
    }
    return hash;
}

string Identifier::toString() const {
    ostringstream oss;
    oss << hex << setfill('0');
    for (size_t i = 0; i < _value.size(); ++i) {
        oss << setw(2) << static_cast<int>(_value[i]);
        if (i == 3 || i == 5 || i == 7 || i == 9)
            oss << "-";
    }
    return oss.str();
}