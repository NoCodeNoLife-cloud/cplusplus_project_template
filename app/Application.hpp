#pragma once
#include <iostream>
#include <glog/logging.h>

namespace app {
/// \brief Class Application
/// \details This class is the entry point for the program.
/// It initializes the start time, executes the main task and prints the run time.
class Application {
public:
  /// \brief Start the application.
  /// This function is the main entry point of the application. It first
  /// initializes the logging system, then records the start time of the
  /// application. After that, it calls the MainTask() function to do the actual
  /// work of the application. Finally, it records the run time of the
  /// application and exits the application.
  auto start() -> void {
    initLogging();
    initStartTime();
    try {
      mainTask();
    }
    catch (std::exception& e) {
      LOG(ERROR) << e.what();
    }
    getRunTime();
    finishMain();
  }

private:
  std::chrono::time_point<std::chrono::steady_clock> start_;
  std::chrono::time_point<std::chrono::steady_clock> end_;
  /// \brief The main task of the application.
  /// This function is called by the Start() function after the logging system is
  /// initialized and the start time of the application is recorded. The actual
  /// work of the application is done in this function. The boolean return value
  /// of this function indicates whether the application should exit with EXIT_SUCCESS
  /// or EXIT_FAILURE.
  static auto mainTask() -> int {
    return EXIT_SUCCESS;
  }

  /// \brief Initialize the start time of the application.
  /// This function records the current high resolution time as the start time
  /// of the application. It is called during the application startup process
  /// to ensure accurate measurement of the application's run time.
  static auto initLogging() -> void {
    google::InitGoogleLogging("main");
    FLAGS_logtostdout = true;
  }

  /// \brief Initialize the start time of the application.
  /// This function records the current high resolution time as the start time
  /// of the application. It is called during the application startup process
  /// to ensure accurate measurement of the application's run time.
  auto initStartTime() -> void {
    start_ = std::chrono::high_resolution_clock::now();
  }

  /// \brief Get the run time of the application.
  /// This function returns the run time of the application since the last call
  /// to InitStartTime() in seconds. The run time is calculated by taking the
  /// difference between the current time and the start time of the application.
  auto getRunTime() -> void {
    end_ = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration = end_ - start_;
    LOG(INFO) << "program run time: " << duration.count() << " s" << std::endl;
  }

  /// \brief Shutdown the logging system.
  /// This function is called after the application finishes its main task. It
  /// is used to shut down the logging system to prevent any potential resource
  /// leak.
  static auto finishMain() -> void {
    google::ShutdownGoogleLogging();
  }
};
}
