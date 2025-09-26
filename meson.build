project('librtl', 'cpp',
  default_options: ['cpp_std=c++17',
                    'b_lto=true',
                    'b_ndebug=if-release',
                    'warning_level=2', ]
)

fmt = dependency('fmt', default_options: ['header-only=true'])
absl = dependency('absl_container')

executable('librtl', sources: files(
    'src/main.cc'
  ),
  dependencies: [absl, fmt]
)
