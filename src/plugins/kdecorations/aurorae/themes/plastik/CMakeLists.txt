add_subdirectory(code)

install(DIRECTORY package/
        DESTINATION ${KDE_INSTALL_DATADIR}/${KWIN_NAME}/decorations/kwin4_decoration_qml_plastik)

install(FILES package/metadata.desktop
        DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/${KWIN_NAME}
        RENAME kwin4_decoration_qml_plastik.desktop)

file(COPY package/ DESTINATION ${CMAKE_BINARY_DIR}/bin/deepin-kwin/decorations/kwin4_decoration_qml_plastik)
