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

#ifndef QWAYLANDBRCMEGLINTEGRATION_H
#define QWAYLANDBRCMEGLINTEGRATION_H

#include <QtWaylandClient/private/qwaylandclientbufferintegration_p.h>
#include <QtWaylandClient/private/wayland-wayland-client-protocol.h>
#include <wayland-client-core.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <EGL/eglext_brcm.h>

#include <QtCore/qglobal.h>

struct qt_brcm;

QT_BEGIN_NAMESPACE

class QWindow;

namespace QtWaylandClient {

class QWaylandWindow;

class QWaylandBrcmEglIntegration : public QWaylandClientBufferIntegration
{
public:
    QWaylandBrcmEglIntegration();
    ~QWaylandBrcmEglIntegration();

    void initialize(QWaylandDisplay *waylandDisplay) override;

    bool supportsThreadedOpenGL() const override { return true; }
    bool supportsWindowDecoration() const override { return false; }

    QWaylandWindow *createEglWindow(QWindow *window);
    QPlatformOpenGLContext *createPlatformOpenGLContext(const QSurfaceFormat &glFormat, QPlatformOpenGLContext *share) const override;

    EGLDisplay eglDisplay() const;

    struct qt_brcm *waylandBrcm() const;

    PFNEGLFLUSHBRCMPROC eglFlushBRCM;
    PFNEGLCREATEGLOBALIMAGEBRCMPROC eglCreateGlobalImageBRCM;
    PFNEGLDESTROYGLOBALIMAGEBRCMPROC eglDestroyGlobalImageBRCM;

    void *nativeResource(NativeResource resource) override;
    void *nativeResourceForContext(NativeResource resource, QPlatformOpenGLContext *context) override;

private:
    static void wlDisplayHandleGlobal(void *data, struct ::wl_registry *registry, uint32_t id, const QString &interface, uint32_t version);

    struct wl_display *m_waylandDisplay = nullptr;
    struct qt_brcm *m_waylandBrcm = nullptr;

    EGLDisplay m_eglDisplay = EGL_NO_DISPLAY;

    QWaylandDisplay *m_display = nullptr;
};

}

QT_END_NAMESPACE

#endif // QWAYLANDBRCMEGLINTEGRATION_H
