/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */


#ifndef TBGE_LIB_OBJECT_OBJECT_H_
#define TBGE_LIB_OBJECT_OBJECT_H_

#include <string>
namespace tbge
{

class Object {
 public:
  Object();

  int get_id();

  std::string get_class_name();
  std::string get_name();
  virtual std::string get_full_name();

  Object& set_name(std::string);

 private:
  virtual int assignId();

  int id_;
  const std::string class_name_ = "Object";
  std::string name_;
};

} // namespace tbge

#endif  // TBGE_LIB_OBJECT_OBJECT_H_