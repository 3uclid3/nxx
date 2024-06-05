
catch2 = subproject('catch2', default_options:['tests=false', 'warning_level=1', 'werror=false'])
catch2_dep = catch2.get_variable('catch2_with_main_dep')

tests = []
subdir('nxx')

nxx_test = executable(
    'nxx.test',
    tests,
    install : false,
    dependencies : [catch2_dep, nxx_dep],
    c_args : [macros],
    cpp_args : [macros]
)

test('nxx', nxx_test)