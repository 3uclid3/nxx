project(
    'nxx', ['cpp'],
    version : 'v0.1',
    license: 'GPL-3.0',
    default_options : [
        'cpp_std=c++23',
        'default_library=static',
        'warning_level=2',
        'werror=true',
        'cpp_eh=none',
        'cpp_rtti=false'
    ]
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

nxx = []
nxx_dep = []

subdir('nxx')

if build_tests
    subdir('tests')
endif
