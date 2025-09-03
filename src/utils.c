#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

const char *find_value(EnvFile *env, const char *key) {
  for (int i = 0; i < env->count; i++) {
    if (strcmp(env->pairs[i].key, key) == 0) {
      return env->pairs[i].value;
    }
  }
  return NULL;
}

char *strdup(const char *s) {
  char *d = malloc(strlen(s) + 1);
  if (d) strcpy(d, s);
  return d;
}

int create_backup(const char *filepath) {
  struct stat st;
  if (stat(filepath, &st) != 0) {
    return 0;
  }

  time_t now = time(NULL);
  struct tm *tm_info = localtime(&now);
  
  char backup_path[512];
  snprintf(backup_path, sizeof(backup_path), "%s.backup.%04d%02d%02d_%02d%02d%02d",
           filepath, 
           tm_info->tm_year + 1900,
           tm_info->tm_mon + 1,
           tm_info->tm_mday,
           tm_info->tm_hour,
           tm_info->tm_min,
           tm_info->tm_sec
          );

  FILE *src = fopen(filepath, "r");
  if (!src) return 0;

  FILE *dst = fopen(backup_path, "w");
  if (!dst) {
    fclose(src);
    return 0;
  }

  char buffer[1024];
  size_t bytes;
  while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
    fwrite(buffer, 1, bytes, dst);
  }

  fclose(src);
  fclose(dst);
  
  print_colored(COLOR_GREEN, "✓ Backup created: %s\n", backup_path);
  return 1;
}

int restore_backup(const char *filepath) {
  DIR *dir;
  struct dirent *entry;
  
  char dir_path[1024] = ".";
  char file_name[512];
  
  const char *last_slash = strrchr(filepath, '/');
  if (last_slash) {
    size_t dir_len = last_slash - filepath;
    if (dir_len > 0 && dir_len < sizeof(dir_path) - 1) {
      strncpy(dir_path, filepath, dir_len);
      dir_path[dir_len] = '\0';
    }
    if (strlen(last_slash + 1) < sizeof(file_name)) {
      strcpy(file_name, last_slash + 1);
    } else {
      print_colored(COLOR_RED, "✗ Filename too long\n");
      return 0;
    }
  } else {
    if (strlen(filepath) < sizeof(file_name)) {
      strcpy(file_name, filepath);
    } else {
      print_colored(COLOR_RED, "✗ Filename too long\n");
      return 0;
    }
  }
  
  char backup_pattern[1024];
  if (snprintf(backup_pattern, sizeof(backup_pattern), "%s.backup.", file_name) >= sizeof(backup_pattern)) {
    print_colored(COLOR_RED, "✗ Backup pattern too long\n");
    return 0;
  }
  
  char most_recent_backup[1024] = "";
  time_t most_recent_time = 0;
  
  dir = opendir(dir_path);
  if (dir) {
    while ((entry = readdir(dir)) != NULL) {
      if (strncmp(entry->d_name, backup_pattern, strlen(backup_pattern)) == 0) {
        char full_backup_path[1024];
        int result;
        if (strcmp(dir_path, ".") == 0) {
          result = snprintf(full_backup_path, sizeof(full_backup_path), "%s", entry->d_name);
        } else {
          result = snprintf(full_backup_path, sizeof(full_backup_path), "%s/%s", dir_path, entry->d_name);
        }
        
        if (result >= 0 && result < sizeof(full_backup_path)) {
          struct stat st;
          if (stat(full_backup_path, &st) == 0 && st.st_mtime > most_recent_time) {
            most_recent_time = st.st_mtime;
            strcpy(most_recent_backup, full_backup_path);
          }
        }
      }
    }
    closedir(dir);
  }
  
  if (strlen(most_recent_backup) == 0) {
    print_colored(COLOR_RED, "✗ No backup found for %s\n", filepath);
    return 0;
  }
  
  if (rename(most_recent_backup, filepath) == 0) {
    print_colored(COLOR_GREEN, "✓ Backup restored: %s\n", filepath);
    return 1;
  } else {
    print_colored(COLOR_RED, "✗ Failed to restore backup\n");
    return 0;
  }
}

int confirm_action(const char *message) {
  printf("%s%s%s (y/N): ", COLOR_YELLOW, message, COLOR_RESET);
  fflush(stdout);
  
  char response[10];
  if (fgets(response, sizeof(response), stdin) == NULL) {
    return 0;
  }
  
  response[strcspn(response, "\n")] = 0;
  
  return (strcasecmp(response, "y") == 0 || strcasecmp(response, "yes") == 0);
}

void print_colored(const char *color, const char *format, ...) {
  va_list args;
  va_start(args, format);
  
  printf("%s", color);
  vprintf(format, args);
  printf("%s", COLOR_RESET);
  
  va_end(args);
}
