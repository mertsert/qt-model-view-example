#include "mainwindow.h"

#define DB_PATH "../ExamManagement/db/exams.db"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
      db_{DB_PATH},
      studentModel_(nullptr,db_.db()),
      teacherModel_(nullptr,db_.db()),
      gradeModel_(nullptr,db_.db())

{
    showWidget_ = new DisplayWidget(&gradeModel_, &teacherModel_, &studentModel_,this );
    editWidget_ = new EditWidget(&gradeModel_, &teacherModel_, &studentModel_,this );
    showWidget_->hide();
    editWidget_->hide();

    widget_ = new QWidget(this);
    layout_ = new QVBoxLayout(widget_);

    show_ = new QPushButton("Show");
    layout_->addWidget(show_);
    edit_ = new QPushButton("Edit");
    layout_->addWidget(edit_);
    exit_ = new QPushButton("Exit");
    layout_->addWidget(exit_);
    widget_->setLayout(layout_);

    setMinimumSize(editWidget_->minimumSize());
    setCentralWidget(widget_);

    connect(show_ , &QPushButton::clicked, this, &MainWindow::onShowClicked);
    connect(edit_ , &QPushButton::clicked, this, &MainWindow::onEditClicked);
    connect(exit_ , &QPushButton::clicked, this, &MainWindow::onExitClicked);
    connect(showWidget_, &DisplayWidget::clickedReturn, this, &MainWindow::onShowClosed);
    connect(editWidget_, &EditWidget::clickedReturn, this, &MainWindow::onEditClosed);
}

MainWindow::~MainWindow()
{
    widget_->deleteLater();
    layout_->deleteLater();
    show_->deleteLater();
    edit_->deleteLater();
    exit_->deleteLater();
    editWidget_->deleteLater();
    showWidget_->deleteLater();
}

void MainWindow::onShowClicked()
{
    showWidget_->show();
    widget_->hide();
    this->setMinimumSize(showWidget_->minimumSize());
    this->setMaximumSize(showWidget_->minimumSize());
}

void MainWindow::onEditClicked()
{
    editWidget_->show();
    widget_->close();
    this->setMinimumSize(editWidget_->minimumSize());
    this->setMaximumSize(editWidget_->minimumSize());
}

void MainWindow::onExitClicked()
{
    this->close();
    this->destroy();
}

void MainWindow::onShowClosed()
{
    widget_->show();
    showWidget_->close();
}

void MainWindow::onEditClosed()
{
   widget_->show();
   editWidget_->close();
}
