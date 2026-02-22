#ifndef TBGE_COMPONENTS_LCOKED_MODEL_H_
#define TBGE_COMPONENTS_LCOKED_MODEL_H_

#include <string>

class LockComponent {
 public:
  void set_locked_description(std::string locked_description) {
    locked_description_ = locked_description;
  }
  std::string get_locked_description() { return locked_description_; }

  bool is_locked() { return is_locked_; }
  void toggle_locked() { is_locked_ = !is_locked_; }
  void lock() { is_locked_ = true; }
  void unlcok() { is_locked_ = false; }

 private:
  std::string locked_description_;
  bool is_locked_;
};

#endif  // TBGE_COMPONENTS_LCOKED_MODEL_H_