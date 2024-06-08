sources = []

subdir('nxx')

nxx = static_library(
    'nxx',
    sources,
    install: false,
    c_args: ['-ffreestanding', sanitizers],
    cpp_args: ['-ffreestanding', sanitizers],
    include_directories: ['.'],
)

nxx_dep = declare_dependency(
    link_with: nxx,
    sources: sources,
    include_directories: ['.'],
)