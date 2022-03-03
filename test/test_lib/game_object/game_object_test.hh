


#include <vector>

#include "include/gtest/gtest.h"
#include "src/lib/game_object/game_object.hh"

TEST(GameObject, defaultConstructor) {
  tbge::GameObject actual = tbge::GameObject();
  // Testing separate attributes
  EXPECT_EQ(actual.get_class_name(), "GameObject");
  EXPECT_EQ(actual.get_name(), "GameObject_" + std::to_string(actual.get_id()));
  EXPECT_EQ(actual.get_full_name(), "GameObject_" +
            std::to_string(actual.get_id()));
  EXPECT_EQ(actual.get_parent(), nullptr);
  EXPECT_EQ(actual.get_children(), std::vector<tbge::GameObject*>());
}

TEST(GameObject, nameConstructor) {
  // Containting upper- and lower-case and special characters since it should
  // not matter, and to test that everything goes as it should.
  tbge::GameObject actual = tbge::GameObject("Some-Name");
  int id = actual.get_id();

  EXPECT_EQ(actual.get_class_name(), "GameObject");
  EXPECT_EQ(actual.get_name(), "Some-Name");
  EXPECT_EQ(actual.get_full_name(), "Some-Name");
  EXPECT_EQ(actual.get_parent(), nullptr);
  EXPECT_EQ(actual.get_children(), std::vector<tbge::GameObject*>());
}

TEST(GameObject, copyConstructor) {
  int start_num_game_objects =
      tbge::global::GlobalSingleton::get_instance().get_game_objects().size();

  tbge::GameObject first_default = tbge::GameObject();
  tbge::GameObject first_name = tbge::GameObject("Some_Name");
  tbge::GameObject parent = tbge::GameObject();
  tbge::GameObject actual = tbge::GameObject(first_default);

  EXPECT_NE(first_default.get_id(), actual.get_id());
  EXPECT_EQ(first_default.get_class_name(), actual.get_class_name());
  EXPECT_EQ(first_default.get_name(), actual.get_name());
  EXPECT_EQ(first_default.get_full_name(), actual.get_full_name());
  EXPECT_EQ(first_default.get_parent(), actual.get_parent());
  EXPECT_EQ(first_default.get_children(), actual.get_children());

  first_name.set_parent(parent);
  actual = tbge::GameObject(first_name);

  EXPECT_NE(first_name.get_id(), actual.get_id());
  EXPECT_EQ(first_name.get_class_name(), actual.get_class_name());
  EXPECT_EQ(first_name.get_name(), actual.get_name());
  EXPECT_EQ(first_name.get_full_name(), actual.get_full_name());
  EXPECT_EQ(first_name.get_parent(), actual.get_parent());
  EXPECT_EQ(first_name.get_children(), actual.get_children());

  EXPECT_GT(
      tbge::global::GlobalSingleton::get_instance().get_game_objects().size(),
      start_num_game_objects);
}

TEST(GameObject, id) {
  tbge::GameObject copy1 = tbge::GameObject();
  tbge::GameObject copy2 = tbge::GameObject();

  EXPECT_EQ(tbge::GameObject().get_id()-1, tbge::GameObject().get_id());
  EXPECT_EQ(tbge::GameObject("Name").get_id()-1,
            tbge::GameObject("Test").get_id());
  EXPECT_EQ(tbge::GameObject("Name").get_id()-1, tbge::GameObject().get_id());
  EXPECT_NE(tbge::GameObject(copy1).get_id(), copy1.get_id());
  EXPECT_NE(tbge::GameObject(copy1).get_id(),
            tbge::GameObject(copy2).get_id());
}

/**
 * @test Tests all names, eg. class_name, name and full_name.
 *       In different permutations of how they got their names @n @n
 *       <b>See also</b>
 *       @n
 *       &emsp;&emsp;&emsp; @ref tbge::GameObject::GameObject()
 *       @n
 *       &emsp;&emsp;&emsp; @ref tbge::GameObject::GameObject(std::string)
 *       @n
 *       &emsp;&emsp;&emsp; @ref tbge::GameObject::get_class_name()
 *       @n
 *       &emsp;&emsp;&emsp; @ref tbge::GameObject::get_name()
 *       @n
 *       &emsp;&emsp;&emsp; @ref tbge::GameObject::set_name(std::string)
 *       @n
 *       &emsp;&emsp;&emsp; @ref tbge::GameObject::get_full_name()
 */
