/*************************************************************************
	> File Name: wrapper_json.c
	> Author: wei 
	> Mail: 1931248856@qq.com 
	> Created Time: Sat Nov  7 18:28:40 2020
 ************************************************************************/
#include "head.h"
#define MAX 50
extern struct User *bteam;
extern struct User *rteam;
extern struct BallStatus ball_status;
extern struct Bpoint ball;

char *string = NULL;
cJSON *spirit = NULL;
cJSON *red = NULL;
cJSON *blue = NULL;
cJSON *ball_spirit = NULL;
cJSON *player = NULL;
cJSON *name = NULL;
cJSON *who = NULL;
cJSON *x = NULL;
cJSON *y = NULL;

int add_player_to_team(cJSON *team, struct User *user) {
    char tmp[512] = {0};
    sprintf(tmp, "x = %d, y = %d", user->loc.x, user->loc.y);
    //Show_Message(, NULL, tmp, 1);
    if ((player = cJSON_CreateObject()) == NULL) return -1;
    cJSON_AddItemToArray(team, player);
    if ((x = cJSON_CreateNumber(user->loc.x)) == NULL) return -1;
    if ((y = cJSON_CreateNumber(user->loc.y)) == NULL) return -1;
    if ((name = cJSON_CreateString(user->name)) == NULL) return -1;
    cJSON_AddItemToObject(player, "x", x);
    cJSON_AddItemToObject(player, "y", y);
    cJSON_AddItemToObject(player, "name", name);
    sprintf(tmp, "name = %s, x = %d, y = %d", name->valuestring, x->valueint, y->valueint);
    //Show_Message(, NULL, tmp, 1);
    return 0;
}

char  *create_spirit() {
    if ((spirit = cJSON_CreateObject()) == NULL) goto end;
    if ((red = cJSON_CreateArray()) == NULL) goto end;
    if ((blue = cJSON_CreateArray()) == NULL) goto end;
    if ((ball_spirit = cJSON_CreateObject()) == NULL) goto end;

    cJSON_AddItemToObject(spirit, "red", red);
    cJSON_AddItemToObject(spirit, "blue", blue);
    cJSON_AddItemToObject(spirit, "ball", ball_spirit);

    for (int i = 0; i < MAX; i++) {
        if (rteam[i].online == 1) {
            if (add_player_to_team(red, &rteam[i]) < 0) goto end;
        }
        if (bteam[i].online == 1) {
            if (add_player_to_team(blue, &bteam[i]) < 0) goto end;
        }
    }
    char tmp[512] = {0};
    sprintf(tmp, "%s", ball_status.by_team ? "blue" : "red");
    if ((who = cJSON_CreateString(tmp)) == NULL) goto end;
    if ((name = cJSON_CreateString(ball_status.name)) == NULL) goto end;
    if ((x = cJSON_CreateNumber((int)ball.x)) == NULL) goto end;
    if ((y = cJSON_CreateNumber((int)ball.y)) == NULL) goto end;

    cJSON_AddItemToObject(ball_spirit, "who", who);
    cJSON_AddItemToObject(ball_spirit, "name", name);
    cJSON_AddItemToObject(ball_spirit, "x", x);
    cJSON_AddItemToObject(ball_spirit, "y", y);

    sprintf(tmp, "ball.x = %d, ball.y = %d", (int)ball.x, (int)ball.y);
    //Show_Message(, NULL, tmp, 1);
    string = cJSON_Print(spirit);
end:
    cJSON_Delete(spirit);
    return string;
}
