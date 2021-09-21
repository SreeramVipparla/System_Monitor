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
Processor& System::Cpu() {
  return cpu_;
}
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
std::string System::Kernel() {
return LinuxParser::Kernel();
}git 
float System::MemoryUtilization() {
return LinuxParser::MemoryUtilization();
}
std::string System::OperatingSystem() {
return LinuxParser::OperatingSystem();
}
int System::RunningProcesses() {
   return LinuxParser::RunningProcesses();
}int System::TotalProcesses() {
   return LinuxParser::TotalProcesses();
}
 
long int System::UpTime() {
  long uptime = LinuxParser::UpTime();
  return uptime;
}
