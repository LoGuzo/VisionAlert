cmake_minimum_required(VERSION 3.16)

# 프로젝트명 자동 설정
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} VERSION 0.1 LANGUAGES CXX)

# C++17 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)

# OpenCV 경로 지정 (MinGW용 빌드 기준)
set(OpenCV_DIR "C:/opencv/mingw_build")
find_package(OpenCV REQUIRED)

# Qt 경로 지정
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.3/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# 소스 파일
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS inc/*.h)
file(GLOB_RECURSE UIS ui/*.ui)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})

# include 디렉토리 추가 (OpenCV + 프로젝트용 헤더)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/ui
)

# 라이브러리 링크
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        ${OpenCV_LIBS}
)

# OpenCV DLL 복사
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OpenCV_DIR}/x64/mingw/bin/libopencv_world4100.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
