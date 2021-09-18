#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid) : pid_(pid) {}
int Process::Pid() const { return pid_; }

float Process::CpuUtilization() { 
    long int upTime = LinuxParser::UpTime(pid_);
    vector<string> cpuInfo = LinuxParser::ProcessorUtilization(pid_);
    long int utime = std::stol(cpuInfo[13]);
    long int stime = std::stol(cpuInfo[14]);
    long int cutime = std::stol(cpuInfo[15]);
    long int cstime = std::stol(cpuInfo[16]); 
    long int startime = std::stol(cpuInfo[21]);
    
    int long totalTime = utime + stime;
    totalTime += cutime + cstime;

    float seconds = (float)upTime - ((float)startime / sysconf(_SC_CLK_TCK));
    float cpuUsage = (((float)totalTime / sysconf(_SC_CLK_TCK)) / seconds);

    cpu_ = cpuUsage;

    return cpuUsage; 
}
string Process::Command() const { return LinuxParser::Command(Pid()); }

string Process::Ram()  { 
    string ramstring = LinuxParser::Ram(pid_); 
    try {
        ram_ = std::stol(ramstring) / 1024;        
    } catch(...) {
        ram_ = 0;
    }
    return std::to_string(ram_);
}
string Process::User() const { return LinuxParser::User(Pid()); }

long int Process::UpTime() const { return LinuxParser::UpTime(Pid()); }
bool Process::operator<(Process const& a) const { 
    return cpu_ < a.cpu_;
}


void Process::setRam() {
    string ramStr = LinuxParser::Ram(pid_);
    try {
        ram_ = std::stol(ramStr) / 1024;
    } catch (...) {
        ram_ = 0;
    }
}