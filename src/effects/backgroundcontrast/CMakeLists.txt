#######################################
# Effect

# Source files
set(contrast_SOURCES
    contrast.cpp
    contrastshader.cpp
    main.cpp
)
kwin4_add_effect_module(kwin4_effect_contrast ${contrast_SOURCES})
