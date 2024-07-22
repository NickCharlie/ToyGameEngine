#include "Demo/MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "Demo/Player.hpp"
#include "Resource/ResManager.hpp"
#include "BackGround/BackGroundGroup.hpp"

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

    _scene.background_groups().push_back(ToyGameEngine::BackGrounds::BackGroundGroup());

    ToyGameEngine::BackGrounds::BackGround* bg = new ToyGameEngine::BackGrounds::BackGround();
    bg->push_pixmap("firstBg", "D:/bg.jpg");
    // bg->set_pixmap_state("firstBg");
    _scene.background_groups()[0].append(bg);

    ToyGameEngine::Spirits::Spirit* sp1 = new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(30, 30), ToyGameEngine::Math::Geometry::Square(30, 30, 20));

    sp1->add_pixmap("shuati", new QPixmap("D:/shuati.png"));
    sp1->add_pixmap("bushua", new QPixmap("D:/bushua.png"));
    sp1->set_pixmap_state(std::string("shuati"));

    _scene.groups().back().append(sp1);

    ToyGameEngine::Spirits::Spirit* sp2 = new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(100, 100), ToyGameEngine::Math::Geometry::Square(100, 100, 60));

    sp2->add_exist_pixmap("shuati");
    sp2->add_exist_pixmap("bushua");
    sp2->set_pixmap_state(std::string("shuati"));

    _scene.groups().back().append(sp2);

    ToyGameEngine::Spirits::Spirit* sp3 = new ToyGameEngine::Spirits::SquareSpirit(
        ToyGameEngine::Math::Geometry::Point(240, 240), ToyGameEngine::Math::Geometry::Square(0, 0, 150));

    sp3->add_exist_pixmap("shuati");
    sp3->add_exist_pixmap("bushua");
    sp3->set_pixmap_state(std::string("bushua"));

    _scene.groups().back().append(sp3);

    _scene.groups().back().append(new ToyGameEngine::Spirits::Player<ToyGameEngine::Math::Geometry::Circle>(
        ToyGameEngine::Math::Geometry::Point(400, 300), ToyGameEngine::Math::Geometry::Circle(400, 300, 20)));

    _scene.start();
}
