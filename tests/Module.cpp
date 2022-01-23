#include "ziapi/Module.hpp"

#include <gtest/gtest.h>

#include "dylib/dylib.hpp"
#include "ziapi/Logger.hpp"

TEST(Module, example)
{
    try {
        dylib lib("module", dylib::extension);
        auto entry_point_fn = lib.get_function<std::unique_ptr<ziapi::IModule>()>("LoadModule");
        auto module = entry_point_fn();
        ziapi::Logger::Info("Module loaded: " + std::string(module->GetName()) + " - " + module->GetDescription());
    } catch (const dylib::exception &e) {
        ziapi::Logger::Error(e.what());
    }
}