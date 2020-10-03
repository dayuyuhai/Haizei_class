/*************************************************************************
	> File Name: file_transfer.c
	> Author: 
	> Mail: 
	> Created Time: Fri 18 Sep 2020 06:56:54 PM CST
 ************************************************************************/

#include "head.h"

/*
void submit(struct FileMsg *fmsg) {
    FILE *fp = fopen("recv.pdf", "ab");
    fwrite(fmsg->buff, 1, sizeof(fmsg->buff), fp);
}
*/


void send_file(const char *filename, int sockfd) {
    FILE *fp = NULL;
    if ((fp = fopen(filename, "rb")) == NULL) {
        perror("fopen");
        return ;
    }

    char *p;
    struct FileMsg fmsg;
    memset(&fmsg, 0, sizeof(fmsg));

    fseek(fp, 0L, SEEK_END);   // 文件指针 偏移到文件末尾
    fmsg.size = ftell(fp);    // 获得文件指针当前位置
    fseek(fp, 0L, SEEK_SET);
    strcpy(fmsg.name, (p = strrchr(filename, '/')) ? p + 1 : filename);    

    /*
     * The  strchr() function returns a pointer to the first occurrence of the
       character c in the string s.

       The strrchr() function returns a pointer to the last occurrence of  the
       character c in the string s.
    */

    size_t nread;

    while ((nread = fread(fmsg.buff, 1, sizeof(fmsg.buff), fp))) {
        printf("send %ld size!\n", sizeof(fmsg));
        send(sockfd, (void *)&fmsg, sizeof(fmsg), 0);
        memset(fmsg.buff, 0, sizeof(fmsg.buff));
    }

    return ;
}

void recv_file(int sockfd) {
    size_t recv_size, total_size = 0, write_size = 0, sum_size = 0;
    struct FileMsg packet_t, packet, packet_pre;
    int packet_size = sizeof(struct FileMsg);
    int offset = 0, cnt = 0;
    FILE *fp = NULL;

    bzero(&packet, 0);
    bzero(&packet_t, 0);
    bzero(&packet_pre, 0);

    while (1) {
        if (offset) {
            memcpy(&packet, &packet_pre, offset);
        }
        while ((recv_size = recv(sockfd, (void *)&packet_t, packet_size, 0)) > 0) {

            total_size = recv_size + offset;

            if (total_size == packet_size) {
                memcpy((char *)&packet + offset, &packet_t, recv_size);
                DBG(L_GREEN"整包"NONE " : %d\n", packet_size);
                offset = 0;

                // submit(&packet);

                break;
            } else if (total_size < packet_size) {
                memcpy((char *)&packet + offset, &packet_t, recv_size);
                DBG(YELLOW"拆包"NONE " : %ld\n", recv_size);
                offset += recv_size;
            } else {
                int need = packet_size - offset;
                memcpy((char *)&packet + offset, &packet_t, need);
                DBG(BLUE"粘包"NONE " : %d\n", packet_size);

                // submit(&packet);

                offset = recv_size - need;
                memcpy((char *)&packet_pre, (char *)&packet_t + need, offset);
                break;
            }

        }
        if (!cnt) {
            DBG(PURPLE"Start recv file %s, with size %ld!\n"NONE, packet.name, packet.size);

            char name[1024] = {0};
            sprintf(name, "./data/%s", packet.name);
            if ((fp = fopen(name, "wb")) == NULL) {
                perror("fopen");
                return ;
            }
        }
        cnt++;
        if (packet.size - sum_size >= sizeof(packet.buff)) {
            write_size = fwrite(packet.buff, 1, sizeof(packet.buff), fp);
        } else {
            write_size = fwrite(packet.buff, 1, packet.size - sum_size, fp);
        }

        sum_size += write_size;
        memset(packet.buff, 0, sizeof(packet.buff));

        if (sum_size >= packet.size) {
            DBG("Finish\n");
            break;
        }


    }
    fclose(fp);
    return ;
}

