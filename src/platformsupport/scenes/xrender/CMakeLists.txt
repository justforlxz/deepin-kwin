# set(xrenderbackend_SOURCES
#     platformxrendersurfacetexture_x11.cpp
#     xrenderbackend.cpp
# )

# ecm_qt_declare_logging_category(xrenderbackend_SOURCES
#     HEADER logging.h
#     IDENTIFIER KWIN_XRENDER
#     CATEGORY_NAME kwin_scene_xrender
#     DEFAULT_SEVERITY Critical
# )

# add_library(SceneXRenderBackend STATIC ${xrenderbackend_SOURCES})
# target_link_libraries(SceneXRenderBackend kwin Qt::Core Qt::Gui)
# target_include_directories(SceneXRenderBackend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(kwin PRIVATE
    xrenderbackend.cpp
    xrendersurfacetexture_x11.cpp
    xrendersurfacetexture.cpp
)
target_include_directories(kwin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
