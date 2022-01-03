/*!   FILENAME:  DatabaseManager.h
 *    DESCRIPTION:
 *           Operates data in the local database
 *    NOTES:
 *            Uses SQLITE to operate the database
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlRecord>
#include <mutex>

#include "Singleton.h"

/** Operates data in the local database */
class DatabaseManager : public QObject, public Singleton<DatabaseManager>
{
        Q_OBJECT

        friend class Singleton<DatabaseManager>;

    public:

        /** Get data for EventLog Model */
        bool getEventLog (QVector<QString> &headers,  QVector<QVector<QString>> &data,  QString timeshift);

        /** Get picture Url by record-id */
        QStringList getUrlById (const int id);

    public slots:

        /** Push new record into database
         *  qint64 timestamp - Epoch Unix Timestamp */
        void pushData(QString photographer, int width, int height, QString url, QString url2,
                      qint64 timestamp, QString description);

    private:
        /** Private constructor because of singleton */
        DatabaseManager();

        /** Initializes the database */
        void initDatabase();

        /** Initializes the database */
        void createLogsTable();

        std::mutex databaseMutex;
};

#endif // DATABASEMANAGER_H
