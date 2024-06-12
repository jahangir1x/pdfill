#ifndef INFODB_H
#define INFODB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class InfoDb {
public:
    static QPair<double, double> getCoordinates(int id);
};

#endif // INFODB_H
