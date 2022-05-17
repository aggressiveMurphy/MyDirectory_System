#include "clearcontacts.h"
#include "ui_clearcontacts.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
extern QString lastFileName;
clearContacts::clearContacts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clearContacts)
{
    ui->setupUi(this);
    if(readFile()==0)
    {
        QMessageBox::critical(this,"错误","文件打开失败，请重试");
        this->close();
    }
}

clearContacts::~clearContacts()
{
    delete ui;
}

void clearContacts::on_pushButton_clicked()
{
    QString name=this->ui->le_name->text();
    for(int i=0;i<contact_Lines.length();i++)
    {
        QString line=contact_Lines.at(i);
        line=line.trimmed();
        QStringList section=line.split(" ");
        QString s="";
        if(searchCount(name,s)==-1)
        {
            QMessageBox::warning(this,"错误","搜索不到联系人，请重试！");
            this->close();
            break;
        }
        else
        {
            QString content;
            int row=searchCount(name,content);
            int r=QMessageBox::question(this,"确定删除以下信息？",content,"确定","取消");
            if(r==0)
            {
                contact_Lines.removeAt(row);
                QFile file(lastFileName);
                if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
                {
                    QMessageBox::critical(this,"错误","文件打开失败，请重试");
                    this->close();
                }
                else
                {
                    QTextStream out(&file);
                    for(int i=0;i< contact_Lines.length();i++)
                    {
                        QString line = contact_Lines.at(i)+"\n";
                        out << line;
                    }
                    file.close();
                    int r1=QMessageBox::information(this,"提示","删除成功","确认","取消");
                    if(r1==0)
                        this->close();
                    break;
                }
            }
            if(r==1)
                this->close();
            break;
        }
    }
}
bool clearContacts::readFile()
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
int clearContacts::searchCount(QString name,QString &content)
{
    int row = 0;
    int num = -1;
    for(int i=0;i< contact_Lines.length();i++){
        QString line = contact_Lines.at(i);
        line = line.trimmed();
        QStringList section = line.split(" ");
         if(section.at(0)==name)
         {
             content=section.at(0)+'\n'+section.at(1)
                     +'\n'+section.at(2)+'\n'+section.at(3)
                     +'\n'+section.at(4)+'\n'+section.at(5);
             num = row;
          }
         row++;
    }
    return num;
}

void clearContacts::on_pushButton_2_clicked()
{
    this->close();
}
