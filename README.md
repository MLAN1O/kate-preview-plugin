# Kate Document Preview plugin (standalone fork)

Standalone build of Kate's **Document Preview** plugin, based on
`addons/preview` from [Kate v26.08.1](https://invent.kde.org/utilities/kate/-/tree/v26.08.1/addons/preview).
It does not require building the full Kate application.

## Customizations

- Close button (`window-close`) at the right of the preview toolview toolbar,
  connected to `KTextEditor::MainWindow::hideToolView()`.
- Main toolbar toggle action for the preview toolview, synchronized with the
  toolview visibility.
- The preview toolview keeps the upstream lock, auto-update, manual update,
  and KPart menu actions.

## Requirements

- Kate / KTextEditor 6.x (tested with Kate 26.08.1 and KTextEditor 6.31.0).
- CMake >= 3.16, ECM, Qt 6 (Core, Gui, Widgets), and KF6 development packages
  for CoreAddons, I18n, TextEditor, WidgetsAddons, XmlGui, Parts, and Config.

On Fedora:

```bash
sudo dnf install cmake extra-cmake-modules qt6-qtbase-devel \
  kf6-kcoreaddons-devel kf6-ki18n-devel kf6-ktexteditor-devel \
  kf6-kwidgetsaddons-devel kf6-kxmlgui-devel kf6-kparts-devel \
  kf6-kconfig-devel
```

## Build and install

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build -j"$(nproc)"
sudo cmake --install build
```

The plugin is installed in the KTextEditor plugin directory, normally
`/usr/lib64/qt6/plugins/kf6/ktexteditor/`.

Back up the existing `ktexteditorpreviewplugin.so` before installing if
needed, then restart Kate.

## AI assistance

See [AI-USAGE.md](AI-USAGE.md).

## License

This work is based on Kate's Document Preview plugin and is licensed under
LGPL-2.0-or-later. See `LICENSES/LGPL-2.0-or-later.txt`.
