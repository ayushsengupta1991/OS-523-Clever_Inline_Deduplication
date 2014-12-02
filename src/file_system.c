/*
 * file_system.c
 *
 *  Created on: Nov 27, 2014
 *      Author: manoj
 */
#include <stdio.h>
#include <file_sys.h>
#define STORE

int main()
{

int n;
char* name = "manoj1.fasta";
char buf[512];
fs_init();
FILE *readfile;

#ifdef STORE

    //If any new test case
	//fs_sync();
	struct File* new_file = (struct File*)malloc(sizeof(struct File));
	strcpy(new_file->key,name);

	readfile = fopen(name, "r");
	int block_no=0;
	while((n = fread(&buf, sizeof(char), BLKSIZE ,readfile)) > 0)
	{
		//printf("\n iter %d n %d",block_no, n, sizeof(char));
		/*printf("\n Read out", buf[i]);
		for(i = 0; i < n; i++)
			printf("%c ", buf[i]);
		printf("\n");*/
		file_data_write(new_file, buf, n, block_no);
		block_no++;
	}

	float dedup_ratio;
	dedup_ratio = deduplication_ratio();

	file_meta_data_write(new_file);

	printf("\n system_dedup_ratio %f", dedup_ratio);
	printf("\n finished");

#else

	char *dump = "dump_manoj.fasta";
	struct File* file = (struct File*)malloc(sizeof(struct File));
	file_stat(name, file);

	FILE *dp = fopen(dump, "w");

	int b_no = 0;

	while((n = file_data_read(file, buf, b_no)) > 0)
	{
	  fwrite(buf, sizeof(char), n, dp);
	  b_no++;
	}
	//printf("\n file size %d", file->f_size);

	fclose(dp);
	printf(" \n Data wrote on dump.fasta \n finished");
#endif

return 0;

}






