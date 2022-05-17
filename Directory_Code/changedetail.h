#ifndef CHANGEDETAIL_H
#define CHANGEDETAIL_H

#include <QDialog>
//explicit修饰的构造函数只能以指定形式被调用
//编译器支持C++11，会变为nullptr，不支持变为NULL。所以直接用nullptr
namespace Ui {
class changeDetail;
}

class changeDetail : public QDialog
{
    Q_OBJECT

public:
    explicit changeDetail( QList<QString> contact_Lines,int i,QWidget *parent = nullptr);
    ~changeDetail();
    void setData(QString name);
    bool readFile();
private:
    Ui::changeDetail *ui;
protected:
    QList<QString> c;
    QList<QString> contact_Lines;
    int index;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // CHANGEDETAIL_H
