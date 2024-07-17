#include "Demo/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "Demo/Player.hpp"

#include <QPixmap>

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

    ToyGameEngine::Spirits::Spirit* sp1 = new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(30, 30), ToyGameEngine::Math::Geometry::Square(30, 30, 20));

    sp1->push_pixmap(new QPixmap("D:/shuati.png"));
    sp1->push_pixmap(new QPixmap("D:/bushua.png"));

    _scene.groups().back().append(sp1);

    ToyGameEngine::Spirits::Spirit* sp2 = new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(100, 100), ToyGameEngine::Math::Geometry::Square(100, 100, 60));

    sp2->push_pixmap(new QPixmap("D:/shuati.png"));
    sp2->push_pixmap(new QPixmap("D:/bushua.png"));

    _scene.groups().back().append(sp2);

    ToyGameEngine::Spirits::Spirit* sp3 = new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(240, 240), ToyGameEngine::Math::Geometry::Square(0, 0, 150));

    sp3->push_pixmap(new QPixmap("D:/shuati.png"));
    sp3->push_pixmap(new QPixmap("D:/bushua.png"));
    
    sp3->_pixmap_state = 1;

    _scene.groups().back().append(sp3);

    _scene.groups().back().append(new ToyGameEngine::Spirits::Player<ToyGameEngine::Math::Geometry::Circle>(
        ToyGameEngine::Math::Geometry::Point(400, 300), ToyGameEngine::Math::Geometry::Circle(400, 300, 20)));

    _scene.start();
}
