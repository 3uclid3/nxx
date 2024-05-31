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

nxx = static_library(
    'nxx',
    sources,
    install : false,
    include_directories : ['nxx'],
    c_args : ['-ffreestanding', sanitizers],
    cpp_args : ['-ffreestanding', sanitizers]
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
        'nxx/nxx/debug/assert-test-impl.cpp',
        'nxx/nxx/memory/alloc-test-impl.cpp',
        'nxx/nxx/memory/new-test-impl.cpp',

        # tests
        'nxx/nxx/algorithm/min.test.cpp',
        'nxx/nxx/debug/assert.test.cpp',
        'nxx/nxx/container/span.test.cpp',
        'nxx/nxx/container/static-array.test.cpp',
        'nxx/nxx/memory/allocator/fallback-allocator.test.cpp',
        'nxx/nxx/memory/allocator/null-allocator.test.cpp',
        'nxx/nxx/memory/allocator/stack-allocator.test.cpp',
        'nxx/nxx/memory/memory-block.test.cpp',
        'nxx/nxx/string/format-to.test.cpp',
        'nxx/nxx/string/format.test.cpp',
        'nxx/nxx/string/string-view.test.cpp',
        'nxx/nxx/string/to-string-view.test.cpp',
        'nxx/nxx/type-trait/add-const-volatile.test.cpp',
        'nxx/nxx/type-trait/add-const.test.cpp',
        'nxx/nxx/type-trait/add-lvalue-reference.test.cpp',
        'nxx/nxx/type-trait/add-pointer.test.cpp',
        'nxx/nxx/type-trait/add-rvalue-reference.test.cpp',
        'nxx/nxx/type-trait/add-volatile.test.cpp',
        'nxx/nxx/type-trait/bits-of.test.cpp',
        'nxx/nxx/type-trait/conditional.test.cpp',
        'nxx/nxx/type-trait/decay.test.cpp',
        'nxx/nxx/type-trait/integral-constant.test.cpp',
        'nxx/nxx/type-trait/is-arithmetic.test.cpp',
        'nxx/nxx/type-trait/is-base-of.test.cpp',
        'nxx/nxx/type-trait/is-const.test.cpp',
        'nxx/nxx/type-trait/is-floating-point.test.cpp',
        'nxx/nxx/type-trait/is-integral.test.cpp',
        'nxx/nxx/type-trait/is-enum-class.test.cpp',
        'nxx/nxx/type-trait/is-enum.test.cpp',
        'nxx/nxx/type-trait/is-same.test.cpp',
        'nxx/nxx/type-trait/is-signed-integer.test.cpp',
        'nxx/nxx/type-trait/is-signed.test.cpp',
        'nxx/nxx/type-trait/remove-const-volatile.test.cpp',
        'nxx/nxx/type-trait/remove-const.test.cpp',
        'nxx/nxx/type-trait/remove-pointer.test.cpp',
        'nxx/nxx/type-trait/remove-reference.test.cpp',
        'nxx/nxx/type-trait/remove-volatile.test.cpp',
        'nxx/nxx/utility/integer-sequence.test.cpp',
        'nxx/nxx/utility/source-location.test.cpp',
        'nxx/nxx/utility/to-underlying.test.cpp',
        'nxx/nxx/def.test.cpp'
    )

    nxx_test = executable(
        'nxx.test',
        tests,
        install : false,
        dependencies : [catch2_dep, nxx_dep]
    )

    test('nxx', nxx_test)
endif