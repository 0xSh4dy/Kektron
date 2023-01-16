#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "processes/processes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RenderProcesses(){
    std::unique_ptr<ProcessManager>pManager = std::make_unique<ProcessManager>();
    pManager->EnumerateProcesses();
}
