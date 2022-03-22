#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>


#include "../models/student.h"
#include "../models/teacher.h"
#include "../models/grade.h"

class DisplayStudent: public QWidget
{
    Q_OBJECT
public:
    explicit DisplayStudent(Grade *g, Teacher *s, QWidget *parent = nullptr);
    ~DisplayStudent();


private:
    QComboBox *comboBox_;
    QTableView *gradeView_;
    QLabel *label;
    QVBoxLayout *mainLayout;

    QSortFilterProxyModel model_;

private slots:
    void onTeacherChanged(QString str);

};

class DisplayGrades: public QWidget
{
    Q_OBJECT
public:
    explicit DisplayGrades(Grade *g, Student *t, QWidget *parent = nullptr);
    ~DisplayGrades();

private:
    QComboBox *comboBox_;
    QTableView *gradeView_;
    QLabel *label;
    QVBoxLayout *mainLayout;

    QSortFilterProxyModel model_;

private slots:
    void onStudentChanged(QString str);
};

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(Grade *gModel, Teacher *tModel, Student *sModel , QWidget *parent = nullptr);
    ~DisplayWidget();
private:

    QTabWidget *tabWidget_;
    QPushButton *backButton_;
    QVBoxLayout *mainLayout;

    DisplayGrades *tabGrades_;
    DisplayStudent *tabStudents_;



signals:
    void clickedReturn();
};

#endif // DISPLAY_H
