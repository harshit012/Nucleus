#ifndef PAGE_H
#define PAGE_H

#include<QString>
#include<QDebug>
class Page
{
private:
int fileSaved;
QString data;
QString path;
QString fileName;
QString fileNameWithoutExtension;
QString extension;
QString location;
public:
    Page();
    int getFileSaved() const;
    QString getData() const;
    void setData(const QString &value);
    QString getPath() const;
    void setPath(const QString &value);
    QString getExtension() const;
    QString getFileName() const;
    QString getLocation() const;
    QString getFileNameWithoutExtension() const;
};

#endif // PAGE_H
