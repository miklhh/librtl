#ifndef _LIBRTL_NETLIST_H
#define _LIBRTL_NETLIST_H

#include "librtl-util.h"

#include <string>
#include <vector>
#include <optional>


LIBRTL_NAMESPACE_BEGIN(rtl)

struct In { std::optional<std::string> name = std::nullopt; };
struct Out { std::optional<std::string> name = std::nullopt; };

class Node {
    std::vector<In> in;
    std::vector<Out> out;
};

class Net {
public:
    In* dst;
    Out* src;
};

class Netlist {
public: 
    std::vector<Node> nodes;
    std::vector<Net> nets;

    // Serialize to JSON format
    void serialize_json() const {

    }
};

LIBRTL_NAMESPACE_END(rtl)
#endif
