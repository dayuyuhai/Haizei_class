/*************************************************************************
	> File Name: 1.ls.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2020 03:37:03 PM CST
 ************************************************************************/

#include"head.h"
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<math.h>
#include<grp.h>
#include<sys/ioctl.h>
#include<ctype.h>
#include<termios.h>

#define MAXNAME 512
#define MAXFILE 1024

void do_ls(char *);
void show_info(char *, struct stat *);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void file_print(char *, struct stat *);
void mode_to_str(mode_t mode, char *modestr);
void update_color(mode_t mode);
int cmp_name(const void* p1, const void* p2);

int bg_c, fg_c;
int l_flag = 0, a_flag = 0, p_flag = 0;

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

    DBG("<Debug> : optind = %d\n", optind);
    DBG("<Debug> : argv[optind] = %s\n", argv[optind]);
    DBG("<Debug> : argv[optind - 1] = %s\n", argv[optind - 1]);
    DBG("<Debug> : argc[0] = %s\n", argv[0]);

    argc -= optind;
    argv += optind;

    if (argc == 0) {
        DBG("<Debug> : Doing with = .\n");
        do_ls(".");
    } else {
        while (argc--) {
		    do_ls(*argv++);
            DBG("<Debug> : Done with = %s\n", *(argv - 1));
	    }
    }
	return 0;
}

void size_window(char names[][MAXNAME], int cnt, int *row, int *col) {
    struct winsize size;
    int len[cnt], max = 0, total_len = 0;
    memset(len, 0, cnt * sizeof(int));
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0) {
        perror("ioctl()");
        exit(1);
    }
    DBG("Debug : win.row = %d, win.col = %d\n", size.ws_row, size.ws_col);
    for (int i = 0; i < cnt; i++) {
        len[i] = strlen(names[i]);
        if (max < len[i]) max = len[i];
        total_len += len[i] + 2;
    }
    if (max + 1 >= size.ws_col) {
        *row = cnt;
        *col = 1;
        return ;
    }
    if (total_len <= size.ws_col) {
        *row = 1;
        *col = cnt;
        return ;
    }

    int try_begin = 0;
    for (int i = 0, tmp = 0; i < cnt; i++) {
        tmp += len[i] + 1;
        if (tmp >= size.ws_col) {
            try_begin = i;
            break;
        }
    }
    
    for (int i = try_begin; ;i--) {
        int *wide = (int *)malloc(i * sizeof(int));
        memset(wide, 0, sizeof(int) * i);
        *row = ceil(cnt / i);
        int sum = 0;
        for (int x = 0; x < i; x++) {
            for (int y = x * *row; y < (x + 1) * *row && y < cnt; y++) {
                if (wide[x] < len[y]) wide[x] = len[y];
            }
            sum += (wide[x] + 1);
        }
        if (sum > size.ws_col) continue;
        if (sum <= size.ws_col) {
            *col = i;
            break;
        }
    }
}

void show_files(char names[][MAXNAME], int cnt, int row, int col) {
    int wide[col];
    memset(wide, 0, sizeof(int) * col);
    struct stat tmp_st;
    for (int i = 0; i < col; i++) {
        for (int j = (i * row); j < (i + 1) * row && j < cnt; j++) {
            if (wide[i] < strlen(names[j])) wide[i] = strlen(names[j]);
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = i; j < i + (row * col) && j < cnt; j += row) {
            lstat(names[j], &tmp_st);
            update_color(tmp_st.st_mode);
            int wide_tmp = wide[j / row] + 2;
            printf("\033[%d;%dm%-*s\033[0m", 
                   bg_c, fg_c, wide_tmp, names[j]);
        }
        printf("\n");
    }
}

