#include "changecontacts.h"
#include "ui_changecontacts.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
extern QString lastFileName;
changeContacts::changeContacts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeContacts)
{
    ui->setupUi(this);
}

changeContacts::~changeContacts()
{
    delete ui;
}

void changeContacts::on_pushButton_clicked()
{
    int i = 0;
    QString name = this->ui->le_name->text();
    if(readFile()== 0){
        QMessageBox::critical(this,"错误","文件无法读取！","确定");
        this->close();
    }
    if(searchCount(name)==-1)
    {
        QMessageBox::critical(this,"错误","未能查询到联系人，请重新输入！","确定");
    }else{
       i = searchCount(name);
       changeDetail c(contact_Lines,i);
       c.exec();
    }
}
int changeContacts::searchCount(QString name)
{
    int rows = 0;
    int num = -1;
    for(int i=0;i<contact_Lines.length();i++)
    {
        QString line = contact_Lines.at(i);
        line = line.trimmed();//去掉line头尾的空格
        QStringList section = line.split(" ");//将line中以空格分隔的字符串拆分成不同部分
         if(section.at(0)==name){
               num = rows;
          }
         rows++;
    }
    return num;
}
bool changeContacts::readFile()
{
    QFile file(lastFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line=in.readLine();
        contact_Lines.append(line);
    }
    file.close();
    return 1;
}

void changeContacts::on_pushButton_2_clicked()
{
    this->close();
}
