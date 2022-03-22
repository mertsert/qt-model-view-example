#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "dbmanager.h"
#include "models/student.h"
#include "models/teacher.h"
#include "models/grade.h"

#include "views/edit.h"
#include "views/display.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onShowClicked();
    void onEditClicked();
    void onExitClicked();
    void onShowClosed();
    void onEditClosed();

private:
    QWidget *widget_;
    QVBoxLayout *layout_;
    QPushButton *show_;
    QPushButton *edit_;
    QPushButton *exit_;

    DbManager db_;
    Student studentModel_;
    Teacher teacherModel_;
    Grade gradeModel_;

    EditWidget *editWidget_;
    DisplayWidget *showWidget_;

};

#endif // MAINWINDOW_H
