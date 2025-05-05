#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "../file_tape/file_tape.hpp"
#include "tape_sorter.hpp"

struct MergeElement {
  int value;
  tape *tape;

  bool operator>(const MergeElement &other) const {
    return value > other.value;
  }
};

tape_sorter::tape_sorter(tape &input, tape &output, const class config &config)
    : input_tape(input), output_tape(output), config(config) {}

void tape_sorter::sort() {
  split();
  merge();
}

void tape_sorter::split() {
  size_t block_size = config.memory_limit / sizeof(int);
  if (block_size == 0) {
    return;
  }
  std::vector<int> buffer;

  input_tape.move_to_start();
  while (!input_tape.is_at_end()) {
    buffer.clear();
    for (size_t i = 0; i < block_size && !input_tape.is_at_end(); ++i) {
      buffer.push_back(input_tape.read_number());
      input_tape.move_right();
    }
    std::sort(buffer.begin(), buffer.end());

    auto tmp_tape = create_tmp_tape();
    std::string beb;
    tmp_tape->move_to_start();
    for (int num : buffer) {
      tmp_tape->write_number(num);
      tmp_tape->move_right();
    }
    tmp_tapes.push_back(std::move(tmp_tape));
  }
}

void tape_sorter::merge() {
  std::priority_queue<MergeElement, std::vector<MergeElement>, std::greater<>>
      pq;

  for (auto &tape_ptr : tmp_tapes) {
    tape *tape = tape_ptr.get();
    tape->move_to_start();
    if (!tape->is_at_end()) {
      int value = tape->read_number();
      pq.push({value, tape});
    }
  }

  output_tape.move_to_start();
  while (!pq.empty()) {
    MergeElement elem = pq.top();
    pq.pop();

    output_tape.write_number(elem.value);
    output_tape.move_right();

    elem.tape->move_right();
    if (!elem.tape->is_at_end()) {
      int next_value = elem.tape->read_number();
      pq.push({next_value, elem.tape});
    }
  }
}

std::unique_ptr<tape> tape_sorter::create_tmp_tape() {
  static int counter = 0;
  std::string filename = "../tmp/temp_" + std::to_string(counter++) + ".bin";

  return std::make_unique<file_tape>(filename, config);
}
