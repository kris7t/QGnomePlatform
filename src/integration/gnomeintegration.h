#ifndef GNOMEINTEGRATION_H
#define GNOMEINTEGRATION_H

#include <qpa/qplatformintegration.h>
#include <qpa/qplatformintegrationplugin.h>
#include <QtXcb/qxcbintegration.h>
#include <QtWaylandClient/private/qwaylandintegration_p.h>
#include <QtWaylandClient/private/qwaylandshmbackingstore_p.h>
#include <QtWaylandClient/private/qwaylanddisplay_p.h>

class GnomeIntegration;

class GnomeBackingStore : public QtWaylandClient::QWaylandShmBackingStore {
public:
    GnomeBackingStore(QWindow *window);

    void flush(QWindow *window, const QRegion &region, const QPoint &offset) override;
};

class GnomeIntegration : public QtWaylandClient::QWaylandIntegration {
public:
    GnomeIntegration();

    QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const override;
    QPlatformTheme *createPlatformTheme(const QString &name) const override;


private:
};


class QGnomePlatformIntegrationPlugin : public QPlatformIntegrationPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformIntegrationFactoryInterface_iid FILE "qgnome.json")
public:
    QGnomePlatformIntegrationPlugin(QObject *parent = 0);

    virtual QPlatformIntegration *create(const QString &key, const QStringList &paramList);
};



#endif // GNOMEINTEGRATION_H
