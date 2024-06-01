project(
    'nxx', ['cpp'],
    version : 'v0.1',
    license: 'GPL-3.0',
    default_options : [
        'cpp_std=c++2a',
        'default_library=static',
        'warning_level=2',
        'werror=true',
        'cpp_eh=none',
        'cpp_rtti=false'
    ]
)

sources = files(
    'nxx/nxx/string/format.cpp'
)

opt_asan = get_option('asan')
opt_ubsan = get_option('ubsan')
opt_build_tests = get_option('build_tests')

asan = opt_asan.enabled() 
if opt_asan.auto()
	asan = not meson.is_subproject()
endif

ubsan = opt_ubsan.enabled()
if opt_ubsan.auto()
	ubsan = not meson.is_subproject()
endif

build_tests = opt_build_tests.enabled()
if opt_build_tests.auto()
	build_tests = not meson.is_subproject()
endif

sanitizers = []
if asan
    sanitizers += ['address']
endif
if ubsan
    sanitizers += ['undefined']
endif
if sanitizers.length() > 0
    sanitizers = '-fsanitize=' + ','.join(sanitizers)
endif

macros = []
if build_tests
    macros += ['-DNXX_NO_DECLARE_NEW_OPERATOR']
endif


nxx = static_library(
    'nxx',
    sources,
    install : false,
    include_directories : ['nxx'],
    c_args : ['-ffreestanding', sanitizers, macros],
    cpp_args : ['-ffreestanding', sanitizers, macros]
)

nxx_dep  = declare_dependency(
   link_with : nxx,
   sources : sources,
   include_directories : ['nxx']
)

if build_tests
    catch2 = subproject('catch2', default_options:['tests=false', 'warning_level=1', 'werror=false'])
    catch2_dep = catch2.get_variable('catch2_with_main_dep')

    tests = files(
        # utility
        'nxx/nxx/debug/assert_test_impl.cpp',
        'nxx/nxx/memory/alloc_test_impl.cpp',
        'nxx/nxx/memory/new_test_impl.cpp',

        # tests
        'nxx/nxx/algorithm/all_of.test.cpp',
        'nxx/nxx/algorithm/all.test.cpp',
        'nxx/nxx/algorithm/any_of.test.cpp',
        'nxx/nxx/algorithm/any.test.cpp',
        'nxx/nxx/algorithm/clamp.test.cpp',
        'nxx/nxx/algorithm/find_if.test.cpp',
        'nxx/nxx/algorithm/find.test.cpp',
        'nxx/nxx/algorithm/max.test.cpp',
        'nxx/nxx/algorithm/min.test.cpp',
        'nxx/nxx/algorithm/none_of.test.cpp',
        'nxx/nxx/algorithm/none.test.cpp',
        'nxx/nxx/debug/assert.test.cpp',
        'nxx/nxx/container/span.test.cpp',
        'nxx/nxx/container/static_array.test.cpp',
        'nxx/nxx/memory/allocator/fallback_allocator.test.cpp',
        'nxx/nxx/memory/allocator/null_allocator.test.cpp',
        'nxx/nxx/memory/allocator/stack_allocator.test.cpp',
        'nxx/nxx/memory/construct_at.test.cpp',
        'nxx/nxx/memory/memory_block.test.cpp',
        'nxx/nxx/memory/unique_ptr.test.cpp',
        'nxx/nxx/string/format_to.test.cpp',
        'nxx/nxx/string/format.test.cpp',
        'nxx/nxx/string/string_view.test.cpp',
        'nxx/nxx/string/to_string_view.test.cpp',
        'nxx/nxx/type_trait/add_const_volatile.test.cpp',
        'nxx/nxx/type_trait/add_const.test.cpp',
        'nxx/nxx/type_trait/add_lvalue_reference.test.cpp',
        'nxx/nxx/type_trait/add_pointer.test.cpp',
        'nxx/nxx/type_trait/add_rvalue_reference.test.cpp',
        'nxx/nxx/type_trait/add_volatile.test.cpp',
        'nxx/nxx/type_trait/bits_of.test.cpp',
        'nxx/nxx/type_trait/conditional.test.cpp',
        'nxx/nxx/type_trait/decay.test.cpp',
        'nxx/nxx/type_trait/integral_constant.test.cpp',
        'nxx/nxx/type_trait/is_arithmetic.test.cpp',
        'nxx/nxx/type_trait/is_base_of.test.cpp',
        'nxx/nxx/type_trait/is_const.test.cpp',
        'nxx/nxx/type_trait/is_floating_point.test.cpp',
        'nxx/nxx/type_trait/is_integral.test.cpp',
        'nxx/nxx/type_trait/is_enum_class.test.cpp',
        'nxx/nxx/type_trait/is_enum.test.cpp',
        'nxx/nxx/type_trait/is_same.test.cpp',
        'nxx/nxx/type_trait/is_signed_integer.test.cpp',
        'nxx/nxx/type_trait/is_signed.test.cpp',
        'nxx/nxx/type_trait/is_static_array.test.cpp',
        'nxx/nxx/type_trait/remove_const_volatile.test.cpp',
        'nxx/nxx/type_trait/remove_const.test.cpp',
        'nxx/nxx/type_trait/remove_pointer.test.cpp',
        'nxx/nxx/type_trait/remove_reference.test.cpp',
        'nxx/nxx/type_trait/remove_volatile.test.cpp',
        'nxx/nxx/utility/integer_sequence.test.cpp',
        'nxx/nxx/utility/function.test.cpp',
        'nxx/nxx/utility/on_scope_exit.test.cpp',
        'nxx/nxx/utility/ref_wrap.test.cpp',
        'nxx/nxx/utility/source_location.test.cpp',
        'nxx/nxx/utility/swap.test.cpp',
        'nxx/nxx/utility/to_underlying.test.cpp',
        'nxx/nxx/def.test.cpp'
    )

    nxx_test = executable(
        'nxx.test',
        tests,
        install : false,
        dependencies : [catch2_dep, nxx_dep],
        c_args : [macros],
        cpp_args : [macros]
    )

    test('nxx', nxx_test)
endif
