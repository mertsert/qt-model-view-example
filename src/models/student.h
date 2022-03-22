#ifndef STUDENT_H
#define STUDENT_H

#include <QSqlTableModel>

class Student : public QSqlTableModel
{
public:
    explicit Student(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase());
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    Q_INVOKABLE bool addItem(const QString &name, const QString &surname);

};

#endif // STUDENT_H
