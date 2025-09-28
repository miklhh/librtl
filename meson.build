project('librtl', 'cpp',
  default_options: [
    'cpp_std=c++23',
    'b_lto=true',
    'b_ndebug=if-release',
    'warning_level=2',
  ]
)

fmt = subproject('fmt', default_options: ['header-only=true'])
json = subproject('json')

absl_dep = dependency('absl_container')
catch2_with_main_dep = dependency('catch2-with-main')
fmt_dep = fmt.get_variable('fmt_header_only_dep')
json_dep = json.get_variable('nlohmann_json_dep')
magic_enum_dep = dependency('magic_enum')

executable('librtl-test', sources: files(
    'src/netlist.cc',
    'test/netlist.cc',
  ),
  dependencies: [
    absl_dep,
    catch2_with_main_dep,
    fmt_dep,
    json_dep,
    magic_enum_dep,
  ]
)
