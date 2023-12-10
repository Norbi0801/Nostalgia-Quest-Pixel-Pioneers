#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fmt/format.h>

namespace Utils {
    inline std::string GetWorkingDirectory() {
        std::filesystem::path workingDir = std::filesystem::current_path();
        char preferred_separator = std::filesystem::path::preferred_separator;
        return fmt::format("{}{}", workingDir.string(), preferred_separator);
    }
}
