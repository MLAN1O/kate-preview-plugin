cmake_minimum_required(VERSION 3.16)
project(kate-preview-plugin VERSION 26.08.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(ECM 6.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(KF6CoreAddons REQUIRED)
find_package(KF6I18n REQUIRED)
find_package(KF6TextEditor REQUIRED)
find_package(KF6WidgetsAddons REQUIRED)
find_package(KF6XmlGui REQUIRED)
find_package(KF6Parts REQUIRED)
find_package(KF6Config REQUIRED)

kcoreaddons_add_plugin(ktexteditorpreviewplugin INSTALL_NAMESPACE "kf6/ktexteditor")

target_compile_definitions(ktexteditorpreviewplugin PRIVATE TRANSLATION_DOMAIN="ktexteditorpreviewplugin")

ecm_qt_declare_logging_category(
  DEBUG_SOURCES
  HEADER ktexteditorpreview_debug.h
  IDENTIFIER KTEPREVIEW
  CATEGORY_NAME "ktexteditorpreviewplugin"
)

target_sources(
  ktexteditorpreviewplugin
  PRIVATE
    ${DEBUG_SOURCES}
    ktexteditorpreviewplugin.cpp
    ktexteditorpreviewview.cpp
    previewtoggleclient.cpp
    previewwidget.cpp
    kpartview.cpp
)

target_include_directories(ktexteditorpreviewplugin PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(
  ktexteditorpreviewplugin
  PRIVATE
    KF6::CoreAddons
    KF6::I18n
    KF6::TextEditor
    KF6::WidgetsAddons
    KF6::XmlGui
    KF6::Parts
    KF6::ConfigCore
)
