/*!   FILENAME:  DatabaseManager.h
 *    DESCRIPTION:
 *           Operates data in the local database
 *    NOTES:
 *            Uses SQLITE to operate the database
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <map>

#include "Singleton.h"

/** will store data in the menory in this struct **/
struct DataRecordStruct{
    int id;
    QString photographer;
    int width;
    int height;
    QString url;
    QString url2;
    qint64 timestamp;
    QString description;
};

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

        /** Push new record into database
         *  qint64 timestamp - Epoch Unix Timestamp */
        void pushData(QString photographer, int width, int height, QString url, QString url2,
                      qint64 timestamp, QString description);

    private:
        DatabaseManager() {};
        int lastElemntId = 0;
        std::vector<DataRecordStruct> datastorage;
};

#endif // DATABASEMANAGER_H
