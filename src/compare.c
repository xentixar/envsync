#include "compare.h"
#include "parser.h"
#include "utils.h"
#include <stdio.h>

void compare_env(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  int diff = 0;

  if (!env1 || !env2) {
    return;
  }

  printf("[EnvCompare]: Comparing %s <-> %s\n\n", path1, path2);

  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    const char *val1 = find_value(env1, key);

    if (!val1) {
      diff++;
      printf("Missing in %s: %s\n", path1, key);
    }
  }

  for (int i = 0; i < env1->count; i++) {
    const char *key = env1->pairs[i].key;
    if (!find_value(env2, key)) {
      diff++;
      printf("Extra in %s: %s\n", path1, key);
    }
  }

  if (diff == 0) {
    printf("No diff found on comparing\n");
  }

  free_env(env1);
  free_env(env2);
}
