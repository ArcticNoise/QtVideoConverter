#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Settings settings;

private slots:
    void onStartTranscoding();
    void onEndTranscoding();    
    void on_action_Settings_triggered();
};

#endif // MAINWINDOW_H
