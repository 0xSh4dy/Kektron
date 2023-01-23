#include "processes.h"

#include<tlhelp32.h>
#include"../helpers.hpp"
#include<QDebug>
#include<QListWidgetItem>
#include<QTableWidgetItem>
#include<QHeaderView>
#include<string>

ProcessManager::ProcessManager(){

}

std::vector<Process*>ProcessManager::EnumerateProcesses(){
    std::vector<Process*>processList;
    HANDLE hSnapshot;
    bool result;
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);
    result = InvalidHandleCheck(hSnapshot,"CreateToolhel32Snapshot failed");
    Process* process;
    std::wstring processName;
    if(!result){
        while(Process32Next(hSnapshot,&processEntry)){
            processName = processEntry.szExeFile;
            std::string procName(processName.begin(),processName.end());
            process = new Process;
            process->name = procName;
            process->pid = processEntry.th32ProcessID;
            process->isAvailable = false;
            processList.push_back(process);
            processName.clear();
        }
    }
    CloseHandle(hSnapshot);
    return processList;
}

void ProcessManager::SetupRenderer(){
    this->processList = this->EnumerateProcesses();
}

void ProcessManager::RenderProcesses(QTableWidget* tableWidget){
    QListWidgetItem* item;

    tableWidget->insertColumn(0);
    tableWidget->insertColumn(1);
    tableWidget->insertColumn(2);
    for(auto process:this->processList){
        QTableWidgetItem* pNameItem = new QTableWidgetItem;
        QTableWidgetItem* pidItem = new QTableWidgetItem;
        QTableWidgetItem* statusItem = new QTableWidgetItem;
        pNameItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        pNameItem->setText(QString::fromStdString(process->name));
        pidItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        pidItem->setText(QString::fromStdString(std::to_string(process->pid)));
        statusItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->UpdateAvailability(statusItem,process);
        tableWidget->insertRow(tableWidget->rowCount());
        tableWidget->setItem(tableWidget->rowCount()-1,0,pNameItem);
        tableWidget->setItem(tableWidget->rowCount()-1,1,pidItem);
        tableWidget->setItem(tableWidget->rowCount()-1,2,statusItem);
    }

    QHeaderView* verticalHeader = new QHeaderView(Qt::Vertical,tableWidget);
    verticalHeader->setVisible(false);
    tableWidget->setVerticalHeader(verticalHeader);
    tableWidget->setHorizontalHeaderLabels({"Process","PID","Status"});

}

void ProcessManager::UpdateAvailability(QTableWidgetItem* statusItem,Process* process){
    HANDLE hProcess;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS,true,process->pid);
    if(hProcess!=NULL){
        statusItem->setText("Available");
    }
    else{
        statusItem->setText("Not available");
    }
}
