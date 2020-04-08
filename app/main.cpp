

#include <QtCore/QDebug>
#include <QtCore/QCommandLineParser>
#include <QtCore/QUrlQuery>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QQuickWindow>
#include <libhomescreen.hpp>
#include <qlibwindowmanager.h



int main(int argc, char *argv[])
{
    QString graphic_role = QString("v2x");

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("AGL");

    QQmlApplicationEngine engine;

    QCommandLineParser parser;
    parser.addPositionalArgument("port", app.translate("main", "port for binding"));
    parser.addPositionalArgument("secret", app.translate("main", "secret for binding"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);
    QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.length() == 2) {
        int port = positionalArguments.takeFirst().toInt();
        QString secret = positionalArguments.takeFirst();
            std::string token = secret.toStdString();
        QUrl bindingAddress;
        bindingAddress.setScheme(QStringLiteral("ws"));
        bindingAddress.setHost(QStringLiteral("localhost"));
        bindingAddress.setPort(port);
        bindingAddress.setPath(QStringLiteral("/api"));
        QUrlQuery query;
        query.addQueryItem(QStringLiteral("token"), secret);
        bindingAddress.setQuery(query);
        QQmlContext *context = engine.rootContext();
        context->setContextProperty(QStringLiteral("bindingAddress"), bindingAddress);
      

        LibHomeScreen* hs = new LibHomeScreen();
        QLibWindowmanager* qwm = new QLibWindowmanager();

        // WindowManager
        if(qwm->init(port, secret) != 0){
            exit(EXIT_FAILURE);
        }

        AGLScreenInfo screenInfo(qwm->get_scale_factor());

        // Request a surface as described in layers.json windowmanager’s file
        if (qwm->requestSurface(graphic_role) != 0) {
            exit(EXIT_FAILURE);
        }
        // Create an event callback against an event type. Here a lambda is called when SyncDraw event occurs
        qwm->set_event_handler(QLibWindowmanager::Event_SyncDraw, [qwm, graphic_role](json_object *object) {
	        Q_UNUSED(object);
            qwm->endDraw(graphic_role);
        });

        // HomeScreen
        hs->init(port, token.c_str());
        // Set the event handler for Event_ShowWindow which will activate the surface for windowmanager
        hs->set_event_handler(LibHomeScreen::Event_ShowWindow, [qwm, &graphic_role](json_object *object){
            qDebug("Surface %s got showWindow\n", graphic_role.toStdString().c_str());
            qwm->activateWindow(graphic_role);
        });

        engine.rootContext()->setContextProperty("screenInfo", &screenInfo);
        engine.load(QUrl(QStringLiteral("qrc:/v2x.qml")));
        QObject *root = engine.rootObjects().first();
        QQuickWindow *window = qobject_cast<QQuickWindow *>(root);
        QObject::connect(window, SIGNAL(frameSwapped()), qwm, SLOT(slotActivateWindow()
        ));
    }
    return app.exec();
}
