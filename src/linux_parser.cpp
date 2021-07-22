#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>
#include <iostream>


#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, hostname, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> hostname >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}



// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key{""};
  string val{""};
  string total_mem{""};
  string free_mem{""};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> val) {
        if (key == "MemTotal:") total_mem = val;
        if (key == "MemFree:") free_mem = val;
      }
    }
  }

  return (std::stof(total_mem) - std::stof(free_mem)) / std::stof(total_mem);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  string val{""};
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream stream(line);
    stream >> val;
  }
  return stoi(val);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }
// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
    vector<string> cpuInfo;
    const std::string CPU{"cpu"};
    std::string line, key, value, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == CPU) { 
                linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;  
            }            
        }
    }

    cpuInfo.push_back(user);
    cpuInfo.push_back(nice);
    cpuInfo.push_back(system);
    cpuInfo.push_back(idle);
    cpuInfo.push_back(iowait);
    cpuInfo.push_back(irq);
    cpuInfo.push_back(softirq);
    cpuInfo.push_back(steal);
    cpuInfo.push_back(guest);
    cpuInfo.push_back(guest_nice);

    return cpuInfo;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key{""};
  string val{""};
  string total_p{""};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream stream(line);
      while (stream >> key >> val) {
        if (key == "processes") total_p = val;
      }
    }
  }

  return std::stoi(total_p);
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key{""};
  string val{""};
  string running_p{""};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream stream(line);
      while (stream >> key >> val) {
        if (key == "procs_running") running_p = val;
      }
    }
  }

  return std::stoi(running_p);
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid) +
                       LinuxParser::kCmdlineFilename);
  if (stream.is_open()) {
    string line;
    std::getline(stream, line);
    return line;
  }

  return "";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid_) { 
    const string VM_SIZE{"VmSize:"};
    string line, key, vmsize;
    std::ifstream stream(kProcDirectory + std::to_string(pid_) + kStatusFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            linestream >> key;
            if (key == VM_SIZE) {
                linestream >> vmsize;
            }
        }
    }
    return vmsize;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string token;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid) +
                       LinuxParser::kStatusFilename);
  if (stream.is_open()) {
    while (stream >> token) {
      if (token == "Uid:") {
        if (stream >> token) return token;
      }
    }
  }
  return string("");
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string token = Uid(pid);
  string uid;
  string user;
  string line;
  std::ifstream filestream(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), 'x', ' ');
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> uid) {
        if (uid == token) {
          return user;
        }
      }
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string token;
  string line;
  vector<string> values;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid) +
                       LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> token) {
      values.push_back(token);
    }
  }
  int upTimePid = UpTime() -stol(values[21])/sysconf(_SC_CLK_TCK);
  return upTimePid;
}

vector<string> LinuxParser::ProcessorUtilization(int pid) {
    string line, tmp;
    vector<string> info;
    std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
    if (stream.is_open()) {
        while (std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> tmp) {
                info.push_back(tmp);
            }
        }
    }

    return info;
}