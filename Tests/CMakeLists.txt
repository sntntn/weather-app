cmake_minimum_required(VERSION 3.5)

project(weather-app-tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Core Network REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Positioning)
find_package(Qt6 REQUIRED COMPONENTS Test)

include_directories(
    .
    ../Source
    ../Source/Api
    ../Source/Data
    ../Source/Pages
    ../Source/Settings
    ../Source/Utils
    ../Source/Widgets
)

set(TEST_SOURCES
    main.cpp
    test_MainWindow.cpp
    test_Settings.cpp
    test_UserLocation.cpp
    test_WeatherAPI.cpp
    test_Parser.cpp
    test_WeatherData.cpp
    test_DetailedWeatherPage.cpp
    test_Serializer.cpp
)

set(CPP_SOURCES
    ../Source/MainWindow.cpp
    ../Source/MainWindow.h
    ../Source/MainWindow.ui

    ../Source/Api/ApiHandler.cpp ../Source/Api/ApiHandler.h
    ../Source/Api/GeocodingAPI.cpp ../Source/Api/GeocodingAPI.h
    ../Source/Api/WeatherAPI.cpp ../Source/Api/WeatherAPI.h
    ../Source/Api/DetailedWeatherAPI.cpp ../Source/Api/DetailedWeatherAPI.h
    ../Source/Api/Parser.cpp ../Source/Api/Parser.h

    ../Source/Data/Data.h
    ../Source/Data/DetailedWeatherData.cpp ../Source/Data/DetailedWeatherData.h
    ../Source/Data/GeoLocationData.cpp ../Source/Data/GeoLocationData.h
    ../Source/Data/WeatherData.cpp ../Source/Data/WeatherData.h

    ../Source/Pages/Page.cpp ../Source/Pages/Page.h
    ../Source/Pages/HomePage.cpp ../Source/Pages/HomePage.h
    ../Source/Pages/DetailedWeatherPage.cpp ../Source/Pages/DetailedWeatherPage.h
    ../Source/Pages/CustomCompleter.cpp ../Source/Pages/CustomCompleter.h

    ../Source/Settings/Settings.cpp ../Source/Settings/Settings.h
    ../Source/Settings/SettingsDialog.cpp ../Source/Settings/SettingsDialog.h
    ../Source/Settings/WidgetsManager.h

    ../Source/Utils/Serializable.h
    ../Source/Utils/Serializer.cpp ../Source/Utils/Serializer.h
    ../Source/Utils/UserLocation.cpp ../Source/Utils/UserLocation.h
    ../Source/Utils/GraphDialog.cpp ../Source/Utils/GraphDialog.h

    ../Source/Widgets/BasicWidget.h ../Source/Widgets/BasicWidget.cpp
    ../Source/Widgets/WeatherWidget.cpp ../Source/Widgets/WeatherWidget.h
    ../Source/Widgets/ErrorWidget.h ../Source/Widgets/ErrorWidget.cpp
    ../Source/Widgets/WeatherWidget.cpp ../Source/Widgets/WeatherWidget.h
    ../Source/Widgets/DetailedPageWidgets.cpp ../Source/Widgets/DetailedPageWidgets.h
)

add_executable(weather-app-tests ${TEST_SOURCES} ${CPP_SOURCES} catch.hpp)

target_link_libraries(weather-app-tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(weather-app-tests PRIVATE Qt6::Network)
target_link_libraries(weather-app-tests PRIVATE Qt6::Positioning)
target_link_libraries(weather-app-tests PRIVATE Qt6::Test)
