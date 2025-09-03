#include "utils.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>

const char *find_value(EnvFile *env, const char *key) {
  for (int i = 0; i < env->count; i++) {
    if (strcmp(env->pairs[i].key, key) == 0) {
      return env->pairs[i].value;
    }
  }
  return NULL;
}

char *strdup(const char *s) {
  char *dup = malloc(strlen(s) + 1);
  if (dup) {
    strcpy(dup, s);
  }
  return dup;
}
