#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QString>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};