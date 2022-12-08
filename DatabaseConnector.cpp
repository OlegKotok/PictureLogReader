/*!   FILENAME:  DatabaseConnector.h
 *    DESCRIPTION:
 *        Connect to databes from another thread
 */

#include "DatabaseConnector.h"
#include <DatabaseManager.h>

template<>
DatabaseConnector * Singleton<DatabaseConnector>::m_st_instance_p = nullptr;

/*! Function Description: Emit new signal with datas to DatabaseManage
 *                        Signal will be recived in independed thread
 *
 * INPUTS:
 * PARAMETERS:
 *      QString photographer - name of photographer
 *      int width - picture width
 *      int height - picture height
 *      QString url - original url
 *      QString url2 - preview url
 *      time_t timestamp - Epoch Unix Timestamp
 *      QString description - image description
 */
void DatabaseConnector::sendData(QString photographer, int width, int height, QString url, QString url2,
                                 time_t timestamp, QString description, const QString& pic_type)
{
    DatabaseManager::getInstance()->pushData(photographer, width, height, url, url2,
                  static_cast<qint64>(timestamp), description, pic_type);
}
