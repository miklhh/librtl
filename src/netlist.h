#ifndef _LIBRTL_NETLIST_H
#define _LIBRTL_NETLIST_H

#include "component.h"
#include "librtl-util.h"

#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <fmt/format.h>

#include <atomic>
#include <cstdlib>
#include <unordered_map>
#include <utility>

NAMESPACE_BEGIN(rtl)

struct Wire {
    ComponentOutputHandle src;
    ComponentInputHandle dst;

    bool operator==(const Wire& rhs) const noexcept
    {
        return std::make_tuple(src, dst) == std::make_tuple(rhs.src, rhs.dst);
    }
};

NAMESPACE_END(rtl)

NAMESPACE_BEGIN(std)

template <> struct hash<rtl::Wire> {
    std::size_t operator()(const rtl::Wire& wire)
    {
        auto&& tuple = std::make_tuple(
            wire.src.handle_raw, wire.src.idx, wire.dst.handle_raw, wire.dst.idx
        );
        return rtl::detail::hash_tuple(tuple);
    }
};

NAMESPACE_END(std)

NAMESPACE_BEGIN(rtl)

// Node centric (component centric) netlist
class Netlist {
public:
    // Emplace a component into this netlist
    template <typename COMPONENT_T> ComponentHandle component_emplace(COMPONENT_T&& c)
    {
        components.emplace(next_raw_handle, std::forward<COMPONENT_T>(c));
        return ComponentHandle { next_raw_handle++ };
    }

    void wire_add(ComponentOutputHandle src, ComponentInputHandle dst)
    {
        assert(components.find(src.handle_raw) != components.end());
        assert(components.find(dst.handle_raw) != components.end());
        wires[src.handle_raw].insert(Wire { src, dst });
    }

    void wire_add(ComponentInputHandle dst, ComponentOutputHandle src)
    {
        wire_add(src, dst);
    }

    // Debug print
    std::string pretty_str() const;

    Component& operator[](ComponentHandle handle)
    {
        return components.at(handle.handle_raw);
    }

    const Component& operator[](ComponentHandle handle) const
    {
        return components.at(handle.handle_raw);
    }

private:
    std::atomic<ComponentHandleRaw> next_raw_handle { 1 /* zero reserved for none */ };
    std::unordered_map<ComponentHandleRaw, Component> components {};
    absl::flat_hash_map<ComponentHandleRaw, absl::flat_hash_set<Wire>> wires;
};

NAMESPACE_END(rtl)

#endif
