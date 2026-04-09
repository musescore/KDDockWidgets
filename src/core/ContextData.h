/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#ifdef KDDOCKWIDGETS_CONTEXT_SUPPORT

#include <cstddef>

namespace KDDockWidgets {

class Config;
class DockRegistry;

namespace Core {
class DragController;
}

class ContextData
{
public:
    static ContextData *context(int ctx);
    static size_t contextCount();
    static bool hasContext(int ctx);
    static void destroyContext(int ctx);

    Config *config = nullptr;
    DockRegistry *dockRegistry = nullptr;
    Core::DragController *dragController = nullptr;
};

} // namespace KDDockWidgets

#endif // KDDOCKWIDGETS_CONTEXT_SUPPORT
