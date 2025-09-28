#ifndef _LIBRTL_COMPONENTS_H
#define _LIBRTL_COMPONENTS_H

#include "librtl-util.h"

#include <functional>
#include <tuple>
#include <vector>


NAMESPACE_BEGIN(rtl)

enum ComponentTypeTag {
    BLACKBOX,
    HIERARCHY,

    IN_PORT,
    OUT_PORT,

    AND2,
    INV,
    NAND2,
    NOR2,
    OR2,
};

// Raw handle to an `rtl::Component` in an `rtl::Netlist`. The component handles are
// persistant "pointers" to objects in the netlist.
using ComponentHandleRaw = std::size_t;

// User handle to an input of an `rtl::Component` in an `rtl::Netlist`
struct ComponentInputHandle {
    ComponentHandleRaw handle_raw;
    std::size_t idx;
    bool operator==(const ComponentInputHandle& rhs) const noexcept {
        using std::make_tuple;
        return make_tuple(handle_raw, idx) == make_tuple(rhs.handle_raw, rhs.idx);
    }
};

// User handle to an output of an `rtl::Component` in an `rtl::Netlist`
struct ComponentOutputHandle {
    ComponentHandleRaw handle_raw;
    std::size_t idx;
    bool operator==(const ComponentOutputHandle& rhs) const noexcept {
        using std::make_tuple;
        return make_tuple(handle_raw, idx) == make_tuple(rhs.handle_raw, rhs.idx);
    }
};

// User handle to an `rtl::Component` in an `rtl::Netlist`
struct ComponentHandle {
    ComponentHandleRaw handle_raw;

    ComponentInputHandle in(unsigned i) const noexcept
    {
        return ComponentInputHandle{ .handle_raw = handle_raw, .idx = i };
    }

    ComponentOutputHandle out(unsigned i) const noexcept
    {
        return ComponentOutputHandle{ .handle_raw = handle_raw, .idx = i };
    }

    bool operator==(const ComponentHandle& rhs) const noexcept
    {
        return handle_raw == rhs.handle_raw;
    }
};

struct ComponentInfo {
    ComponentTypeTag tag;
};

struct Component {
    ComponentInfo info;
    std::vector<ComponentOutputHandle> in;
    std::vector<ComponentInputHandle> out;
};


template<ComponentTypeTag TAG, unsigned N_INPUTS, unsigned N_OUTPUTS>
static inline Component make_component()
{
    return Component{
        .info{ .tag = TAG },
        .in{ std::vector<ComponentOutputHandle>(N_INPUTS) },
        .out{ std::vector<ComponentInputHandle>(N_OUTPUTS) },
    };
}

static inline Component make_and2() { return make_component<AND2, 2, 1>(); }
static inline Component make_or2() { return make_component<OR2, 2, 1>(); }

NAMESPACE_END(rtl)

template<>
struct std::hash<rtl::ComponentHandle> {
    std::size_t operator()(const rtl::ComponentHandle& handle) const noexcept {
        return std::hash<std::size_t>()(handle.handle_raw);
    }
};

#endif
