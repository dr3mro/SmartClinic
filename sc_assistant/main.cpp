#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QtDebug>
#include <QQmlContext>
#include "backend.h"
//#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationName("dramrosman");
    QCoreApplication::setOrganizationDomain("osmansoft.com");
    QCoreApplication::setApplicationName("clinicassistant");


    QGuiApplication app(argc, argv);

    QTranslator t;
    if(!t.load(":/sc_assistant_ar_EG.qm"))
        qDebug() << "Failed loading translation" ;
    qApp->installTranslator(&t);
    qmlRegisterType<BackEnd>("Sc_assistant.BackEnd", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.retranslate();
    engine.load(url);

    return app.exec();
}
