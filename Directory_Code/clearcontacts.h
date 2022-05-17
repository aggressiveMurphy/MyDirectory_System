#ifndef CLEARCONTACTS_H
#define CLEARCONTACTS_H

#include <QDialog>

namespace Ui {
class clearContacts;
}

class clearContacts : public QDialog
{
    Q_OBJECT

public:
    explicit clearContacts(QWidget *parent = nullptr);
    ~clearContacts();
    bool readFile();
    int searchCount(QString name,QString &content);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::clearContacts *ui;
    QList<QString> contact_Lines;
};

#endif // CLEARCONTACTS_H
