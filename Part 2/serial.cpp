#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

int main(int argc, char* argv[]) {
  std::string infile = "input.txt";
  if (argc > 1) infile = argv[1];
  const std::string finput = infile;

  std::ifstream in(infile);
  if (!in) {
    std::cerr << "File " << finput << " could not be opened"
              << "\n";
    return 1;
  }

  std::vector<std::pair<double, double>> locations;
  double latitude, longitude;
  while (in >> latitude >> longitude) {
    locations.emplace_back(latitude, longitude);
  }

  if (locations.empty()) {
    std::cerr << "Error: could not find latitude/longitude pairs in "
              << finput << "\n";
    return 1;
  }

  std::cout << "[parent] PID number is:" << getpid()
            << " UID is:" << getuid()
            << " GID is:" << getgid() << "\n";

  for (size_t i = 0; i < locations.size(); ++i) {
    std::ostringstream url;
    url << "https://api.open-meteo.com/v1/forecast?latitude="
        << std::fixed << std::setprecision(6) << locations[i].first
        << "&longitude=" << std::fixed << std::setprecision(6)
        << locations[i].second << "&current_weather=true";

    std::ostringstream output_filename;
    output_filename << "file" << (i + 1) << ".json";

    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      return 1;
    }
    if (pid == 0) {
      std::cout << "[child ] PID=" << getpid()
                << " PPID=" << getppid()
                << " UID=" << getuid()
                << " GID=" << getgid() << "\n";
      execlp("/usr/bin/curl",
             "curl",
             "-sS",
             "-o",
             output_filename.str().c_str(),
             url.str().c_str(),
             static_cast<char*>(nullptr));
      perror("execlp");
      _exit(127);
    } else {
      if (waitpid(pid, nullptr, 0) < 0) {
        perror("waitpid");
        return 1;
      }
    }
  }

  std::cout << "Serial fetch was successful: " << locations.size()
            << " file(s) have been saved."
            << "\n";
  return 0;
}

