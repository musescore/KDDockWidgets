/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "QmlConfig.h"
#include "Config.h"
#include "DockWidgetInstantiator.h"
#include "kddockwidgets/core/DockWidget.h"

#include <QDebug>
#include <QQmlEngine>
#include <private/qglobal_p.h>

using namespace KDDockWidgets;

namespace {
// Stored as a dynamic property on the engine so ctx lives per-engine
// rather than as a process-wide singleton.
constexpr const char *kKddwCtxProperty = "_kddw_ctx";
}

int KDDockWidgets::ctxForEngine(QQmlEngine *engine)
{
    if (!engine)
        return 0;
    return engine->property(kKddwCtxProperty).toInt();
}

void KDDockWidgets::setCtxForEngine(QQmlEngine *engine, int ctx)
{
    if (!engine)
        return;
    engine->setProperty(kKddwCtxProperty, ctx);
}

QmlConfig::QmlConfig() = default;

QmlConfig::~QmlConfig()
{
    Config::self(m_ctx).setDockWidgetFactoryFunc(nullptr);
}

QJSValue QmlConfig::dockWidgetFactoryFunc() const
{
    return m_dockWidgetFactoryFunc;
}

void QmlConfig::setDockWidgetFactoryFunc(const QJSValue &func)
{
    if (m_dockWidgetFactoryFunc.equals(func))
        return;

    m_dockWidgetFactoryFunc = func;

    if (m_dockWidgetFactoryFunc.isCallable()) {
        QJSValue jsFunc = m_dockWidgetFactoryFunc;
        Config::self(m_ctx).setDockWidgetFactoryFunc(
            [jsFunc](const QString &name) mutable -> KDDockWidgets::Core::DockWidget * {
                if (!jsFunc.isCallable())
                    return nullptr;

                QJSValue result = jsFunc.call(QJSValueList() << name);
                if (result.isError() || result.isNull() || result.isUndefined())
                    return nullptr;

                auto dwInstantiator = qobject_cast<KDDockWidgets::DockWidgetInstantiator *>(result.toQObject());
                if (!dwInstantiator) {
                    qWarning() << "QmlConfig: Factory function did not return a valid DockWidgetInstantiator for" << name;
                    return nullptr;
                }

                auto dw = dwInstantiator->controller();
                if (!dw)
                    qWarning() << "QmlConfig: Factory function did not return a valid DockWidget for" << name;

                return dw;
            });
    } else {
        Config::self(m_ctx).setDockWidgetFactoryFunc(nullptr);
    }

    Q_EMIT dockWidgetFactoryFuncChanged();
}

int QmlConfig::ctx() const
{
    return m_ctx;
}

void QmlConfig::setCtx(int ctx)
{
    if (m_ctx == ctx)
        return;
    m_ctx = ctx;
    setCtxForEngine(qmlEngine(this), ctx);
    Q_EMIT ctxChanged();
}
