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
    displayTable();
    loadTable();


}

MainWindow::~MainWindow()
{

    saveTable();

    delete ui;
}

void MainWindow::loadTable() {
    // Setup Directory
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\pwman.txt");

    // Check if it is possible to use our file
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0,"error", file.errorString());
    }

    // Load in all the items in the file
    QTextStream in(&file);
    while(!in.atEnd()) {

        QString sitetxt = QString(in.readLine());
        QString pwtxt = QString(in.readLine());

        addItemToTable(&sitetxt, &pwtxt);
    }

    // QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
    // ui->listWidget->addItem(item);
    // item->setFlags(item->flags() | Qt::ItemIsEditable);

    file.close();
}

void MainWindow::saveTable() {

    // Setup Directory
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\pwman.txt"); // we can put the path in header file

    // Check if it is possible to use our file
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0,"error", file.errorString());
    }
    qDebug() << table->rowCount();
    // Save all the items in the file
    QTextStream out(&file);

    for (int i = 0; i < table->rowCount(); ++i) {
        out << table->item(i,0)->text() << "\n" << table->item(i, 1)->text() << "\n";
        // qDebug() << i;
    }

    file.close();

}

void MainWindow::on_btnAdd_clicked()
{

    QString sitetxt = ui->siteText->text();
    QString pwtxt = ui->pwText->text();


    if (sitetxt.isEmpty() || pwtxt.isEmpty()) {
        return;
    }

    addItemToTable(&sitetxt, &pwtxt);


    // Clear Texts
    ui->siteText->clear();
    ui->pwText->clear();
    ui->siteText->setFocus();

}

void MainWindow::addItemToTable(QString* sitetxt, QString* pwtxt) {

    QTableWidgetItem* siteitem = new QTableWidgetItem();
    QTableWidgetItem* pwitem = new QTableWidgetItem();
    siteitem->setText(*sitetxt);
    pwitem->setText(*pwtxt);

    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row,0,siteitem);
    table->setItem(row,1,pwitem);

}


void MainWindow::on_btnRemove_clicked()
{

}

void MainWindow::on_btnGenerate_clicked()
{
    QString password = "";
    srand(time(NULL));

    // Future extension -> make it meet current standards
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
