#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "../config/config.hpp"
#include "../tape/tape.hpp"

class tape_sorter {
public:
  tape_sorter(tape &input, tape &output, const class config &config);
  void sort();
  ~tape_sorter() = default;

private:
  tape &input_tape;
  tape &output_tape;
  config config;
  std::vector<std::unique_ptr<tape>> tmp_tapes;

  void split();
  void merge();
  std::unique_ptr<tape> create_tmp_tape();
};
