#include "dbmanager.h"
#include "QDebug"
#include "QSqlQuery"
#include "QSqlError"

DbManager::DbManager(QString path, QObject *parent)
    : QObject{parent}
{
    db_= QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(path);

    if (!db_.open())
    {
        qDebug() << "Error: connection with database failed";
        return;
    }

   qDebug() << "Database: connection ok";

#ifdef TEST
    InitTables();
#endif
}

void DbManager::InitTables()
{
    QSqlQuery query{db_};
    query.exec("create table student(student_id int primary key, name varchar(20), surname varchar(20) )");
    query.exec("create table teacher(teacher_id int primary key, name varchar(20), surname varchar(20) )");
    query.exec("create table result(result_id int primary key, result int, teacher_id int, student_id int)");

}

const QSqlDatabase &DbManager::db() const
{
    return db_;
}


