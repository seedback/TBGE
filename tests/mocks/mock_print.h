#ifndef TBGE_TEST_MOCK_PRINT_H_
#define TBGE_TEST_MOCK_PRINT_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/command/command_action/print.h"

class MockPrint : public tbge::Print {
public:
  using Print::Print;
  MOCK_METHOD(void, execute, (std::vector<std::string>& arguments), (override));
};

#endif // TBGE_TEST_MOCK_PRINT_H_
