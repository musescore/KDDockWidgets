/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ContextData.h"

#ifdef KDDOCKWIDGETS_CONTEXT_SUPPORT

#include "../Config.h"
#include "DockRegistry.h"
#include "DragController_p.h"

#include <map>

namespace KDDockWidgets {

static std::map<int, ContextData *> s_contextData;

ContextData *ContextData::context(int ctx)
{
    auto it = s_contextData.find(ctx);
    if (it != s_contextData.end())
        return it->second;

    auto *d = new ContextData();
    // Order matters: Config is first, then DockRegistry (may use Config), then DragController.
    d->config = new Config(ctx);
    d->dockRegistry = new DockRegistry(nullptr, ctx);
    d->dragController = new Core::DragController(nullptr, ctx);

    s_contextData.emplace(ctx, d);
    return d;
}

size_t ContextData::contextCount()
{
    return s_contextData.size();
}

bool ContextData::hasContext(int ctx)
{
    return s_contextData.count(ctx) > 0;
}

void ContextData::destroyContext(int ctx)
{
    auto it = s_contextData.find(ctx);
    if (it == s_contextData.end())
        return;

    ContextData *d = it->second;
    // Destroy in reverse order of creation.
    delete d->dragController;
    delete d->dockRegistry;
    delete d->config;
    delete d;

    s_contextData.erase(it);
}

} // namespace KDDockWidgets

#endif // KDDOCKWIDGETS_CONTEXT_SUPPORT
