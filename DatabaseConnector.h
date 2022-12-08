/*!   FILENAME:  DatabaseConnector.h
 *    DESCRIPTION:
 *        Connect to databes from another thread
 */


#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QString>

class DatabaseConnector
{
    public:
        static void sendData(QString photographer, int width, int height, QString url, QString url2,
                  time_t timestamp, QString description, const QString& pic_type);
};

#endif // DATABASECONNECTOR_H
