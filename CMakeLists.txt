cmake_minimum_required(VERSION 3.5)

# OpenCV 경로 설정
set(pathOPENCV C:/opencv/mingw_build)
include_directories(${pathOPENCV}/include)
set(LIBOPENCV ${pathOPENCV}/x64/mingw/lib/libopencv_world4100.dll.a)
set(OPENCV_DLL ${pathOPENCV}/x64/mingw/bin/libopencv_world4100.dll)

# 프로젝트 설정
get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C CXX)

# C++11 표준 사용
set(CMAKE_CXX_STANDARD 11)

# 소스 파일 가져오기
file(GLOB SOURCES src/*.cpp)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBOPENCV})

# 빌드 후 DLL 자동 복사
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENCV_DLL}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
