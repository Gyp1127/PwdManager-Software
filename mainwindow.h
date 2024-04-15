#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtablewidget.h"
#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGenerate_clicked();

    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void displayTable();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QTableWidget* table;
    bool cellActive;
    int rowActive;
    const QString characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&";
    int PW_LEN = 16;
};
#endif // MAINWINDOW_H
