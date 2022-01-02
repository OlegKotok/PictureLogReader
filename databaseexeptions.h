#ifndef DATABASEEXEPTIONS_H
#define DATABASEEXEPTIONS_H

#include <QObject>
#include <QSqlError>
#include <string>
#include <QString>
#include <stdexcept>

class DatabaseExeption : public std::runtime_error, public QSqlError
{
public:
    DatabaseExeption(std::string s, const QSqlError& er,  const QString& lq="no query") :
        std::runtime_error(s.c_str()), QSqlError(er), lastQuery(lq) {};
    const QString lastQuery;
};

#endif // DATABASEEXEPTIONS_H
