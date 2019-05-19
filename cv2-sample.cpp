/*******************************************************
 * [ 説明 ]
 *  OpenCVを用いたC++サンプル
 *******************************************************/

/*******************************************************
 * インクルードファイル
 *******************************************************/
#include "argparse.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*******************************************************
 * 定数定義
 *******************************************************/

/**
 * @def INPUT_FILE_LEN
 * @brief 入力ファイル名の最大値
 */
#define INPUT_FILE_LEN  (1024)

/*******************************************************
 * 列挙体／構造体
 *******************************************************/

/*******************************************************
 * 関数宣言
 *******************************************************/

/*******************************************************
 * 変数宣言
 *******************************************************/

/**
 * @fn int main(int argc, char* argv[])
 * @brief ファイルの存在確認
 * @param[in] file_name ファイル名
 * @return ファイルが存在する場合にTRUEを返す，存在しなければFALSEを返す．
 */
using namespace cv;
int main(int argc, char *argv[])
{
	/* --- 変数宣言 --- */
	Mat im, im_sobel, im_laplacian, im_canny, im_tmp;
	int mode;
	char input_file[INPUT_FILE_LEN];

	/* --- 引数登録 --- */
	ArgParseAdd("--mode", "int", "画像入力モード(0: 静止画ファイル, 1: カメラ入力)");
	ArgParseAdd("--input_file", "str", "静止画ファイル(mode==0のときのみ)");
	ArgParseProc(argc, argv);

	/* --- 引数読み込み --- */
	ArgParseGetValue("--mode", &mode);

	if (mode == 0) {
		/* --- 画像をグレースケールで取得 --- */
		ArgParseGetValue("--input_file", input_file);
		im = imread(input_file, 0);

		/* 画像が無いときのエラー処理 */
		if (!im.data) {
			return -1;
		}

 		/* --- Sobelフィルタでエッジ検出 --- */
		Sobel(im, im_tmp, CV_32F, 1, 1);
		convertScaleAbs(im_tmp, im_sobel, 1, 0);

		/* --- Laplacianフィルタでエッジ検出 --- */
		Laplacian(im, im_tmp, CV_32F, 3);
		convertScaleAbs(im_tmp, im_laplacian, 1, 0);   

		/* --- Cannyアルゴリズムでエッジ検出 --- */
		Canny(im, im_canny, 50, 200);

		/* --- 画像を表示 --- */
		imshow("Grayscale", im);
		imshow("Sobel", im_sobel);
		imshow("Laplacian", im_laplacian);
		imshow("Canny", im_canny);

 		/* --- 画像を保存 --- */
		imwrite("gray.jpg", im);
		imwrite("sobel.jpg", im_sobel);
		imwrite("laplacian.jpg", im_laplacian);
		imwrite("canny.jpg", im_canny);

		/* --- 任意のキーが押されるまで待機 --- */
		waitKey(0);
	} else {
		/* --- カメラのキャプチャ --- */
		VideoCapture cap(0);

		/* --- キャプチャできないときのエラー処理 --- */
		std::cout << "Press key to exit" << std::endl;
		while (1) {
			/* --- カメラ映像取得 --- */
			cap >> im;

 			/* --- Sobelフィルタでエッジ検出 --- */
			Sobel(im, im_tmp, CV_32F, 1, 1);
			convertScaleAbs(im_tmp, im_sobel, 1, 0);

			/* --- Laplacianフィルタでエッジ検出 --- */
			Laplacian(im, im_tmp, CV_32F, 3);
			convertScaleAbs(im_tmp, im_laplacian, 1, 0);   

			/* --- Cannyアルゴリズムでエッジ検出 --- */
			Canny(im, im_canny, 50, 200);

			/* --- 表示 --- */
			imshow("Camera", im);
			imshow("Sobel", im_sobel);
			imshow("Laplacian", im_laplacian);
			imshow("Canny", im_canny);

			/* --- キー入力があれば終了 --- */
			if (waitKey(33) >= 0) {
				break;
			}
		}
	}

	/* --- 終了 --- */
	return 0;
}
