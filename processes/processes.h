#include<vector>
#include<string>

typedef struct {
    std::string name;
    int pid;
}Process;

class ProcessManager{
public:
    ProcessManager();
    std::vector<Process*>EnumerateProcesses();
};
