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

headers = files(
    'nxx/nxxdef.hpp',
    'nxx/nxxint.hpp'
)

sources = files(
    'nxx/nxx/dummy.cpp'
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
    catch2_dep = dependency('catch2', fallback: ['catch2', 'catch2_with_main_dep'])

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