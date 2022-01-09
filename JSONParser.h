/*!   FILENAME:  JSONParser.h
 *    DESCRIPTION:
 *           JSON Parser to parse data from https://www.pexels.com/ru-ru/api/documentation/
 *
 *    INTERFACE:
 *      setContent(QString contents) - set source string
 */

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>
#include <QUrl>
#include <QJsonObject>

class JSONParser
{
public:
    JSONParser() = default;
    JSONParser(QString json);

    /*! set json source string and start parse */
    void setContent(QString json);

    /*! Check is record 'next_page' exist or no */
    bool isNextJSONLink() const;

    /*! Check picture record by currentIndex is exist */
    bool isPictureExist() const;

    /** ********** getter section ********** */
    QString getPictureUrl();
    QString getSmallUrl();
    int getWidth();
    int getHeight();
    QString getPhotogrName();
    QString getDescription();
    /** ********** getter section ********** */

    /*! Switch to next picture record */
    bool nextPic();

    /*! Return link to next json-page */
    const QUrl getNextLink() const;

private:
    QString contents;
    QJsonObject root;
    unsigned int currentIndex = 0;

    /** Get JSON-record of picture by ID */
    QJsonObject getPictureRecord();
};

#endif // JSONPARSER_H
