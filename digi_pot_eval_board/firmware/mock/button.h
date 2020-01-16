
#pragma once

#include "../artl/button.h"

namespace pq4 {

struct default_button_time_traits {
    unsigned long bounce() const { return 0; }
    unsigned long hold() const { return 500; }
};


template<typename HANDLERS>
struct button : public artl::button<HANDLERS, default_button_time_traits> {
    using base = artl::button<HANDLERS, default_button_time_traits>;
    using base::base;
};

}
