#ifndef TBGE_GLOBAL_GLOBAL_H_
#define TBGE_GLOBAL_GLOBAL_H_

#include <vector>
#include <string>
#include <map>

namespace tbge {
class GameObject;

namespace global {
class Global {
 public:
  friend class GameObject;
  friend class GameObjectWithCommands;
  
  static Global& getInstance();

  const static std::vector<GameObject*> getGameObjects();
  const static GameObject* getGameObject(int id);
  const static GameObject* getGameObject(const std::string& name);
  const static std::vector<GameObject*> getAllGameObjectsWithName(const std::string& name);
  const static bool hasGameObject(int id);
  const static bool hasGameObject(const std::string& name);
  const static void addCommandWordAlias(const std::string& command, const std::string& alias);
  const static std::map<std::string, std::vector<std::string>> getCommandWordAliases();
  const static std::string getCommandWordFromAlias(const std::string& alias);
  const static void addDescriptorAlias(const std::string& command, const std::string& alias);
  const static std::map<std::string, std::vector<std::string>> getDescriptorAliases();
  const static std::string getDescriptorFromAlias(const std::string& alias);

 protected:
  Global();
  ~Global();

  void static registerGameObject(GameObject* gameObject);
  void static unregisterGameObject(GameObject* gameObject);
  void static clearAliases();

  std::vector<GameObject*> game_objects_;
  std::map<std::string, std::vector<std::string>> command_word_aliases_;
  std::map<std::string, std::vector<std::string>> descriptor_aliases_;

 private:
  Global(const Global&) = delete;
};

}  // namespace global
}  // namespace tbge

#endif  // TBGE_GLOBAL_GLOBAL_H_
