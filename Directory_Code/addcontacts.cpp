#include "addcontacts.h"
#include "ui_addcontacts.h"
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
extern QString lastFileName;
addContacts::addContacts(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addContacts)
{
    ui->setupUi(this);
}

addContacts::~addContacts()
{
    delete ui;
}

void addContacts::on_pb_addOK_clicked()
{
    //获取用户输入的信息
    QString name=this->ui->le_name->text();
    QString phone=this->ui->le_phone->text();
    QString email=this->ui->le_email->text();
    QString address=this->ui->le_address->text();
    QString group=this->ui->cb_group->currentText();
    //获取性别勾选信息,使用了按钮组
    QString sex=this->ui->sexGroup->checkedButton()->text();//获取被选中的按钮的文本信息
    QString content=name+'\n'+sex+'\n'+phone+'\n'+email+'\n'+address+'\n'+group;
    QString cont=name+' '+sex+' '+phone+' '+email+' '+address+' '+group+' ';
    //判断用户输入内容是否完整
    if(name.length()<1||phone.length()!=11||email.length()<1||email.contains("@")!=1||address.length()<1)
    {
        QMessageBox::critical(this,"错误","信息填写不符合要求，请重新检查","确定");
    }else{
        int r=QMessageBox::question(this,"请确认信息",content,"确认","取消");
        if(r==0)
        {
            writeToFile(cont);
            clearInterface();
        }
        else
            this->close();
    }
}
void addContacts::clearInterface()
{//还原界面
    this->ui->le_name->clear();
    this->ui->le_phone->clear();
    this->ui->le_email->clear();
    this->ui->le_address->clear();
    this->ui->rb_male->setChecked(true);
    this->ui->cb_group->setCurrentIndex(0);
    this->ui->le_name->setFocus();//还原光标位置
}

void addContacts::on_pb_addCancel_clicked()
{
    this->close();
}
void addContacts::writeToFile(QString content)
{
    QFile file(lastFileName);
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","打开文件失败,请重试");
        return;
    }
    else{
        QTextStream out(&file);
        content=content+"\n";
        out<<content;
    }
    file.close();
}
