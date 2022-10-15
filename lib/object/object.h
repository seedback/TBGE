/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */


#ifndef TBGE_LIB_OBJECT_OBJECT_H_
#define TBGE_LIB_OBJECT_OBJECT_H_
namespace tbge
{

class Object {
 public:
  Object();

  int getId();

 private:
  int assignId();

  int id_;
};

} // namespace tbge

#endif  // TBGE_LIB_OBJECT_OBJECT_H_