#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256

typedef struct {
    char timestamp[MAX_STR_LEN];
    char source_file[MAX_STR_LEN];
    char ip[MAX_STR_LEN];
    char application[MAX_STR_LEN];
    char content[MAX_STR_LEN];
    char category[MAX_STR_LEN];
    char computer_name[MAX_STR_LEN];
    char action[MAX_STR_LEN];
} LogInfo;

void parse_log_entry(const char *log_entry, LogInfo *log_info) {
    char *tmp_str;
    char *aux_str;
    char *log_copy = strdup(log_entry);

    if (!log_copy) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Extract timestamp
    tmp_str = strchr(log_copy, '(');
    if (tmp_str) {
        *tmp_str = '\0';
        strncpy(log_info->timestamp, log_copy, MAX_STR_LEN);
        *tmp_str = '(';
    } else {
        strncpy(log_info->timestamp, "Unknown", MAX_STR_LEN);
    }

    // Extract source file
    tmp_str = strchr(log_copy, '>');
    if (tmp_str) {
        tmp_str++;
        aux_str = strchr(tmp_str, ' ');
        if (aux_str) {
            *aux_str = '\0';
            strncpy(log_info->source_file, tmp_str, MAX_STR_LEN);
            *aux_str = ' ';
        } else {
            strncpy(log_info->source_file, "Unknown", MAX_STR_LEN);
        }
    }

    // Move aux_str past the source file
    if (aux_str) {
        aux_str++;
    }

    // Extract IP address
    tmp_str = strchr(aux_str, ' ');
    if (tmp_str) {
        tmp_str++;
        aux_str = strchr(tmp_str, ' ');
        if (aux_str) {
            *aux_str = '\0';
            strncpy(log_info->ip, tmp_str, MAX_STR_LEN);
            *aux_str = ' ';
        } else {
            strncpy(log_info->ip, "Unknown", MAX_STR_LEN);
        }
    }

    // Extract application
    tmp_str = strstr(aux_str, "Application:");
    if (tmp_str) {
        tmp_str += strlen("Application:");
        while (*tmp_str == ' ') {
            tmp_str++;
        }
        aux_str = strchr(tmp_str, ',');
        if (aux_str) {
            *aux_str = '\0';
            strncpy(log_info->application, tmp_str, MAX_STR_LEN);
            *aux_str = ',';
        } else {
            strncpy(log_info->application, tmp_str, MAX_STR_LEN);
        }
    } else {
        strncpy(log_info->application, "Unknown", MAX_STR_LEN);
    }

    // Extract content
    tmp_str = strstr(aux_str, "Content:");
    if (tmp_str) {
        tmp_str += strlen("Content:");
        while (*tmp_str == ' ') {
            tmp_str++;
        }
        strncpy(log_info->content, tmp_str, MAX_STR_LEN);
    } else {
        strncpy(log_info->content, "Unknown", MAX_STR_LEN);
    }

    // Extract category
    tmp_str = strstr(aux_str, "Category:");
    if (tmp_str) {
        tmp_str += strlen("Category:");
        while (*tmp_str == ' ') {
            tmp_str++;
        }
        aux_str = strchr(tmp_str, ',');
        if (aux_str) {
            *aux_str = '\0';
            strncpy(log_info->category, tmp_str, MAX_STR_LEN);
            *aux_str = ',';
        } else {
            strncpy(log_info->category, tmp_str, MAX_STR_LEN);
        }
    } else {
        strncpy(log_info->category, "Unknown", MAX_STR_LEN);
    }

    // Extract computer name
    tmp_str = strstr(aux_str, "Computer name:");
    if (tmp_str) {
        tmp_str += strlen("Computer name:");
        while (*tmp_str == ' ') {
            tmp_str++;
        }
        aux_str = strchr(tmp_str, ',');
        if (aux_str) {
            *aux_str = '\0';
            strncpy(log_info->computer_name, tmp_str, MAX_STR_LEN);
            *aux_str = ',';
        } else {
            strncpy(log_info->computer_name, tmp_str, MAX_STR_LEN);
        }
    } else {
        strncpy(log_info->computer_name, "Unknown", MAX_STR_LEN);
    }

    // Extract action
    tmp_str = strstr(aux_str, "Action:");
    if (tmp_str) {
        tmp_str += strlen("Action:");
        while (*tmp_str == ' ') {
            tmp_str++;
        }
        aux_str = strchr(tmp_str, ',');
        if (aux_str) {
            *aux_str = '\0';
            strncpy(log_info->action, tmp_str, MAX_STR_LEN);
            *aux_str = ',';
        } else {
            strncpy(log_info->action, tmp_str, MAX_STR_LEN);
        }
    } else {
        strncpy(log_info->action, "Unknown", MAX_STR_LEN);
    }

    free(log_copy);
}

