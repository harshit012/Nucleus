#ifndef PYTHONPROGRAMLAUNCHER_H
#define PYTHONPROGRAMLAUNCHER_H
#include<QThread>
#include<QString>
#include<page.h>
#include<QProcess>
#include<QTextEdit>
#include<QObject>
class PythonProgramLauncher:public QThread
{
public:
    QString inputDataString;
    Page *page;
    QTextEdit *textEditor;
     QProcess *process;
    PythonProgramLauncher(QTextEdit *textEditor);
    void setInputDataString(const QString &value);
    QString getInputDataString() const;

    Page *getPage() const;
    void setPage(Page *value);

protected:
    void run() override;

public slots:
        void processOutput();
};

#endif // PYTHONPROGRAMLAUNCHER_H
