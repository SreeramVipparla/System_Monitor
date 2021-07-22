
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid() const;               // TODO: See src/process.cpp
  std::string User() const;      // TODO: See src/process.cpp
  std::string Command() const;   // TODO: See src/process.cpp
  float CpuUtilization() ;  // TODO: See src/process.cpp

  std::string Ram() const;                 // TODO: See src/process.cpp
  long int UpTime() const;                 // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
; 
    long int getRam() const { return ram_; }
  void setRam();// TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  long int ram_ = 0;
  int pid_;
  float cpu_;
};
#endif
