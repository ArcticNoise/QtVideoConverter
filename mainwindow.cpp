#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);        

    setWindowTitle("Video converter");
    setWindowIcon(QIcon(":/imgs/LarianLogo.png"));

    settings.setWindowModality(Qt::ApplicationModal);

    connect(ui->textEdit,SIGNAL(started()),this,SLOT(onStartTranscoding()));
    connect(ui->textEdit,SIGNAL(finished()),this,SLOT(onEndTranscoding()));

    ui->textEdit->setSound(false);
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

void MainWindow::on_action_Settings_triggered()
{
    settings.show();
}

void MainWindow::on_action_Sound_toggled(bool arg1)
{
    ui->textEdit->setSound(arg1);
}
