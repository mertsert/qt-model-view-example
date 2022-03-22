#include "grade.h"
#include <QSqlRecord>
#include <QSqlError>

Grade::Grade(QObject *parent, const QSqlDatabase &db)
    : QSqlRelationalTableModel{parent, db}
{
    this->setTable("result");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->setRelation(2, QSqlRelation("teacher", "teacher_id", "name"));
    this->setRelation(3, QSqlRelation("student", "student_id", "name"));

    this->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->setHeaderData(1, Qt::Horizontal, QObject::tr("Result"));
    this->setHeaderData(2, Qt::Horizontal, QObject::tr("Teacher"));
    this->setHeaderData(3, Qt::Horizontal, QObject::tr("Student"));

}
QVariant Grade::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount()) {
        return QString("");
    }
    if(role < Qt::UserRole) {
        return QSqlRelationalTableModel::data(index, role);
    }
    else
    {
        return QSqlRelationalTableModel::data(this->index(index.row(), role - Qt::UserRole), Qt::DisplayRole);
    }
}

bool Grade::addItem(const int &result, const int &teacher, const int &student)
{
    QSqlRecord rec = this->record();
    rec.remove(0);
    rec.setValue(0, result);
    rec.setValue(1, teacher);
    rec.setValue(2, student);
    this->insertRecord(-1, rec);
    qDebug() << "database error: " << this->lastError();

    if(this->submitAll())
    {
        this->database().commit();
        return true;
    }
    else
    {
        this->database().rollback();
        qDebug() << "database error: " << this->lastError();
        return false;
    }
}
