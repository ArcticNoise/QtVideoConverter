#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->textEdit,SIGNAL(started()),this,SLOT(onStartTranscoding()));
    connect(ui->textEdit,SIGNAL(finished()),this,SLOT(onEndTranscoding()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartTranscoding()
{
    ui->progressBar->setRange(0,0);
}

void MainWindow::onEndTranscoding()
{
    ui->progressBar->setRange(0,1);
}
