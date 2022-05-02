/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
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
******************************************************************************/

#ifndef BRCMBUFFER_H
#define BRCMBUFFER_H

#include <QtWaylandCompositor/private/qwayland-server-wayland.h>
#include <QtWaylandCompositor/private/qwaylandutils_p.h>

#include <QtCore/QList>
#include <QtCore/QSize>

#include <EGL/egl.h>

QT_BEGIN_NAMESPACE

class BrcmBuffer : public QtWaylandServer::wl_buffer
{
public:
    BrcmBuffer(struct ::wl_client *client, uint32_t id, const QSize &size, EGLint *data, size_t count);
    ~BrcmBuffer();

    bool isYInverted() const { return m_invertedY; }
    void setInvertedY(bool inverted) { m_invertedY = inverted; }

    EGLint *handle() { return m_handle.data(); }

    QSize size() { return m_size; }

    static BrcmBuffer *fromResource(struct ::wl_resource *resource) { return QtWayland::fromResource<BrcmBuffer *>(resource); }

protected:
    void buffer_destroy_resource(Resource *resource) override;
    void buffer_destroy(Resource *resource) override;

private:
    QList<EGLint> m_handle;
    bool m_invertedY = false;
    QSize m_size;
};

QT_END_NAMESPACE

#endif // BRCMBUFFER_H
