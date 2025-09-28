#include "src/netlist.h"

#include <fmt/format.h>
#include <magic_enum/magic_enum.hpp>

#include <string>

std::string rtl::Netlist::pretty_str() const
{
    std::string str { "Components: \n" };
    for (auto&& [handle, c] : components) {
        std::string_view tag_str = magic_enum::enum_name(c.info.tag);
        str += fmt::format("  * {}\n", tag_str);
    }
    return str;
}
