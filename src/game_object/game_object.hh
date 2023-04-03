//  _________ __    _______ ______ _____  
// |  _   _  |_ \  |_   __ \   __ \ __  | 
// |_/ | | \_|_) |   | |__) | |__) |  \_| 
//     | | |  __'.   |  __ /|  ___/  ____ 
//    _| |_| |__) | _| |  \ \_|\ '.___]  |
//   |_____|_____/ |____| |___||'._____.' 
//																				 

#include <vector>

namespace tbge{
class GameObject {
 public:
  // Constructors
  /// @brief Constructor for a GameObject that only automatically sets id_
  GameObject();

  //Accessors
  /// @brief Get the unique ID of the GameObject
  /// @return The unique ID of the GameObject
  int get_id();

  void set_parent(GameObject*);
  GameObject* get_parent();

  bool has_child(GameObject *);
  void set_children(std::vector<GameObject*>);
  void add_child(GameObject*);
  void remove_child(GameObject*);
  void remove_child_by_index(int);
  void remove_child_by_id(int);
  void remove_child_by_name(int);
  std::vector<GameObject*> get_children();
  GameObject* get_child_by_index(int);
  GameObject* get_child_by_id(int);
  GameObject* get_child_by_name(int);
  
 protected:
  /// @brief Generates a unique ID for every GameObject
  void set_id();

 private:
  int id_;
  GameObject* parent_;
  std::vector<GameObject*> children_;
};
};