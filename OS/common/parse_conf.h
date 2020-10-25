/*************************************************************************
	> File Name: parse_conf.h
	> Author: 
	> Mail: 
	> Created Time: Sun 18 Oct 2020 03:28:27 PM CST
 ************************************************************************/

#ifndef _PARSE_CONF_H
#define _PARSE_CONF_H
int parse_conf(char *string);
int get_string(const char *file, char *buff, size_t size);
cJSON *get_cjson(const char *file);
int get_json_valueint(cJSON *conf, const char *who, const char *config);
char *get_json_valuestring(cJSON *conf, const char *who, const char *config);
cJSON *get_json_valueobject(cJSON *conf, const char *who);

#endif
