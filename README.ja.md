「お前は今まで食ったパンの枚数を覚えているのか？」 by ディオ

livcvcmd
================================================================================

OpenCVでコマンドラインツールを書く際に引数の処理、画像の読み込みや保存ファイル名の共通書式を引き受け画像の処理のコードに集中できるようにするシンプルなフレームワークです。

OpenCVで実験プログラムを書くたびに cv::imread() を書いて、コマンドライン引数の処理を書いて、書いたはいいけど時間がないからパスの処理はいい加減で、人に渡せるようなレベルにならないという事態を解消するために作りました。

必要環境
================================================================================

- OpenCV 2.4.*
- boost 1.48.1 以降（boost::program_options、boost::filesystemが必要）
- CMake 2.6 以降

インストール
================================================================================

```bash
# git clone ...
cd libcvcmd/build
cmake ..
make
sudo make install
```

基本的な使い方
================================================================================

```cpp
#include <cvcmd/application.hpp>

// cvcmd::application がコマンドライン引数の処理などを実装している
class application : public cvcmd::application
{
public:
	application()
	{
		// 作成するコマンドがウィンドウ表示を行うことを設定する。
		display_image(true);
	}

	virtual std::string description()
	{
		// コマンドの概要や使い方を返す。
		// --help で実行した際に表示される。
		return
			"this is libcvcmd sample program. display images and quit."
			;
	}

	virtual int on_image(const cv::Mat& image)
	{
		// コマンドライン引数に複数の画像ファイルが渡された場合、
		// 画像一枚ごとにこの仮想関数が呼び出される。

		// 画像表示の指定
		add_display_image("image", image);


		// 画像の保存の指定
		add_output_image("origin", image);

		// C++ のmain関数の戻り値の仕様に従ってintを返す。
		return 0;
	}
};

int main(int argc, char* argv[])
{
	return application().exec(argc, argv);
}

```

実行方法
================================================================================

```bash
my_cmd test1.png test2.png
ls
# test1.png.origin.png test2.png.origin.png
```

ウィンドウ上での操作
================================================================================

- SPACEキー 画像ファイルが複数指定されていた場合、次の画像の処理に移る
- qキー 以降の画像の処理をキャンセルし、コマンドを終了する。

フレームワークが提供するコマンドラインオプション
================================================================================

- -h [ --help ]              ヘルプの表示
- --without-display          ウィンドウ表示をすべて抑制する。テキスト出力と画像保存のみ行いたい時に指定する。
- --without-output           画像の保存をすべて抑制する。ウィンドウでの確認のみしたい場合に指定する。
- --only-output arg          ウィンドウの名前を指定する（add_display_image() で指定した文字列）。ここで指定したウィンドウのみを表示する。
- --only-display arg         出力画像の名前を指定する（add_output_image() で指定した文字列）。ここで指定した画像のみを保存する。
- --input-file arg           入力画像の指定。オプション指定のない形式も可能。
- --output-format arg (=png) 出力画像のフォーマットの指定。拡張子で指定する。実行環境のOpenCVが対応しているフォーマットが指定可能。



