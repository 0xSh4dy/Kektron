#include<vector>
#include<string>
#include<windows.h>
#include<QListWidget>
#include<QTableWidget>

typedef struct {
    std::string name;
    DWORD pid;
    bool isAvailable;
}Process;

class ProcessManager{
public:
    ProcessManager();
    std::vector<Process*>EnumerateProcesses();
    void RenderProcesses(QTableWidget*);
};
