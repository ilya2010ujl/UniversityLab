#include "mainwindow.h"

MainWindow::MainWindow(Viewport *viewport, QWidget *parent)
    : QMainWindow(parent), m_viewport(viewport)
{

    setCentralWidget(m_viewport);

    this->setFocusPolicy(Qt::NoFocus);
    m_viewport->setFocusPolicy(Qt::StrongFocus);
}

