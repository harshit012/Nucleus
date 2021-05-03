#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->ui->gotoFrame->setVisible(false);
    this->fullScreenMode=0;
    this->gotoFrameVisible=0;
    this->current=0;

    this->page=new Page();
    this->pages.push_back(this->page);

    QString sPath="";
    this->dirModel=new QFileSystemModel(this);
    this->dirModel->setRootPath(sPath);
    this->dirModel->sort(Qt::AscendingOrder);
    this->ui->treeView->setModel(this->dirModel);

    QPixmap fullScreenButtonIcon(":/img/icons/fullScreen.png");
    this->ui->fullScreenButton->setIcon(fullScreenButtonIcon);
    this->ui->fullScreenButton->setIconSize(QSize(65,65));

    QPixmap exitFullScreenButtonIcon(":/img/icons/exitFullScreen.png");
    this->ui->exitFullScreenButton->setIcon(exitFullScreenButtonIcon);
    this->ui->exitFullScreenButton->setIconSize(QSize(65,65));

    QPixmap newButtonIcon(":/img/icons/new.png");
    this->ui->newButton->setIcon(newButtonIcon);
    this->ui->newButton->setIconSize(QSize(65,65));
    QPixmap openButtonIcon(":/img/icons/open.png");
    this->ui->openButton_2->setIcon(openButtonIcon);
    this->ui->openButton_2->setIconSize(QSize(65,65));
    QPixmap saveButtonIcon(":/img/icons/save.png");
    this->ui->saveButton->setIcon(saveButtonIcon);
    this->ui->saveButton->setIconSize(QSize(65,65));
    QPixmap fontButtonIcon(":/img/icons/font.png");
    this->ui->fontButton->setIcon(fontButtonIcon);
    this->ui->fontButton->setIconSize(QSize(65,65));
    QPixmap gotoButtonIcon(":/img/icons/goto.png");
    this->ui->gotoButton->setIcon(gotoButtonIcon);
    this->ui->gotoButton->setIconSize(QSize(65,65));
    QPixmap findButtonIcon(":/img/icons/find.png");
    this->ui->findButton->setIcon(findButtonIcon);
    this->ui->findButton->setIconSize(QSize(65,65));
    QPixmap clearAllButtonIcon(":/img/icons/clearAll.png");
    this->ui->clearAllButton->setIcon(clearAllButtonIcon);
    this->ui->clearAllButton->setIconSize(QSize(65,65));
    QPixmap cmdButtonIcon(":/img/icons/cmd2.png");
    this->ui->cmdButton->setIcon(cmdButtonIcon);
    this->ui->cmdButton->setIconSize(QSize(65,65));
    QPixmap runButtonIcon(":/img/icons/run.png");
    this->ui->cmdButton_2->setIcon(runButtonIcon);
    this->ui->cmdButton_2->setIconSize(QSize(65,65));
    QPixmap textColorButtonIcon(":/img/icons/color.png");
    this->ui->textColorButton->setIcon(textColorButtonIcon);
    this->ui->textColorButton->setIconSize(QSize(65,65));
    QPixmap logoIcon(":/img/icons/icon.png");
    QWidget::setWindowIcon(logoIcon);
    QWidget::setWindowTitle("HCEditor");

    QShortcut *shortcut1=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_S),this);
    QObject::connect(shortcut1,SIGNAL(activated()),this,SLOT(on_saveButton_clicked()));
    QShortcut *shortcut2=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_G),this);
    QObject::connect(shortcut2,SIGNAL(activated()),this,SLOT(on_gotoButton_clicked()));
    QShortcut *shortcut3=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_O),this);
    QObject::connect(shortcut3,SIGNAL(activated()),this,SLOT(on_openButton_2_clicked()));
    QShortcut *shortcut4=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_N),this);
    QObject::connect(shortcut4,SIGNAL(activated()),this,SLOT(on_newButton_clicked()));
    QShortcut *shortcut5=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_F),this);
    QObject::connect(shortcut5,SIGNAL(activated()),this,SLOT(on_fontButton_clicked()));
    QShortcut *shortcut6=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_R),this);
    QObject::connect(shortcut6,SIGNAL(activated()),this,SLOT(on_cmdButton_2_clicked()));
    QShortcut *shortcut7=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_F1),this);
    QObject::connect(shortcut7,SIGNAL(activated()),this,SLOT(on_cmdButton_clicked()));
    QShortcut *shortcut8=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Up),this);
    QObject::connect(shortcut8,SIGNAL(activated()),this,SLOT(on_up_clicked()));
    QShortcut *shortcut9=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Down),this);
    QObject::connect(shortcut9,SIGNAL(activated()),this,SLOT(on_down_clicked()));
    QShortcut *shortcut10=new QShortcut(Qt::Key_Escape,this);
    QObject::connect(shortcut10,SIGNAL(activated()),this,SLOT(on_exitFullScreenButton_clicked()));




    populateRadioButtons();
    hideAllRadioButtons();
    this->ui->radioButton1->setVisible(true);
    this->ui->radioButton1->setChecked(true);
    this->ui->fileNameLabel->setText("untitled");
    this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->up->setVisible(false);
    this->ui->exitFullScreenButton->setVisible(false);
    this->ui->down->setVisible(false);
    this->textColor=QColor("white");
    this->ui->treeView->setColumnWidth(0,150);
    this->ui->DarkRadioButton->setChecked(true);

    this->ui->newButton->setToolTip("New Page");
    this->ui->openButton_2->setToolTip("Open file");
    this->ui->saveButton->setToolTip("Save file");
    this->ui->fontButton->setToolTip("Font");
    this->ui->textColorButton->setToolTip("Text Color");
    this->ui->gotoButton->setToolTip("Goto");
    this->ui->clearAllButton->setToolTip("Clear All");
    this->ui->findButton->setToolTip("Find");
    this->ui->cmdButton->setToolTip("command prompt");
    this->ui->cmdButton_2->setToolTip("Compile/Run");
    this->ui->pageCloseButton->setToolTip("Close current page");
    this->programFinished=-1;
    this->compilationState=0;
    this->pyThread=NULL;
    this->process=NULL;
    QMainWindow::showFullScreen();

}



