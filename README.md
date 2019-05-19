# 003.OpenCV-CPP-Sample

実行手順

	$ git clone https://github.com/ryoma-jp/003.OpenCV-CPP-Sample.git
	$ cd 003.OpenCV-CPP-Sample
	$ mkdir build
	$ cd build
	$ cmake ..
	
	# 静止画入力の場合
	$ ./cv2-sample --mode 0 --input_file test.jpg
	
	# カメラ入力の場合
	$ ./cv2-sample --mode 1
