/*!   FILENAME:  DatabaseManager.cpp
 *    DESCRIPTION:
 *            Operates data in the local database
 */

#include <QDebug>
#include <QString>
#include <QStringLiteral>
#include <QDateTime>

#include "DatabaseManager.h"
#include "databaseexeptions.h"

/** path to local database */
#define _DATABASENAME_ "database.sqlite"

/** Convenient way to print debug info */
#define DB_FUNC_DEBUG(query_name, error_string) (qDebug()<<"QSqlQuery '"<<(query_name)<<"' error"<<(error_string)<<"in"<<__func__)


template<>
DatabaseManager * Singleton<DatabaseManager>::m_st_instance_p = nullptr;


/** Function Description: Constructor */
DatabaseManager::DatabaseManager() :
    QObject (nullptr)
{

}


/** Function Description: Initialize the database */
void DatabaseManager::initDatabase()
{

}

void DatabaseManager::createLogsTable()
{

}


//** **************** main functionality **************** **//


/*! Function Description: Prepare model for EventLog from database
 *  OUTPUTS:
 *    PARAMETERS:
 *           QVector<QString> &headers - Names of the table columns
 *           QVector<QVector<QString>>   &data - Link to the list of the rows for the table, all datas are prepared to the view
 *           QString timeshift - Select log period. Ex: '-1 year', '-2 months', '-3 days'
 */
bool DatabaseManager::getEventLog (QVector<QString>  &headers,  QVector< QVector<QString> > &data, QString timeshift = "-100 year")
{

    return true;
}

/*! Function Description: Get picture-url's and description by record-id
 * INPUTS:
 *    PARAMETERS:
 *           int id - id of the record in database
 *
 *    RETURN:
 *           QStringList - the list of parameters
 */
QStringList DatabaseManager::getUrlById (const int id)
{
    QStringList m_details;

    return m_details;
}


/*! Function Description: Public slot to push new datas into database
 *
 * INPUTS:
 * PARAMETERS:
 *      QString photographer - name of photographer
 *      int width - picture width
 *      int height - picture height
 *      QString url - original url
 *      QString url2 - preview url
 *      qint64 timestamp - Epoch Unix Timestamp
 *      QString description - image description
 */
void DatabaseManager::pushData (
        QString photographer,
        int width,
        int height,
        QString url,
        QString url2,
        qint64 timestamp,
        QString description
      )
{

}


