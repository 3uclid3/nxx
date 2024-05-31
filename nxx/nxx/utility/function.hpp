#pragma once

#include <nxx/debug/assert.hpp>
#include <nxx/def.hpp>
#include <nxx/memory/unique-ptr.hpp>
#include <nxx/utility/forward.hpp>
#include <nxx/utility/move.hpp>

namespace nxx {

template<typename>
class function;

template<typename, size_t>
class inplace_function; // TODO

template<typename ReturnT, class... ArgumentsT>
class function<ReturnT(ArgumentsT...)>
{
public:
    function() = default;
    function(const function& other);
    function(function&& other);

    template<typename F>
    function(F&& f);

    function& operator=(const function& other);
    function& operator=(function&& other);

    operator bool() const;
    ReturnT operator()(ArgumentsT... args) const;

private:
    struct interface
    {
        virtual ~interface() = default;
        virtual ReturnT invoke(ArgumentsT... args) const = 0;
        virtual interface* clone() const = 0;
    };

    template<typename F>
    struct implementation : interface
    {
        implementation(F&& f);

        ReturnT invoke(ArgumentsT... args) const override;
        interface* clone() const override;

        F _f;
    };

private:
    unique_ptr<interface> _impl;
};

template<typename ReturnT, class... ArgumentsT>
template<typename F>
function<ReturnT(ArgumentsT...)>::implementation<F>::implementation(F&& func)
    : _f(forward<F>(func))
{
}

template<typename ReturnT, class... ArgumentsT>
template<typename F>
ReturnT function<ReturnT(ArgumentsT...)>::implementation<F>::invoke(ArgumentsT... args) const
{
    return _f(args...);
}

template<typename ReturnT, class... ArgumentsT>
template<typename F>
function<ReturnT(ArgumentsT...)>::interface* function<ReturnT(ArgumentsT...)>::implementation<F>::clone() const
{
    return new implementation<F>(*this);
}

template<typename ReturnT, class... ArgumentsT>
function<ReturnT(ArgumentsT...)>::function(const function& other)
    : _impl(other.clone())
{
}

template<typename ReturnT, class... ArgumentsT>
function<ReturnT(ArgumentsT...)>::function(function&& other)
    : _impl(move(other.impl))
{
}

template<typename ReturnT, class... ArgumentsT>
template<typename F>
function<ReturnT(ArgumentsT...)>::function(F&& f)
    : _impl(make_unique<implementation<F>>(move(f)))
{
}

template<typename ReturnT, class... ArgumentsT>
function<ReturnT(ArgumentsT...)>& function<ReturnT(ArgumentsT...)>::operator=(const function& other)
{
    _impl = unique_ptr<interface>{other.clone()};
    return *this;
}

template<typename ReturnT, class... ArgumentsT>
function<ReturnT(ArgumentsT...)>& function<ReturnT(ArgumentsT...)>::operator=(function&& other)
{
    _impl = move(other._impl);
    return *this;
}

template<typename ReturnT, class... ArgumentsT>
function<ReturnT(ArgumentsT...)>::operator bool() const
{
    return _impl;
}

template<typename ReturnT, class... ArgumentsT>
ReturnT function<ReturnT(ArgumentsT...)>::operator()(ArgumentsT... args) const
{
    NXX_ASSERT(_impl);
    return _impl->invoke(forward<ArgumentsT>(args)...);
}

} // namespace nxx