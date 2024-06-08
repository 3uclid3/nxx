project(
    'nxx', ['cpp'],
    version : '0.1.0',
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
tests = get_option('tests')

asan = opt_asan.enabled() 
if opt_asan.auto()
	asan = tests
endif

ubsan = opt_ubsan.enabled()
if opt_ubsan.auto()
	ubsan = tests
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

nxx = []
nxx_dep = []

subdir('nxx')

if tests
    subdir('tests')
endif
