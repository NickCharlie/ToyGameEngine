#include "Demo/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "Demo/Player.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    _scene.stop();
    delete ui;
}

void MainWindow::init()
{
    ui->canvas->load_scene(&_scene);
    _scene.append_spiritgroup();
    _scene.groups().back().key_event_update = true;

    _scene.groups().back().append(new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(30, 30), ToyGameEngine::Math::Geometry::Square(30, 30, 20)));

    _scene.groups().back().append(new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(100, 100), ToyGameEngine::Math::Geometry::Square(100, 100, 60)));

    _scene.groups().back().append(new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(240, 240), ToyGameEngine::Math::Geometry::Square(0, 0, 150)));

    _scene.groups().back().append(new ToyGameEngine::Spirits::Player<ToyGameEngine::Math::Geometry::Circle>(
        ToyGameEngine::Math::Geometry::Point(400, 300), ToyGameEngine::Math::Geometry::Circle(400, 300, 20)));

    _scene.start();
}
