/*************************************************************************
	> File Name: parse_conf.c
	> Author: 
	> Mail: 
	> Created Time: Sun 18 Oct 2020 03:28:59 PM CST
 ************************************************************************/

#include"head.h"

int get_string(const char *file, char *buff, size_t size) {
    FILE *f = NULL;

    if ((f = fopen(file, "r")) == NULL) {
        return -1;
    }

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (len > size) {
        fprintf(stderr, "Buffer is less than the len of file\n");
        return -1;
    }
    fread(buff, len, 1, f);
    fclose(f);
    return len;
}

int parse_conf(char *string) {
    const cJSON *master = NULL;
    const cJSON *slave = NULL;
    cJSON *conf = NULL;
    int status = 0;

    if ((conf = cJSON_Parse(string)) == NULL) {
        const char *err_ptr = cJSON_GetErrorPtr();
        if (err_ptr != NULL) {
            fprintf(stderr, "Error Before : %s\n", err_ptr);
            status = -1;
            goto end;
        }
    }

    master = cJSON_GetObjectItemCaseSensitive(conf, "Master");
    slave = cJSON_GetObjectItemCaseSensitive(conf, "Slave");

    cJSON *master_port = cJSON_GetObjectItemCaseSensitive(master, "MasterPort");
    cJSON *slave_port = cJSON_GetObjectItemCaseSensitive(slave, "SlavePort");

    printf("MasterPort = %d, SlavePort = %d\n", master_port->valueint, slave_port->valueint);

end:
    cJSON_Delete(conf);
    return status;
}

cJSON *get_cjson(const char *file) {
    char buff[512];
    get_string(file, buff, sizeof(buff));
    cJSON *conf = NULL;

    if ((conf = cJSON_Parse(buff)) == NULL) {
        const char *err_ptr = cJSON_GetErrorPtr();
        if (err_ptr != NULL) {
            return NULL;
        }
    }

    return conf;
}

int get_json_valueint(cJSON *conf, const char *who, const char *config) {
    const cJSON *Who = NULL;
    Who = cJSON_GetObjectItemCaseSensitive(conf, who);

    cJSON *Config = cJSON_GetObjectItemCaseSensitive(Who, config);

    return Config->valueint;
}

char *get_json_valuestring(cJSON *conf, const char *who, const char *config) {
    const cJSON *Who = NULL;
    Who = cJSON_GetObjectItemCaseSensitive(conf, who);

    cJSON *Config = cJSON_GetObjectItemCaseSensitive(Who, config);

    return Config->valuestring;
}

cJSON *get_json_valueobject(cJSON *conf, const char *who) {
    cJSON *Who = NULL;
    Who = cJSON_GetObjectItemCaseSensitive(conf, who);

    return Who;
}

