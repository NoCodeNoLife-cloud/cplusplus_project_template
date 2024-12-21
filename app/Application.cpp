#include "Application.hpp"

/// \brief The main entry point of the program.
/// \param argc The number of command line arguments
/// \param argv The command line arguments
/// \return EXIT_SUCCESS if the program run successfully, EXIT_FAILURE otherwise
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  app::Application application;
  application.start();
}
