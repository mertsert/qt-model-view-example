#include "display.h"
#include <QHeaderView>

DisplayWidget::DisplayWidget(Grade *gModel, Teacher* tModel, Student *sModel, QWidget *parent):
        QWidget{parent},
        tabWidget_{new QTabWidget(this)},
        tabGrades_{new DisplayGrades(gModel,sModel,this)},
        tabStudents_{new DisplayStudent(gModel,tModel)}
{

    backButton_ = new QPushButton("Go Back");
    connect(backButton_, &QPushButton::clicked, this, &DisplayWidget::clickedReturn);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget_);
    mainLayout->addWidget(backButton_);
    setLayout(mainLayout);

    setWindowTitle(tr("Exam Management"));
    tabWidget_->addTab(tabGrades_, tr("Grades"));
    tabWidget_->addTab(tabStudents_, tr("Students"));
    setMinimumSize(370,400);
}

DisplayWidget::~DisplayWidget()
{
    tabWidget_->deleteLater();
    backButton_->deleteLater();
    mainLayout->deleteLater();
}

DisplayGrades::DisplayGrades(Grade *g, Student *s, QWidget *parent)
    : QWidget{parent}, model_{g}
{
    g->select();
    s->select();

    // init tableview.
    model_.setSourceModel(g);
    gradeView_ = new QTableView(this);
    gradeView_->setModel(&model_);
    model_.setFilterKeyColumn(3);
    QHeaderView *hview = gradeView_->horizontalHeader();
    hview->hideSection(0);
    hview->swapSections(1,3);
    gradeView_->setHorizontalHeader(hview);

    // init combobox.
    comboBox_ = new QComboBox(this);
    comboBox_->setModel(s);
    comboBox_->setModelColumn(1);
    comboBox_->setCurrentIndex(-1);
    connect(comboBox_, &QComboBox::currentTextChanged, this, &DisplayGrades::onStudentChanged);

    label = new QLabel("Student: ",this);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(comboBox_);
    mainLayout->addWidget(gradeView_);
    setLayout(mainLayout);

}

DisplayGrades::~DisplayGrades()
{
    comboBox_->deleteLater();
    gradeView_->deleteLater();
    label->deleteLater();
    mainLayout->deleteLater();
}

void DisplayGrades::onStudentChanged(QString st)
{
    model_.setFilterFixedString(st);
}

DisplayStudent::DisplayStudent(Grade *g, Teacher *t, QWidget *parent) :
    QWidget{parent}, model_{g}
{
    g->select();
    t->select();

    model_.setSourceModel(g);
    model_.setFilterKeyColumn(2);
    gradeView_ = new QTableView(this);
    gradeView_->setModel(&model_);
    QHeaderView *hview = gradeView_->horizontalHeader();
    hview->hideSection(0);
    hview->hideSection(1);
    hview->swapSections(1,3);
    gradeView_->setHorizontalHeader(hview);

    comboBox_ = new QComboBox(this);
    comboBox_->setModel(t);
    comboBox_->setModelColumn(1);
    comboBox_->setCurrentIndex(-1);
    connect(comboBox_, &QComboBox::currentTextChanged, this, &DisplayStudent::onTeacherChanged);

    label = new QLabel("Teacher: ",this);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(comboBox_);
    mainLayout->addWidget(gradeView_);
    setLayout(mainLayout);
}

DisplayStudent::~DisplayStudent()
{
    comboBox_->deleteLater();
    gradeView_->deleteLater();
    label->deleteLater();
    mainLayout->deleteLater();
}

void DisplayStudent::onTeacherChanged(QString str)
{
    model_.setFilterFixedString(str);
}
