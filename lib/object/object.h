/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 * 
 * This is the base class for all classes in the engine.
 * It is not meant to be used by itself, but has been left non-virtual to allow
 * for future unforseen usecases
 */

// NOLINT(build/header_guard)
#ifndef TBGE_LIB_OBJECT_OBJECT_H_
#define TBGE_LIB_OBJECT_OBJECT_H_

#include <string>
namespace tbge {

class Object {
 public:
  Object();
  explicit Object(std::string);

  int get_id();

  std::string get_name();
  virtual std::string get_class_name();
  virtual std::string get_full_name();

  Object& set_name(std::string);

 protected:
  Object& _set_id(int);

 private:
  int assignId();

  int id_ = -1;
  std::string name_;
};

}  // namespace tbge

#endif  // TBGE_LIB_OBJECT_OBJECT_H_
