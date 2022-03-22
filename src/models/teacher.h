#ifndef TEACHER_H
#define TEACHER_H

#include <QSqlTableModel>

class Teacher : public QSqlTableModel
{
public:
    explicit Teacher(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase());
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    Q_INVOKABLE bool addItem(const QString &name, const QString &surname);
};

#endif // TEACHER_H
