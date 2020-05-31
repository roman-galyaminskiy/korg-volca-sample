#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

class Component
{
private:
  virtual void changed(uint8_t *event, uint8_t size) = 0;
};

class Mediator
{
public:
  virtual void notify(Component *component, uint8_t *event, uint8_t size) = 0;
};

#endif // MEDIATOR_HPP
