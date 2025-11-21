#pragma once

#include <array>
#include <string_view>

namespace order_rules {
    inline constexpr std::array<std::string_view, 5> kAllowedOrderTypes = {
        "Wedding",
        "Portrait",
        "Event",
        "Product",
        "Studio"
    };
}

