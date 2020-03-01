#include "SlamLauncher.h"

int main(int argc, char* argv[]) {
	bool scanCheck = false;   // スキャン表示のみか
	bool odometryOnly = false; // オドメトリによる地図構築か
	char* filename; // データファイル名
	int startN = 0; // 開始スキャン番号

	if (argc < 2) {
		printf("Error: too few arguments.\n");
		return(1);
	}

	// コマンド引数の処理
	int idx = 1;
	// コマンドオプションの解釈('-'のついた引数)
	if (argv[1][0] == '-') {
		for (int i = 1; ; i++) {
			char opinion = argv[1][i];
			if (opinion == NULL) break;
			else if (opinion == 's') scanCheck = true; // スキャン表示のみ
			else if (opinion == 'o') odometryOnly = true; // オドメトリによる地図構築
		}
		if (argc == 2) {
			printf("Error: no file name.\n");
			return(1);
		}
		idx++;
	}
	if (argc >= idx + 1) filename = argv[idx]; // '-'ある場合idx=2, ない場合idx=1
	if (argc == idx + 2) startN = atoi(argv[idx + 1]); // argcがidxより2大きければstartNがある
	else if (argc >= idx + 2) {
		printf("Error: invalid arguments.\n");
		return(1);
	}

	// ファイルを開く
	SlamLauncher sl;
	bool flag = sl.setFilename(filename);
	if (!flag) return(1);

	sl.setStartN(startN); // 開始スキャン番号の設定

	// 処理本体
	if (scanCheck) sl.showScans();
	else { // スキャン表示以外はSlamLauncher内で場合分け
		sl.setOdometryOnly(odometryOnly);
		sl.customizeFramework();
		sl.run();
	}

	return(0);
}