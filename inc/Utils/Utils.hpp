#pragma once

#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QSize>

namespace ToyGameEngine 
{
    namespace Utils
    {
        class Util {
        public:
            static QSize get_mainwindow_size() {
                QWidgetList widgets = QApplication::topLevelWidgets();
                for (QWidget* widget : widgets) {
                    if (QMainWindow* mainwindow = qobject_cast<QMainWindow*>(widget)) {
                        return mainwindow->size();
                    }
                }
                return QSize();
            }
        };
    }
}