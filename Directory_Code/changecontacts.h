#ifndef CHANGECONTACTS_H
#define CHANGECONTACTS_H

#include <QDialog>
#include <changedetail.h>
#include <QStandardItem>
#include <QStandardItemModel>
namespace Ui {
class changeContacts;
}

class changeContacts : public QDialog
{
    Q_OBJECT

public:
    explicit changeContacts(QWidget *parent = nullptr);
    ~changeContacts();
    bool readFile();
    int searchCount(QString name);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::changeContacts *ui;
    QList<QString> contact_Lines;
};

#endif // CHANGECONTACTS_H
