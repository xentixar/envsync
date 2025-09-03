#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

EnvFile *parse_env(const char *path) {
  printf("[EnvParser]: Parsing %s\n", path);

  EnvFile *env = (EnvFile *)malloc(sizeof(EnvFile));
  env->count = 0;

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
