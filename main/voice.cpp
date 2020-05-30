#include "voice.hpp"

Voice::Voice(uint8_t c) : channel(c) {}

uint8_t Voice::get_channel() {
  return channel;
}

uint8_t Voice::get_parameter() {
  return controlled_parameter;
}

uint8_t* Voice::get_parameter_range() {
  uint8_t range[] = {
    controlled_parameter_range_from, controlled_parameter_range_to};
  return range;
}