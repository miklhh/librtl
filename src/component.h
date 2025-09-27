#ifndef _LIBRTL_COMPONENTS_H
#define _LIBRTL_COMPONENTS_H

#include "librtl-util.h"

#include <cstddef>

LIBRTL_NAMESPACE_BEGIN(rtl)

enum ComponentTag {
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

struct ComponentInfo {
    ComponentTag tag;
};


struct Component {
    ComponentInfo info;
    unsigned n_inputs;
    unsigned n_outputs;
};


template<ComponentTag TAG, unsigned N_INPUTS, unsigned N_OUTPUTS>
static inline Component make_component()
{
    return Component{
        .info = { .tag = TAG }, .n_inputs = N_INPUTS, .n_outputs = N_OUTPUTS
    };
}

static inline Component make_and2() { return make_component<AND2, 2, 1>(); }
static inline Component make_or2() { return make_component<OR2, 2, 1>(); }

LIBRTL_NAMESPACE_END(rtl)

#endif
