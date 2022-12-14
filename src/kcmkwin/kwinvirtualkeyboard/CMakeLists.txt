#SPDX-FileCopyrightText: 2020 Aleix Pol Gonzalzez <aleixpol@kde.org>
#SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kcm_virtualkeyboard\")

kcmutils_generate_module_data(
    kcm_virtualkeyboard_PART_SRCS
    MODULE_DATA_HEADER virtualkeyboarddata.h
    MODULE_DATA_CLASS_NAME VirtualKeyboardData
    SETTINGS_HEADERS virtualkeyboardsettings.h
    SETTINGS_CLASSES VirtualKeyboardSettings
)

kconfig_add_kcfg_files(kcm_virtualkeyboard_PART_SRCS virtualkeyboardsettings.kcfgc GENERATE_MOC)
add_library(deepin-kcm_virtualkeyboard MODULE kcmvirtualkeyboard.cpp ${kcm_virtualkeyboard_PART_SRCS})
target_include_directories(deepin-kcm_virtualkeyboard PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(deepin-kcm_virtualkeyboard
    KF5::I18n
    KF5::KCMUtils
    KF5::QuickAddons
)

kcoreaddons_desktop_to_json(deepin-kcm_virtualkeyboard "deepin-kcm_virtualkeyboard.desktop")

install(TARGETS deepin-kcm_virtualkeyboard DESTINATION ${KDE_INSTALL_PLUGINDIR}/kcms)
install(FILES deepin-kcm_virtualkeyboard.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
kpackage_install_package(package deepin-kcm_virtualkeyboard kcms)
