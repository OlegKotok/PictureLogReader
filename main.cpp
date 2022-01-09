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

/*! Function Description: Push random datas into DB
 *
 * DEPENDENCY:
 *      DtbaseManager::pushData() - public slot to push datas
 *
 * INPUTS:
 * PARAMETERS:
 *     const QModelIndex &index - index of current cell
 *
 * OUTPUTS:
 * RETURN:
 *     QVariant - QString of the cell by index
 *
 */
void AddRecordsToDB()
{
    qDebug() << ">>entering thread" << Qt::endl;
    DatabaseConnector::getInstance()->sendData("Вася", 100, 200, "ddd", "",
                                                time(nullptr), "current time");

    struct tm localTime;
    localTime.tm_year = 2021 - 1900;
    localTime.tm_mon  = 07 - 1;
    localTime.tm_mday = 24;
    localTime.tm_hour = 15;
    localTime.tm_min = 46;
    localTime.tm_sec = 29;

    //implement databaseConnector, class just emit signal to database thread

    const QStringList names = {"Петрович", "Хренович", "Бухлович", "Алконович"};

    DatabaseConnector::getInstance()->sendData("Петя", 100, 200, "ddd", "",
                                                mktime(&localTime), "2021-07-24T15:46:29");

    for (auto i=0; i< 1000; i++) {
        time_t nextTime = time(nullptr) - 60 * 60 * 3 * i;
        QString uName = names[rand() % names.size()];
        DatabaseConnector::getInstance()->sendData(uName, rand()%5000, rand()%3000, "", "", nextTime, asctime(gmtime(&nextTime)));

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    qDebug() << "<<leaving thread" << Qt::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qDebug() << "app run" << Qt::endl;
    QGuiApplication app(argc, argv);

    try
    {
        DatabaseManager::getInstance();
    }
    catch (DatabaseExeption &ex)
    {
        qDebug() << Qt::endl << " Database exeption! : " << ex.what() << ex.text();
        qDebug() << " Last query: " << Qt::endl << ex.lastQuery << Qt::endl;
        return ex.type();
    }

    qDebug() << "Database manager ok" << Qt::endl;

    /** Put datas to database in separeted thread */
    qDebug() << "Main Thread id " << QThread::currentThreadId() <<endl;
    NetworkManager::getInstance()->AddPicturesToDB();

    qmlRegisterType<EventLogModel>("eventLogModel", 1, 0,
                                   "EventLogModel");

    qDebug() << "Eventlogmodel ok" << Qt::endl;

    /*! OpenSSL library to get photos by https
     *  Install this version of OpenSSL depends from your compiler and put*.ddl
     *  all *.dll from \OpenSSL-Win32 into \Qt\5.15.2\msvc2019\bin folder
     */
    qDebug() << "OPEN SSL: " << QSslSocket::supportsSsl()
             << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString() <<Qt::endl;

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
