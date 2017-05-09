#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPixmap>
#include <QtXml>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    int getCompressionRate();
    int getSoundOutput();

    void readOptionsXml();
    void writeOptionsXml();

    void setSoundOutput(int value);

private:
    Ui::Settings *ui;    
    int compressionRate;
    int soundOutput;
    QPixmap compressionJackalImage;

    void changeCompressionJackalImage(int value);


private slots:
    void on_jackalSlider_valueChanged(int value);
    void on_applySettingsButton_clicked();
    void on_cancelSettingsButton_clicked();
};

#endif // SETTINGS_H
