#include "pythonprogramlauncher.h"

void PythonProgramLauncher::setInputDataString(const QString &value)
{
    inputDataString = value;
}

QString PythonProgramLauncher::getInputDataString() const
{
    return inputDataString;
}

void PythonProgramLauncher::run()
{
    QString program="py";
    QStringList args;
    args<<this->page->getPath();
    if(this->process==NULL) delete this->process;
    this->process = new QProcess();
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    process->start(program,args,QProcess::ReadWrite);
    process->setProcessChannelMode(QProcess::MergedChannels);
    int count=0;
    while(1)
    {
    if(process->waitForFinished()==false) break;
    if(inputDataString.size()>0) process->write(this->inputDataString.toUtf8().toBase64());
    this->inputDataString="";
    qDebug()<<count;
    count++;
    }
}

void PythonProgramLauncher::processOutput()
{
    QTextStream stdoutData(process->readAllStandardOutput());
    QTextStream stdoutError(process->readAllStandardError());
    while (!stdoutData.atEnd())
     {
        QString line = stdoutData.readLine(); //read one line at a time
        qDebug()<<line;
        this->textEditor->append(line);
     }
    while (!stdoutError.atEnd())
     {
        QString line = stdoutError.readLine(); //read one line at a time
        qDebug()<<line;
        this->textEditor->append(line);
     }
}

Page *PythonProgramLauncher::getPage() const
{
    return page;
}

void PythonProgramLauncher::setPage(Page *value)
{
    page = value;
}

PythonProgramLauncher::PythonProgramLauncher(QTextEdit *textEditor)
{
    this->textEditor=textEditor;
    this->inputDataString="";
    this->page=NULL;
    this->process=NULL;
}
