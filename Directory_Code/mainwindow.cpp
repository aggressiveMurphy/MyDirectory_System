#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStatusBar>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <addcontacts.h>
#include <changecontacts.h>
#include <searchcontacts.h>
#include <clearcontacts.h>
QString lastFileName;
int isNew=0;
int isOpen=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //状态栏
    QStatusBar *sBar=statusBar();
    sBar->addWidget(new QLabel("版权所有@黄芷晴20202132009",this));
    sBar->addPermanentWidget(new QLabel("版本:1.0.0",this));
    this->model=new QStandardItemModel;
    setTableHeader();
    this->ui->tableView->setModel(model);//显示列表
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setTableHeader()
{//设置表头
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
void MainWindow::readFromFile()
{//读文件
    QString path=QFileDialog::getOpenFileName(
                this,
                "打开",
                "../",
               "Text(*.txt);;"
                "all(*.*)"
                );
    if(path=="")//用户直接关闭了文件对话框
    {
        return;
    }else{
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::critical(this,"错误","文件打开失败，请重试");
            return;
        }else if(!file.isReadable())
        {
            QMessageBox::warning(this,"错误","文件不可读");
        }
        else{
            lastFileName=path;
            isOpen=1;
        }
        file.close();
    }
}
void MainWindow::displayAll()
{//显示全部
    QFile file(lastFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","打开文件失败,请重试");
        return;
    }else{
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line=in.readLine();
            contact_Lines.append(line);
        }
        file.close();
    }
    int row=0;
    for(int i=0;i<contact_Lines.length();i++)
    {
        QString line=contact_Lines.at(i);
        line=line.trimmed();
        QStringList section=line.split(" ");
        display(row++,section);
    }
    contact_Lines.clear();
}
void MainWindow::display(int row,QStringList section)
{
    for(int i=0;i<section.length();i++)
    {
        this->model->setItem(row,i,new QStandardItem(section.at(i)));
    }
}
void MainWindow::on_actionopen_triggered()
{//打开文件
    this->model->clear();
    setTableHeader();
    readFromFile();
    displayAll();
}
void MainWindow::on_actionsaveas_triggered()
{//文件另存为
    QFile file(lastFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line=in.readLine();
        contact_Lines.append(line);
    }
    file.close();
    QString path=QFileDialog::getOpenFileName(
                this,
                "打开",
                "../",
               "Text(*.txt);;"
                "all(*.*)");
    QFile file1(path);
    if(!file1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","打开文件失败,请重试");
        return;
    }
    else{
        QString content;
        QTextStream out(&file1);
        for(int i=0;i<contact_Lines.length();i++)
        {
            content=contact_Lines.at(i);
            content=content+"\n";
            out<<content;
        }
    }
    file1.close();
    isNew=0;
    lastFileName=path;
    QMessageBox::information(this,"保存文件","保存文件成功",QMessageBox::Ok);
}


void MainWindow::on_pb_search_clicked()
{
    searchContacts s;
    s.exec();
}

void MainWindow::on_pb_add_clicked()
{
    addContacts a;
    a.exec();
}

void MainWindow::on_pb_change_clicked()
{
    changeContacts c;
    c.exec();
}

void MainWindow::on_pb_clear_clicked()
{
    clearContacts cl;
    cl.exec();
}

void MainWindow::on_pb_show_clicked()
{
    model->clear();
    setTableHeader();
    displayAll();
}

void MainWindow::on_actionnew_triggered()
{//新建文件
    int r=QMessageBox::information(this,"新建文件","请先选择文件路径","确定","取消");
    if(r==0)
    {
        QFileDialog dlg;
        QString path=dlg.getOpenFileName(this,"open file","/home","Text(*.txt);;""all(*.*)");
        lastFileName=path;
    }
    isNew=1;
    isOpen=1;
    displayAll();
}

void MainWindow::on_actionabout_triggered()
{//关于
    QMessageBox::about(this,"关于","通讯录管理系统\n"
                                 "作者:黄芷晴\n"
                                 "版本:1.0.0 时间:2021年10月\n"
                                 "开发环境:QT Creator 4.11.0\n"
                                 "鸣谢:\n"
                                 "黑马程序员qt教程: \n https://www.bilibili.com/video/BV1XW411x7NU?p=80 \n"
                                 "qt快速精通教程:\n https://www.bilibili.com/video/BV1Dy4y187rJ");
}
