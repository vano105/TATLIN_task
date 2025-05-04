#pragma once

#include <string>

struct config {
public:
  size_t memory_limit = 1024 * 1024;
  size_t read_delay = 0;
  size_t write_delay = 0;
  size_t shift_delay = 0;
  double rewind_delay_per_position = 0.0;

  config load_config(const std::string &file_name);
};
