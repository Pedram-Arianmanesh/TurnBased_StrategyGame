cmake_minimum_required(VERSION 3.16)

project(TurnBased_StrategyGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# منابع پروژه
set(PROJECT_SOURCES
    src/main.cpp


    src/splashscreen.cpp
    src/splashscreen.h
    src/menupage.cpp
    src/menupage.h
    src/playerdialog.cpp
    src/playerdialog.h
    src/gamepage.cpp
    src/gamepage.h
    src/logic/cell.cpp
    src/logic/cell.h
    src/logic/agent.cpp
    src/logic/agent.h
    src/logic/boardparser.cpp
    src/logic/boardparser.h
    src/logic/gameboard.cpp
    src/logic/gameboard.h
    src/logic/gamestate.cpp
    src/logic/gamestate.h
)

# فایل‌های UI
set(UI_FILES
    src/splashscreen.ui
    src/menupage.ui
    src/playerdialog.ui
    src/agentgallery.ui
)

# فایل منابع
set(RESOURCE_FILES
    resources/resources.qrc
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TurnBased_StrategyGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${UI_FILES}
        ${RESOURCE_FILES}
        src/logic/hexboardwidget.h src/logic/hexboardwidget.cpp

        src/agentgallery.h src/agentgallery.cpp src/agentgallery.ui




    )
else()
    if(ANDROID)
        add_library(TurnBased_StrategyGame SHARED
            ${PROJECT_SOURCES}
            ${UI_FILES}
            ${RESOURCE_FILES}
        )
    else()
        add_executable(TurnBased_StrategyGame
            ${PROJECT_SOURCES}
            ${UI_FILES}
            ${RESOURCE_FILES}
        )
    endif()
endif()

# مسیرهای هدر
target_include_directories(TurnBased_StrategyGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic
)

# لینک کتابخانه‌ها
target_link_libraries(TurnBased_StrategyGame PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
)

# تنظیمات خاص پلتفرم
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TurnBased_StrategyGame)
endif()

set_target_properties(TurnBased_StrategyGame PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# نصب و بسته‌بندی
include(GNUInstallDirs)
install(TARGETS TurnBased_StrategyGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# فاینالایز برای Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TurnBased_StrategyGame)
endif()