TEST(GameObject, names) {
  tbge::GameObject default_constructed = tbge::GameObject();
  tbge::GameObject name_constructed = tbge::GameObject("Child");
  tbge::GameObject parent = tbge::GameObject("Parent");
  tbge::GameObject grandparent = tbge::GameObject("Grandparent");

  EXPECT_EQ(default_constructed.get_class_name(), "GameObject");
  EXPECT_EQ(default_constructed.get_name(),
            "GameObject_" + std::to_string(default_constructed.get_id()));
  EXPECT_EQ(default_constructed.get_full_name(),
            "GameObject_" + std::to_string(default_constructed.get_id()));

  EXPECT_EQ(name_constructed.get_class_name(), "GameObject");
  EXPECT_EQ(name_constructed.get_name(), "Child");
  EXPECT_EQ(name_constructed.get_full_name(), "Child");

  name_constructed.set_parent(parent);

  EXPECT_EQ(name_constructed.get_class_name(), "GameObject");
  EXPECT_EQ(name_constructed.get_name(), "Child");
  EXPECT_EQ(name_constructed.get_full_name(), "Parent.Child");

  parent.set_parent(grandparent);

  EXPECT_EQ(name_constructed.get_class_name(), "GameObject");
  EXPECT_EQ(name_constructed.get_name(), "Child");
  EXPECT_EQ(name_constructed.get_full_name(), "Grandparent.Parent.Child");

  name_constructed.set_name("New_name");

  EXPECT_EQ(name_constructed.get_class_name(), "GameObject");
  EXPECT_EQ(name_constructed.get_name(), "New_name");
  EXPECT_EQ(name_constructed.get_full_name(), "Grandparent.Parent.New_name");

  parent.set_name("New_parent");

  EXPECT_EQ(name_constructed.get_class_name(), "GameObject");
  EXPECT_EQ(name_constructed.get_name(), "New_name");
  EXPECT_EQ(name_constructed.get_full_name(),
            "Grandparent.New_parent.New_name");
}

/**
 * @brief  Grandparent1       Grandparent2       Grandparent3
 *            |       |          |    
 *         Parent1 Parent2    Parent3
 *            |       |
 *         Child1  Child3
 *         Child2
 *        
 */
