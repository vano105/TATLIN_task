#include <iostream>

#include "config/config.hpp"
#include "file_tape/file_tape.hpp"
#include "tape_sorter/tape_sorter.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
    return 1;
  }

  config config = config::load_config("../config.txt");
  file_tape input_tape(argv[1], config);
  file_tape output_tape(argv[2], config);

  tape_sorter sorter(input_tape, output_tape, config);
  sorter.sort();

  return 0;
}
