#include "compare.h"
#include "parser.h"
#include <stdio.h>

void compare_env(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  if (!env1 || !env2) {
    return;
  }

  printf("[EnvCompare]: Comparing %s <-> %s\n", path1, path2);

  free_env(env1);
  free_env(env2);
}
