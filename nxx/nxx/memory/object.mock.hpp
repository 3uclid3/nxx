#pragma once

namespace nxx::mock {

template<typename ConcreteT>
struct base_object
{
    bool ctor_default : 1 {false};
    bool ctor_copy : 1 {false};
    bool ctor_move : 1 {false};
    bool otor_copy : 1 {false};
    bool otor_move : 1 {false};

    inline static void reset_counts()
    {
        ctor_count = 0;
        dtor_count = 0;
        move_count = 0;
        copy_count = 0;
    }

    inline static int ctor_count = 0;
    inline static int dtor_count = 0;
    inline static int move_count = 0;
    inline static int copy_count = 0;
};

struct object : base_object<object>
{
    object()
    {
        ctor_default = true;

        ++ctor_count;
    }

    explicit object(int initialValue)
        : value(initialValue)
        , ctorInt(true)
    {
        ++ctor_count;
    }

    object(const object& other)
        : value(other.value)
    {
        ctor_copy = true;
        ++ctor_count;
        ++copy_count;
    }

    object(object&& other)
        : value(other.value)
    {
        ctor_move = true;
        ++ctor_count;
        ++move_count;
    }

    ~object()
    {
        ++dtor_count;
    }

    object& operator=(const object& other)
    {
        value = other.value;
        otor_copy = true;
        ++copy_count;
        return *this;
    }

    object& operator=(object&& other)
    {
        value = other.value;
        otor_move = true;
        ++move_count;
        return *this;
    }

    bool operator==(const object& other) const
    {
        return value == other.value;
    }

    int value{-1};
    bool ctorInt : 1 {false};
};

struct copy_only_object : base_object<copy_only_object>
{
    constexpr copy_only_object() = default;
    constexpr copy_only_object(int initialValue)
        : value(initialValue)
    {
        ctorInt = true;
    }

    constexpr copy_only_object(const copy_only_object& other)
        : value(other.value)
    {
        ctor_copy = true;
    }

    ~copy_only_object()
    {
        ++dtor_count;
    }

    constexpr copy_only_object(copy_only_object&& other) = delete;

    constexpr copy_only_object& operator=(const copy_only_object& other)
    {
        value = other.value;
        operatorCopy = true;
        return *this;
    }

    constexpr copy_only_object& operator=(copy_only_object&& other) = delete;

    int value{-1};
    bool ctorInt : 1 {false};
    bool ctor_copy : 1 {false};
    bool operatorCopy : 1 {false};

    inline static int dtor_count = 0;
};

struct move_only_object : base_object<copy_only_object>
{
    constexpr move_only_object() = default;
    constexpr move_only_object(int initialValue)
        : value(initialValue)
    {
        ctorInt = true;
    }

    constexpr move_only_object(const move_only_object& other) = delete;

    constexpr move_only_object(move_only_object&& other)
        : value(other.value)
    {
        ctor_move = true;
    }

    ~move_only_object()
    {
        ++dtor_count;
    }

    constexpr move_only_object& operator=(const move_only_object& other) = delete;

    constexpr move_only_object& operator=(move_only_object&& other)
    {
        value = other.value;
        operatorMove = true;
        return *this;
    }

    int value{-1};
    bool ctorInt : 1 {false};
    bool ctor_move : 1 {false};
    bool operatorMove : 1 {false};

    inline static int dtor_count = 0;
};

struct trivial_object
{
    int value{0};
};

struct object_fixture
{
    object_fixture()
    {
        object::reset_counts();
        copy_only_object::reset_counts();
        move_only_object::reset_counts();
    }

    virtual ~object_fixture()
    {
        object::reset_counts();
        copy_only_object::reset_counts();
        move_only_object::reset_counts();
    }
};

} // namespace nxx::mock
