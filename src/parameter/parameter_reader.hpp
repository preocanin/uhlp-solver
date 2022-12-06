#pragma once

#include <string_view>

namespace parameter {
namespace reader {

enum class FileFormat {
    AP,
    CAB
};

bool readParameters(const std::string_view& file_path, FileFormat format);

} // namespace reader
} // namespace parameter