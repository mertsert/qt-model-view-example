#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
class DbManager : public QObject
{
    Q_OBJECT
public:
    explicit DbManager(QString path, QObject *parent = nullptr);

    void InitTables();

    const QSqlDatabase &db() const;

private:
    QSqlDatabase db_;


};

#endif // DBMANAGER_H
