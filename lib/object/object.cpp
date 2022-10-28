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
  AssignId();
  if (name.size() > 0) {
    name_ = name;
    return;
  }
  name_ = GetClassName() + "_" + std::to_string(id_);
}

bool Object::operator== (const Object& rhs) {
  if (name_ != rhs.name_) return false;
  return true;
}

int Object::GetId() {
  return id_;
}

std::string Object::GetClassName() {
  return "Object";
}

std::string Object::GetName() {
  return name_;
}

/**
 * @brief Returns the full name of the object, which is on the format
 *        @c [parent.full_name].[this.name] @n
 *        @note An object of type tbge::Object cannot have a parent thus
 *        GetFullName just returns the name, this is intended to be overridden
 *        in sub-classes
 */
std::string Object::GetFullName() {
  return GetName();
}

/**
 * @return @c this to allow for method-chaining
 */
Object& Object::SetName(std::string name) {
  if (name.size() > 0) {
    name_ = name;
    return *this;
  }
  name_ = GetClassName() + "_" + std::to_string(id_);
  return *this;
}

Object& Object::SetId(int id) {
  id_ = id;
  return *this;
}

int Object::AssignId() {
  static int id_counter = 0;
  id_ = id_counter++;
  return id_counter;
}

}  // namespace tbge
