#include "sync.h"
#include "parser.h"
#include "utils.h"
#include <stdio.h>

void sync_env(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  if (!env1 || !env2) {
    return;
  }

  FILE *fp = fopen(path1, "a");
  if (!fp) {
    perror("Error opening file1 for append");
    return;
  }

  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    if (!find_value(env1, key)) {
      fprintf(fp, "\n%s=\n", key);
      printf("Added %s to %s\n", key, path1);
    }
  }

  fclose(fp);
  free_env(env1);
  free_env(env2);
}