void print_log_info(const LogInfo *log_info) {
    printf("Timestamp: %s\n", log_info->timestamp);
    printf("Source File: %s\n", log_info->source_file);
    printf("IP Address: %s\n", log_info->ip);
    printf("Application: %s\n", log_info->application);
    printf("Content: %s\n", log_info->content);
    printf("Category: %s\n", log_info->category);
    printf("Computer Name: %s\n", log_info->computer_name);
    printf("Action: %s\n\n", log_info->action);
}

int main() {
    const char *log_entries[] = {
        "2024 May 15 01:02:59 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 14 18:02:56 EchoBendQNAP daemon info qulogd[3936] conn log: Users: sysadmin, Source IP: 10.200.126.5, Computer name: ---, Connection type: HTTPS, Accessed resources: ---, Action: Logout.",
        "2024 May 16 08:00:01 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 16 01:00:00 EchoBendQNAP daemon info qulogd[3936] event log: Users: ---, Source IP: ---, Computer name: ---, Application: Storage & Snapshots, Category: Snapshot, Content: [Storage & Snapshots] Started creating scheduled snapshot. Shared folder: MarVista.",
        "2024 May 16 06:10:04 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 15 23:10:01 EchoBendQNAP daemon info qulogd[3936] event log: Users: ---, Source IP: ---, Computer name: localhost, Application: App Center, Category: Settings, Content: [App Center] Started app update check. The current setting is to \"Install required updates automatically\".",
        "2024 May 16 05:00:04 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 15 22:00:00 EchoBendQNAP daemon info qulogd[3936] event log: Users: System, Source IP: 127.0.0.1, Computer name: ---, Application: Hybrid Backup Sync, Category: Job Status, Content: [Hybrid Backup Sync] Started Sync job: \"QNAP Dropbox\".",
        "2024 May 22 10:00:13 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 22 03:00:12 EchoBendQNAP daemon info qulogd[3936] event log: Users: ---, Source IP: ---, Computer name: ---, Application: Malware Remover, Category: General, Content: [Malware Remover] Scan completed.",
        "2024 May 22 08:30:03 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 22 01:30:01 EchoBendQNAP daemon info qulogd[3936] event log: Users: ---, Source IP: ---, Computer name: ---, Application: Malware Remover, Category: General, Content: [Malware Remover] Finished automatic update check. No new software version found.",
        "2024 May 22 08:00:02 (NMS_echo) any->C:\\Users\\catenactio\\AppData\\Local\\visualsyslog\\syslog 192.168.30.3 May 22 01:00:01 EchoBendQNAP daemon info qulogd[3936] event log: Users: ---, Source IP: ---, Computer name: ---, Application: Storage & Snapshots, Category: Snapshot, Content: [Storage & Snapshots] Started creating scheduled snapshot. Shared folder: MarVista."
    };

    size_t num_entries = sizeof(log_entries) / sizeof(log_entries[0]);
    LogInfo log_infos[num_entries];

    for (size_t i = 0; i < num_entries; i++) {
        parse_log_entry(log_entries[i], &log_infos[i]);
        print_log_info(&log_infos[i]);
    }

    return 0;
}
