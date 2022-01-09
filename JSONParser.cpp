#include "JSONParser.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

JSONParser::JSONParser(QString json)
{
    setContent(std::move(json));
};

void JSONParser::setContent(QString json)
{
    contents = std::move(json);

    QJsonDocument document = QJsonDocument::fromJson(contents.toUtf8());

    root = document.object();

    currentIndex = 0;
};

/*! Check is record 'next_page' exist or no */
bool JSONParser::isNextJSONLink() const
{
    return root.contains("next_page");
};

/*! Return link to next json-page */
const QUrl JSONParser::getNextLink() const
{
    if (isNextJSONLink())
    {
        return root.value("next_page").toString();
    }
    return QString();
};

/*! Switch to next picture record
 *
 * RETURN:
 *     bool - return true if next picture record is exist
 */
bool JSONParser::nextPic()
{
    currentIndex++;
    return isPictureExist();
}

/*! Get QJsonObject of current picture */
QJsonObject JSONParser::getPictureRecord()
{
    QJsonValue jv = root.value("photos");

    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        if (!ja.isEmpty() && currentIndex < ja.count())
        {
            qDebug() << "get picture index " << currentIndex;
            return ja.at(currentIndex).toObject();
        }
    }
    return QJsonObject();
};

/*! Get Url of current picture */
QString JSONParser::getPictureUrl()
{
    QJsonObject jr = getPictureRecord();
    if (jr.contains("src"))
    {
        QJsonObject urljson = jr.value("src").toObject();

        if (urljson.contains("original"))
        {
            QJsonValue jv = urljson.value("original");
            if (jv.isString())
            {
                qDebug() << jv.toString();
                return jv.toString();
            }
        }
    }
    return QString();
};

/*! Get Url of current picture */
QString JSONParser::getSmallUrl()
{
    QJsonObject jr = getPictureRecord();
    if (jr.contains("src"))
    {
        QJsonObject urljson = jr.value("src").toObject();

        if (urljson.contains("small"))
        {
            QJsonValue jv = urljson.value("small");
            if (jv.isString())
            {
                qDebug() << jv.toString();
                return jv.toString();
            }
        }
    }
    return QString();
};

/*! Get Photographer Name */
QString JSONParser::getPhotogrName()
{
    QJsonObject jr = getPictureRecord();
    if (jr.contains("photographer"))
    {
        qDebug() << "photographer " << jr.value("photographer").toString();
        return jr.value("photographer").toString();
    }
    return QString();
};

/*! Get Description of img */
QString JSONParser::getDescription()
{
    QJsonObject jr = getPictureRecord();
    if (jr.contains("alt"))
    {
        qDebug() << "description " << jr.value("alt").toString();
        return jr.value("alt").toString();
    }
    return QString();
};

/*! Get image width */
int JSONParser::getWidth()
{
    QJsonObject jr = getPictureRecord();
    if (jr.contains("width"))
    {
        qDebug() << "photo width " << jr.value("width").toInt();
        return jr.value("width").toInt();
    }
    return 0;
};

/*! Get image height */
int JSONParser::getHeight()
{
    QJsonObject jr = getPictureRecord();
    if (jr.contains("height"))
    {
        qDebug() << "photo height " << jr.value("height").toInt();
        return jr.value("height").toInt();
    }
    return 0;
};

/*! Check picture record by currentIndex is exist*/
bool JSONParser::isPictureExist() const
{
    QJsonValue jv = root.value("photos");

    if(jv.isArray())
    {
        QJsonArray ja = jv.toArray();
        return (!ja.isEmpty() && currentIndex < ja.count());

    }
    else
    {
        return false;
    }
};
