cmake_minimum_required(VERSION 2.8)
project(opencv-cpp)

set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")

# argparseが格納されているライブラリパスを指定
set(LOCAL_LIB_PATH /usr/local/lib /home/pi/local/lib)

# OpenCVのパッケージを探す
find_package(OpenCV REQUIRED)

# OpenCVが見つかった場合のみ設定を行う
if(OpenCV_FOUND)
	# インクルードパスを指定
	include_directories(/home/pi/local/include ${OpenCV_INCLUDE_DIRS})

	# ライブラリパスを指定
	link_directories(${LOCAL_LIB_PATH})

	# 実行ファイル名とソース指定
	add_executable(cv2-sample cv2-sample.cpp)

	# リンクするライブラリ指定
	target_link_libraries(cv2-sample argparse ${OpenCV_LIBS})
endif(OpenCV_FOUND)

