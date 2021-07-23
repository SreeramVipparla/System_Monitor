#include "system.h"

#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "process.h"
#include "processor.h"
using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
  return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids = LinuxParser::Pids();
  processes_.clear();
  for (long unsigned int i = 0; i < pids.size(); i++) {
    if (!LinuxParser::Ram(pids[i]).empty()) {
      Process process(pids[i]);
      processes_.emplace_back(process);
    }
  }
  
  std::sort(processes_.rbegin(), processes_.rend());
  return processes_;
}
// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
return LinuxParser::Kernel();
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
return LinuxParser::OperatingSystem();
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
   return LinuxParser::RunningProcesses();
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
   return LinuxParser::TotalProcesses();
}
 
 // TODO: Return the number of seconds since the system started running
long int System::UpTime() {
  long uptime = LinuxParser::UpTime();
  return uptime;
}
