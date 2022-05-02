/****************************************************************************
**
** Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "qwaylandinputmethodcontrol.h"
#include "qwaylandinputmethodcontrol_p.h"

#include "qwaylandcompositor.h"
#include "qwaylandseat.h"
#include "qwaylandsurface.h"
#include "qwaylandview.h"
#include "qwaylandtextinput.h"
#include "qwaylandqttextinputmethod.h"

#include <QtGui/QInputMethodEvent>

QWaylandInputMethodControl::QWaylandInputMethodControl(QWaylandSurface *surface)
    : QObject(*new QWaylandInputMethodControlPrivate(surface), surface)
{
    connect(d_func()->compositor, &QWaylandCompositor::defaultSeatChanged,
            this, &QWaylandInputMethodControl::defaultSeatChanged);
    QWaylandTextInput *textInput = d_func()->textInput();
    if (textInput) {
        connect(textInput, &QWaylandTextInput::surfaceEnabled, this, &QWaylandInputMethodControl::surfaceEnabled);
        connect(textInput, &QWaylandTextInput::surfaceDisabled, this, &QWaylandInputMethodControl::surfaceDisabled);
        connect(textInput, &QWaylandTextInput::updateInputMethod, this, &QWaylandInputMethodControl::updateInputMethod);
    }

    QWaylandQtTextInputMethod *textInputMethod = d_func()->textInputMethod();
    if (textInputMethod) {
        connect(textInputMethod, &QWaylandQtTextInputMethod::surfaceEnabled, this, &QWaylandInputMethodControl::surfaceEnabled);
        connect(textInputMethod, &QWaylandQtTextInputMethod::surfaceDisabled, this, &QWaylandInputMethodControl::surfaceDisabled);
        connect(textInputMethod, &QWaylandQtTextInputMethod::updateInputMethod, this, &QWaylandInputMethodControl::updateInputMethod);
    }
}

QVariant QWaylandInputMethodControl::inputMethodQuery(Qt::InputMethodQuery query, QVariant argument) const
{
    Q_D(const QWaylandInputMethodControl);

    QWaylandTextInput *textInput = d->textInput();
    if (textInput != nullptr && textInput->focus() == d->surface)
        return textInput->inputMethodQuery(query, argument);

    QWaylandQtTextInputMethod *textInputMethod = d_func()->textInputMethod();
    if (textInputMethod && textInputMethod->focusedSurface() == d->surface)
        return textInputMethod->inputMethodQuery(query, argument);

    return QVariant();
}

void QWaylandInputMethodControl::inputMethodEvent(QInputMethodEvent *event)
{
    Q_D(QWaylandInputMethodControl);

    QWaylandTextInput *textInput = d->textInput();
    if (textInput) {
        textInput->sendInputMethodEvent(event);
    } else if (QWaylandQtTextInputMethod *textInputMethod = d->textInputMethod()) {
        textInputMethod->sendInputMethodEvent(event);
    } else {
        event->ignore();
    }
}

bool QWaylandInputMethodControl::enabled() const
{
    Q_D(const QWaylandInputMethodControl);

    return d->enabled;
}

void QWaylandInputMethodControl::setEnabled(bool enabled)
{
    Q_D(QWaylandInputMethodControl);

    if (d->enabled == enabled)
        return;

    d->enabled = enabled;
    emit enabledChanged(enabled);
    emit updateInputMethod(Qt::ImQueryInput);
}

void QWaylandInputMethodControl::surfaceEnabled(QWaylandSurface *surface)
{
    Q_D(QWaylandInputMethodControl);

    if (surface == d->surface)
        setEnabled(true);
}

void QWaylandInputMethodControl::surfaceDisabled(QWaylandSurface *surface)
{
    Q_D(QWaylandInputMethodControl);

    if (surface == d->surface)
        setEnabled(false);
}

void QWaylandInputMethodControl::setSurface(QWaylandSurface *surface)
{
    Q_D(QWaylandInputMethodControl);

    if (d->surface == surface)
        return;

    d->surface = surface;

    QWaylandTextInput *textInput = d->textInput();
    QWaylandQtTextInputMethod *textInputMethod = d->textInputMethod();
    setEnabled((textInput && textInput->isSurfaceEnabled(d->surface))
               || (textInputMethod && textInputMethod->isSurfaceEnabled(d->surface)));
}

void QWaylandInputMethodControl::defaultSeatChanged()
{
    Q_D(QWaylandInputMethodControl);

    disconnect(d->textInput(), nullptr, this, nullptr);
    disconnect(d->textInputMethod(), nullptr, this, nullptr);

    d->seat = d->compositor->defaultSeat();
    QWaylandTextInput *textInput = d->textInput();
    QWaylandQtTextInputMethod *textInputMethod = d->textInputMethod();

    if (textInput) {
        connect(textInput, &QWaylandTextInput::surfaceEnabled, this, &QWaylandInputMethodControl::surfaceEnabled);
        connect(textInput, &QWaylandTextInput::surfaceDisabled, this, &QWaylandInputMethodControl::surfaceDisabled);
    }

    if (textInputMethod) {
        connect(textInputMethod, &QWaylandQtTextInputMethod::surfaceEnabled, this, &QWaylandInputMethodControl::surfaceEnabled);
        connect(textInputMethod, &QWaylandQtTextInputMethod::surfaceDisabled, this, &QWaylandInputMethodControl::surfaceDisabled);
    }

    setEnabled((textInput && textInput->isSurfaceEnabled(d->surface))
               || (textInputMethod && textInputMethod->isSurfaceEnabled(d->surface)));
}

QWaylandInputMethodControlPrivate::QWaylandInputMethodControlPrivate(QWaylandSurface *surface)
    : compositor(surface->compositor())
    , seat(compositor->defaultSeat())
    , surface(surface)
{
}

QWaylandQtTextInputMethod *QWaylandInputMethodControlPrivate::textInputMethod() const
{
    return QWaylandQtTextInputMethod::findIn(seat);
}

QWaylandTextInput *QWaylandInputMethodControlPrivate::textInput() const
{
    return QWaylandTextInput::findIn(seat);
}

#include "moc_qwaylandinputmethodcontrol.cpp"
