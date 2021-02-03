#include "Blaze.h"
#include <spdlog/spdlog.h>

void Blaze::Setup() {
    spdlog::info("Setting up BlazeEngine");
    spdlog::set_level(spdlog::level::debug);

#ifndef NDEBUG
#endif
}
