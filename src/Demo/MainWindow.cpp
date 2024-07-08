#include "Demo/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "Spirit/Spirit.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ui->canvas->load_scene(&_scene);
    _scene.groups().emplace_back();

    ToyGameEngine::Spirits::SquareSpirit *square = new ToyGameEngine::Spirits::SquareSpirit(ToyGameEngine::Math::Geometry::Point(30, 30));
    square->replace(ToyGameEngine::Math::Geometry::Square(30, 30, 20));
    _scene.groups().back().append(square);

    square = new ToyGameEngine::Spirits::SquareSpirit(ToyGameEngine::Math::Geometry::Point(100, 100));
    square->replace(ToyGameEngine::Math::Geometry::Square(100, 100, 60));
    _scene.groups().back().append(square);

    square = new ToyGameEngine::Spirits::SquareSpirit(ToyGameEngine::Math::Geometry::Point(240, 240));
    square->replace(ToyGameEngine::Math::Geometry::Square(240, 240, 150));
    _scene.groups().back().append(square);
}
