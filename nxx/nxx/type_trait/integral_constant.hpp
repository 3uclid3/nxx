#pragma once

namespace nxx {

template<typename T, T ValueT>
struct integral_constant
{
    using value_type = T;

    static constexpr value_type value = ValueT;

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template<bool ValueT>
struct bool_constant : public integral_constant<bool, ValueT>
{};

struct false_type : public bool_constant<false>
{};

struct true_type : public bool_constant<true>
{};

} // namespace nxx
