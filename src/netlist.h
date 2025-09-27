#ifndef _LIBRTL_NETLIST_H
#define _LIBRTL_NETLIST_H

#include "librtl-util.h"
#include "component.h"

#include <vector>


LIBRTL_NAMESPACE_BEGIN(rtl)

// Endpoint of a wire
struct WireHandle {
    Component* component;
    unsigned idx;
};

static WireHandle wire_handle(Component* component, unsigned idx)
{
    return WireHandle{ .component = component, .idx = idx };
}

// Wires within a netlist
struct Wire {
    WireHandle src, dst;
};

class Netlist {
public: 
    std::vector<Component> components;
    std::vector<Wire> wires;

    // Serialize to JSON format
    void serialize_json() const;
};

LIBRTL_NAMESPACE_END(rtl)
#endif