MainWindow::~MainWindow()
{
    QListIterator<Page*> iter(this->pages);
    while(iter.hasNext())
    {
        delete iter.next();
    }
    delete ui;
}

void MainWindow::on_clearAllButton_clicked()
{
    this->ui->mainTextEdit->clear();
}


void MainWindow::on_mainTextEdit_cursorPositionChanged()
{
    QTextCursor cursor;
    QString str=this->ui->mainTextEdit->toPlainText();
    int count=0;
    cursor=this->ui->mainTextEdit->textCursor();
    int length=cursor.position();
    QString lineCountStr("1\n");
    int e=0;
    for(e=0;e<length;e++)
    {
        if(str[e]=='\n')
        {
            count++;
        }
    }

    this->ui->lineCountlabel->setText(QString::number(count+1));
}

void MainWindow::on_saveButton_clicked()
{
    this->page=this->pages[current];
    QString text=this->ui->mainTextEdit->toPlainText();
    QString fileName;
    QString text2;
    if(this->page->getFileSaved()==0)
    {
    fileName=QFileDialog::getSaveFileName(this,tr("Save file"),"c:/","All files (*.*);;c++ (*.cpp);;python (*.py);;HText (*.htxt)");
    if(fileName.length()==0) return;
    this->page->setPath(fileName);
    }else fileName=this->page->getPath();
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        file.close();
        return;
    }
    int flag=0;
    if(this->page->getExtension()==QString("htxt"))
    {
        for(int i=0;i<text.size();i++)
        {
          int value=text[i].toLatin1()+10;
          if(value>=127) value=value%127;
          text2.append(QChar(value).toLatin1());
        }
        flag=1;
    }
    QTextStream out(&file);
    if(flag==0) out<<text;
    else out<<text2;
    file.close();
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
    this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->treeView->setCurrentIndex(this->dirModel->index(fileName));
    this->ui->treeView->expand(this->dirModel->index(fileName));
}


