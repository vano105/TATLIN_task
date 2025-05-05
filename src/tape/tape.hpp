#pragma once

class tape {
public:
  virtual void move_left() = 0;
  virtual void move_right() = 0;
  virtual int read_number() = 0;
  virtual void write_number(int value) = 0;
  virtual void move_to_start() = 0;
  virtual void move_to_end() = 0;
  virtual bool is_at_end() = 0;
  virtual ~tape() = default;
};
