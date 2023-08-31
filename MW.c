#include "md5.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

FILE* fp;
int new_money, new_bounty, i;
int p_money = 16441, p_bounty = 58109, p_name = 23089; // Positions of specific variable in file

int get_file();
void get_modified();
void update_data();
void updata_hash();
int listdir(const char *PATH);


int main()
{
	// system("color 0a");
	// printf(" +------------------+\n");
	// printf(" | CREATED BY SHAIL |\n");
	// printf(" +------------------+\n");


	char Uname[30];
	if (get_file(Uname)) {
		exit(0);
		if(fp)
		{
			fseek(fp, p_name, SEEK_SET);
			fgets(Uname, sizeof(Uname)-1, fp);
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
	return 1;
}


int get_file(char *Uname)
{
	char mw_path[100];
	char path[100];
	char new_path[100] = "";

	FILE *cmd = popen("echo %userprofile%\\Documents\\NFS Most Wanted\\", "r");
	fgets(mw_path, sizeof(mw_path)-1, cmd);
	mw_path[strlen(mw_path)-1] = '\0';
	if (listdir(mw_path)) {
		// fp = fopen(new_path, "rb+"); // Opening file in (read + write) mode
		return 1;
	}
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


int listdir(const char *PATH)
{
	short dir_num = 0;
	struct dirent *entry;
	DIR *dp;

	dp = opendir(PATH);
	if (dp)
	{
		while(entry = readdir(dp)) {
			if (dir_num++ > 1)
				puts(entry->d_name);
		}
		closedir(dp);
		return 1;
	}
	return 0;
}
