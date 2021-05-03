#include "page.h"

int Page::getFileSaved() const
{
    return fileSaved;
}


QString Page::getData() const
{
    return data;
}

void Page::setData(const QString &value)
{
    data = value;
}

QString Page::getPath() const
{
    return path;
}

void Page::setPath(const QString &value)
{
    path = value;
    QString tempString=value;
    int index=-1;
    int finalIndex;
    while(1)
    {
        index=tempString.indexOf('/',index+1);
        if(index==-1) break;
        finalIndex=index;
    }
    this->fileName=value.right(tempString.size()-finalIndex-1);
    this->location=value.left(finalIndex);
    index=this->fileName.indexOf('.');
    this->extension=fileName.right(this->fileName.size()-index-1);
    this->fileNameWithoutExtension=fileName.left(index);
    this->fileSaved=1;
}

QString Page::getExtension() const
{
    return extension;
}


QString Page::getFileName() const
{
    return fileName;
}

QString Page::getLocation() const
{
    return location;
}

QString Page::getFileNameWithoutExtension() const
{
    return fileNameWithoutExtension;
}

Page::Page()
{
    this->fileSaved=0;
    this->fileName="untitled";
    this->path="untitled";
}
