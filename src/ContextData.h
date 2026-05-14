/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"

#include <cstddef>

namespace KDDockWidgets {

class Config;
class DockRegistry;

namespace Core {
class DragController;
}

/**
 * @brief Holds per-context KDDockWidgets state
 */
class DOCKS_EXPORT ContextData
{
public:
    static ContextData *context(int ctx);
    static void destroyContext(int ctx);
    static size_t contextCount();

    Config *config = nullptr;
    DockRegistry *reg = nullptr;
    Core::DragController *dctrl = nullptr;

private:
    ContextData() = default;
    ~ContextData() = default;
};

}
