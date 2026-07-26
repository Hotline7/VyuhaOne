#include "vyuhaone/version.hpp"
#include <string_view>

namespace vyuhaone
{
    std::string_view version()
    {
        return VYUHAONE_ENGINE_VERSION;
    }
}