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
    initDatabase();
}


/** Function Description: Initialize the database */
void DatabaseManager::initDatabase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase (QStringLiteral (u"QSQLITE"),
                            QSqlDatabase::defaultConnection);

    QSqlQuery query;

    database.setDatabaseName (QStringLiteral(_DATABASENAME_));

    if (!database.open() )
    {
        qDebug() << "Opening database error:" << database.lastError().text();
        throw DatabaseExeption("Opening database error", database.lastError());
    }
    else
    {
        qDebug() << "Database is open.";
        qDebug() << database.databaseName();
        // Check foreign keys contraint
        Q_UNUSED (query.exec ("PRAGMA foreign_keys = ON") );


        /*********** CREATING NEW LOGS TABLE ***********/

        if (!database.tables().contains(QStringLiteral("logs")))
        {
            qDebug() << "logs table not exist. creating new (empty) logs";
            createLogsTable();
        }
    }
}

void DatabaseManager::createLogsTable()
{
    databaseMutex.lock();
    QSqlDatabase database = QSqlDatabase::database (QSqlDatabase::defaultConnection);
    QSqlQuery query (database);
    if (!database.open())
    {
          qDebug() << "Create new log file - opendatabase error exeption";
          throw DatabaseExeption("Create new log file - opendatabase error exeption", query.lastError(), query.lastQuery());
    }

    query.prepare(QStringLiteral("CREATE TABLE logs("
                                 " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 " timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                                 " userName  VARCHAR(255), "
                                 " width     INT, "
                                 " height    INT, "
                                 " url      VARCHAR(255), "
                                 " url2     VARCHAR(255), "
                                 " description      TEXT"
                                 " );"
                                ));
    if (!query.exec() )
    {
        qDebug() << "Create new Log-table error exeption";
        throw DatabaseExeption("Create new Log-table error exeption", query.lastError(), query.lastQuery());
    }
    query.prepare(QStringLiteral("CREATE INDEX iLogTimestamp ON logs (timestamp);"));
    if (!query.exec() )
    {
        qDebug() << "Log-table creating index not critical error exeption";
    }
    databaseMutex.unlock();
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
    QSqlDatabase database = QSqlDatabase::database (
                                        QSqlDatabase::defaultConnection);
    if (!database.open())
    {
          qDebug() << "Get Event Log Error: Database not open. " << database.lastError().text();
          return false;
    }
    QSqlQuery query (database);

    query.prepare(QStringLiteral("SELECT id, "
                      " date(timestamp) AS date, "
                      " time(timestamp) AS time, "
                      " userName AS Photographer, "
                      " cast(width as text) || ' x ' || cast(height as text) AS size, "
                      " url as picture"
                      " FROM logs "
                      " WHERE date(timestamp) BETWEEN date('now', '%1') AND date('now');"
                  ).arg(timeshift));

    qDebug() << "Query: " << query.lastQuery();
    databaseMutex.lock();
    if (!query.exec() )
    {
        qDebug() << "Executing query in DatabaseManager::getEventLog processing" <<
                 query.lastQuery() << "query and got:" << query.lastError().text();
        return false;
    }
    databaseMutex.unlock();

    /** Get headers data to the model */
    QSqlRecord rec = query.record();
    headers.clear();
    headers.reserve(rec.count());
    for (int i = 0; i < rec.count(); i++)
    {
        headers.push_back(rec.fieldName(i));
    }

    /** Fill data model */
    data.clear();
    while (query.next())
    {
        QVector<QString> row;
        row.reserve(rec.count());
        for (int columnIndex = 0; columnIndex < rec.count(); columnIndex++)
        {
            row.append(query.value(columnIndex).toString());
        }
        data.push_back(row);
    }
    qDebug()<<"selected records count: "<<data.size();

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
    QSqlDatabase database = QSqlDatabase::database (
                                        QSqlDatabase::defaultConnection);
    if (!database.open())
    {
          qDebug() << "Get Event Log Error: Database not open. " << database.lastError().text();
          return m_details;
    }
    QSqlQuery query (database);

    query.prepare(QStringLiteral("SELECT url, url2, description"
                      " FROM logs "
                      " WHERE id = %1 + 1;"
                  ).arg(id));
    databaseMutex.lock();
    if (!query.exec() )
    {
        qDebug() << "Executing query in DatabaseManager::getEventLog processing" <<
                 query.lastQuery() << "query and got:" << query.lastError().text();
        return m_details;
    }
    databaseMutex.unlock();

    ///< Get details event-log description
    QSqlRecord rec = query.record();
    query.next();
    m_details.reserve(rec.count());
    qDebug()<<"getting event log details. record's count: "<<rec.count();
    for (int columnIndex = 0; columnIndex < rec.count(); columnIndex++)
    {
        m_details.append(query.value(columnIndex).toString());
        qDebug()<<"Details : " << query.value(columnIndex).toString();
    }
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
    QSqlDatabase database = QSqlDatabase::database (QSqlDatabase::defaultConnection);
    QSqlQuery query (database);
    if (!database.open())
    {
          qDebug() << "Add new record - database not open";
          throw DatabaseExeption("Add new record - database not open", query.lastError(), query.lastQuery());
    }

    //** prepare query */
    query.prepare(QStringLiteral("INSERT INTO logs"
                                 "(timestamp, userName, width, height, url, url2, description) "
                                 "VALUES("
                                 "datetime('%1', 'unixepoch'), '%2', '%3', '%4', '%5', '%6', '%7');"
                                ).arg(QString::number(timestamp),
                                      photographer, QString::number(width), QString::number(height),
                                      url, url2, description)
                  );
    databaseMutex.lock();
    if (!query.exec() )
    {
        qDebug() << "Cannot add new datas into database!" << Qt::endl;
        throw DatabaseExeption("Bad query. Cannot add new datas into database!", query.lastError(), query.lastQuery());
    }
    databaseMutex.unlock();
}


