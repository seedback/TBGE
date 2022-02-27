
#ifndef TBGE_TEST_GLOBAL_GLOBAL_SINGLETON_TEST_HH_  // NOLINT
#define TBGE_TEST_GLOBAL_GLOBAL_SINGLETON_TEST_HH_

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "src/lib/global/global_singleton.hh"

#include "gtest/gtest.h"

/**
 * @test Sanity-check that GlobalSingleton is actually a singleton
 *       This is achieved by running
 *       tbge::global::GlobalSingleton::get_instance() twice and comparing the
 *       returned pointers, checking that tehy're the same. @n @n
 *       <b>See also:</b>
 *       - tbge::global::GlobalSingleton::get_instance()
 */
TEST(GlobalSingleton, isSingleton) {
  tbge::global::GlobalSingleton& inst =
      tbge::global::GlobalSingleton::get_instance();
  ASSERT_EQ(&inst, &tbge::global::GlobalSingleton::get_instance());
}

/**
 * @test Tests that tbge::global::GlobalSingleton::command_word_aliases() works as both an
 *       accessor or a mutator depending on the number of input arguments. @n @n
 *       <b>See also:</b>
 *       - tbge::global::GlobalSingleton::command_word_aliases()
 *       - tbge::global::GlobalSingleton::command_word_aliases(std::multimap<std::string, std::string>)
 */
TEST(GlobalSingleton, commandWordAliases) {
  tbge::global::GlobalSingleton& inst =
      tbge::global::GlobalSingleton::get_instance();
  std::multimap<std::string, std::string> valid_input;
  valid_input.emplace("LOOK", "LOOK");
  valid_input.emplace("GRAB", "TAKE");
  valid_input.emplace("INSPECT", "INSPECT");

  std::multimap<std::string, std::string> valid_input_mixed_case;
  valid_input_mixed_case.emplace("LoOk", "lOoK");
  valid_input_mixed_case.emplace("GrAb", "tAkE");
  valid_input_mixed_case.emplace("InSpEcT", "iNsPeCt");

  std::multimap<std::string, std::string> invalid_input;
  invalid_input.emplace("LOk", "LOOK");
  invalid_input.emplace("GRAB_", "TAKE");
  invalid_input.emplace("INSPECT5", "INSPECT");

  std::multimap<std::string, std::string> expected;
  expected.emplace("LOOK", "LOOK");
  expected.emplace("GRAB", "TAKE");
  expected.emplace("INSPECT", "INSPECT");

  inst.command_word_aliases(valid_input);
  ASSERT_EQ(inst.command_word_aliases(), expected);
  inst.command_word_aliases(valid_input_mixed_case);
  ASSERT_EQ(inst.command_word_aliases(), expected);
  inst.command_word_aliases(invalid_input);
  ASSERT_NE(inst.command_word_aliases(), expected);
}

/**
 * @test Testing that
 *       tbge::global::GlobalSingleton::add_command_word_alias(std::string,
 *       std::string) where the input arguments are either @b all-upper-case,
 *       @b all-lower-case or @b all-mixed-case always adds @a command-words
 *       @b all-upper-case. @n @n
 *       <b>See also:</b>
 *       - tbge::global::GlobalSingleton::add_command_word_alias(std::string,
 *       std::string)
 */
TEST(GlobalSingleton, addCommandWordAliases) {
  tbge::global::GlobalSingleton& inst =
      tbge::global::GlobalSingleton::get_instance();
  std::multimap<std::string, std::string> start_value;
  start_value.emplace("LOOK", "LOOK");
  start_value.emplace("GRAB", "TAKE");
  start_value.emplace("INSPECT", "INSPECT");

  std::multimap<std::string, std::string> expected;
  expected.emplace("LOOK", "LOOK");
  expected.emplace("GRAB", "TAKE");
  expected.emplace("INSPECT", "INSPECT");
  expected.emplace("OPEN", "OPEN");
  expected.emplace("CLOSE", "CLOSE");
  expected.emplace("GO", "GO");

  inst.command_word_aliases(start_value);
  inst.add_command_word_alias("oPeN", "OpEn");
  inst.add_command_word_alias("close", "close");
  inst.add_command_word_alias("GO", "GO");

  ASSERT_EQ(inst.command_word_aliases(), expected);
}

/**
 * @test Testing that
 *       tbge::global::GlobalSingleton::get_command_words_by_alias(std::string)
 *       where the input arguments are either @b all-upper-case,
 *       @b all-lower-case or @b all-mixed-case always returns the
 *       @a command-word in @b all-upper-case. @n @n
 *       <b>See also:</b>
 *       - tbge::global::GlobalSingleton::get_command_words_by_alias(std::string)
 */
TEST(GlobalSingleton, getCommandWordsByAlias) {
  tbge::global::GlobalSingleton& inst =
      tbge::global::GlobalSingleton::get_instance();
  std::vector<std::string> actual;
  std::vector<std::string> expected;

  // Resetting the singleton from from earlier tests
  inst.command_word_aliases(std::multimap<std::string, std::string>());
  // First entry is the alias, second entry is the command-word
  inst.add_command_word_alias("LOOK", "LOOK");
  inst.add_command_word_alias("SEE", "LOOK");
  inst.add_command_word_alias("INSPECT", "LOOK");
  inst.add_command_word_alias("INSPECT", "INSPECT");
  inst.add_command_word_alias("GO", "GO");
  inst.add_command_word_alias("MOVE", "GO");
  inst.add_command_word_alias("GO", "OPEN");
  inst.add_command_word_alias("TEST", "TEST");
  inst.add_command_word_alias("TEST", "TEMP");

  expected.push_back("LOOK");
  expected.push_back("INSPECT");
  actual = inst.get_command_words_by_alias("INSPECT");
  ASSERT_EQ(actual, expected);

  expected.clear();
  expected.push_back("GO");
  expected.push_back("OPEN");
  actual = inst.get_command_words_by_alias("GO");
  ASSERT_EQ(actual, expected);

  expected.clear();
  expected.push_back("TEST");
  expected.push_back("TEMP");
  actual = inst.get_command_words_by_alias("TEST");
  ASSERT_EQ(actual, expected);
}


#endif  // #ifndef TBGE_TEST_GLOBAL_GLOBAL_SINGLETON_TEST_HH_ //NOLINT