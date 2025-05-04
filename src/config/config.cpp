#include <fstream>
#include <sstream>

#include "config.hpp"

config load_config(const std::string &file_name) {
  config config;
  std::ifstream file(file_name);
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key;

    if (std::getline(iss, key, '=')) {
      std::string value_str;
      if (std::getline(iss, value_str)) {
        if (key == "memory_limit")
          config.memory_limit = std::stoul(value_str);
        else if (key == "read_delay")
          config.read_delay = std::stoul(value_str);
        else if (key == "write_delay")
          config.write_delay = std::stoul(value_str);
        else if (key == "shift_delay")
          config.shift_delay = std::stoul(value_str);
        else if (key == "rewind_delay_per_position")
          config.rewind_delay_per_position = std::stod(value_str);
      }
    }
  }

  return config;
}
