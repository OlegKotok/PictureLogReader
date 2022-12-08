/*!   FILENAME:  networkmanager.h
 *    DESCRIPTION:
 *           Will take pictures from external source and put it to database
 *           Could be executed in separate thread
 */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Singleton.h"
#include <QThread>
#include <QNetworkAccessManager>

class NetworkManager : public QObject, public Singleton<NetworkManager>
{
    Q_OBJECT
    friend class Singleton<NetworkManager>;

public:
    /*! Function Description: Public function.
     *  Send signal to start dataThread
     */
    void AddPicturesToDB();

private slots:
    /*! Function Description: Run on thread started */
    void onThreadStarted();

private:
    /*!Function Description: Make single get rest request to online storage */
    void loadSinglePage(const QUrl &url,  const QString& pic_type);

    /*! Function Description: Parse response from the server */
    void parseResponse(QString contents, const QString& pic_type);

    QThread *dataThread;
    QNetworkAccessManager *manager;

    /*! Constructor: Create new thread, start event-loop and moove object to this thread*/
    NetworkManager();
};

#endif // NETWORKMANAGER_H