void MainWindow::on_openButton_2_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open file"),"c:/","All files (*.*);;c++ (*.cpp);;python (*.py);;HText (*.htxt)");
    this->openFileinNewPage(fileName,true);
    this->ui->treeView->setCurrentIndex(this->dirModel->index(fileName));
    this->ui->treeView->expand(this->dirModel->index(fileName));
}

void MainWindow::on_newButton_clicked()
{
    int index=this->pages.size();
    if(index>19) return;
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    this->radioButtons[index]->setVisible(true);
    this->pages.push_back(new Page());
    current=index;
    this->radioButtons[index]->setChecked(true);
    this->ui->mainTextEdit->clear();
    this->ui->fileNameLabel->setText("untitled");
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
}



void MainWindow::on_gotoButton_clicked()
{
    if(this->gotoFrameVisible==0)
    {
        this->ui->gotoFrame->setVisible(true);
        this->gotoFrameVisible=1;
        this->ui->gotoLineEdit->setFocus();
        return;
    }
     this->ui->gotoFrame->setVisible(false);
    this->gotoFrameVisible=0;
}

void MainWindow::on_gotoCloseButton_clicked()
{
   this->ui->gotoFrame->setVisible(false);
   this->gotoFrameVisible=0;
}

void MainWindow::on_gotoFrameCancelButton_clicked()
{
   this->ui->gotoFrame->setVisible(false);
   this->gotoFrameVisible=0;
}

void MainWindow::on_gotoFrameGotoButton_clicked()
{
    int gotoLine=this->ui->gotoLineEdit->text().toInt()-1;
    QString data;
    int count=0;
    data=this->ui->mainTextEdit->toPlainText();
    int i;
    for(i=0;i<data.length();i++)
    {
        if(data[i]=='\n') count++;
        if(count==gotoLine) break;
    }
    if(i==data.length())
    {
        QMessageBox mb;
        mb.setText("Invalid line number");
        mb.setWindowTitle("HCEditor");
        mb.show();
        mb.exec();
        this->ui->gotoFrame->setVisible(false);
        this->gotoFrameVisible=0;
        return;
    }
    QTextCursor cursor;
    cursor=this->ui->mainTextEdit->textCursor();
    cursor.setPosition(i+1,QTextCursor::MoveAnchor);
    this->ui->mainTextEdit->setTextCursor(cursor);
    this->ui->gotoFrame->setVisible(false);
    this->gotoFrameVisible=0;
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_findButton_clicked()
{
    QTextCursor cursor1;
    cursor1=this->ui->mainTextEdit->textCursor();
    int pos=cursor1.position();
    QString data=this->ui->mainTextEdit->toPlainText();
    QString toFind=this->ui->findFrameLineEdit->text();
    QString temp("");
    int i=pos;
    int found=0;
    int start;
    while(i<data.length())
    {
        while((data[i]==' '||data[i]=='\n')&&i<data.length()) i++;
        start=i;
        while(data[i]!=' '&&data[i]!='\n'&&i<data.length())
        {
            temp.append(data[i]);
            i++;
        }
        if(temp==toFind)
        {
            found=1;
            break;
        }
        temp="";
        i++;
    }
    if(found==0)
    {
        QMessageBox mb;
        mb.setText(toFind.append(" Not Found"));
        mb.setWindowTitle("HCEditor");
        mb.show();
        mb.exec();
        return;
    }
    QTextCursor cursor;
    cursor=this->ui->mainTextEdit->textCursor();
    cursor.setPosition(start,QTextCursor::MoveAnchor);

    cursor.setPosition(i,QTextCursor::KeepAnchor);
    this->ui->mainTextEdit->setTextCursor(cursor);
    this->ui->mainTextEdit->setFocus();
}


void MainWindow::on_mainTextEdit_textChanged()
{
    QString content=this->ui->mainTextEdit->toPlainText();
    QString fileName("");
    int flag=0;
    int endPos;
    int startPos=0;
    for(int i=0;i<content.size();i++)
    {
       if(content[i]=='#')
       {
           startPos=i;
           if(i<content.size()-1)
           {
               if(content[++i]=='[')
               {
                   i++;
                   while(i<content.size())
                   {
                       if(content[i]==']')
                       {
                           if(i<content.size()-1)
                           {
                               if(content[++i]=='#')
                               {
                                   flag=1;
                                   break;
                                   endPos=i;
                               }
                           }
                       }
                       fileName.append(content[i]);
                       i++;
                   }
               }
           }
       }
    }
    if(flag==1)
    {
        startPos;
        QString finalString("");
        for(int i=0;i<startPos;i++) finalString.append(content[i]);
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            file.close();
            return;
        }
        QTextStream in(&file);
        finalString.append(in.readAll());
        file.close();
        this->ui->mainTextEdit->setText(finalString);
        //this->ui->mainTextEdit->setFocus();
        int start=this->ui->mainTextEdit->toPlainText().size();
        QTextCursor cursor;
        cursor=this->ui->mainTextEdit->textCursor();
        cursor.setPosition(start-1);

    }
}

