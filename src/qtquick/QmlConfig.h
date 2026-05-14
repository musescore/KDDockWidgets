/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/docks_export.h>

#include <QQuickItem>

QT_BEGIN_NAMESPACE
class QQmlEngine;
QT_END_NAMESPACE

namespace KDDockWidgets {

/// @brief Returns the KDDockWidgets ctx associated with @p engine, or 0 if unset.
/// The ctx is stored on the engine itself (as a dynamic property), so each
/// QQmlEngine carries its own ctx — no process-wide singleton.
DOCKS_EXPORT int ctxForEngine(QQmlEngine *engine);

/// @brief Associates @p ctx with @p engine. Called from QmlConfig::setCtx.
DOCKS_EXPORT void setCtxForEngine(QQmlEngine *engine, int ctx);

class DOCKS_EXPORT QmlConfig : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Config)
    QML_SINGLETON
    Q_PROPERTY(QJSValue dockWidgetFactoryFunc READ dockWidgetFactoryFunc WRITE setDockWidgetFactoryFunc NOTIFY dockWidgetFactoryFuncChanged)
    Q_PROPERTY(int ctx READ ctx WRITE setCtx NOTIFY ctxChanged)
public:
    QmlConfig();
    ~QmlConfig() override;

    QJSValue dockWidgetFactoryFunc() const;
    void setDockWidgetFactoryFunc(const QJSValue &func);

    int ctx() const;
    void setCtx(int ctx);

Q_SIGNALS:
    void dockWidgetFactoryFuncChanged();
    void ctxChanged();

private:
    QJSValue m_dockWidgetFactoryFunc;
    int m_ctx = 0;
};

}
