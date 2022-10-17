/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include <iostream>
#include <string>

#include "lib/object/object.h"

namespace tbge {

/**
 * @brief Default constructor
*/
Object::Object() : Object("") {}

/**
 * @brief Name constructor
*/
Object::Object(std::string name) {
  assignId();
  if (name.size() > 0) {
    name_ = name;
    return;
  }
  name_ = get_class_name() + "_" + std::to_string(id_);
}

int Object::get_id() {
  return id_;
}

std::string Object::get_class_name() {
  return "Object";
}

std::string Object::get_name() {
  return name_;
}

/**
 * @brief Returns the full name of the object, which is on the format
 *        @c [parent.full_name].[this.name] @n
 *        NOTE: an object of type tbge::Object cannot have a parent thus
 *        get_full_name just returns the name, this is intended to be overridden
 *        in sub-classes
 */
std::string Object::get_full_name() {
  return get_name();
}

/**
 * @return @c this to allow for method-chaining
 */
Object& Object::set_name(std::string name) {
  if(name.size() > 0) {
    name_ = name;
    return *this;
  }
  name_ = name_ = get_class_name() + "_" + std::to_string(id_);
  return *this;
}

int Object::assignId() {
  static int id_counter = -1;
  id_counter++;
  id_ = id_counter;
  return id_counter;
}

}  // namespace tbge