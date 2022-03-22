#include "teacher.h"
#include <QSqlRecord>
#include <QSqlError>

Teacher::Teacher(QObject *parent, const QSqlDatabase &db)
    : QSqlTableModel{parent, db}
{
    this->setTable("teacher");
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

QVariant Teacher::data(const QModelIndex &index, int role) const
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

bool Teacher::addItem(const QString &name, const QString &surname)
{
    QSqlRecord rec = this->record();
    rec.remove(0);
    rec.setValue(0, name);
    rec.setValue(1, surname);
    this->insertRecord(-1, rec);

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
