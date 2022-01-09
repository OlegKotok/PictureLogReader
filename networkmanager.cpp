/*!   FILENAME:  networkmanager.cpp
 *    DESCRIPTION:
 *           Will take pictures from external source and put it to database
 *           Could be executed in separate thread
 */
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "networkmanager.h"
#include "apikey.h"

template<>
NetworkManager * Singleton<NetworkManager>::m_st_instance_p = nullptr;


/*!Function Description: Make single get rest request to online storage */
void NetworkManager::loadSinglePage(const int pageToLoad = 1)
{
    /****** get curl request ******/
    qDebug() << "Thread id " << QThread::currentThreadId() << Qt::endl;
    QNetworkRequest request( QStringLiteral
                             ("https://api.pexels.com/v1/search?page=%1&per_page=80&query=cats"
                             ).arg (QString::number (pageToLoad) )
                           );
    request.setRawHeader("Authorization", _APIKEY_); //change your api key before using

    QNetworkReply *reply = manager->get(request); //make request

    QObject::connect(reply, &QNetworkReply::finished, [=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "new data recived. Page " << pageToLoad;
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

/*! Function Description: Parse response from the server */
void NetworkManager::parseResponse(QString contents)
{
    qDebug() << "content recived : " << contents;
}






 /*! Function Description: Public function. Start event-loop and run the thread.
  */
void NetworkManager::AddPicturesToDB()
{
    dataThread->start();
}

/*! Function Description: Runs when thread are started. will be working in independed thread with event-loop functionality
 */
void NetworkManager::onThreadStarted()
{
    this->manager = new QNetworkAccessManager();

    loadSinglePage(5);
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
