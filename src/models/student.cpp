#include "student.h"
#include <QSqlRecord>
#include <QSqlError>

Student::Student(QObject *parent, const QSqlDatabase &db)
    : QSqlTableModel{parent, db}
{
    this->setTable("student");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant Student::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount()) {
        return QString("");
    }
    if(role < Qt::UserRole) {
        return QSqlTableModel::data(index, role);
    }
    else
    {
        return QSqlTableModel::data(this->index(index.row(), role - Qt::UserRole), Qt::DisplayRole);
    }
}

bool Student::addItem(const QString &name, const QString &surname)
{
    QSqlRecord rec = this->record();
    rec.setValue(1, name);
    rec.setValue(2, surname);
    this->insertRecord(-1, rec);

    if(this->submitAll())
    {
        this->database().commit();
        return true;
    }
    else
    {
        qDebug() << "database error: " << this->lastError();
        this->database().rollback();
        return false;
    }
}
