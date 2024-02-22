#include "configreader.h"

#define MAXTIMES 256
namespace KWin
{

ConfigReaderThread::ConfigReaderThread(const QString &service, const QString &path, const QString &interface, const QString &propertyName)
    : m_service(service), m_path(path), m_interface(interface), m_propertyName(propertyName)
{
}

ConfigReaderThread::~ConfigReaderThread()
{
}

void ConfigReaderThread::run()
{
    bool found = false;
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    for (int i = 1; i < MAXTIMES; i *= 2) {
        auto sleepfunc = [&i]{
            QThread::sleep(i);
        };
        if (!sessionBus.interface()->isServiceRegistered(m_service)) {
            sleepfunc();
            continue;
        }
        QDBusInterface dbus(m_service, m_path, m_interface);
        if (!dbus.isValid()) {
            sleepfunc();
            continue;
        }
        QVariant property = dbus.property(m_propertyName.toStdString().c_str());

        if (property.isValid()) {
            Q_EMIT propertyFound(property);
            found = true;
            break;
        }

        sleepfunc();
    }

    if (!found) {
        qWarning() << "cannot get dbus property";
    }
}

ConfigReader::ConfigReader(const QString &service, const QString &path, const QString &interface, const QString &propertyName)
    : m_interface(interface), m_propertyName(propertyName)
{
    ConfigReaderThread *thread = new ConfigReaderThread(service, path, interface, propertyName);
    connect(thread, SIGNAL(propertyFound(QVariant)), this, SLOT(slotSetProperty(QVariant)));

    thread->start();

    QDBusConnection::sessionBus().connect(service, path, "org.freedesktop.DBus.Properties", "PropertiesChanged",
                                          "sa{sv}as", this, SLOT(slotUpdateProperty(QDBusMessage)));
}

ConfigReader::~ConfigReader()
{
}

void ConfigReader::slotUpdateProperty(QDBusMessage msg)
{
    QList<QVariant> arguments = msg.arguments();
    if (3 != arguments.count()) {
        return;
    }

    QString interfaceName = msg.arguments().at(0).toString();
    if (interfaceName == m_interface) {
        QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
        QStringList keys = changedProps.keys();
        for (int i = 0; i < keys.size(); ++i) {
            if (keys.at(i) == m_propertyName) {
                m_property = changedProps.value(keys.at(i));
                break;
            }
        }
    }
    if (m_propertyName == "WindowRadius")
        Q_EMIT sigRadiusChanged(m_property);
}

void ConfigReader::slotSetProperty(QVariant property)
{
    m_property = property;
}

}