void do_ls(char *dir) {
	DIR *dirp = NULL;
	struct dirent *direntp;
	if ((dirp = opendir(dir)) == NULL) {
        // 如果是一个文件
        if (access(dir, R_OK) == 0) {
            if (l_flag == 1) {
                struct stat tmp_st;
                lstat(dir, &tmp_st);
                show_info(dir, &tmp_st);
            } else {
                printf("%s\n", dir);
            }
        return ;
        } else {
            perror(dir);
            exit(1);
        }
	}
    printf("%s:\n", dir);
    char names[MAXFILE][MAXNAME] = {0};
    int cnt = 0;
    while ((direntp = readdir(dirp)) != NULL) {
        if ((a_flag == 0) && (direntp->d_name[0] == '.')) continue;
        strcpy(names[cnt++], direntp->d_name);
    }
    qsort(names, cnt, MAXNAME, cmp_name);
    chdir(dir);
    if (l_flag == 1) {
        for (int i = 0; i < cnt; i++) {
            struct stat st_tmp;
            lstat(names[i], &st_tmp);
            show_info(names[i], &st_tmp);
            printf("\n");
        }
    } else {
        int row, col;
        size_window(names, cnt, &row, &col);
        printf("row =  %d, col =  %d\n", row, col);
        show_files(names, cnt, row, col);
    }
    return ;
}

int cmp_name(const void* _a, const void* _b) {
    char *a = (char *)_a;
    char *b = (char *)_b;
    for (int i = 0; i < strlen(a); i++) {
        a[i] = tolower(a[i]);
    }
    for (int i = 0; i < strlen(b); i++) {
        b[i] = tolower(b[i]);
    }
    return strcmp(a, b);
}

void update_color(mode_t mode) {
    bg_c = 0;
    fg_c = 37;
    // if (mode & (S_IXGRP | S_IXUSR | S_IXOTH)) fg_c = 32;
    if (mode & 0111) fg_c = 32;
    switch (mode & S_IFMT) {
        case S_IFDIR:  fg_c = 34;     break;
        case S_IFLNK:  fg_c = 35;     break;
    }

}

void mode_to_str(mode_t mode, char *modestr) {
	strcpy(modestr, "----------");
	switch (mode & S_IFMT) {
           case S_IFBLK:  modestr[0] = 'b';     break;
           case S_IFCHR:  modestr[0] = 'c';     break;
           case S_IFDIR:  modestr[0] = 'd';     break;
           case S_IFIFO:  modestr[0] = 'p';     break;
           case S_IFLNK:  modestr[0] = 'l';     break;
           case S_IFSOCK: modestr[0] = 's';     break;
    }
	if (S_IRUSR & mode) modestr[1] = 'r';
	if (S_IWUSR & mode) modestr[2] = 'w';
	if (S_IXUSR & mode) modestr[3] = 'x';
	if (S_IRGRP & mode) modestr[4] = 'r';
	if (S_IWGRP & mode) modestr[5] = 'w';
	if (S_IXGRP & mode) modestr[6] = 'x';
	if (S_IROTH & mode) modestr[7] = 'r';
	if (S_IWOTH & mode) modestr[8] = 'w';
	if (S_IXOTH & mode) modestr[9] = 'x';
    return ;
}

void show_info(char *filename, struct stat *st) {
	char modestr[15] = {0};
    mode_to_str(st->st_mode, modestr);
    printf("%s ", modestr);
    printf("%4ld ", st->st_nlink);
    printf("%4s ", uid_to_name(st->st_uid));
    printf("%4s ", gid_to_name(st->st_gid));
    printf("%4ld ", st->st_size);
	printf("%.12s ", 4 + ctime(&st->st_mtime));
    update_color(st->st_mode);
    printf("\033[%d;%dm%s\033[0m", bg_c, fg_c, filename);
}

char *uid_to_name(uid_t uid) {
    struct passwd *pw_ptr;
    static char tmpstr[10];
    // 用户（人）走了程序可能还留着有用
    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(tmpstr, "%d", uid);
        return tmpstr;
    } else {
        return pw_ptr->pw_name;
    }
}

char *gid_to_name(gid_t gid) {
    struct group *gr_ptr;
    static char tmpstr[10];
    if ((gr_ptr = getgrgid(gid)) == NULL) {
        sprintf(tmpstr, "%d", gid);
        return tmpstr;
    } else {
        return gr_ptr->gr_name;
    }

}
