#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPixmap>

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

private:
    Ui::Settings *ui;    
    int compressionRate;
    QPixmap compressionJackalImage;

    void changeCompressionJackalImage(int value);

private slots:
    void on_jackalSlider_valueChanged(int value);
};

#endif // SETTINGS_H
