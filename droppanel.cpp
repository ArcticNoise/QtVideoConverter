#include "droppanel.h"

DropPanel::DropPanel(QWidget *parent): QTextEdit(parent)
{
    cursor = textCursor();

    setAcceptDrops(true);
    availableExtensions << QString("mp4") << QString("avi") << QString("mov");

    mTranscodingProcess = new QProcess(this);

    connect(mTranscodingProcess, SIGNAL(started()), this, SLOT(processStarted()));
    connect(mTranscodingProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(mTranscodingProcess, SIGNAL(finished(int)), this, SLOT(encodingFinished()));
}

void DropPanel::setSound(bool value)
{
    withSound = value;
}

void DropPanel::setSettings(Settings *value)
{
    settings = value;
}

void DropPanel::dragEnterEvent(QDragEnterEvent* pe)
{
    QList<QUrl> urlList = pe->mimeData()->urls();
    foreach (QUrl url, urlList)
    {
        QFileInfo fi(url.toString());
        QString ext = fi.suffix();
        if(isAvailableExt(&ext)){pe->accept(); break;}
        else{pe->ignore();}
    }
}

void DropPanel::dropEvent(QDropEvent* pe)
{
    clear();

    emit started();

    setReadOnly(true);

    QList<QUrl> urlList = pe->mimeData()->urls();

    foreach (QUrl url, urlList)
    {
        QFileInfo fi(url.toLocalFile());
        QString ext = fi.suffix();
        QString path = fi.canonicalFilePath();
        if(isAvailableExt(&ext)){filesToTranscode.append(path);}
    }

    transcodeNextFile();
}

bool DropPanel::isAvailableExt(QString *ext)
{
    foreach (QString str, availableExtensions)
    {
        if(ext->toLower() == str) return true;
    }
    return false;
}

void DropPanel::processStarted()
{
    qDebug() << "processStarted()";
}

void DropPanel::readyReadStandardOutput()
{
    printOutputMessage(mTranscodingProcess->readAllStandardOutput());
}

void DropPanel::encodingFinished()
{
    // Set the encoding status by checking output file's existence
    QString fileName = convertedFile;

    if (QFile::exists(fileName))
    {
        printOutputMessage("Transcoding Status: Successful!");
    }
    else
    {
        printOutputMessage("Transcoding Status: Failed!");
    }

    transcodeNextFile();
}

void DropPanel::encodeVideoFile(QString* path)
{
    QString program = "ffmpeg";

    QString input = *path;

    QStringList arguments;

    QFileInfo fi(*path);

    QString extension = "mp4";

    QString output = fi.absoluteDir().absolutePath() + QDir::separator() + fi.completeBaseName() + "(compressed)" + "." + extension;

    if(path->isEmpty())
    {
        qDebug() << "No input";
        QMessageBox::information(this,
                     tr("ffmpeg"),tr("Input file not specified"));
        return;
    }

    if(output.isEmpty())
    {
        qDebug() << "No output";
        QMessageBox::information(this,
                     tr("ffmpeg"),tr("Output file not specified"));
        return;
    }

    QString fileName = output;
    qDebug() << "output file check " << fileName;
    qDebug() << "QFile::exists(fileName) = " << QFile::exists(fileName);
    if (QFile::exists(fileName))
    {
         if (QMessageBox::question(this, tr("ffmpeg"),
                    tr("There already exists a file called %1 in "
                    "the current directory. Overwrite?").arg(fileName),
                    QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
             == QMessageBox::No)
             return;
         QFile::remove(fileName);
         while(QFile::exists(fileName)) {
             qDebug() << "output file still there";
         }
     }

    arguments << "-i" << input;

    if(!withSound)
    {
        arguments << "-an";
    }

    arguments << "-crf";

    int compressionValue = settings->getCompressionRate() * 10;

    arguments << QString::number(compressionValue);

    arguments << output;

    qDebug() << arguments;

    convertedFile = output;

    mTranscodingProcess->setProcessChannelMode(QProcess::MergedChannels);
    mTranscodingProcess->start(program, arguments);
}

void DropPanel::printOutputMessage(QString msg)
{
    mOutputString.append(msg);
    setText(mOutputString);

    cursor.movePosition(QTextCursor::End);
    setTextCursor(cursor);
}

void DropPanel::transcodeNextFile()
{
    if(!filesToTranscode.isEmpty())
    {
        QString path = filesToTranscode.takeFirst();
        encodeVideoFile(&path);
    }
    else
    {
        setReadOnly(false);
        emit finished();
    }
}
