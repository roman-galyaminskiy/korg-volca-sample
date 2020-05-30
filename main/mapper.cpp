#include "mapper.hpp"

Mapper::Mapper() {
  volca->initialize();   
  controller->start();
  controller->enableExtendedMode();
}

void Mapper::notify() {}

void Mapper::notify(Component* component) {
  if (component == volca) {
    Serial.println("volca");
  }
  else if (component == controller) {
    Serial.println("volca");
  }
}