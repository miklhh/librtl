#include "src/component.h"
#include "src/netlist.h"

#include <absl/container/flat_hash_map.h>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include <string>


TEST_CASE("Basic gate test")
{
    rtl::Netlist netlist;
    rtl::ComponentHandle and2_1 = netlist.component_emplace(rtl::make_and2());
    rtl::ComponentHandle and2_2 = netlist.component_emplace(rtl::make_and2());

    auto abc = rtl::make_and2();

    netlist.wire_add(and2_1.in(0), and2_2.out(0));


    std::cout << netlist.pretty_str() << std::endl;



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
