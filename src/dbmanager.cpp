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

#ifdef DB_CREATED
    InitTables();
#endif
}

void DbManager::InitTables()
{
    QSqlQuery query{db_};
    query.exec("create table student(student_id integer primary key autoincrement, name varchar(20) not null, surname varchar(20) not null)");
    query.exec("create table teacher(teacher_id integer primary key autoincrement, name varchar(20) not null, surname varchar(20) not null)");
    query.exec("create table result(result_id integer primary key autoincrement, result int, teacher_id int, student_id int)");

}

const QSqlDatabase &DbManager::db() const
{
    return db_;
}


