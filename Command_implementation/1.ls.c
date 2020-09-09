/*************************************************************************
	> File Name: 1.ls.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2020 03:37:03 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<sys/ioctl.h>
#include<termios.h>


#define COLOR(a, b) "\033[1;" #b "m" a "\033[0m"

#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)
#define YELLOW(a) COLOR(a, 33)
#define BLUE(a) COLOR(a, 34)
#define PURPLE(a) COLOR(a, 35)

typedef struct Link {
    char *str;
    struct Link *next;
} Link;

void do_ls(char *);
int l_flag = 0, a_flag = 0, p_flag = 0;
void show_info(char *, struct stat *);
void file_print(char *, struct stat *);
int strIcmp(const char*, const char*);
void link_filename(char *, Link *);

int main(int argc, char *argv[]) {
	int opt;
	while ((opt = getopt(argc, argv, "la")) != -1) {
		switch (opt) {
			case 'l':
				l_flag = 1;
				break;
			case 'a':
				a_flag = 1;
				break;
			default:
				fprintf(stderr, "Usage : %s [-la]\n", argv[0]);
				exit(1);   //出错返回大于0的值
		}
	}

	for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') continue;
		p_flag = 1;
		do_ls(argv[i]);
	}
	if (p_flag == 0) do_ls(".");
	return 0;
}

void do_ls(char *dir) {
	DIR *dirp = NULL;
    int cnt = 0;
    Link head;
    head.str = NULL, head.next = NULL;
	struct dirent *direntp;
	if ((dirp = opendir(dir)) == NULL) {
		perror("lstat1");
		exit(1);
	}
	printf(PURPLE("%s:") "\n", dir);
	char realpath[100] = {0};
	strcpy(realpath, dir);
	while ((direntp = readdir(dirp)) != NULL) {
		if ((a_flag == 0) && (direntp->d_name[0] == '.')) continue;
        link_filename(direntp->d_name, &head);
    }
    Link *p = head.next;
    while (p) {
    	struct stat st;
	    strcpy(realpath, dir);
		strcat(realpath, "/");
    	strcat(realpath, p->str);
	    if (lstat(realpath, &st) < 0) {
	        perror("lstat2");
		    exit(1);
        }
        if (l_flag == 1)   show_info(p->str, &st);
        else {
            struct winsize size;  
            if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0) {
                perror("ioctl TIOCGWINSZ error");
                exit(1);
            } 
            if ((cnt += (strlen(p->str) + 4)) > (size.ws_col - 30)) {
                printf("\n");
                cnt = 0;
            }
            file_print(p->str, &st);
        }
        p = p->next;
    }
	printf("\n");
    return ;
}

void link_filename(char *filename, Link *head) {
    Link *p = head;
    while (p->next && strIcmp(p->next->str, filename) < 0) {
        p = p->next;
    }
    Link *q = (Link *)malloc(sizeof(Link));
	q->str = strdup(filename);
	q->next = p->next;
    p->next = q;
    return ;
}

int strIcmp(const char* p1, const char* p2) {
    while (*p1) {
        char c1 = *p1;
        char c2 = *p2;
        if (c1 >= 'A' && c1 <= 'Z')
            c1 += 'a' - 'A';
        if (c2 >= 'A' && c2 <= 'Z')
            c2 += 'a' - 'A';
        if (c1 != c2)
            return c1 - c2;
        p1++, p2++;
    }
    return *p1 - *p2;
}

void file_print(char *filename, struct stat *st) {
	if (S_ISDIR(st->st_mode)) printf(BLUE("%s\t"), filename);
	else if (S_ISLNK(st->st_mode)) printf(RED("%s\t"), filename);
	else if (access(filename, X_OK) != -1) printf(GREEN("%s\t"), filename);
	else printf("%s\t", filename);
    return ;
}



void show_info(char *filename, struct stat *st) {
	char modestr[15] = {0};
	strcpy(modestr, "----------");
	struct passwd *pw = getpwuid(st->st_uid);
	struct group *gr = getgrgid(st->st_gid);
	char *time  = ctime(&st->st_mtime);
	char short_time[15] = {0};
	strncpy(short_time, time + 4, 12);
	switch (st->st_mode & S_IFMT) {
           case S_IFBLK:  modestr[0] = 'b';     break;
           case S_IFCHR:  modestr[0] = 'c';     break;
           case S_IFDIR:  modestr[0] = 'd';     break;
           case S_IFIFO:  modestr[0] = 'p';     break;
           case S_IFLNK:  modestr[0] = 'l';     break;
           case S_IFSOCK: modestr[0] = 's';     break;
    }
	if (S_IRUSR & st->st_mode) modestr[1] = 'r';
	if (S_IWUSR & st->st_mode) modestr[2] = 'w';
	if (S_IXUSR & st->st_mode) modestr[3] = 'x';
	if (S_IRGRP & st->st_mode) modestr[4] = 'r';
	if (S_IWGRP & st->st_mode) modestr[5] = 'w';
	if (S_IXGRP & st->st_mode) modestr[6] = 'x';
	if (S_IROTH & st->st_mode) modestr[7] = 'r';
	if (S_IWOTH & st->st_mode) modestr[8] = 'w';
	if (S_IXOTH & st->st_mode) modestr[9] = 'x';
	printf("%s %4ld %4s %6s %6ld %12s ", 
			modestr, st->st_nlink, pw->pw_name, gr->gr_name, st->st_size, short_time);
	file_print(filename, st);
    printf("\n");
    return ;
}

