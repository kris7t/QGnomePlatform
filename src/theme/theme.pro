TEMPLATE = lib

CONFIG += plugin \
          c++11 \
          link_pkgconfig

QT += core-private \
      gui-private \
      widgets \

equals(QT_MAJOR_VERSION, 5): greaterThan(QT_MINOR_VERSION, 7): QT += theme_support-private
equals(QT_MAJOR_VERSION, 5): lessThan(QT_MINOR_VERSION, 8): QT += platformsupport-private

PKGCONFIG += gtk+-3.0 \
             gtk+-x11-3.0

TARGET = qgnomeplatform
target.path += $$[QT_INSTALL_PLUGINS]/platformthemes
INSTALLS += target

SOURCES += \
    platformplugin.cpp \
    qgnomeplatformtheme.cpp \
    gnomehintssettings.cpp \
    qgtk3dialoghelpers.cpp

HEADERS += \
    platformplugin.h \
    qgnomeplatformtheme.h \
    gnomehintssettings.h \
    qgtk3dialoghelpers.h
