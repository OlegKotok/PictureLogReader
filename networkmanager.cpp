/*!   FILENAME:  networkmanager.cpp
 *
 *    DESCRIPTION:
 *           Will take pictures from external source and put it to database
 *           Could be executed in separate thread
 *
 *    NOTES:
 *           To get response from QNetworkAccessManager we need to use signal-slot conception
 *           To get it we need to run event-loop cycle, normally its started in app.exec(), but that's is not thread we need
 *           We can't do it in simple thread, like std::thread or QThread, thats why we are creadet inherited singleton object
 *           and make signal-slots connection when thread will be running, in this case, event-loop will be created in new thread as we need.
 *
 */
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "networkmanager.h"
#include "apikey.h"
#include "JSONParser.h"
#include <DatabaseConnector.h>
#include <QMessageBox>

template<>
NetworkManager * Singleton<NetworkManager>::m_st_instance_p = nullptr;


/*!Function Description: Make single get rest request to online storage */
void NetworkManager::loadSinglePage(const QUrl &url)
{
    /****** get curl request ******/
    qDebug() << "Thread id " << QThread::currentThreadId() << Qt::endl;
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", _APIKEY_); //change your api key before using

    QNetworkReply *reply = manager->get(request); //make request

    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Reply Thread : " << QThread::currentThreadId() << Qt::endl;

            /****** parse response ******/
            parseResponse( QString::fromUtf8( reply->readAll() ) );
        }
        else
        {
            QString err = reply->errorString();
            qDebug() << "Server error " << err;
        }
        reply->deleteLater();
    });
    qDebug()<<" exit thread ";
}

/*! Function Description: Parse response from the server and put datas to database*/
void NetworkManager::parseResponse(QString contents)
{
    qDebug() << "content recived : " << contents;
    JSONParser jp;
    jp.setContent(contents);

    time_t nextTime = time(nullptr); // timestamp coutdownd from now
    while (jp.isPictureExist())
    {
        nextTime -= 60 * 60 * 3;
        DatabaseConnector::sendData( jp.getPhotogrName(),
                                                    jp.getWidth(),
                                                    jp.getHeight(),
                                                    jp.getPictureUrl(),
                                                    jp.getSmallUrl(),
                                                    nextTime,
                                                    jp.getDescription()
                                                   );
        jp.nextPic();
    }
    qDebug() << "NextLink: " << jp.getNextLink();
}



 /*! Function Description: Public function. Start event-loop and run the thread.
  */
void NetworkManager::AddPicturesToDB()
{
    //dataThread->start();
    onThreadStarted();
}

/*! Function Description: Runs when thread are started. will be working in independed thread with event-loop functionality
 */
void NetworkManager::onThreadStarted()
{
    this->manager = new QNetworkAccessManager();

    loadSinglePage( QUrl (QStringLiteral ("https://api.pexels.com/v1/search?page=1&per_page=80&query=cats") ) );
}

/*! Function Description: Constructor
 *  Create new thread with event-loop and moove just-created object to this thread
 *  Make onThreadStarted signal-slot connections
 */
NetworkManager::NetworkManager()
{
    dataThread = new QThread;
    this->moveToThread(dataThread);
    QObject::connect(dataThread, &QThread::started, this, &NetworkManager::onThreadStarted);
}
