#define GTEST_COLOR yes

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "component/component_test.h"
#include "component/util/utilPrintHandler_test.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}