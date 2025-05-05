#pragma once

#include <chrono>
#include <fstream>
#include <string>

#include "../config/config.hpp"
#include "../tape/tape.hpp"

class file_tape : public tape {
public:
  file_tape(const std::string &file_name, const class config &config);
  ~file_tape();

  void move_left() override;
  void move_right() override;
  int read_number() override;
  void write_number(int value) override;
  void move_to_start() override;
  void move_to_end() override;
  bool is_at_end() override;

private:
  std::fstream file;
  std::string file_name;
  config config;
  std::streampos current_pos;

  void delay(size_t delay) const;
};
