install(DIRECTORY package/
        DESTINATION ${KDE_INSTALL_DATADIR}/${KWIN_NAME}/effects/kwin4_effect_fade)

install(FILES package/metadata.desktop
        DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/${KWIN_NAME}
        RENAME kwin4_effect_fade.desktop)

file(COPY package/ DESTINATION ${CMAKE_BINARY_DIR}/bin/deepin-kwin/effects/kwin4_effect_fade)
