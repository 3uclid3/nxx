project(
    'nxx', ['cpp'],
    version : 'v0.1',
    license: 'GPL-3.0',
    default_options : [
        'cpp_std=c++20',
        'warning_level=2',
        'werror=true',
        'cpp_eh=none',
        'cpp_rtti=false'
    ]
)

headers = files(
    'nxx/nxxdef.hpp',
    'nxx/nxxint.hpp'
)

sources = files(
    'nxx/nxx/dummy.cpp'
)

nxx = static_library(
    'nxx',
    sources,
    install : false,
    include_directories : ['nxx'],
)

nxx_dep  = declare_dependency(
   link_with : nxx,
   sources : sources,
   include_directories : ['nxx']
)

build_tests = get_option('build_tests').enabled()

if get_option('build_tests').auto()
	build_tests = not meson.is_subproject()
endif

if build_tests
    catch2 = subproject('catch2', default_options:['werror=false'])
    catch2_dep = dependency('catch2', fallback: ['catch2', 'catch2_with_main_dep'], default_options:['tests=false'])

    sources_test = files(
        'nxx/nxxint.test.cpp'
    )

    nxx_test = executable(
        'nxx.test',
        sources_test,
        install : false,
        dependencies : [catch2_dep, nxx_dep]
    )

    test('nxx', nxx_test)
endif