#include "gnomeintegration.h"

#include <QtWaylandClient/private/qwaylandclipboard_p.h>
#include <qpa/qplatformintegrationfactory_p.h>
#include <qpa/qplatformthemefactory_p.h>
#include <QCoreApplication>

GnomeIntegration::GnomeIntegration()
    : QtWaylandClient::QWaylandIntegration()
{
}


QPlatformBackingStore *GnomeIntegration::createPlatformBackingStore(QWindow *window) const {
    return new GnomeBackingStore(window);
}

QPlatformTheme *GnomeIntegration::createPlatformTheme(const QString &name) const {
    auto gnome = QPlatformThemeFactory::create("gnome");
    if (gnome)
        return gnome;
    return QtWaylandClient::QWaylandIntegration::createPlatformTheme(name);
}

QGnomePlatformIntegrationPlugin::QGnomePlatformIntegrationPlugin(QObject *parent)
    : QPlatformIntegrationPlugin(parent) {

}

QPlatformIntegration *QGnomePlatformIntegrationPlugin::create(const QString &key, const QStringList &paramList) {
    Q_UNUSED(paramList);
    if (key == "gnome") {
        if (qEnvironmentVariableIsSet("WAYLAND_DISPLAY")) {
            if (!qEnvironmentVariableIsSet("QT_WAYLAND_FORCE_DPI"))
                qputenv("QT_WAYLAND_FORCE_DPI", "96");
            if (!qEnvironmentVariableIsSet("QT_WAYLAND_DECORATION"))
                qputenv("QT_WAYLAND_DECORATION", "adwaita");
            return new GnomeIntegration();
        }
        else {
            int argc = QCoreApplication::arguments().count();
            char *argv[argc];
            int i = 0;
            for (QString it : QCoreApplication::arguments()) {
                argv[i] = strdup(qPrintable(it));
                i++;
            }
            auto xcb = QPlatformIntegrationFactory::create("xcb", paramList, argc, argv);
            for (int i = 0; i < argc; i++) {
                free(argv);
            }
            return xcb;
        }
    }
    return nullptr;
}

GnomeBackingStore::GnomeBackingStore(QWindow *window)
    : QtWaylandClient::QWaylandShmBackingStore(window) {

}

void GnomeBackingStore::flush(QWindow *window, const QRegion &region, const QPoint &offset) {
    QRegion regionCopy(region);
    if (window)
        regionCopy = regionCopy.united(QRegion(window->x(), window->y(), window->width(), window->height()));
    QtWaylandClient::QWaylandShmBackingStore::flush(window, regionCopy, offset);
}
