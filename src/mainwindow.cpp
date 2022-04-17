#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::addValue);

    objectModel = new QStringListModel(this);

    ui->listView->setModel(objectModel);
}

MainWindow::~MainWindow() {
    delete objectModel;
    delete ui;
}

// Функция добавления значения (вызывается по получению Enter в строке ввода)
void MainWindow::addValue() {
    // Получаем значение с строки ввода
    auto data = ui->lineEdit->text();

    if (data == "")
            return;

    // Создаем потоковый объект хранения вводимых строк и присваиваем ему текущие данные в модели
    QStringList stream = objectModel->stringList();

    // Добавляем к текущим данным новую строчку
    stream << data;

    objectModel->setStringList(stream);

    ui->lineEdit->clear();
}

// Слот обработки двойного нажатия на объект в списке
void MainWindow::on_listView_doubleClicked(const QModelIndex &index) {
    auto messageBox = new QMessageBox;

    messageBox->setWindowFlags(Qt::WindowMinimizeButtonHint);
    messageBox->setStyleSheet("color:#f8f8f8;\nbackground-color:#181818;");
    messageBox->setWindowTitle(this->windowTitle());

    messageBox->setText(QString("You want to delete element \"%1\"\?").arg(objectModel->data(index).toString()));
    messageBox->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);

    this->setEnabled(false);

    messageBox->show();

    connect(messageBox, &QMessageBox::accepted,[this, messageBox, index]() {
        objectModel->removeRow(index.row());

        messageBox->close();

        this->setEnabled(true);
    });

    connect(messageBox, &QMessageBox::rejected, [this, messageBox]() {
        messageBox->close();

        this->setEnabled(true);
    });
}
