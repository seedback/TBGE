/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include <iostream>

#include "lib/object/object.h"

namespace tbge {

Object::Object() {
  assignId();
}

int Object::assignId() {
  static int id_counter = -1;
  id_counter++;
  id_ = id_counter;
  return id_counter;
}

int Object::getId() {
  return id_;
}

}  // namespace tbge