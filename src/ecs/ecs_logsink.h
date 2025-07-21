#ifndef TBGE_SRC_ECS_ECS_LOGSINK_H_
#define TBGE_SRC_ECS_ECS_LOGSINK_H_

#include <absl/log/check.h>
#include <absl/log/initialize.h>
#include <absl/log/log.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

class EcsLogSink : public absl::LogSink {
 public:
  EcsLogSink() : log_folder_("logs") {
    // Create logs directory if it doesn't exist
    std::filesystem::create_directories(log_folder_);

    // Create log file with timestamp
    std::string filename = log_folder_ + "/ecs_" + GetTimestamp() + ".log";
    log_file_.open(filename, std::ios::app);

    if (!log_file_.is_open()) {
      std::cerr << "Failed to open log file: " << filename << std::endl;
    }
  }

  ~EcsLogSink() {
    if (log_file_.is_open()) {
      log_file_.close();
    }
  }

  void Send(const absl::LogEntry& entry) override {
    // Format: [TIMESTAMP] [SEVERITY] filename:line message
    std::string message =
        "[" + GetTimestamp() + "] " + "[" +
        std::string(absl::LogSeverityName(entry.log_severity())) + "] " +
        std::string(entry.source_basename()) + ":" + std::to_string(entry.source_line()) +
        " " + std::string(entry.text_message());

    // Write to file
    if (log_file_.is_open()) {
      log_file_ << message << std::endl;
      log_file_.flush();  // Ensure immediate write
    }

    #ifdef _DEBUG
    // Also output to console for debugging
    std::cout << "[" << entry.log_severity() << "] "
              << entry.text_message_with_prefix_and_newline();
    #endif
  }

 private:
  std::ofstream log_file_;
  std::string log_folder_;

  std::string GetTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d_%H-%M-%S");
    return ss.str();
  }
};

#endif // TBGE_SRC_ECS_ECS_LOGSINK_H_