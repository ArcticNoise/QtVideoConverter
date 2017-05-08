#ifndef DROPPANEL_H
#define DROPPANEL_H

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

    void setSound(bool value);

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

    QList<QString>availableExtensions;
    QList<QString>filesToTranscode;

    bool isAvailableExt(QString* ext);
    QProcess *mTranscodingProcess;

    QString mOutputString;
    QString convertedFile;

    QTextCursor cursor;
    bool withSound;

private slots:
    void readyReadStandardOutput();
    void processStarted();
    void encodingFinished();
};

#endif // DROPPANEL_H
