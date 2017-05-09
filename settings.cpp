#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Settings");

    compressionJackalImage= QPixmap(":/imgs/CompressionJackal.png");

    compressionRate = ui->jackalSlider->value();

    changeCompressionJackalImage(compressionRate);
}

Settings::~Settings()
{
    delete ui;
}

int Settings::getCompressionRate()
{
    return compressionRate;
}

void Settings::changeCompressionJackalImage(int value)
{
    int compressionValue = value * 2;

    QPixmap tempImg = compressionJackalImage;

    QSize imgSize = tempImg.size();

    QPixmap downscaledImg = tempImg.scaled(QSize(imgSize.width()/compressionValue,imgSize.height()/compressionValue),  Qt::KeepAspectRatio);

    QPixmap upscaledImg = downscaledImg.scaled(QSize(imgSize.width(),imgSize.height()),  Qt::KeepAspectRatio);

    ui->jackalImage->setPixmap(upscaledImg);

}

void Settings::on_jackalSlider_valueChanged(int value)
{
    compressionRate = value;
    changeCompressionJackalImage(compressionRate);
}
