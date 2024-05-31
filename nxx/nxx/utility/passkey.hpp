#pragma once

namespace nxx {

template<typename T>
class pass_key
{
private:
    friend T;

    // Avoid = default to disallow creation by uniform initialization.
    pass_key()
    {}
};

} // namespace nxx