void MainWindow::on_cmdButton_clicked()
{
   system("start cmd.exe @cmd /k ""c:""");
}

void MainWindow::populateRadioButtons()
{
    radioButtons.push_back(this->ui->radioButton1);
    radioButtons.push_back(this->ui->radioButton2);
    radioButtons.push_back(this->ui->radioButton3);
    radioButtons.push_back(this->ui->radioButton4);
    radioButtons.push_back(this->ui->radioButton5);
    radioButtons.push_back(this->ui->radioButton6);
    radioButtons.push_back(this->ui->radioButton7);
    radioButtons.push_back(this->ui->radioButton8);
    radioButtons.push_back(this->ui->radioButton9);
    radioButtons.push_back(this->ui->radioButton10);
    radioButtons.push_back(this->ui->radioButton11);
    radioButtons.push_back(this->ui->radioButton12);
    radioButtons.push_back(this->ui->radioButton13);
    radioButtons.push_back(this->ui->radioButton14);
    radioButtons.push_back(this->ui->radioButton15);
    radioButtons.push_back(this->ui->radioButton16);
    radioButtons.push_back(this->ui->radioButton17);
    radioButtons.push_back(this->ui->radioButton18);
    radioButtons.push_back(this->ui->radioButton19);
    radioButtons.push_back(this->ui->radioButton20);
}

void MainWindow::hideAllRadioButtons()
{
    QListIterator<QRadioButton*> iter(this->radioButtons);
    while(iter.hasNext())
    {
        iter.next()->setVisible(false);
    }
}

void MainWindow::openFileinNewPage(QString fileName,bool newPage)
{
    QString text;
    QString text2;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        file.close();
        return;
    }
    QTextStream in(&file);
    text+=in.readAll();
    file.close();
    if(newPage) this->on_newButton_clicked();
    this->page=this->pages[current];
    this->page->setPath(fileName);
    this->ui->fileNameLabel->setText(this->page->getFileName());
    this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);  
    int flag=0;
    if(this->page->getExtension()==QString("htxt"))
    {
        for(int i=0;i<text.size();i++)
        {
          int value=text[i].toLatin1()-10;
          if(value<=0) value=127+value;
          text2.append(QChar(value).toLatin1());
        }
        flag=1;
    }
    if(flag==1) this->ui->mainTextEdit->setText(text2);
    else this->ui->mainTextEdit->setText(text);
}

void MainWindow::processFinished()
{
     if(this->compilationState==1)
     {
    if(this->process->exitCode())
     this->ui->outputTextEdit->append("Program finished.... with exit code: 1");
    else
        this->ui->outputTextEdit->append("Program finished.... with exit code: 0");
     }
}

void MainWindow::processStateChanged()
{
    qDebug()<<"processStateChanged got called";
}
void MainWindow::setProgramFinished()
{
    this->programFinished=1;
}



void MainWindow::on_radioButton1_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=0;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
    this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));

}

