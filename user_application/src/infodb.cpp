#include "infodb.h"

QPair<double, double> InfoDb::getCoordinates(int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("info.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        return QPair<double, double>(0, 0);
    }

    QSqlQuery query;
    query.prepare("SELECT coordinates_x, coordinates_y FROM form_data WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error: failed to query data: " << query.lastError().text();
        return QPair<double, double>(0, 0);
    }

    if (query.next()) {
        double x = query.value("coordinates_x").toDouble();
        double y = query.value("coordinates_y").toDouble();
        return QPair<double, double>(x, y);
    } else {
        qDebug() << "Error: no data found";
        return QPair<double, double>(0, 0);
    }
}
