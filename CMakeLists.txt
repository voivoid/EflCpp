cmake_minimum_required(VERSION 3.7)

set(MyDepsDir ${CMAKE_CURRENT_BINARY_DIR}/Deps)
set(MyDepsBoostDir ${MyDepsDir}/boost)
set(MyDepsEflDir ${MyDepsDir}/Efl)
set(MyDepsElmDir ${MyDepsDir}/Elm)

if(BUILD_DEPENDENCIES)
  project(EflCppDeps LANGUAGES C CXX)
  add_subdirectory(thirdparty)
  return()
endif()

project(EflCpp LANGUAGES CXX)
message("Will build EflCpp")

set(SOURCES
  inc/EflCpp/application.h
  inc/EflCpp/application_tasks.h
  inc/EflCpp/assert.h
  inc/EflCpp/background.h
  inc/EflCpp/bimap.h
  inc/EflCpp/box.h
  inc/EflCpp/button.h
  inc/EflCpp/canvas.h
  inc/EflCpp/canvas_box.h
  inc/EflCpp/canvas_image.h
  inc/EflCpp/canvas_line.h
  inc/EflCpp/canvas_object.h
  inc/EflCpp/canvas_polygon.h
  inc/EflCpp/canvas_rect.h
  inc/EflCpp/canvas_table.h
  inc/EflCpp/canvas_text.h
  inc/EflCpp/conformant.h
  inc/EflCpp/container.h
  inc/EflCpp/context_popup.h
  inc/EflCpp/dialog.h
  inc/EflCpp/eina_list.h
  inc/EflCpp/elementary_fwd.h
  inc/EflCpp/elementary_inc.h
  inc/EflCpp/entry.h
  inc/EflCpp/elm_obj.h
  inc/EflCpp/elm_obj_item.h
  inc/EflCpp/evas_obj.h
  inc/EflCpp/events/base_events.h
  inc/EflCpp/events/evas_events.h
  inc/EflCpp/events/gesture_events.h
  inc/EflCpp/events/smart_events.h
  inc/EflCpp/exception.h
  inc/EflCpp/files.h
  inc/EflCpp/file_selector.h
  inc/EflCpp/genlist.h
  inc/EflCpp/geo.h
  inc/EflCpp/gestures.h
  inc/EflCpp/grid.h
  inc/EflCpp/hoversel.h
  inc/EflCpp/icon.h
  inc/EflCpp/image.h
  inc/EflCpp/label.h
  inc/EflCpp/layout.h
  inc/EflCpp/list.h
  inc/EflCpp/log.h
  inc/EflCpp/log_utils.h
  inc/EflCpp/macros.h
  inc/EflCpp/naviframe.h
  inc/EflCpp/panel.h
  inc/EflCpp/policies.h
  inc/EflCpp/popup.h
  inc/EflCpp/preferences.h
  inc/EflCpp/progress_bar.h
  inc/EflCpp/resources.h
  inc/EflCpp/safe_callback.h
  inc/EflCpp/scrollable.h
  inc/EflCpp/scroller.h
  inc/EflCpp/segment.h
  inc/EflCpp/spinner.h
  inc/EflCpp/table.h
  inc/EflCpp/theme.h
  inc/EflCpp/thread.h
  inc/EflCpp/timer.h
  inc/EflCpp/toolbar.h
  inc/EflCpp/utils.h
  inc/EflCpp/window.h
  src/application_tasks.cpp
  src/assert.cpp
  src/background.cpp
  src/box.cpp
  src/button.cpp
  src/canvas.cpp
  src/canvas_box.cpp
  src/canvas_image.cpp
  src/canvas_line.cpp
  src/canvas_object.cpp
  src/canvas_polygon.cpp
  src/canvas_rect.cpp
  src/canvas_table.cpp
  src/canvas_text.cpp
  src/conformant.cpp
  src/container.cpp
  src/context_popup.cpp
  src/dialog.cpp
  src/eina_list.cpp
  src/entry.cpp
  src/elm_obj.cpp
  src/elm_obj_item.cpp
  src/evas_obj.cpp
  src/events/base_events.cpp
  src/events/evas_events.cpp
  src/events/gesture_events.cpp
  src/events/smart_events.cpp
  src/file_selector.cpp
  src/genlist.cpp
  src/gestures.cpp
  src/grid.cpp
  src/hoversel.cpp
  src/icon.cpp
  src/image.cpp
  src/label.cpp
  src/layout.cpp
  src/list.cpp
  src/log.cpp
  src/log_utils.cpp
  src/naviframe.cpp
  src/panel.cpp
  src/policies.cpp
  src/popup.cpp
  src/progress_bar.cpp
  src/resources.cpp
  src/scrollable.cpp
  src/scroller.cpp
  src/segment.cpp
  src/spinner.cpp
  src/table.cpp
  src/theme.cpp
  src/thread.cpp
  src/timer.cpp
  src/toolbar.cpp
  src/utils.cpp
  src/window.cpp
  )

