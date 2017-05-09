#ifndef DROPPANEL_H
#define DROPPANEL_H

#include "settings.h"

#include <QTextEdit>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include <QMimeData>
#include <QList>
#include <QDebug>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QProcess>
#include <QMessageBox>
#include <QObject>


class DropPanel : public QTextEdit
{
Q_OBJECT
public:    
    explicit DropPanel(QWidget *parent = 0);

    void setSettings(Settings* value);

signals:
    void started();
    void finished();

protected:
    void dragEnterEvent(QDragEnterEvent* pe);
    void dropEvent(QDropEvent* pe);

private:
    void encodeVideoFile(QString* path);
    void printOutputMessage(QString msg);
    void transcodeNextFile();
    QString getCompressionValueString();

    QList<QString>availableExtensions;
    QList<QString>filesToTranscode;

    Settings *settings;

    bool isAvailableExt(QString* ext);
    QProcess *mTranscodingProcess;

    QString mOutputString;
    QString convertedFile;

    QTextCursor cursor;    

private slots:
    void readyReadStandardOutput();
    void processStarted();
    void encodingFinished();
};

#endif // DROPPANEL_H
