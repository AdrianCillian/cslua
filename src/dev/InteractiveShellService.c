#include <cstdlib>
#include <iostream>
#include <string>

class InteractiveShellService {
public:
  static int exec(const std::string &cmd, std::string &result) {
    char buffer[128];
    std::string output;
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
      return 1;
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != nullptr)
        output += buffer;
    }
    pclose(pipe);
    result = output;
    return 0;
  }

  static int mkdir(const std::string &path) {
    std::string cmd = "mkdir " + path;
    return system(cmd.c_str());
  }

  static int rm(const std::string &path) {
    std::string cmd = "rm -r " + path;
    return system(cmd.c_str());
  }

  static int mv(const std::string &src, const std::string &dst) {
    std::string cmd = "mv " + src + " " + dst;
    return system(cmd.c_str());
  }

  static int cp(const std::string &src, const std::string &dst) {
    std::string cmd = "cp " + src + " " + dst;
    return system(cmd.c_str());
  }

  static int touch(const std::string &path) {
    std::string cmd = "touch " + path;
    return system(cmd.c_str());
  }

  static int ln(const std::string &src, const std::string &dst) {
    std::string cmd = "ln -s " + src + " " + dst;
    return system(cmd.c_str());
  }

  static int chmod(const std::string &path, const std::string &mode) {
    std::string cmd = "chmod " + mode + " " + path;
    return system(cmd.c_str());
  }

  static int chown(const std::string &path, const std::string &owner) {
    std::string cmd = "chown " + owner + " " + path;
    return system(cmd.c_str());
  }

  static int whoami(std::string &result) {
    return exec("whoami", result);
  }

  static int pwd(std::string &result) {
    return exec("pwd", result);
  }

  static int ls(const std::string &path, std::string &result) {
    std::string cmd = "ls " + path;
    return exec(cmd, result);
  }

  static int ps(std::string &result) {
    return exec("ps aux", result);
  }

  static int kill(int pid) {
    std::string cmd = "kill " + std::to_string(pid);
    return system(cmd.c_str());
  }
};
