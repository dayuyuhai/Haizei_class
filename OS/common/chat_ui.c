/******************************************************mZ******************
	> File Name: chat_ui.c
	> Author: 
	> Mail: 
	> Created Time: Sun 23 Aug 2020 02:11:05 PM CST
 ************************************************************************/

#include "head.h"

extern WINDOW *msg_win, *sub_msg_win, *input_win, *sub_input_win, *help_win, *sub_help_win;
extern int msgnum;

WINDOW *create_newwin(int width, int height, int startx, int starty) {
    WINDOW *win;
    win = newwin(height, width, starty, startx);
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, char c) {
    move(y, x);
    addch(c);
    refresh();
}

void gotoxy_puts(int x, int y, char *s) {
    move(y, x);
    addstr(s);
    refresh();
}


void w_gotoxy_putc(WINDOW *win, int x, int y, char c) {
    mvwaddch(win, y, x, c);
    wrefresh(win);
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    wrefresh(win);
}

void show_help() {
    wattron(sub_help_win, COLOR_PAIR(2));
    w_gotoxy_puts(sub_help_win, 2, 3, "Help:");
    wattron(sub_help_win, COLOR_PAIR(7));
    w_gotoxy_puts(sub_help_win, 3, 3, "使用@user进行私聊");

}

void init_ui() {
    initscr();
    clear();
    if (!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持彩色！\n");
        exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_BLACK, COLOR_RED);
    init_pair(10, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(11, COLOR_BLACK, COLOR_BLUE);
    init_pair(12, COLOR_BLACK, COLOR_YELLOW);
    init_pair(13, COLOR_BLACK, COLOR_CYAN);
    
    msg_win = create_newwin(MSG_WIDTH, MSG_HEIGHT, 2, 1);
    sub_msg_win = subwin(msg_win, MSG_HEIGHT - 2, MSG_WIDTH - 2, 2, 3);
    help_win = create_newwin(HELP_WIDTH, MSG_HEIGHT, MSG_WIDTH + 2, 1);
    sub_help_win = subwin(help_win, MSG_HEIGHT - 2, HELP_WIDTH - 2, 2, MSG_WIDTH + 3);
    input_win = create_newwin(HELP_WIDTH + MSG_WIDTH, INPUT_HEIGHT, 2, MSG_WIDTH + 1);
    sub_input_win = subwin(input_win, INPUT_HEIGHT - 2, MSG_WIDTH + HELP_WIDTH - 2, MSG_HEIGHT + 2, 3);
    
    show_help();

    scrollok(sub_msg_win, 1);
    scrollok(sub_input_win, 1);

    

    box(msg_win, 0, 0);
    box(input_win, 0, 0);
    box(help_win, 0, 0);

    wrefresh(msg_win);
    wrefresh(help_win);
    wrefresh(input_win);

} 

void print_message(WINDOW *win, struct ChatMsg *msg, int type) {
    time_t time_now = time(NULL);
    struct tm *tm = localtime(&time_now);
    char timestr[20] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    if (msgnum >= MSG_HEIGHT - 2) {
        msgnum = MSG_HEIGHT - 3;
        scroll(win);
    }
    w_gotoxy_puts(win, 1, msgnum, timestr);
    if (type || msg->type & CHAT_SYS) {
        strcpy(msg->name, "Sys Info");
        wattron(win, COLOR_PAIR(7));
    } else {
        wattron(win, COLOR_PAIR(6));
    }

    w_gotoxy_puts(win, 10, msgnum, msg->name);
    w_gotoxy_puts(win, 10 + strlen(msg->name) + 1, msgnum, msg->msg);
    msgnum++;

}
