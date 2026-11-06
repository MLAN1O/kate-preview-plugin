/*
 *  SPDX-FileCopyrightText: 2026 Max
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "previewtoggleclient.h"

// KF
#include <KActionCollection>
#include <KLocalizedString>
#include <KTextEditor/MainWindow>
#include <KToggleAction>
#include <KXMLGUIFactory>

// Qt
#include <QAction>
#include <QEvent>
#include <QIcon>
#include <QSignalBlocker>
#include <QWidget>

PreviewToggleClient::PreviewToggleClient(KTextEditor::MainWindow *mainWindow, QWidget *toolView)
    : QObject(mainWindow)
    , m_mainWindow(mainWindow)
    , m_toolView(toolView)
{
    setComponentName(QStringLiteral("ktexteditorpreviewplugin"), i18n("Document Preview"));

    m_toggleAction = new KToggleAction(QIcon::fromTheme(QStringLiteral("document-preview")), i18n("Preview"), this);
    m_toggleAction->setToolTip(i18n("Show or hide the document preview"));
    m_toggleAction->setChecked(toolView->isVisible());
    actionCollection()->addAction(QStringLiteral("ktexteditorpreviewplugin_toggle"), m_toggleAction);

    connect(m_toggleAction, &QAction::toggled, this, [this](bool checked) {
        if (checked) {
            m_mainWindow->showToolView(m_toolView);
        } else {
            m_mainWindow->hideToolView(m_toolView);
        }
    });

    setXML(QStringLiteral(
        "<gui name=\"ktexteditorpreviewplugin\">"
        "<ToolBar name=\"mainToolBar\">"
        "<Action name=\"ktexteditorpreviewplugin_toggle\"/>"
        "</ToolBar>"
        "</gui>"));

    if (auto *factory = mainWindow->guiFactory()) {
        factory->addClient(this);
    }

    toolView->installEventFilter(this);
}

PreviewToggleClient::~PreviewToggleClient()
{
    if (m_toolView) {
        m_toolView->removeEventFilter(this);
    }

    if (auto *factory = m_mainWindow->guiFactory()) {
        factory->removeClient(this);
    }
}

bool PreviewToggleClient::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_toolView && (event->type() == QEvent::Show || event->type() == QEvent::Hide)) {
        updateActionState();
    }

    return QObject::eventFilter(watched, event);
}

void PreviewToggleClient::updateActionState()
{
    if (!m_toggleAction || !m_toolView) {
        return;
    }

    const QSignalBlocker blocker(m_toggleAction);
    m_toggleAction->setChecked(m_toolView->isVisible());
}
