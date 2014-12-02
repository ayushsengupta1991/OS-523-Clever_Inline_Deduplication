/* 
	By Ayush Sengupta.
*/
#include <stdio.h>
#include <stdint.h>
uint8_t characterConversion(char a)
{
			if(a == 'A'){
				return 0;
			}
			else if(a == 'C'){
				return 1;
			}
			else if(a == 'G'){
				return 2;
			}
			else if(a == 'T'){
				return 3;
			}
			return 5;
}

char reverseConvert(uint8_t i)
{
	if(i==0)
		return 'A';
	else if(i==1)
		return 'C';
	else if(i==2)
		return 'G';
	else if(i==3) return 'T';
	else return 'I';
}

uint64_t compression(FILE * read, FILE *write)
{

	char ch;
	uint8_t val = 0;
	int count = 0;
	uint64_t n=0;
	while((ch=fgetc(read))!=EOF)
	{
			if(ch == 'A' || ch == 'C' || ch == 'G' || ch == 'T')
			{
				val = val*4 + characterConversion(ch);
				count++;
				if(count>0 && count%4==0)
				{
					fputc((char)val,write);
					n++;
					val=0;
				}
				//printf("%c",ch);
			}
			
	}
	printf("%lld\n",n);
	return n;
}

void decompression(FILE * read, FILE *write,uint64_t length)
{ 
	char ch;
	uint8_t val=0;
	uint8_t c;
	uint64_t n=0;
	while(n<length)
	{
		ch=fgetc(read);
		n++;
		//printf("%c",ch);
		c=(uint8_t)ch;
		uint8_t r;
		char *x=malloc(4*sizeof(char));
		int it=3,j;
		for(j=0;j<4;j++)
		{
			r=c%4;
			x[it]=reverseConvert(r);
			it--;
			c=c/4;
		}
		for(j=0;j<4;j++)
			fputc(x[j],write);
		
	}
	if(ch==EOF)
		printf("END OF FILE REACHED\n");
	printf("%lld\n",n); 
}

int main()
{

	FILE *fp1, *fp2, *fp3;
	fp1 = fopen("ecoli_test.txt", "r+");
	fp2 = fopen("compression", "w+");
	
	//printf("Starting Compression \n");
	uint64_t n;
	n=compression(fp1, fp2);
	fclose(fp1);
	fclose(fp2);
	
	fp2=fopen("compression", "r+");
	fp3=fopen("decompression.txt","w+");
	decompression(fp2,fp3,n);
	fclose(fp2);
	fclose(fp3);
}


