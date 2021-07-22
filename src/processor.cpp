 
#include "processor.h"
#include <vector>
#include <string>
#include "linux_parser.h"

using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<std::string> cpuInfo = LinuxParser::CpuUtilization();
    
    // Idle = idle + iowait
    float idle =  std::stod(cpuInfo[3]) + std::stod(cpuInfo[4]);
    // NonIdle = user + nice + system + irq + softirq + steal
    float nonIdle = std::stod(cpuInfo[0]) + std::stod(cpuInfo[1]) + std::stod(cpuInfo[2]) +
                    std::stod(cpuInfo[5]) + std::stod(cpuInfo[6]) + std::stod(cpuInfo[7]);

    // Total = Idle + NonIdle
    float total = idle + nonIdle;

    float cpuPercent = (total - idle) / total;

    return cpuPercent;
}