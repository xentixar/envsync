#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EnvFile *parse_env(const char *path) {
  FILE *fp = fopen(path, "r");

  if (!fp) {
    perror("Error opening file.");
    return NULL;
  }

  printf("[EnvParser]: Parsing %s\n", path);

  EnvFile *env = (EnvFile *)malloc(sizeof(EnvFile));
  env->count = 0;

  char line[512];
  while (fgets(line, sizeof(line), fp)) {
    if (line[0] == '#' || line[0] == '\n') {
      continue;
    }

    char *eq = strchr(line, '=');
    if (!eq) {
      continue;
    }

    *eq = '\0';
    char *key = strdup(line);
    char *value = strdup(eq + 1);

    value[strcspn(value, "\n")] = 0;

    env->pairs[env->count].key = key;
    env->pairs[env->count].value = value;
    env->count++;
  }

  fclose(fp);

  return env;
}

void free_env(EnvFile *env) {
  if (!env) {
    return;
  }

  for (int i = 0; i < env->count; i++) {
    free(env->pairs[i].key);
    free(env->pairs[i].value);
  }

  free(env);
}
