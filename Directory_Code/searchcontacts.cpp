#include "searchcontacts.h"
#include "ui_searchcontacts.h"
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>//字符串容器
#include <QDebug>
extern QString lastFileName;
searchContacts::searchContacts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchContacts)
{
    ui->setupUi(this);
    this->model=new QStandardItemModel;
    setTableHeader();
    //给表格视图绑定模型
    this->ui->tableView->setModel(model);
    if(readFile()==0)
    {
        QMessageBox::critical(this,"错误","文件打开失败，请重试");
        this->close();
    }
}

searchContacts::~searchContacts()
{
    delete ui;
}

void searchContacts::on_btn_search_clicked()
{
    this->model->clear();
    setTableHeader();
    int index=this->ui->cb_method->currentIndex();
    QString content=this->ui->le_content->text();
    doSearch(index,content);
}
void searchContacts::doSearch(int index,QString content)
{
    int row=0;
    for(int i=0;i<contact_Lines.length();i++)
    {
        QString line=contact_Lines.at(i);//取第i行
        line=line.trimmed();//去掉字符串开头和末尾的空白
        QStringList section=line.split(" ");//将用空格分开的内容拆分成几个字符串并存在字符串表中
        switch (index)
        {
         case 1:
            if(content==section.at(0))
            {
                display(row++,section);
            }
            break;
         case 2:
            if(content==section.at(2))
            {
                display(row++,section);
            }
            break;
        case 3:
           if(content==section.at(5))
           {
               display(row++,section);
           }
           break;
        default:
            break;
        }
    }
}
void searchContacts::display(int row,QStringList section)
{
    for(int i=0;i<section.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(section.at(i)));
    }
}
void searchContacts::setTableHeader()
{
    //设置表头及宽度
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("手机"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("邮箱"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("地址"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("所属组别"));
    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,50);
    this->ui->tableView->setColumnWidth(2,150);
    this->ui->tableView->setColumnWidth(3,200);
    this->ui->tableView->setColumnWidth(4,150);
    this->ui->tableView->setColumnWidth(5,100);
}
bool searchContacts::readFile()
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
