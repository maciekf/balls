#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ballsParent = ui->ballsFrame;
    Controller *sth = new Controller(ballsParent);
    sth->init(ballsParent);
    connect(ui->actionNew, SIGNAL(triggered()), Controller::control, SLOT(fillBoard()));
    connect(Controller::control, SIGNAL(newFirstScore(int)), ui->firstScore, SLOT(display(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
