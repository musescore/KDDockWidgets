/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "LayoutSaverInstantiator.h"
#include "core/LayoutSaver_p.h"

using namespace KDDockWidgets;

LayoutSaverInstantiator::LayoutSaverInstantiator(QObject *parent)
    : QObject(parent)
{
}

LayoutSaverInstantiator::~LayoutSaverInstantiator() = default;

int LayoutSaverInstantiator::ctx() const
{
    return m_ctx;
}

void LayoutSaverInstantiator::setCtx(int ctx)
{
    if (m_ctx == ctx)
        return;
    m_ctx = ctx;
    m_saver.reset();
    Q_EMIT ctxChanged();
}

LayoutSaver *LayoutSaverInstantiator::saver()
{
    if (!m_saver)
        m_saver = std::make_unique<LayoutSaver>(m_ctx);
    return m_saver.get();
}

bool LayoutSaverInstantiator::saveToFile(const QString &jsonFilename)
{
    return saver()->saveToFile(jsonFilename);
}

bool LayoutSaverInstantiator::restoreFromFile(const QString &jsonFilename)
{
    return saver()->restoreFromFile(jsonFilename);
}

QVector<QString> LayoutSaverInstantiator::affinities() const
{
    return m_saver ? m_saver->dptr()->m_affinityNames : QVector<QString>();
}

void LayoutSaverInstantiator::setAffinities(const QVector<QString> &affinities)
{
    saver()->setAffinityNames(affinities);
    Q_EMIT affinitiesChanged();
}
