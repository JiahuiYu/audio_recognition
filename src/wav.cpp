/**-------------------------/// wav format analyse \\\---------------------------
 *
 * <b>wav format analyse</b>
 * @version : 
 * @since : 2015  2月 07
 *
 * @description :
 *     
 * @usage :
 *
 * @author : 'Jiahui Yu' | yjh199511  gmail.com
 * @copyright 
 * @TODO :
 *
 *--------------------------\\\ wav format analyse ///---------------------------*/

#include "wav.h"

TWav::TWav(const char *filename){
	fp = fopen(filename, "rb");
	assert(fp != NULL);
	fread(wav_info.riff_id, 1, 4, fp);
	wav_info.riff_id[4] = '\0';
	fread(&wav_info.size0, 4, 1, fp);
	fread(wav_info.wave_fmt, 1, 8, fp);
	wav_info.wave_fmt[8] = '\0';
	fread(&wav_info.size1, 4, 1, fp);
	fread(&wav_info.fmttag, 2, 1, fp);
	fread(&wav_info.channel, 2, 1, fp);
	fread(&wav_info.sample_per_sec, 4, 1, fp);
	fread(&wav_info.byte_per_sec, 4, 1, fp);
	fread(&wav_info.block_align, 2, 1, fp);
	fread(&wav_info.bit_per_sample, 2, 1, fp);
	if (wav_info.size1 == 0x10){
		fread(wav_info.data_id, 1, 4, fp);
		wav_info.data_id[4] = '\0';
		fread(&wav_info.size2, 4, 1, fp);
	}
	else{
		fseek(fp, 6, SEEK_CUR);
		uint32_t offset;
		fread(&offset, 4, 1, fp);
		fseek(fp, offset, SEEK_CUR);
		fread(wav_info.data_id, 1, 4, fp);
		wav_info.data_id[4] = '\0';
		fread(&wav_info.size2, 4, 1, fp);
	}
	data_offset = wav_info.size0 + 8 - wav_info.size2;

#ifdef WAV_TEST
	printf("=====test file header=====\n");
	printf("riff_id        %-8s 文件头标志\"RIFF\"\n", wav_info.riff_id);
	printf("size0          %-8d 文件总长-8\n", wav_info.size0);
	printf("wave_fmt       %-8s 文件头标志\"WAVEfmt \"\n", wav_info.wave_fmt);
	printf("size1          %-8s 样例文件/标准文件\n", (wav_info.size1 == 0x12) ? "样例文件" : "标准文件");
	printf("fmttag         %-8d \n", wav_info.fmttag);
	printf("channel        %-8d 声道数\n", wav_info.channel);
	printf("sample_per_sec %-8d 采样率\n", wav_info.sample_per_sec);
	printf("byte_per_sec   %-8d 每秒播放字节数\n", wav_info.byte_per_sec);
	printf("block_align    %-8d 采样一次占字节数\n", wav_info.block_align);
	printf("bit_per_sample %-8d 量化数\n", wav_info.bit_per_sample);
	printf("data_id        %-8s \"data\"标志\n", wav_info.data_id);
	printf("size2          %-8d 采样数据字节数\n", wav_info.size2);
	printf("=========================\n");
	printf("播放时长:      %d sec\n", wav_info.size2 / wav_info.byte_per_sec);
#endif
}

TWav::~TWav(){
	fclose(fp);
}

int16_t TWav::GetSample(){
	int16_t s1;
	fread(&s1, 2, 1, fp);
	//FIXME check file end
	return s1;
}

void TWav::StartFromOffset(int offset){
	fseek(fp, data_offset+offset, SEEK_SET);
}
