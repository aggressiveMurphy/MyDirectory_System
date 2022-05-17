#ifndef ADDCONTACTS_H
#define ADDCONTACTS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class addContacts; }
QT_END_NAMESPACE

class addContacts : public QDialog
{
    Q_OBJECT

public:
    addContacts(QWidget *parent = nullptr);
    ~addContacts();
    void clearInterface();
    void writeToFile(QString content);
private slots:
    void on_pb_addOK_clicked();

    void on_pb_addCancel_clicked();
private:
    Ui::addContacts *ui;
};
#endif // ADDCONTACTS_H
