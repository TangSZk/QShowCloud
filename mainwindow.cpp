#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->update();
    cloudGLWidget = new glShowCloud(ui->openGLWidget);
    qDebug("w:%d h:%d",width(),height());
    cloudGLWidget->resize(ui->openGLWidget->width(),ui->openGLWidget->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    cloudGLWidget->update();
}

