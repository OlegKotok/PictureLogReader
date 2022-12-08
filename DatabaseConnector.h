/*!   FILENAME:  DatabaseConnector.h
 *    DESCRIPTION:
 *        Connect to databes from another thread
 */


#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QObject>
#include "Singleton.h"

class DatabaseConnector: public QObject, public Singleton<DatabaseConnector>
{
    Q_OBJECT
    friend class Singleton<DatabaseConnector>;

public:
    DatabaseConnector();

    void sendData(QString photographer, int width, int height, QString url, QString url2,
                  time_t timestamp, QString description);
private:
    void Connect();

signals:
    /** Signal to DatabaseManager
     *  qint64 timestamp - Epoch Unix Timestamp */
    /*void newDatas(QString photographer, int width, int height, QString url, QString url2,
                  qint64 timestamp, QString description);*/
};

#endif // DATABASECONNECTOR_H
