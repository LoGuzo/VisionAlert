cmake_minimum_required(VERSION 3.5)

# 프로젝트명 자동 설정
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C CXX)

# C++11 사용
set(CMAKE_CXX_STANDARD 11)

# ✅ OpenCV 수동 경로 설정 (MinGW용 빌드 기준)
set(OpenCV_DIR "C:/opencv/mingw_build")

# include, lib, dll 경로 지정
set(OpenCV_INCLUDE_DIR "${OpenCV_DIR}/include")
set(OpenCV_LIB "${OpenCV_DIR}/x64/mingw/lib/libopencv_world4100.dll.a")
set(OpenCV_DLL "${OpenCV_DIR}/x64/mingw/bin/libopencv_world4100.dll")

# include 디렉토리 등록
include_directories(${OpenCV_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 소스 파일 가져오기
file(GLOB SOURCES src/*.cpp)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# OpenCV 라이브러리 링크
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIB})

# 빌드 후 DLL 복사
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OpenCV_DLL}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
