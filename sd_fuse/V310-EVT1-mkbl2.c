/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * mkbl2    led.bin  bl2.bin   14336
 * argv[0]  argv[1]  argv[2]  argv[3]
 */

int main (int argc, char *argv[])
{
	FILE *fp;
	unsigned char src;
	char *Buf, *a;
	int	 BufLen;
	int	 nbytes, fileLen;
	unsigned int checksum = 0;
	int	 i;

	if (argc != 4) {
		printf("Usage: mkbl2 <source file> <destination file> <size> \n");
		return -1;
	}

	BufLen = atoi(argv[3]);         //14336 = BufLen
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);

	fp = fopen(argv[1], "rb");      //argv[1] = led.bin
	if( fp == NULL) {
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	fileLen = ftell(fp);            //fileLen = 实际文件大小
	fseek(fp, 0L, SEEK_SET);

/*
	if ( BufLen > fileLen ) {
		printf("Usage: unsupported size\n");
		free(Buf);
		fclose(fp);
		return -1;
	}
*/

	nbytes = fread(Buf, 1, BufLen, fp);

/*
	if ( nbytes != BufLen )	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}
*/

	if ( nbytes < BufLen ) {
		int i = 0;

		printf("The source file is too small !\n");

		for(i = nbytes; i < BufLen; i++)
			Buf[i] = 0;
	}


	fclose(fp);

	for(i = 0; i < (14 * 1024) - 4; i++) {
		checksum += (unsigned char)(Buf[i]);
	}

	*(unsigned int *)(Buf + i) = checksum;

	fp = fopen(argv[2], "wb");
	if (fp == NULL) {
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a = Buf;
	nbytes = fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);
	fclose(fp);

	return 0;
}

