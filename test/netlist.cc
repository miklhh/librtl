#include <absl/container/flat_hash_map.h>
#include <fmt/format.h>
#include <catch2/catch_test_macros.hpp>


#include <iostream>
#include <string>


namespace rtl {
    void haha() {
        std::cout << "HAHA" << std::endl;
    }
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
