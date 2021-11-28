cmake_minimum_required(VERSION 2.8)
project( kmeans ) 
add_executable( kmeans src/main.cpp src/image/image.cpp src/kmeans/kmeans.cpp src/colors/colors.cpp src/matrix/matrix.cpp src/label/label.cpp)
target_include_directories( kmeans PRIVATE src/ )
