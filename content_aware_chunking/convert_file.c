/*
	By Ayush Sengupta.
*/
#include<stdio.h>
int main()
{
	char ch;
	FILE *read=fopen("ecoli_parsed.txt","r+");
	FILE *write=fopen("ecoli_without_whitespace.txt","w+");
	while((ch=fgetc(read))!=EOF)
	{
		if(ch=='A' || ch=='C' || ch=='G' || ch=='T')
			fputc(ch,write);
	}	
	fclose(read);
	fclose(write);
}