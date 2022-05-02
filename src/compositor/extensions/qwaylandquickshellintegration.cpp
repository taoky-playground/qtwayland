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

#include "qwaylandquickshellintegration.h"

/*!
 * \class QWaylandQuickShellIntegration
 * \inmodule QtWaylandCompositor
 * \since 5.14
 * \brief Provides support for shell surface integration with QtQuick.
 *
 * Shell surface implementations should inherit from this class in order to provide
 * an integration between the shell surface and QtQuick.
 *
 * Shell integration is installed as an event filter for a QWaylandQuickShellSurfaceItem.
 * Reimplement the event filter method and return \c true when you want to filter the
 * event out, otherwise return \c false.
 *
 * Example:
 *
 * \code
 * class MyShellIntegration : public QWaylandQuickShellIntegration
 * {
 *     Q_OBJECT
 * public:
 *     MyShellIntegration(QObject *parent = nullptr);
 *
 * protected:
 *     bool eventFilter(QObject *object, QEvent *event) override;
 * };
 *
 * MyShellIntegration::MyShellIntegration(QObject *parent)
 *     : QWaylandQuickShellIntegration(parent)
 * {
 * }
 *
 * bool MyShellIntegration::eventFilter(QObject *object, QEvent *event)
 * {
 *     QWaylandQuickShellSurfaceItem *shellSurfaceItem = qobject_cast<QWaylandQuickShellSurfaceItem *>(object);
 *     if (!shellSurfaceItem)
 *         return QWaylandQuickShellIntegration::eventFilter(object, event);
 *
 *     if (event->type() == QEvent::MouseMove) {
 *         QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
 *         qDebug() << "Mouse moved on" << shellSurfaceItem << "pos:" << mouseEvent->pos();
 *         return true;
 *     }
 *
 *     return QWaylandQuickShellIntegration::eventFilter(object, event);
 * }
 * \endcode
 *
 * \sa QWaylandQuickShellSurfaceItem
 * \sa QObject::eventFilter()
 */

QWaylandQuickShellIntegration::QWaylandQuickShellIntegration(QObject *parent)
    : QObject(parent)
{
}

QWaylandQuickShellIntegration::~QWaylandQuickShellIntegration()
{
}