TEST(GameObject, parentsAndChildren) {
  tbge::GameObject child1 = tbge::GameObject("child1");
  tbge::GameObject child2 = tbge::GameObject("child2");
  tbge::GameObject child3 = tbge::GameObject("child3");

  tbge::GameObject parent1 = tbge::GameObject("parent1");
  tbge::GameObject parent2 = tbge::GameObject("parent2");
  tbge::GameObject parent3 = tbge::GameObject("parent3");

  tbge::GameObject grandparent1 = tbge::GameObject("grandparent1");
  tbge::GameObject grandparent2 = tbge::GameObject("grandparent2");
  tbge::GameObject grandparent3 = tbge::GameObject("grandparent3");

  ASSERT_EQ(child1.get_parent(), nullptr);
  ASSERT_EQ(child2.get_parent(), nullptr);
  ASSERT_EQ(child3.get_parent(), nullptr);
  ASSERT_EQ(parent1.get_parent(), nullptr);
  ASSERT_EQ(parent2.get_parent(), nullptr);
  ASSERT_EQ(parent3.get_parent(), nullptr);
  ASSERT_EQ(grandparent1.get_parent(), nullptr);
  ASSERT_EQ(grandparent2.get_parent(), nullptr);
  ASSERT_EQ(grandparent3.get_parent(), nullptr);

  // Testing set_parent() with references
  child1.set_parent(parent1);
  child2.set_parent(parent1);
  child3.set_parent(parent2);

  // testing set_parent() with pointers
  parent1.set_parent(&grandparent1);
  parent2.set_parent(&grandparent1);
  parent3.set_parent(&grandparent2);

  ASSERT_EQ(child1.get_parent(), &parent1);
  ASSERT_EQ(child2.get_parent(), &parent1);
  ASSERT_EQ(child3.get_parent(), &parent2);
  ASSERT_EQ(parent1.get_parent(), &grandparent1);
  ASSERT_EQ(parent2.get_parent(), &grandparent1);
  ASSERT_EQ(parent3.get_parent(), &grandparent2);
  ASSERT_EQ(grandparent1.get_parent(), nullptr);
  ASSERT_EQ(grandparent2.get_parent(), nullptr);
  ASSERT_EQ(grandparent3.get_parent(), nullptr);

  ASSERT_EQ(child1.get_children().size(), 0);
  ASSERT_EQ(child2.get_children().size(), 0);
  ASSERT_EQ(child3.get_children().size(), 0);
  ASSERT_EQ(parent1.get_children().size(), 2);
  ASSERT_EQ(parent2.get_children().size(), 1);
  ASSERT_EQ(parent3.get_children().size(), 0);
  ASSERT_EQ(grandparent1.get_children().size(), 2);
  ASSERT_EQ(grandparent2.get_children().size(), 1);
  ASSERT_EQ(grandparent3.get_children().size(), 0);

  ASSERT_EQ(parent1.get_children()[0], &child1);
  ASSERT_EQ(parent1.get_children()[1], &child2);
  ASSERT_EQ(parent2.get_children()[0], &child3);
  ASSERT_EQ(grandparent1.get_children()[0], &parent1);
  ASSERT_EQ(grandparent1.get_children()[1], &parent2);
  ASSERT_EQ(grandparent2.get_children()[0], &parent3);

  ASSERT_EQ(grandparent1.get_children()[0]->get_children()[0], &child1);
  ASSERT_EQ(grandparent1.get_children()[0]->get_children()[1], &child2);
  ASSERT_EQ(grandparent1.get_children()[1]->get_children()[0], &child3);
}

TEST(GameObject, getChildByName) {
  tbge::GameObject child1 = tbge::GameObject("child1");
  tbge::GameObject child2 = tbge::GameObject("child2");
  tbge::GameObject child3 = tbge::GameObject("child3");

  tbge::GameObject parent1 = tbge::GameObject("parent1");
  tbge::GameObject parent2 = tbge::GameObject("parent2");
  tbge::GameObject parent3 = tbge::GameObject("parent3");

  tbge::GameObject grandparent1 = tbge::GameObject("grandparent1");
  tbge::GameObject grandparent2 = tbge::GameObject("grandparent2");
  tbge::GameObject grandparent3 = tbge::GameObject("grandparent3");

  tbge::GameObject greatgrandparent1 = tbge::GameObject("greatgrandparent1");

  child1.set_parent(parent1);
  child2.set_parent(parent1);
  child3.set_parent(parent2);

  parent1.set_parent(grandparent1);
  parent2.set_parent(grandparent1);
  parent3.set_parent(grandparent2);

  grandparent1.set_parent(greatgrandparent1);

  ASSERT_EQ(grandparent1.get_child_by_name("parent1"), &parent1);
  ASSERT_EQ(grandparent1.get_child_by_name("parent2"), &parent2);
  ASSERT_EQ(grandparent1.get_child_by_name("parent3"), nullptr);
  ASSERT_EQ(parent1.get_child_by_name("child1"), &child1);
  ASSERT_EQ(parent1.get_child_by_name("child2"), &child2);
  ASSERT_EQ(parent2.get_child_by_name("child3"), &child3);


  ASSERT_EQ(grandparent1.get_child_by_name("parent1")->
            get_child_by_name("child1"), &child1);

  ASSERT_EQ(grandparent1.get_child_by_name("parent1.child2"), (&child2));
  ASSERT_EQ(greatgrandparent1.get_child_by_name("grandparent1.parent2.child3"),
            &child3);
}
