#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/Snake.h"

class Controller {
 public:
  void HandleInput(Snake &snake, bool &running) const;
};

#endif