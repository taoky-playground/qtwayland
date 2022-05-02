/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QWAYLANDDATAOFFER_H
#define QWAYLANDDATAOFFER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qinternalmimedata_p.h>

#include <QtWaylandClient/private/qtwaylandclientglobal_p.h>
#include <QtWaylandClient/private/qwayland-wayland.h>

QT_REQUIRE_CONFIG(wayland_datadevice);

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

class QWaylandDisplay;
class QWaylandMimeData;

class QWaylandAbstractDataOffer
{
public:
    virtual void startReceiving(const QString &mimeType, int fd) = 0;
    virtual QMimeData *mimeData() = 0;

    virtual ~QWaylandAbstractDataOffer() = default;
};

class Q_WAYLAND_CLIENT_EXPORT QWaylandDataOffer
        : public QtWayland::wl_data_offer // needs to be the first because we do static casts from the user pointer to the wrapper
        , public QWaylandAbstractDataOffer
{
public:
    explicit QWaylandDataOffer(QWaylandDisplay *display, struct ::wl_data_offer *offer);
    ~QWaylandDataOffer() override;
    QMimeData *mimeData() override;

    QString firstFormat() const;

    void startReceiving(const QString &mimeType, int fd) override;

protected:
    void data_offer_offer(const QString &mime_type) override;

private:
    QWaylandDisplay *m_display = nullptr;
    QScopedPointer<QWaylandMimeData> m_mimeData;
};


class QWaylandMimeData : public QInternalMimeData {
public:
    explicit QWaylandMimeData(QWaylandAbstractDataOffer *dataOffer);
    ~QWaylandMimeData() override;

    void appendFormat(const QString &mimeType);

protected:
    bool hasFormat_sys(const QString &mimeType) const override;
    QStringList formats_sys() const override;
    QVariant retrieveData_sys(const QString &mimeType, QMetaType type) const override;

private:
    int readData(int fd, QByteArray &data) const;

    QWaylandAbstractDataOffer *m_dataOffer = nullptr;
    mutable QStringList m_types;
    mutable QHash<QString, QByteArray> m_data;
};

} // namespace QtWaylandClient

QT_END_NAMESPACE
#endif
