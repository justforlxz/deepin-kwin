add_executable(kwin_wayland_wrapper)

set_target_properties(kwin_wayland_wrapper PROPERTIES
    OUTPUT_NAME deepin-kwin_wayland_wrapper
)

target_sources(kwin_wayland_wrapper PRIVATE
    kwin_wrapper.cpp
    wl-socket.c
)

ecm_qt_declare_logging_category(kwin_wayland_wrapper
    HEADER
        wrapper_logging.h
    IDENTIFIER
        KWIN_WRAPPER
    CATEGORY_NAME
        kwin_wayland_wrapper
    DEFAULT_SEVERITY
        Warning
)

target_link_libraries(kwin_wayland_wrapper Qt${QT_MAJOR_VERSION}::Core Qt${QT_MAJOR_VERSION}::DBus KF5::DBusAddons KF5::CoreAddons KWinXwaylandCommon)
set_property(TARGET kwin_wayland_wrapper PROPERTY C_STANDARD 11)
install(TARGETS kwin_wayland_wrapper ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
