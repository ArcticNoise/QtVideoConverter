#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Settings");

    readOptionsXml();

    compressionJackalImage= QPixmap(":/imgs/CompressionJackal.png");

    ui->jackalSlider->setValue(compressionRate);

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

int Settings::getSoundOutput()
{
    return soundOutput;
}

void Settings::setSoundOutput(int value)
{
    soundOutput = value;
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

void Settings::readOptionsXml()
{
    QDomDocument document;
    QFile file("options.xml");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "Failed to open file";
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug() << "Failed to open document";
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();
    QDomElement compressionRateOptions = root.firstChildElement("CompressionRate");
    QDomElement soundOutputOptions = root.firstChildElement("SoundOutput");

    compressionRate = compressionRateOptions.attribute("value").toInt();
    setSoundOutput(soundOutputOptions.attribute("value").toInt());
}

void Settings::writeOptionsXml()
{
    QDomDocument document;
    QFile file("options.xml");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "Failed to open file";
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug() << "Failed to open document";
        }
        file.close();
    }

    QDomElement root = document.firstChildElement();
    QDomElement compressionRateOptions = root.firstChildElement("CompressionRate");
    QDomElement soundOutputOptions = root.firstChildElement("SoundOutput");

    compressionRateOptions.setAttribute("value", compressionRate);
    soundOutputOptions.setAttribute("value", soundOutput);

    if(!file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for writing." );
    }

    QTextStream stream(&file);
    stream << document.toString();

    file.close();
}

void Settings::on_jackalSlider_valueChanged(int value)
{
    changeCompressionJackalImage(value);
}

void Settings::on_applySettingsButton_clicked()
{
    compressionRate = ui->jackalSlider->value();
    writeOptionsXml();
    close();
}

void Settings::on_cancelSettingsButton_clicked()
{
    ui->jackalSlider->setValue(compressionRate);
    close();
}
