#include <absl/container/flat_hash_map.h>
#include <fmt/format.h>

#include <iostream>
#include <string>


int main()
{
    absl::flat_hash_map<int, std::string> map{ 
        { 1, "abc123" },
        { 2, "hello" },
        { 1337, "elite" },
    };
    for (auto [key, val] : map) {
        std::cout << fmt::format("key: {}, val: {}", key, val) << std::endl;
    }
    std::cout << "Hello world!" << std::endl;
    return 0;
}
