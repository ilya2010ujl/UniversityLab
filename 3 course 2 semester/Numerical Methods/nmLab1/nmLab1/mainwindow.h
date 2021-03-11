#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Viewport/viewport.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Viewport *viewport, QWidget *parent = nullptr);

private:
    Viewport *m_viewport;
};
#endif // MAINWINDOW_H
