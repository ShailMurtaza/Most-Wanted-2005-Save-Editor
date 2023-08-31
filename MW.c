#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "md5.h"
#include "my_strcat.h"


FILE* fp;
int new_money, new_bounty, i;
int p_money = 16441, p_bounty = 58109, p_name = 23089; // Positions of specific variable in file

char *get_file();
void get_modified();
void update_data();
void updata_hash();
char **listdir(const char *PATH, size_t *dirs_len);
void error(char *msg);


int main()
{
	// system("color 0a");
	// printf(" +------------------+\n");
	// printf(" | CREATED BY SHAIL |\n");
	// printf(" +------------------+\n");


	char *Uname = get_file();
	if (Uname) {
		error("JUST TERMINATE PROGRAM");
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
			error("\n ERROR");
		}
		printf("\n DONE .... ");
		getchar();
		getchar();
		return 0;
	}
	return 1;
}


char *get_file()
{
	char temp[50];
	char *temp_p = NULL;
	char *mw_path = (char *) calloc(1, 1); // Empty string
	char **dirs = NULL;
	size_t dirs_len;
	char *Uname;

	FILE *cmd = popen("echo %userprofile%\\Documents\\NFS Most Wanted\\", "r");
	if (cmd) {
		while(fgets(temp, sizeof(temp), cmd)) {
			temp_p = mw_path;
			mw_path = my_strcat(mw_path, temp);
			free(temp_p);
			if (!mw_path) {
				error("\n Mmw_path allocation failed");
			}
		}
		pclose(cmd);
		mw_path[strlen(mw_path)-1] = '\0'; // Remove \n from echo output. World is going to destroy because now mw_path has 1 extra unused byte allocated
		dirs = listdir(mw_path, &dirs_len);
		if (dirs) {
			// fp = fopen(new_path, "rb+"); // Opening file in (read + write) mode
		}
	}
	return Uname;
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


char **listdir(const char *PATH, size_t *dirs_len)
{
	(*dirs_len) = 0;
	char **dirs = NULL;
	char *dir = NULL; // Empty string

	short dir_num = 0;
	struct dirent *entry;
	DIR *dp;

	dp = opendir(PATH);
	if (dp)
	{
		while(entry = readdir(dp)) {
			if (dir_num++ > 1) { // Skip "." and ".." Directory
				dir = my_strcat("", entry->d_name);
				if (dir) {
					if (dirs) {
						dirs = (char **) realloc(dirs, ++(*dirs_len));
					}
					else {
						dirs = (char **) malloc(++(*dirs_len) * sizeof(char*));
					}
					dirs[(*dirs_len)-1] = dir;
				}
			}
		}
		closedir(dp);
	}
	return dirs;
}


void error(char *msg)
{
	perror(msg);
	exit(-1);
}
