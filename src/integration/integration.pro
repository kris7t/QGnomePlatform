TEMPLATE = lib

CONFIG += plugin \
          c++11 \-
          link_pkgconfig

QT += core-private \
      gui-private \
      waylandclient-private \
      widgets \

equals(QT_MAJOR_VERSION, 5): greaterThan(QT_MINOR_VERSION, 7): QT += theme_support-private
equals(QT_MAJOR_VERSION, 5): lessThan(QT_MINOR_VERSION, 8): QT += platformsupport-private

PKGCONFIG += gtk+-3.0 \
             gtk+-x11-3.0

TARGET = qgnome
target.path += $$[QT_INSTALL_PLUGINS]/platforms
INSTALLS += target

SOURCES += \
    gnomeintegration.cpp

HEADERS += \
    gnomeintegration.h