void MainWindow::on_radioButton2_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=1;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
         this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton3_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=2;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
    this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton4_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=3;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
    this->ui->mainTextEdit->setFocus();
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton5_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=4;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
    this->ui->mainTextEdit->setFocus();
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton6_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=5;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
    this->ui->mainTextEdit->setFocus();
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton7_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=6;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton8_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=7;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton9_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=8;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton10_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=9;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_radioButton11_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=10;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton12_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=11;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton13_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=12;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton14_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=13;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton15_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=14;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton16_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=15;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton17_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=16;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton18_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=17;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();

}

void MainWindow::on_radioButton19_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=18;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_radioButton20_clicked()
{
    this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
    current=19;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    QString file=this->pages[current]->getPath();
    if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_pageCloseButton_clicked()
{
    if(this->pages[current]->getFileSaved()==0)
    {
        QMessageBox::StandardButton reply;
        reply=QMessageBox::question(this,"Math Board","Do you want to save file?",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply==QMessageBox::Yes) on_saveButton_clicked();
        if(reply==QMessageBox::Cancel) return;
    }
    if(this->pages.size()==1) exit(0);
    this->page=this->pages[this->current];
    this->pages.removeAt(current);
    delete this->page;
    this->radioButtons[this->pages.size()]->setVisible(false);
    this->ui->radioButton1->setChecked(true);
    current=0;
    this->ui->mainTextEdit->setText(this->pages[current]->getData());
    this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
     this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainTextEdit->setFocus();
}

void MainWindow::on_cmdButton_2_clicked()
{
    this->ui->outputTextEdit->setText("");
    this->on_saveButton_clicked();
    this->page=this->pages[current];
    if(this->page->getExtension()==QString("py"))
        {
                QString program="py";
                QStringList args;
                args<<this->page->getPath();
                if(this->process==NULL) delete this->process;
                this->process =new QProcess();
                connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
                connect(process, SIGNAL(readyReadStandardError()), this, SLOT(processOutput()));
                connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished()));
                connect(process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(processStateChanged()));
                this->process->setInputChannelMode(QProcess::ManagedInputChannel);
                process->setProcessChannelMode(QProcess::MergedChannels);
                this->ui->outputTextEdit->append("Program starts...");
                process->start(program,args,QProcess::ReadWrite);               
        }

        if(this->page->getExtension()==QString("cpp"))
        {
                        QString program="g++";
                        QString exeFileNameWithPath=this->page->getLocation().append(QString("/").append(this->page->getFileNameWithoutExtension().append(".exe")));
                        program="g++";
                        QStringList args;
                        args.append(this->page->getPath());
                        args.append("-o");
                        args.append(exeFileNameWithPath);
                        if(this->process==NULL) delete this->process;
                        this->process =new QProcess();
                        connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
                        connect(process, SIGNAL(readyReadStandardError()), this, SLOT(processOutput()));
                        connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished()));
                        this->process->setInputChannelMode(QProcess::ManagedInputChannel);
                        process->setProcessChannelMode(QProcess::MergedChannels);
                        this->ui->outputTextEdit->append("Program compilation starts...");
                        this->compilationState=0;
                        process->start(program,args,QProcess::ReadWrite);
                        process->waitForFinished();
                        if(process->exitCode()==0)
                        {
                            this->compilationState=1;
                            this->ui->outputTextEdit->append("Program compiled successfully...");
                            program=exeFileNameWithPath;
                            if(this->process==NULL) delete this->process;
                            this->process =new QProcess();
                            connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
                            connect(process, SIGNAL(readyReadStandardError()), this, SLOT(processOutput()));
                            connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished()));
                            this->process->setInputChannelMode(QProcess::ManagedInputChannel);
                            process->setProcessChannelMode(QProcess::MergedChannels);
                            this->ui->outputTextEdit->append("\nProgram starts...");
                            process->start(program,QProcess::ReadWrite);
                        }
        }
}

