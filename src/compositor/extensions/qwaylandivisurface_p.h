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

#ifndef QWAYLANDIVISURFACE_P_H
#define QWAYLANDIVISURFACE_P_H

#include <QtWaylandCompositor/private/qwaylandcompositorextension_p.h>
#include <QtWaylandCompositor/private/qwayland-server-ivi-application.h>

#include <QtWaylandCompositor/QWaylandIviSurface>

#include <QtWaylandCompositor/QWaylandSurfaceRole>

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

QT_BEGIN_NAMESPACE

class Q_WAYLAND_COMPOSITOR_EXPORT QWaylandIviSurfacePrivate
        : public QWaylandCompositorExtensionPrivate
        , public QtWaylandServer::ivi_surface
{
    Q_DECLARE_PUBLIC(QWaylandIviSurface)

public:
    QWaylandIviSurfacePrivate();
    static QWaylandIviSurfacePrivate *get(QWaylandIviSurface *iviSurface) { return iviSurface->d_func(); }

protected:
    void ivi_surface_destroy_resource(Resource *resource) override;
    void ivi_surface_destroy(Resource *resource) override;

private:
    QWaylandIviApplication *m_iviApplication = nullptr;
    QWaylandSurface *m_surface = nullptr;
    uint m_iviId = UINT_MAX;

    static QWaylandSurfaceRole s_role;
};

QT_END_NAMESPACE

#endif // QWAYLANDIVISURFACE_P_H
