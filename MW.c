#include "md5.h"
#include <stdio.h>
#include <stdlib.h>

FILE* fp;
int new_money, new_bounty, i;
int p_money = 16441, p_bounty = 58109, p_name = 23089;


void get_modified();
void update_data();
void updata_hash();


int main()
{
	system("color 0a");
	printf(" +------------------+\n");
	printf(" | CREATED BY SHAIL |\n");
	printf(" +------------------+\n");


	char Uname[9] = "";
	char *path = calloc(100, sizeof(char));
	char new_path[100] = "";

	printf(" Enter path of file of your Most Wanted saved game: ");
	gets(path);

	int x;
	for(i=0;i<strlen(path);i++)
	{
		if(path[i] != '\"')
		{
			new_path[x] = path[i];
			x++;
		}
	}
	free(path);
	fp = fopen(new_path, "rb+"); // Opening file in (read + write) mode
	if(fp)
	{
		fseek(fp, p_name, SEEK_SET);
		fgets(Uname, 8, fp);
		printf("\n Name                       : %s\n", Uname);
		
		fseek(fp, p_money, SEEK_SET); // Seeking where money is stored
		printf(" Current Money              : %d\n", getw(fp));
	
		fseek(fp, p_bounty, SEEK_SET); // Seeking where bounty is stored
		printf(" Current Bounty (1st CAR)   : %d\n\n", getw(fp));
	
		get_modified();
		update_data();
		updata_hash();
	
		fclose(fp);
	}
	else {
		system("color 0c");
		perror("\n ERROR");
	}
	printf("\n DONE .... ");
	getchar();
	getchar();
	return 0;
}


void get_modified()
{
	printf(" ENTER Modified Money  : ");
	scanf("%d", &new_money);
	printf(" ENTER Modified Bounty : ");
	scanf("%d", &new_bounty);
	
	if(new_money < 0)
		new_money = 0;
	if(new_bounty < 0)
		new_bounty = 0;
	
	printf("\n\n Your Money  = %d\n Your Bounty = %d\n\n", new_money, new_bounty);
}


void update_data()
{
	fseek(fp, p_money, SEEK_SET);
	putw(new_money, fp);

	fseek(fp, p_bounty, SEEK_SET);
	putw(new_bounty, fp);
}

#define buff_size 63528
void updata_hash()
{
	int p_hash = 63580;
	char buff[buff_size] = "", ch;
	fseek(fp, 52, SEEK_SET);
	for(i=0;i<buff_size;i++)
	{
		ch = fgetc(fp);
		buff[i] = ch;
	}
	int j,k;
	unsigned *d = md5(buff, i);
	WBunion u;
	fseek(fp, p_hash, SEEK_SET);
	for (j=0;j<4; j++){
		u.w = d[j];
		for (k=0;k<4;k++) {
//			printf("%02x",u.b[k]);
			fputc(u.b[k], fp);
		}
	}
}
