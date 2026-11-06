/*
 *  SPDX-FileCopyrightText: 2026 Max
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

// KF
#include <KXMLGUIClient>
// Qt
#include <QObject>

class KToggleAction;
class QEvent;
class QWidget;

namespace KTextEditor
{
class MainWindow;
}

class PreviewToggleClient : public QObject, public KXMLGUIClient
{
    Q_OBJECT

public:
    PreviewToggleClient(KTextEditor::MainWindow *mainWindow, QWidget *toolView);
    ~PreviewToggleClient() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void updateActionState();

    KTextEditor::MainWindow *const m_mainWindow;
    QWidget *const m_toolView;
    KToggleAction *m_toggleAction;
};
