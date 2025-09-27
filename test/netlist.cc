#include "src/component.h"
#include "src/netlist.h"

#include <absl/container/flat_hash_map.h>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include <string>


TEST_CASE("Basic gate test")
{
    auto and2 = rtl::make_and2();
    and2.input_handle(0);
    rtl::Netlist netlist;
    netlist.components.emplace_back(rtl::make_and2());
    netlist.components.emplace_back(rtl::make_or2());

}


TEST_CASE("flat_hash_map")
{
    absl::flat_hash_map<int, std::string> map{ 
        { 1, "abc123" },
        { 2, "hello" },
        { 1337, "elite" },
    };
    REQUIRE(map[1337] == "elite");
}
