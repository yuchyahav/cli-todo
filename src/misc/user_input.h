#pragma once

#include <string>

namespace todo {
struct UserInput {
  std::string text;  ///< User's raw string input.
  bool vi_mode;      ///< Flag for differentiating ViView input.
};
}  // namespace todo
