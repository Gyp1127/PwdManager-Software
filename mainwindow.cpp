#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Password Manager");

    cellActive = false;
    table = new QTableWidget(ui->tableWidget);
    // connect(ui->tableWidget, &QTableWidget::itemClicked, this, &MainWindow::on_tableWidget_itemClicked);
    // connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::on_btnRemove_clicked);
    displayTable();
    // setCentralWidget(table);

    // // Setup Directory
    // QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\toDoFile.txt");

    // // Check if it is possible to use our file
    // if (!file.open(QIODevice::ReadWrite)) {
    //     QMessageBox::information(0,"error", file.errorString());
    // }

    // // Load in all the items in the file
    // QTextStream in(&file);
    // while(!in.atEnd()) {
    //     QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
    //     ui->listWidget->addItem(item);
    //     item->setFlags(item->flags() | Qt::ItemIsEditable);
    // }

    // file.close();


}

MainWindow::~MainWindow()
{

    // // Setup Directory
    // QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\toDoFile.txt"); // we can put the path in header file

    // // Check if it is possible to use our file
    // if (!file.open(QIODevice::ReadWrite)) {
    //     QMessageBox::information(0,"error", file.errorString());
    // }

    // // Save all the items in the file
    // QTextStream out(&file);

    // for (int i = 0; i < ui->listWidget->count(); ++i) {
    //     out<<ui->listWidget->item(i)->text()<<"\n";
    // }

    // file.close();
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    QString sitetxt = ui->siteText->text();
    QString pwtxt = ui->pwText->text();

    if (sitetxt.isEmpty() || pwtxt.isEmpty()) {
        return;
    }

    QTableWidgetItem* siteitem = new QTableWidgetItem();
    QTableWidgetItem* pwitem = new QTableWidgetItem();
    siteitem->setText(sitetxt);
    pwitem->setText(pwtxt);

    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row,0,siteitem);
    table->setItem(row,1,pwitem);


    // Clear Texts
    ui->siteText->clear();
    ui->pwText->clear();
    ui->siteText->setFocus();

    // QListWidgetItem* item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
    // ui->listWidget->addItem(item);
    // item->setFlags(item->flags() | Qt::ItemIsEditable);
    // ui->txtTask->clear();
    // ui->txtTask->setFocus();



}


void MainWindow::on_btnRemove_clicked()
{
    // if (cellActive)
    // {
    //     ui->tableWidget->removeRow(rowActive);
    //     cellActive = false;
    // }

    QWidget *w = qobject_cast<QWidget *>(sender()->parent());
    if(w){
        int row = ui->tableWidget->indexAt(w->pos()).row();
        ui->tableWidget->removeRow(row);
        ui->tableWidget->setCurrentCell(0, 0);
    }

}

void MainWindow::on_btnGenerate_clicked()
{
    QString password = "";
    srand(time(NULL));

    for (int i = 0; i < PW_LEN; i++) {
        int randomIndex = rand() % characters.length();
        password += characters[randomIndex];
    }

    ui->pwText->setText(password);
}


void MainWindow::displayTable()
{
    table->setRowCount(0);
    table->setColumnCount(2);


    QStringList hlabels;
    hlabels << "Site" << "Password";
    table->setHorizontalHeaderLabels(hlabels);

    table->setMinimumSize(570, 450);
    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 470);

}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    cellActive = true;
    rowActive = item->row();
    qDebug() << ui->tableWidget->itemAt(rowActive, 0)->text();
}
