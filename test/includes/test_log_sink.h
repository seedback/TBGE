#ifndef TBGE_TEST_TEST_LOG_SINK_H_
#define TBGE_TEST_TEST_LOG_SINK_H_

#include <absl/log/globals.h>
#include <absl/log/log.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#define ADITIONAL_TEST_LOGGING false

class TestLogSink : public absl::LogSink {
 public:
  void Send(const absl::LogEntry& entry) override {
    captured_logs_.push_back(std::string(entry.text_message()));
    captured_severities_.push_back(entry.log_severity());
  }

  const std::vector<std::string>& GetCapturedLogs() const {
    return captured_logs_;
  }

  const std::vector<absl::LogSeverity>& GetCapturedSeverities() const {
    return captured_severities_;
  }

  void Clear() {
    captured_logs_.clear();
    captured_severities_.clear();
  }

  void TestLogs(absl::LogSeverity severity, std::string test_string) {
    ASSERT_FALSE(GetCapturedLogs().empty());
    EXPECT_EQ(GetCapturedSeverities()[0], severity);
    EXPECT_THAT(GetCapturedLogs()[0], testing::ContainsRegex(test_string));
#if ADITIONAL_TEST_LOGGING == true
    std::cout << "[" << GetCapturedSeverities()[0] << "] "
              << GetCapturedLogs()[0] << std::endl;
#endif
  }

  void PrintLogs() {
    for (int i = 0; i < captured_logs_.size(); i++) {
      std::cout << "[" << captured_severities_[i] << "] " << captured_logs_[i]
                << std::endl;
    }
  }

  void TestLogs(std::vector<absl::LogSeverity> severities,
                std::vector<std::string> test_strings) {
    const auto& logs = GetCapturedLogs();
    const auto& local_severities = GetCapturedSeverities();

    ASSERT_FALSE(GetCapturedLogs().empty());
    for (int i = 0; i < severities.size(); ++i) {
      EXPECT_EQ(local_severities.at(i), severities.at(i));
    }
    for (int i = 0; i < test_strings.size(); ++i) {
      EXPECT_THAT(logs.at(i), testing::HasSubstr(test_strings[0]));
    }
  }

 private:
  std::vector<std::string> captured_logs_;
  std::vector<absl::LogSeverity> captured_severities_;
};

#endif