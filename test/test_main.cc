#include <absl/log/initialize.h>
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  // Initialize logging once for all tests
  absl::InitializeLog();
  
  ::testing::InitGoogleTest(&argc, argv);
  // ::testing::GTEST_FLAG(filter) = "CreateTooManyEntities";
  return RUN_ALL_TESTS();
}