#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QTabWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>

#include "../models/student.h"
#include "../models/teacher.h"
#include "../models/grade.h"

class EditStudent: public QWidget
{
    Q_OBJECT
public:
    explicit EditStudent(Student *model, QWidget *parent = nullptr);
    ~EditStudent();

private:
    QFormLayout *formLayout_;
    QLineEdit *nameLineEdit_;
    QLineEdit *surnameLineEdit_;
    QPushButton *button_;

    Student *model_;

private slots:
    void onStudentSave();

};

class EditGrade: public QWidget
{
    Q_OBJECT
public:
    explicit EditGrade(Grade *model, Teacher *teacher, Student *student, QWidget *parent = nullptr);
    ~EditGrade();

private:
    QFormLayout *formLayout_;
    QSpinBox  *resultSpinBox_;
    QComboBox *teacherComboBox_;
    QComboBox *studentComboBox_;
    QPushButton *button_;

    Grade *model_;

private slots:
    void onGradeSave();
};

class EditTeacher: public QWidget
{
    Q_OBJECT
public:
    explicit EditTeacher(Teacher *model, QWidget *parent = nullptr);
    ~EditTeacher();

private:

    QFormLayout *formLayout_;
    QLineEdit *nameLineEdit_;
    QLineEdit *surnameLineEdit_;
    QPushButton *button_;

    Teacher *model_;

private slots:
    void onTeacherSave();

};

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditWidget(Grade *gModel, Teacher* tModel, Student *sModel, QWidget *parent = nullptr);
    ~EditWidget();

private:
    QTabWidget *tabWidget_;
    QVBoxLayout *mainLayout;
    QPushButton *backButton_;

    EditStudent *tabAddStudent_;
    EditTeacher *tabAddTeacher_;
    EditGrade *tabAddGrade_;

signals:
    void clickedReturn();

};

#endif // EDIT_H
