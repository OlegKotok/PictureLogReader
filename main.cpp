#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml> /* We connect to use the qmlRegisterSingletonType function */
#include <DatabaseManager.h>
#include <EventLogModel.h>
#include "databaseexeptions.h"

#include <thread>
#include <ctime>
#include <chrono>
#include <QThread>
#include <DatabaseConnector.h>
#include "networkmanager.h"
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qDebug() << "app run" << Qt::endl;
    QGuiApplication app(argc, argv);

    /** Put datas to database in separeted thread */
    qDebug() << "Main Thread id " << QThread::currentThreadId() << Qt::endl;
    NetworkManager::getInstance()->AddPicturesToDB();

    qmlRegisterType<EventLogModel>("eventLogModel", 1, 0,
                                   "EventLogModel");

    qDebug() << "Eventlogmodel ok" << Qt::endl;

    /*! OpenSSL library to get photos by https
     *  Install this version of OpenSSL depends from your compiler and put*.ddl
     *  all *.dll from \OpenSSL-Win32 into \Qt\5.15.2\msvc2019\bin folder
     */
    /*qDebug() << "OPEN SSL: " << QSslSocket::supportsSsl()
             << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString() <<Qt::endl;*/

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
