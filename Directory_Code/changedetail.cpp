#include "changedetail.h"
#include "ui_changedetail.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
extern QString lastFileName;
changeDetail::changeDetail(QList<QString> Line,int i,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeDetail)
{
    c=Line;
    index=i;
    ui->setupUi(this);
    QString line = c.at(index);
    line = line.trimmed();
    QStringList section = line.split(" ");
    this->ui->le_name->setText(section.at(0));
    this->ui->le_phone->setText(section.at(2));
    this->ui->le_email->setText(section.at(3));
    this->ui->le_address->setText(section.at(4));
    if(section.at(1)=="男")
    {
        this->ui->rb_male->setChecked(true);
    }
    else
    {
        this->ui->rb_female->setChecked(true);
    }

    if(section.at(5)=="家人")
    {
        this->ui->comboBox->setCurrentIndex(0);
    }
    if(section.at(5)=="朋友")
    {
        this->ui->comboBox->setCurrentIndex(1);
    }
    if(section.at(5)=="领导")
    {
        this->ui->comboBox->setCurrentIndex(2);
    }
    else if(section.at(5)=="同事")
    {
        this->ui->comboBox->setCurrentIndex(3);
    }
    if(section.at(5)=="同学")
    {
        this->ui->comboBox->setCurrentIndex(4);
    }
    if(section.at(5)=="其他")
    {
        this->ui->comboBox->setCurrentIndex(5);
    }
    this->ui->le_phone->setFocus();
}

changeDetail::~changeDetail()
{
    delete ui;
}

void changeDetail::on_pushButton_clicked()
{
    QString name=this->ui->le_name->text();
    QString phone=this->ui->le_phone->text();
    QString email=this->ui->le_email->text();
    QString address=this->ui->le_address->text();
    QString group=this->ui->comboBox->currentText();
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
            readFile();
            c.replace(index,cont);
            QFile file(lastFileName);
            file.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text);
            QTextStream out(&file);
            for(int i=0;i< c.length();i++)
            {
                QString line = c.at(i)+"\n";
                out << line;
            }
            file.close();
            int k=QMessageBox::information(this,"提示","修改成功","确认","取消");
            if(k==0)
                this->close();
        }
        if(r==1)
            this->close();
    }
}
bool changeDetail::readFile()
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

void changeDetail::on_pushButton_2_clicked()
{
    this->close();
}
