#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "file_tape.hpp"

file_tape::file_tape(const std::string &file_name, const class config &config)
    : file_name(file_name), config(config), current_pos(0) {
  file.open(file_name, std::ios::in | std::ios::out);
  if (!file) {
    file.open(file_name, std::ios::out);
    file.close();
    file.open(file_name, std::ios::in | std::ios::out);
    if (!file) {
      std::cerr << "Failed to create file: " << file_name << '\n';
      return;
    }
  }
}

file_tape::~file_tape() { file.close(); }

int file_tape::read_number() {
  delay(config.read_delay);
  file.seekg(current_pos);
  int value;
  file >> value;
  return value;
}

void file_tape::write_number(int value) {
  delay(config.write_delay);
  file.seekp(current_pos);
  file << value << " ";
  file.flush();
}

void file_tape::move_left() {
  delay(config.shift_delay);
  file.seekg(-1 * sizeof(int), std::ios::cur);
  current_pos = file.tellg();
}

void file_tape::move_right() {
  delay(config.shift_delay);
  file.seekg(sizeof(int), std::ios::cur);
  current_pos = file.tellg();
}

void file_tape::move_to_start() {
  size_t steps = current_pos / sizeof(int);
  size_t delay_per_position =
      static_cast<size_t>(steps * config.rewind_delay_per_position);
  delay(delay_per_position);
  file.seekg(0);
  current_pos = 0;
}

void file_tape::move_to_end() {
  file.seekg(0, std::ios::end);
  size_t steps = (file.tellg() - current_pos) / sizeof(int);
  size_t delay_per_position =
      static_cast<size_t>(steps * config.rewind_delay_per_position);
  delay(delay_per_position);
  current_pos = file.tellg();
}

bool file_tape::is_at_end() { return file.eof(); }

void file_tape::delay(size_t delay) const {
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}
