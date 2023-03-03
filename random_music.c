#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLING_RATE 44100     // サンプリング周波数
#define DURATION_SEC 10         // 音楽の長さ（秒）
#define FREQUENCY 440           // 基本周波数
#define AMPLITUDE 30000         // 振幅
#define MAX_VARIATION 1000      // 変化量の最大値

int main() {
	int num_samples = SAMPLING_RATE * DURATION_SEC;  // サンプル数
	short data[num_samples];                        // サンプルデータ
	srand(time(NULL));                              // 乱数初期化

	// 矩形波のサンプルデータを生成
	for (int i = 0; i < num_samples; i++) {
		if (rand() % 2 == 0) {
			data[i] = AMPLITUDE;
		} else {
			data[i] = -AMPLITUDE;
		}

		// サンプルデータをランダムに変化させる
		int variation = rand() % (2 * MAX_VARIATION) - MAX_VARIATION;
		data[i] += variation;
	}

	// WAVファイル形式で保存
	FILE *fp;
	fp = fopen("random_music.wav", "wb");
	if (fp == NULL) {
		printf("Failed to open file.\n");
		return 1;
	}

	// WAVファイルヘッダを作成
	char riff[] = "RIFF";
	int file_size = num_samples * 2 + 36;
	char wave[] = "WAVE";
	char fmt[] = "fmt ";
	int fmt_size = 16;
	short format_id = 1;
	short channel = 1;
	int byte_per_sec = SAMPLING_RATE * 2;
	short block_size = 2;
	short bit_per_sample = 16;
	char data_header[] = "data";
	int data_size = num_samples * 2;

	fwrite(riff, 1, 4, fp);
	fwrite(&file_size, 4, 1, fp);
	fwrite(wave, 1, 4, fp);
	fwrite(fmt, 1, 4, fp);
	fwrite(&fmt_size, 4, 1, fp);
	fwrite(&format_id, 2, 1, fp);
	fwrite(&channel, 2, 1, fp);
	fwrite(&SAMPLING_RATE, 4, 1, fp);
	fwrite(&byte_per_sec, 4, 1, fp);
	fwrite(&block_size, 2, 1, fp);
	fwrite(&bit_per_sample, 2, 1, fp);
	fwrite(data_header, 1, 4, fp);
	fwrite(&data_size, 4, 1, fp);

	// サンプルデータを保存
	fwrite(data, sizeof(short), num_samples, fp);

	fclose(fp);
	printf("Finished.\n");

	return 0;
}
