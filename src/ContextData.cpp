/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ContextData.h"

#include <map>

#include "Config.h"
#include "core/DockRegistry.h"
#include "core/DragController_p.h"
#include "core/Platform.h"

namespace KDDockWidgets {

static std::map<int, ContextData *> s_data = {};

ContextData *ContextData::context(int ctx)
{
    auto it = s_data.find(ctx);
    if (it != s_data.end())
        return it->second;

    auto *d = new ContextData();
    d->config = new Config(ctx);
    d->reg = new DockRegistry(ctx);
    d->dctrl = new Core::DragController(ctx);

    s_data.insert({ ctx, d });

    return d;
}

void ContextData::destroyContext(int ctx)
{
    auto it = s_data.find(ctx);
    if (it == s_data.end()) {
        return;
    }

    ContextData *d = it->second;
    delete d->config;
    delete d->reg;
    delete d->dctrl;
    delete d;

    s_data.erase(it);

    if (s_data.empty() && Core::Platform::isInitialized()) {
        delete Core::Platform::instance();
    }
}

size_t ContextData::contextCount()
{
    return s_data.size();
}

}
