#include<stdio.h>
int main()
{
	char ch;
	FILE *fp=fopen("decompression.txt","r+");
	int count=0;
	while((ch=fgetc(fp))!=EOF)
	{
		printf("%c",ch);
		count++;
		if(count%75==0)
			printf("\n");
	}
	return 0;
}
