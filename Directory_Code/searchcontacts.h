#ifndef SEARCHCONTACTS_H
#define SEARCHCONTACTS_H

#include <QDialog>
#include <QFile>
#include <QList>//Qt中的容器类,存储给定类型的列表，并可通过索引访问
#include <QString>
#include <QStandardItem>//条目
#include <QStandardItemModel>//标准条目模型，相当于表格
namespace Ui {
class searchContacts;
}

class searchContacts : public QDialog
{
    Q_OBJECT

public:
    explicit searchContacts(QWidget *parent = nullptr);
    ~searchContacts();
    void doSearch(int index,QString content);
    void display(int row,QStringList section);//通过section判断放在第几列
    void setTableHeader();
    bool readFile();
private slots:
    void on_btn_search_clicked();

private:
    Ui::searchContacts *ui;
    QList<QString> contact_Lines;
    QStandardItemModel *model;
};

#endif // SEARCHCONTACTS_H