void MainWindow::on_up_clicked()
{
    if(this->pages.size()==1) return;
    if(this->current==0)
    {
        this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
        current=this->pages.size()-1;
        this->ui->mainTextEdit->setText(this->pages[current]->getData());
        this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
        this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
        this->radioButtons[current]->setChecked(true);
        this->ui->mainTextEdit->setFocus();
    }
    else
    {
        this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
        current=current-1;
        this->ui->mainTextEdit->setText(this->pages[current]->getData());
        this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
        this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
        this->radioButtons[current]->setChecked(true);
        this->ui->mainTextEdit->setFocus();
    }
     QString file=this->pages[current]->getPath();
     if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_down_clicked()
{
    if(this->pages.size()==1) return;
    if(this->current==this->pages.size()-1)
    {
        this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
        current=0;
        this->ui->mainTextEdit->setText(this->pages[current]->getData());
        this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
        this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
        this->radioButtons[current]->setChecked(true);
        this->ui->mainTextEdit->setFocus();
    }
    else
    {
        this->pages[current]->setData(this->ui->mainTextEdit->toPlainText());
        current=current+1;
        this->ui->mainTextEdit->setText(this->pages[current]->getData());
        this->ui->fileNameLabel->setText(this->pages[current]->getFileName());
        this->ui->fileNameLabel->setAlignment(Qt::AlignCenter);
        this->radioButtons[current]->setChecked(true);
        this->ui->mainTextEdit->setFocus();
    }
     QString file=this->pages[current]->getPath();
     if(file!=QString("untitled"))  this->ui->treeView->setCurrentIndex(this->dirModel->index(file));
     this->ui->treeView->expand(this->dirModel->index(file));
}

void MainWindow::on_textColorButton_clicked()
{
    this->textColor=QColorDialog::getColor(Qt::white,this);
    this->ui->mainTextEdit->setTextColor(textColor);
}



void MainWindow::on_fontButton_clicked()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,QFont("Verdana",18));
    if(ok){
      this->ui->mainTextEdit->setFont(font);
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString path=this->dirModel->fileInfo(index).absoluteFilePath();
    this->openFileinNewPage(path,false);
}

void MainWindow::on_lightRadioButton_clicked()
{
    QString text=this->ui->mainTextEdit->toPlainText();
    this->ui->mainTextEdit->clear();
    this->ui->mainTextEdit->setStyleSheet("background-color:white");
    this->ui->mainTextEdit->setTextColor(QColor("black"));
    this->ui->mainTextEdit->setText(text);
}

void MainWindow::on_DarkRadioButton_clicked()
{
    QString text=this->ui->mainTextEdit->toPlainText();
    this->ui->mainTextEdit->clear();
    this->ui->mainTextEdit->setStyleSheet("background-color:black");
    this->ui->mainTextEdit->setTextColor(QColor("white"));
    this->ui->mainTextEdit->setText(text);
}

void MainWindow::on_inputSendButton_clicked()
{
    QString str=this->ui->InputlineEdit->text();
    if(str.size()>0)
    {
        this->ui->outputTextEdit->append(str.trimmed());
        str=str+"\n";
        this->process->write(str.toUtf8());
     }
    this->ui->InputlineEdit->clear();
}

void MainWindow::processOutput()
{
    QTextStream stdoutData(process->readAllStandardOutput());
    QTextStream stdoutError(process->readAllStandardError());
    while (!stdoutData.atEnd())
     {
        QString line = stdoutData.readLine(); //read one line at a time
        this->ui->outputTextEdit->append(line);
     }
    while (!stdoutError.atEnd())
     {
        QString line = stdoutError.readLine(); //read one line at a time
        this->ui->outputTextEdit->append(line);
     }
}

void MainWindow::on_InputlineEdit_returnPressed()
{
    on_inputSendButton_clicked();
}

void MainWindow::on_fullScreenButton_clicked()
{
    this->ui->mainTextEdit->setGeometry(0,0,1600,900);
    this->ui->mainFrame->setVisible(false);
    this->ui->exitFullScreenButton->setVisible(true);
    this->ui->fullScreenButton->setVisible(false);
    this->fullScreenMode=1;
}

void MainWindow::on_exitFullScreenButton_clicked()
{
    this->ui->mainTextEdit->setGeometry(170,60,1381,581);
    this->ui->mainFrame->setVisible(true);
    this->ui->exitFullScreenButton->setVisible(false);
    this->ui->fullScreenButton->setVisible(true);
    this->fullScreenMode=0;
}

