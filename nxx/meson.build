sources = []

subdir('nxx')

nxx = static_library(
    'nxx',
    sources,
    install: false,
    dependencies: [dependency('ntl')],
    c_args: ['-ffreestanding', sanitizers, macros],
    cpp_args: ['-ffreestanding', sanitizers, macros],
    include_directories: ['.'],
)

nxx_dep = declare_dependency(
    link_with: nxx,
    dependencies: [dependency('ntl')],
    sources: sources,
    include_directories: ['.'],
)