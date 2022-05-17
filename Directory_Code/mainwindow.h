#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTableHeader();
    void readFromFile();
    void displayAll();
    void display(int row,QStringList section);
private slots:
    void on_actionopen_triggered();
    void on_actionnew_triggered();
    void on_actionsaveas_triggered();
    void on_pb_search_clicked();
    void on_pb_add_clicked();
    void on_pb_change_clicked();
    void on_pb_clear_clicked();
    void on_pb_show_clicked();
    void on_actionabout_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QList<QString> contact_Lines;
};
#endif // MAINWINDOW_H
