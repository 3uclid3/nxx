

#include <nxx/type_trait/integral_constant.hpp>
#include <nxx/type_trait/is_convertible.hpp>
#include <nxx/type_trait/is_enum.hpp>
#include <nxx/type_trait/underlying_type.hpp>

namespace nxx::impl {

template<typename T, bool = is_enum<T>::value>
struct is_enum_class;

template<typename T>
struct is_enum_class<T, false> : false_type
{};

template<typename T>
struct is_enum_class<T, true> : bool_constant<!is_convertible<T, typename underlying_type<T>::type>::value>
{};

} // namespace nxx::impl

namespace nxx {

template<typename T>
inline constexpr bool is_enum_class = impl::is_enum_class<T>::value;

} // namespace nxx
