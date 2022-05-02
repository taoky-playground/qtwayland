/****************************************************************************
**
** Copyright (C) 2017 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef QWAYLANDQUICKOUTPUT_H
#define QWAYLANDQUICKOUTPUT_H

#include <QtQuick/QQuickWindow>
#include <QtWaylandCompositor/qwaylandoutput.h>
#include <QtWaylandCompositor/qwaylandquickchildren.h>

QT_REQUIRE_CONFIG(wayland_compositor_quick);

QT_BEGIN_NAMESPACE

class QWaylandQuickCompositor;
class QQuickWindow;

class Q_WAYLAND_COMPOSITOR_EXPORT QWaylandQuickOutput : public QWaylandOutput, public QQmlParserStatus
{
    Q_INTERFACES(QQmlParserStatus)
    Q_OBJECT
    Q_WAYLAND_COMPOSITOR_DECLARE_QUICK_CHILDREN(QWaylandQuickOutput)
    Q_PROPERTY(bool automaticFrameCallback READ automaticFrameCallback WRITE setAutomaticFrameCallback NOTIFY automaticFrameCallbackChanged)
    QML_NAMED_ELEMENT(WaylandOutput)
    QML_ADDED_IN_VERSION(1, 0)
public:
    QWaylandQuickOutput();
    QWaylandQuickOutput(QWaylandCompositor *compositor, QWindow *window);

    void update() override;

    bool automaticFrameCallback() const;
    void setAutomaticFrameCallback(bool automatic);

    QQuickItem *pickClickableItem(const QPointF &position);

public Q_SLOTS:
    void updateStarted();

Q_SIGNALS:
    void automaticFrameCallbackChanged();

protected:
    void initialize() override;
    void classBegin() override;
    void componentComplete() override;

private:
    void doFrameCallbacks();

    bool m_updateScheduled = false;
    bool m_automaticFrameCallback = true;
};

QT_END_NAMESPACE

#endif
