#include <QKeyEvent>
#include <QDebug>
#include <Qt>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ObjectsToDraw/Point3D/point3d.h"
#include "ObjectsToDraw/Line3D/line3d.h"

// #define TINYOBJLOADER_USE_DOUBLE
#include "tinyobjloader/tinyobjloader/tiny_obj_loader.h"
#include "ModelToDraw/modeltodraw.h"

#define DEBUG

MainWindow::MainWindow(QWidget *parent)
    :  QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    // setCentralWidget(m_viewport);

    m_ui->setupUi(this);

    this->setFocusPolicy(Qt::NoFocus);
    m_ui->viewport->setFocusPolicy(Qt::StrongFocus);

    QWidget::connect(m_ui->actionPoint, &QAction::triggered, this, &MainWindow::addPoint);
    QWidget::connect(m_ui->actionLine, &QAction::triggered, this, &MainWindow::addLine);
    QWidget::connect(m_ui->actionload_obj, &QAction::triggered, this, &MainWindow::loadObj);

    QWidget::connect(m_ui->actionClear, &QAction::triggered, this,
    [&]()
    {
        m_ui->viewport->clear();
    });

    QWidget::connect(m_ui->actioneditcolorcurrentobject, &QAction::triggered, this,
    [&]()
    {
        m_ui->viewport->editColorCurrentObject();
    });

    QWidget::connect(m_ui->actioncameratoorigin, &QAction::triggered, this,
    [&]()
    {
        m_ui->viewport->cameraToOrigin();
    });

    m_contextMenu = new QMenu();

    m_contextMenu->addMenu(m_ui->menuadd);
    m_contextMenu->addMenu(m_ui->menuviewport);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

QSize MainWindow::sizeHint() const
{
    return QSize(1024, 768);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
#ifdef DEBUG
    qDebug() << "MainWindow " << event;
#endif
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
#ifdef DEBUG
    qDebug() << "MainWindow " << event;
#endif
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef DEBUG
    qDebug() << "MainWindow " << event;
#endif
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
#ifdef DEBUG
    qDebug() << "MainWindow " << event;
#endif
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
#ifdef DEBUG
    qDebug() << "MainWindow " << event;
#endif
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void MainWindow::clear()
{
    m_ui->viewport->clear();
    m_ui->viewport->update();
}

void MainWindow::addPoint()
{
    double x = QInputDialog::getDouble(this, tr("addPoint"), tr("x:"));
    double y = QInputDialog::getDouble(this, tr("addPoint"), tr("y:"));
    double z = QInputDialog::getDouble(this, tr("addPoint"), tr("z:"));

    Point3D *point = new Point3D(QVector3D(x,y,z), 5);

    m_ui->viewport->addObject(point);

    m_ui->viewport->update();
}

void MainWindow::addLine()
{
    double x_begin = QInputDialog::getDouble(this, tr("addPoint"), tr("x:"), m_ui->viewport->geometry().width() / 4);
    double y_begin = QInputDialog::getDouble(this, tr("addPoint"), tr("y:"), 0);
    double z_begin = QInputDialog::getDouble(this, tr("addPoint"), tr("z:"), 0);

    double x_end = QInputDialog::getDouble(this, tr("addPoint"), tr("x:"), - m_ui->viewport->geometry().width() / 4);
    double y_end = QInputDialog::getDouble(this, tr("addPoint"), tr("y:"), 0);
    double z_end = QInputDialog::getDouble(this, tr("addPoint"), tr("z:"), 0);

    Line3D *line = new Line3D(QVector3D(x_begin, y_begin, z_begin), QVector3D(x_end, y_end, z_end));

    m_ui->viewport->addObject(line);

    m_ui->viewport->update();
}

void MainWindow::loadObj()
{
    std::string inputfile = QFileDialog::getOpenFileName(this, tr("Open .obj"),
                                                     "C:\\Users\\Ihtie\\Desktop\\something\\Projects\\objModels",
                                                         tr("*.obj")).toStdString();
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    for(size_t i = 0; i < inputfile.size(); ++i)
    {
        if(inputfile[i] == '/')
        {
            inputfile[i] = '\\';
        }
    }

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty())
    {
        QMessageBox::warning(this, "Warning!", warn.c_str());
    }

    if (!err.empty())
    {
        QMessageBox::warning(this, "Error!", err.c_str());
    }

    if (!ret)
    {
        return;
    }
    // C:/Users/Ihtie/Desktop/something/Projects/objModels/square.obj
    // C:\Users\Ihtie\Desktop\something\Projects\objModels\square.obj

    QVector<qreal> vertex;
    QVector<qreal> normals;
    QVector<qreal> color;

    QColor C = QColorDialog::getColor();;

    for (size_t s = 0; s < shapes.size(); s++)
    {
      // Loop over faces(polygon)
      size_t index_offset = 0;
      for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
      {
        size_t fv = shapes[s].mesh.num_face_vertices[f];

        // Loop over vertices in the face.
        for (size_t v = 0; v < fv; v++) {
          // access to vertex
          tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
          vertex.push_back(attrib.vertices[3*idx.vertex_index+0]);
          vertex.push_back(attrib.vertices[3*idx.vertex_index+1]);
          vertex.push_back(attrib.vertices[3*idx.vertex_index+2]);

          normals.push_back(attrib.normals[3*idx.normal_index+0]);
          normals.push_back(attrib.normals[3*idx.normal_index+1]);
          normals.push_back(attrib.normals[3*idx.normal_index+2]);

          color.push_back(C.redF());
          color.push_back(C.greenF());
          color.push_back(C.blueF());
        }
        index_offset += fv;

        // per-face material
        shapes[s].mesh.material_ids[f];
      }
    }

#ifdef DEBUG
    qDebug() << "end read .obj";
#endif

    ModelToDraw *model = new ModelToDraw(vertex, normals, color, vertex.size() / 3);

    m_ui->viewport->addObject(model);

    m_ui->viewport->update();
}
