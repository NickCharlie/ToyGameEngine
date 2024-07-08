#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include "Scene/Scene.hpp"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui = nullptr;
    ToyGameEngine::Scenes::Scene _scene;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();
};