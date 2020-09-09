

```c
#include "game.h"
int main() {
    initscr();
    	
    	窗口初始化
            
    noecho();
    
    	输入不显示
            
    cbreak();
    
    	按一个交一个，无行缓冲
            
    keypad(stdscr, TRUE);
    
    	功能键允许
            
    initgame();
    signal(14, drawgame);
    
    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 1000;
    setitimer(ITIMER_REAL, &itimer, NULL);
    
    	文件上有时钟脉冲，每个进程都能感受到
        时间同步：ntp网络时钟协议 C/S架构 不/定期通讯
    
    /*
    struct itimerval {
        struct timeval it_interval; // Interval for periodic timer 
        struct timeval it_value;    // Time until next expiration 
    };
    
    it_interval  每隔十秒
    it_value     距离周期（10）还有多少秒

    struct timeval {
        time_t      tv_sec;         // seconds 
        suseconds_t tv_usec;        // microseconds 
    };
	*/
    

Opoint.x = cx;
Opoint.y = Y - 4;

attron(COLOR_PAIR(4));
gotoxy_putc(Opoint.x, Opoint.y, 'o');
attroff(COLOR_PAIR(4));

refresh();

while (1) {
    int c = getch();
    switch(c) {
        case KEY_LEFT:
            Bdir.x -= 2;
            break;
        case KEY_RIGHT:
            Bdir.x += 2;
            break;
        case KEY_UP:
            if (flag) break;
            flag = 1;
            Odir.x = dir_r[get_random(12)];
            Odir.y = -1;
            char blank[] = "                                    ";
            gotoxy_puts(3, Y + 4, blank);
            gotoxy_puts(3, Y + 5, blank);
            break;
        default:
            break;
    }
}
getch();
endwin();
return 0;

}
```

* 9. ```c
    #include <ncurses.h>
    WINDOW *create_newwin(int height, int width, int starty, int startx);
    void destroy_win(WINDOW *local_win);
    
    int main(int argc, char *argv[])
    {
    WINDOW *my_win;
    int startx, starty, width, height;
    int ch;
    initscr();
    /* 初始化并进入 curses 模式
    */
    cbreak();
    /* 行缓冲禁止,传递所有控制信息 */
    keypad(stdscr, TRUE);
    /* 程序需要使用 F1 功能键
    */
    height = 3;
    width = 10;
    starty = (LINES ­ height) / 2;
    /*计算窗口中心位置的行数 */
    startx = (COLS ­ width) / 2;
    /*计算窗口中心位置的列数 */
    printw("Press F1 to exit");
    refresh();
    my_win = create_newwin(height, width, starty, startx);
    27NCURSES Programming HOWTO 中文版(第二版)
    while((ch = getch()) != KEY_F(1))
    {
    switch(ch)
    {
    case KEY_LEFT:
    destroy_win(my_win);
    my_win = create_newwin(height, width, starty,­­startx);
    break;
    case KEY_RIGHT:
    destroy_win(my_win);
    my_win = create_newwin(height, width, starty,++startx);
    break;
    case KEY_UP:
    destroy_win(my_win);
    my_win = create_newwin(height, width, ­­starty,startx);
    break;
    case KEY_DOWN:
    destroy_win(my_win);
    my_win = create_newwin(height, width, ++starty,startx);
    break;
    }
    }
    endwin();
    /*结束 curses 模式
    */
    return 0;
    }
    WINDOW *create_newwin(int height, int width, int starty, int startx)
    {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    /* 0, 0 是字符默认的行列起始位置 */
    wrefresh(local_win);
    /*刷新窗口缓冲,显示 box
    */
    return local_win;
    }
    void destroy_win(WINDOW *local_win)
    {/* box(local_win, ' ', ' ');不会按照预期的那样清除窗口边框。 而是在窗口的四个角落留下残
    余字符*/
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /*参数注解 9.3:
    
    * 1. win:当前操作的窗口
    * 2. ls:用于显示窗口左边界的字符
    * 3. rs:用于显示窗口右边界的字符
    * 4. ts:用于显示窗口上边界的字符
    * 5. bs:用于显示窗口下边界的字符
         28NCURSES Programming HOWTO 中文版(第二版)
    * 6. tl:用于显示窗口左上角的字符
    * 7. tr:用于显示窗口右上角的字符
    * 8. bl:用于显示窗口左下角的字符
    * 9. br:用于显示窗口右下角的字符
         */
         wrefresh(local_win);
    ```

  ```
  #include<stdio.h>
  #include <ncurses.h>
  typedef struct _win_border_struct{
      chtype ls, rs, ts, bs,
      tl, tr, bl, br;
  }WIN_BORDER;
  
  typedef struct _WIN_struct {
      int startx, starty;
      int height, width;
      WIN_BORDER border;
  }WIN;
  
  void init_win_params(WIN *p_win);
  void print_win_params(WIN*p_win);
  void create_box(WIN *win, int boo);
  
  int main(int argc, char *argv[]) {
      WIN win;
      int ch;
      initscr();
      start_color();
      cbreak();
      keypad(stdscr, TRUE);
      noecho();
      init_pair(1, COLOR_CYAN, COLOR_BLACK);
      init_win_params(&win);
      print_win_params(&win);
      attron(COLOR_PAIR(1));
      printw("Press F1 to exit");
      refresh();
      attroff(COLOR_PAIR(1));
      create_box(&win, TRUE);
      while((ch = getch()) != KEY_F(1)) {
          switch(ch) {
              case KEY_LEFT:
              create_box(&win, FALSE);
              win.startx;
              create_box(&win, TRUE);
              break;
              case KEY_RIGHT:
              create_box(&win, FALSE);
              ++win.startx;
              create_box(&win, TRUE);
              break;
              case KEY_UP:
              create_box(&win, FALSE);
              win.starty;
              create_box(&win, TRUE);
              break;
              case KEY_DOWN:
              create_box(&win, FALSE);
              ++win.starty;
              create_box(&win, TRUE);
              break;
          }
      }
      endwin();
      return 0;
  }
  
  void init_win_params(WIN *p_win) {
      p_win->height = 3;
      p_win->width = 10;
      p_win->starty = (LINES - p_win->height)/2;
      p_win->startx = (COLS - p_win->width)/2;
      p_win->border.ls = '|';
      p_win->border.rs = '|';
      p_win->border.ts = '-';
      p_win->border.bs = '-';
      p_win->border.tl = '+';
      p_win->border.tr = '+';
      p_win->border.bl = '+';
      p_win->border.br= '+';
  }
  
  void print_win_params(WIN*p_win) {
  #ifdef _DEBUG
      mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
      p_win->width, p_win->height);
      refresh();
  #endif
  }
  
  void create_box(WIN *p_win, int boo) {
      int i, j;
      int x, y, w, h;
      x = p_win->startx;
      y = p_win->starty;
      w = p_win->width;
      h = p_win->height;
      if(boo == TRUE) {
          mvaddch(y, x, p_win->border.tl);
          mvaddch(y, x + w, p_win->border.tr);
          mvaddch(y + h, x, p_win->border.bl);
          mvaddch(y + h, x + w, p_win->border.br);
          mvhline(y, x + 1, p_win->border.ts, w - 1);
          mvhline(y + h, x + 1, p_win->border.bs, w - 1);
          mvvline(y + 1, x, p_win->border.ls, h - 1);
          mvvline(y + 1, x + w, p_win->border.rs,h - 1);
      }
      else
          for(j = y; j <= y + h; ++j)
              for(i = x; i <= x + w; ++i)
                  mvaddch(j, i, ' ');
      refresh();
  }
  
  ```

  