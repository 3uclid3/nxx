#pragma once

#include <nxx/type_trait/decay.hpp>
#include <nxx/utility/forward.hpp>
#include <nxx/utility/move.hpp>

namespace nxx {

template<typename FunctorT>
[[nodiscard]] constexpr decltype(auto) make_on_scope_exit(FunctorT&& functor);

template<typename OnExitFunctorT>
class on_scope_exit
{
public:
    template<typename FunctorT>
    constexpr on_scope_exit(FunctorT&& functor);
    constexpr on_scope_exit(on_scope_exit&& other);
    constexpr ~on_scope_exit();

    constexpr on_scope_exit(const on_scope_exit&) = delete;

    constexpr void release();

private:
    OnExitFunctorT _exit_functor;
    bool _released{false};
};

template<typename FunctorT>
constexpr decltype(auto) make_on_scope_exit(FunctorT&& functor)
{
    return on_scope_exit<decay<FunctorT>>(forward<FunctorT>(functor));
}

template<typename OnExitFunctorT>
constexpr on_scope_exit<OnExitFunctorT>::on_scope_exit(on_scope_exit&& other)
    : _exit_functor(move(other._exit_functor))
{
    other.release();
}

template<typename OnExitFunctorT>
template<typename FunctorT>
constexpr on_scope_exit<OnExitFunctorT>::on_scope_exit(FunctorT&& functor)
    : _exit_functor(forward<FunctorT>(functor))
{
}

template<typename OnExitFunctorT>
constexpr on_scope_exit<OnExitFunctorT>::~on_scope_exit()
{
    if (!_released)
    {
        _exit_functor();
    }
}

template<typename OnExitFunctorT>
constexpr void on_scope_exit<OnExitFunctorT>::release()
{
    _released = true;
}

} // namespace nxx