if(TIZEN)
  list(APPEND SOURCES
    src/tizen/EflCpp/platform/app_control.h
    src/tizen/EflCpp/platform/app_control.cpp
    src/tizen/EflCpp/platform/application.cpp
    src/tizen/EflCpp/platform/dlog_sink.h
    src/tizen/EflCpp/platform/dlog_sink.cpp
    src/tizen/EflCpp/platform/files.cpp
    src/tizen/EflCpp/platform/file_selector_impl.cpp
    src/tizen/EflCpp/platform/file_selector_impl.h
    src/tizen/EflCpp/platform/preferences.cpp
    src/tizen/EflCpp/platform/resources.cpp
    )
else()
  list(APPEND SOURCES
    src/desktop/EflCpp/platform/application.cpp
    src/desktop/EflCpp/platform/elm_file_selector.h
    src/desktop/EflCpp/platform/elm_file_selector.cpp
    src/desktop/EflCpp/platform/file_selector_impl.cpp
    src/desktop/EflCpp/platform/file_selector_impl.h
    src/desktop/EflCpp/platform/files.cpp
    src/desktop/EflCpp/platform/preferences.cpp
    src/desktop/EflCpp/platform/resources.cpp
    )
endif()

add_library(EflCpp ${SOURCES})

if(TIZEN)
  target_include_directories(EflCpp PRIVATE src/tizen)
  target_compile_definitions(EflCpp PUBLIC EFLCPP_TIZEN)
else()
  target_include_directories(EflCpp PRIVATE src/desktop)
endif()

target_include_directories(EflCpp PUBLIC inc)
target_compile_options(EflCpp PRIVATE -Wall -Wextra -Werror)

set_target_properties(EflCpp PROPERTIES CXX_STANDARD 14)



# Dependencies

# Boost

set(BOOST_ROOT ${MyDepsBoostDir})
find_package(Boost 1.63.0 REQUIRED COMPONENTS filesystem system log)
target_link_libraries(EflCpp PUBLIC Boost::boost Boost::filesystem Boost::log Boost::system)

# Efl

if(TIZEN)

  target_include_directories(EflCpp SYSTEM PRIVATE
    ${CMAKE_SYSROOT}/usr/include/appfw
    ${CMAKE_SYSROOT}/usr/include/dbus-1.0
    ${CMAKE_SYSROOT}/usr/include/dlog
    ${CMAKE_SYSROOT}/usr/include/e_dbus-1
    ${CMAKE_SYSROOT}/usr/include/ecore-1
    ${CMAKE_SYSROOT}/usr/include/ecore-con-1
    ${CMAKE_SYSROOT}/usr/include/ecore-evas-1
    ${CMAKE_SYSROOT}/usr/include/ecore-file-1
    ${CMAKE_SYSROOT}/usr/include/ecore-imf-1
    ${CMAKE_SYSROOT}/usr/include/ecore-imf-evas-1
    ${CMAKE_SYSROOT}/usr/include/ecore-input-1
    ${CMAKE_SYSROOT}/usr/include/edje-1
    ${CMAKE_SYSROOT}/usr/include/eet-1
    ${CMAKE_SYSROOT}/usr/include/efl-1
    ${CMAKE_SYSROOT}/usr/include/efl-extension
    ${CMAKE_SYSROOT}/usr/include/efreet-1
    ${CMAKE_SYSROOT}/usr/include/eina-1
    ${CMAKE_SYSROOT}/usr/include/eina-1/eina
    ${CMAKE_SYSROOT}/usr/include/eldbus-1
    ${CMAKE_SYSROOT}/usr/include/elementary-1

    ${CMAKE_SYSROOT}/usr/include/ethumb-1
    ${CMAKE_SYSROOT}/usr/include/ethumb-client-1
    ${CMAKE_SYSROOT}/usr/include/evas-1
    ${CMAKE_SYSROOT}/usr/include/system

    ${CMAKE_SYSROOT}/usr/lib/dbus-1.0/include
    )

  target_link_libraries(EflCpp PRIVATE
    capi-appfw-app-common
    capi-appfw-app-control
    capi-appfw-application
    capi-base-common
    capi-system-system-settings
    dlog
    ecore
    edje
    eet
    efl-extension
    eina
    elementary
    evas
    )

  if(TIZEN_SDK_VERSION STRGREATER "2.4" OR TIZEN_SDK_VERSION STREQUAL "2.4")
    target_include_directories(EflCpp SYSTEM PRIVATE ${CMAKE_SYSROOT}/usr/include/eo-1)
    target_link_libraries(EflCpp PRIVATE eo)
  endif()

  target_compile_options(EflCpp PRIVATE -Wno-unused-function)
  
else()

  find_package(PkgConfig REQUIRED)
  list(APPEND CMAKE_PREFIX_PATH ${MyDepsEflDir})
  list(APPEND CMAKE_PREFIX_PATH ${MyDepsElmDir})
  pkg_check_modules(EFL REQUIRED elementary IMPORTED_TARGET)

  set_property(TARGET PkgConfig::EFL PROPERTY INTERFACE_LINK_LIBRARIES ${EFL_LDFLAGS}) # TODO: remove this hack as soon as cmake will handle libs properly
  
  target_link_libraries(EflCpp PRIVATE PkgConfig::EFL)

endif()
