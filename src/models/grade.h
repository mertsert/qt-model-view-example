#ifndef GRADE_H
#define GRADE_H

#include <QSqlRelationalTableModel>

class Grade : public QSqlRelationalTableModel
{
public:
    explicit Grade(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase());
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    Q_INVOKABLE bool addItem(const int &result, const int &teacher, const int &student);

};


#endif // GRADE_H
