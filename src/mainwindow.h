#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringListModel* objectModel;

    void addValue();

// Блок `слотов`, берут на себя работу по получению и обработке определенных event'ов
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
