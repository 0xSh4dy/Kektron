#include<vector>
#include<string>
#include<windows.h>
#include<QListWidget>
#include<QTableWidget>
#include<QRadioButton>
#include"mainwindow.h"

typedef struct {
    std::string name;
    DWORD pid;
    bool isAvailable;
}Process;

class ProcessDisplayManager{
    QRadioButton pidRbtn,pnameRbtn,pavRbtn;
    MainWindow* mainWindow;
public:

    ProcessDisplayManager();
};

class ProcessManager:public ProcessDisplayManager{
    std::vector<Process*>processList;
public:
    ProcessManager();
    std::vector<Process*>EnumerateProcesses();
    void RenderProcesses(QTableWidget*);
    void SetupRenderer();
    void UpdateAvailability(QTableWidgetItem*,Process*);
};

