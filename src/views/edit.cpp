#include "edit.h"
#include <QMessageBox>

EditStudent::EditStudent(Student *model, QWidget *parent)
    : QWidget(parent), model_{model}
{
    nameLineEdit_ = new QLineEdit(this);
    surnameLineEdit_ = new QLineEdit(this);
    button_ = new QPushButton("Save",this);
    connect(button_,&QPushButton::clicked, this, &EditStudent::onStudentSave);

    formLayout_ = new QFormLayout(this);
    formLayout_->addRow(tr("Name:"), nameLineEdit_);
    formLayout_->addRow(tr("Surname:"), surnameLineEdit_);
    formLayout_->addRow(button_);

    setLayout(formLayout_);
}

EditStudent::~EditStudent()
{
    formLayout_->deleteLater();
    nameLineEdit_->deleteLater();
    surnameLineEdit_->deleteLater();
    button_->deleteLater();
}

void EditStudent::onStudentSave()
{
    qDebug() << "Saving" << nameLineEdit_->text() << " " << surnameLineEdit_->text();

    if( model_->addItem(nameLineEdit_->text(), surnameLineEdit_->text()) )
    {
        QMessageBox::information(
            this,
            tr("Status"),
            tr("Database updated succesfully..") );
    }
    else
    {
        QMessageBox::warning(
            this,
            tr("Status"),
            tr("An error occured to write db.") );
    }
}

EditTeacher::EditTeacher(Teacher *model, QWidget *parent)
    : QWidget(parent), model_{model}
{
    nameLineEdit_ = new QLineEdit(this);
    surnameLineEdit_ = new QLineEdit(this);
    button_ = new QPushButton("Save",this);
    connect(button_,&QPushButton::clicked, this, &EditTeacher::onTeacherSave);

    formLayout_ = new QFormLayout(this);
    formLayout_->addRow(tr("Name:"), nameLineEdit_);
    formLayout_->addRow(tr("Surname:"), surnameLineEdit_);
    formLayout_->addRow(button_);

    setLayout(formLayout_);
}

EditTeacher::~EditTeacher()
{
    formLayout_->deleteLater();
    nameLineEdit_->deleteLater();
    surnameLineEdit_->deleteLater();
    button_->deleteLater();
}

void EditTeacher::onTeacherSave()
{
    qDebug() << "Saving" << nameLineEdit_->text() << " " << surnameLineEdit_->text();

    if( model_->addItem(nameLineEdit_->text(), surnameLineEdit_->text()) )
    {
        QMessageBox::information(
            this,
            tr("Status"),
            tr("Database updated succesfully..") );
    }
    else
    {
        QMessageBox::warning(
            this,
            tr("Status"),
            tr("An error occured to write db.") );
    }
}

EditGrade::EditGrade(Grade *model, Teacher *teacher, Student *student,  QWidget *parent)
    : QWidget(parent), model_{model}
{
    teacher->select();
    student->select();

    resultSpinBox_ = new QSpinBox(this);
    resultSpinBox_->setMaximum(10);
    resultSpinBox_->setMinimum(0);

    teacherComboBox_ = new QComboBox(this);
    teacherComboBox_->setModel(teacher);
    teacherComboBox_->setModelColumn(1);
    teacherComboBox_->setCurrentIndex(-1);


    studentComboBox_ = new QComboBox(this);
    studentComboBox_->setModel(student);
    studentComboBox_->setModelColumn(1);
    studentComboBox_->setCurrentIndex(-1);


    button_ = new QPushButton("Save",this);
    connect(button_,&QPushButton::clicked, this, &EditGrade::onGradeSave);

    formLayout_ = new QFormLayout(this);
    formLayout_->addRow(tr("Result:"), resultSpinBox_);
    formLayout_->addRow(tr("Teacher:"), teacherComboBox_);
    formLayout_->addRow(tr("Student:"), studentComboBox_);
    formLayout_->addRow(button_);

    setLayout(formLayout_);
}

EditGrade::~EditGrade()
{
    formLayout_->deleteLater();
    resultSpinBox_->deleteLater();
    teacherComboBox_->deleteLater();
    studentComboBox_->deleteLater();
    button_->deleteLater();
}

void EditGrade::onGradeSave()
{
    qDebug() << "Saving" << resultSpinBox_->value() << " " << teacherComboBox_->currentIndex() +1
             << " " << studentComboBox_->currentIndex() + 1;

    if( model_->addItem(resultSpinBox_->value(),teacherComboBox_->currentIndex() + 1 ,
                        studentComboBox_->currentIndex() + 1) )
    {

        QMessageBox::information(
            this,
            tr("Status"),
            tr("Database updated succesfully..") );
    }
    else
    {
        QMessageBox::warning(
            this,
            tr("Status"),
            tr("An error occured to write db.") );
    }
}

EditWidget::EditWidget(Grade *gModel, Teacher* tModel, Student *sModel, QWidget *parent)
    : QWidget{parent}
{
    tabWidget_= new QTabWidget(this);
    tabAddStudent_= new EditStudent(sModel,this);
    tabAddTeacher_= new EditTeacher(tModel,this);
    tabAddGrade_ = new EditGrade(gModel,tModel,sModel,this);

    backButton_ = new QPushButton("Go Back");
    connect(backButton_, &QPushButton::clicked, this, &EditWidget::clickedReturn);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget_);
    mainLayout->addWidget(backButton_);
    setLayout(mainLayout);

    setWindowTitle(tr("Exam Management"));
    tabWidget_->addTab(tabAddStudent_, tr("Students"));
    tabWidget_->addTab(tabAddTeacher_, tr("Teachers"));
    tabWidget_->addTab(tabAddGrade_, tr("Grades"));
    setMinimumSize(250,300);
}

EditWidget::~EditWidget()
{
    tabWidget_->deleteLater();
    mainLayout->deleteLater();
    backButton_->deleteLater();

    tabAddStudent_->deleteLater();
    tabAddTeacher_->deleteLater();
    tabAddGrade_->deleteLater();

}
