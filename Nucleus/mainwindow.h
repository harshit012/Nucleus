#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QRadioButton>
#include<QCursor>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QAction>
#include<QShortcut>
#include<QObject>
#include<QDialog>
#include<QFileDialog>
#include<QProcess>
#include<QDesktopServices>
#include<QUrl>
#include<QDebug>
#include<stdlib.h>
#include<stdio.h>
#include<QListIterator>
#include<page.h>
#include<QListIterator>
#include<QByteArray>
#include<QColor>
#include<QColorDialog>
#include<QPalette>
#include<QFontDialog>
#include<QFont>
#include<QDialog>
#include<QtCore>
#include<QtGui>
#include<QFileSystemModel>
#include<QModelIndex>
#include<pythonprogramlauncher.h>
#include<stdio.h>
#include<stdlib.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_clearAllButton_clicked();

    void on_mainTextEdit_cursorPositionChanged();

    void on_saveButton_clicked();


    void on_openButton_2_clicked();


    void on_newButton_clicked();

    void on_gotoButton_clicked();

    void on_gotoCloseButton_clicked();

    void on_gotoFrameCancelButton_clicked();

    void on_gotoFrameGotoButton_clicked();

    void on_findButton_clicked();


    void on_mainTextEdit_textChanged();

    void on_cmdButton_clicked();


    void on_radioButton1_clicked();

    void on_radioButton2_clicked();

    void on_radioButton3_clicked();

    void on_radioButton4_clicked();

    void on_radioButton5_clicked();

    void on_radioButton6_clicked();

    void on_radioButton7_clicked();

    void on_radioButton8_clicked();

    void on_radioButton9_clicked();

    void on_radioButton10_clicked();

    void on_radioButton11_clicked();

    void on_radioButton12_clicked();

    void on_radioButton13_clicked();

    void on_radioButton14_clicked();

    void on_radioButton15_clicked();

    void on_radioButton16_clicked();

    void on_radioButton17_clicked();

    void on_radioButton18_clicked();

    void on_radioButton19_clicked();

    void on_radioButton20_clicked();

    void on_pageCloseButton_clicked();

    void on_cmdButton_2_clicked();

    void on_up_clicked();

    void on_down_clicked();

    void on_textColorButton_clicked();


    void on_fontButton_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_lightRadioButton_clicked();

    void on_DarkRadioButton_clicked();
    void on_inputSendButton_clicked();
    void processOutput();
    void processFinished();
    void processStateChanged();

    void on_InputlineEdit_returnPressed();

    void on_fullScreenButton_clicked();

    void on_exitFullScreenButton_clicked();


private:
    Ui::MainWindow *ui;
    int gotoFrameVisible;
    int current;
    QList<QRadioButton*> radioButtons;
    QList<Page*> pages;
    Page *page;
    QColor textColor;
    QColor backgroundColor;
    void populateRadioButtons();
    void hideAllRadioButtons();
    void openFileinNewPage(QString fileName,bool newPage);
    PythonProgramLauncher *pyThread;
    QString inputDataString;
    int programFinished;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QProcess *process;
    int compilationState;
    int fullScreenMode;
public:
    void setProgramFinished();
};
#endif // MAINWINDOW_H
