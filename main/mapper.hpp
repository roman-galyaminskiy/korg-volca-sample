#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "Arduino.h"

#include "mediator.hpp"
#include "definitions.hpp"

class Mapper: public Component {
public:
  Mapper(Mediator *m);  

  void changed(uint8_t *event, uint8_t size);
  void enter();
  void exit();
  void pad_pressed(uint8_t pad_index);
  int8_t get_voice_index(uint8_t pad_index);
private:
  Mediator *mediator;

  uint8_t entered = 0;
  int8_t pad_selected = -1;

  int8_t pad_to_voice_map[16] = {
    -1, 5, 4, 2, 2, 4, 5, -1,
    -1, 0, 2, 1, 1, 2, 0, -1
  };
};

#endif