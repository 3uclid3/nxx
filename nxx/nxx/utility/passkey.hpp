#pragma once

namespace nxx {

template<typename T>
class passkey
{
private:
    friend T;

    // Avoid = default to disallow creation by uniform initialization.
    passkey()
    {}
};

} // namespace nxx
