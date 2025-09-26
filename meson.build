project('librtl', 'cpp',
  default_options: ['cpp_std=c++17',
                    'b_lto=true',
                    'b_ndebug=if-release',
                    'warning_level=2', ]
)

json = subproject('json')
json_dep = json.get_variable('nlohmann_json_dep')
absl_dep = dependency('absl_container')
catch2_with_main_dep = dependency('catch2-with-main')
fmt = subproject('fmt', default_options: ['header-only=true'])
fmt_dep = fmt.get_variable('fmt_header_only_dep')

executable('librtl-test', sources: files(
    'test/netlist.cc',
  ),
  dependencies: [absl_dep, catch2_with_main_dep, fmt_dep, json_dep]
)
