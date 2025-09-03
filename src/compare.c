#include "compare.h"
#include "parser.h"
#include "sync.h"
#include "utils.h"
#include <stdio.h>

void compare_env(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  int diff = 0;

  if (!env1 || !env2) {
    return;
  }

  print_colored(COLOR_CYAN, "[EnvCompare]: Comparing %s <-> %s\n\n", path1, path2);

  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    const char *val1 = find_value(env1, key);

    if (!val1) {
      diff++;
      print_colored(COLOR_RED, "✗ Missing in %s: %s\n", path1, key);
    }
  }

  for (int i = 0; i < env1->count; i++) {
    const char *key = env1->pairs[i].key;
    if (!find_value(env2, key)) {
      diff++;
      print_colored(COLOR_YELLOW, "⚠ Extra in %s: %s\n", path1, key);
    }
  }

  if (diff == 0) {
    print_colored(COLOR_GREEN, "✓ No differences found between the files\n");
  } else {
    print_colored(COLOR_MAGENTA, "\n📊 Summary: %d difference(s) found\n", diff);
  }

  free_env(env1);
  free_env(env2);
}

void compare_env_interactive(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  if (!env1 || !env2) {
    return;
  }

  print_colored(COLOR_CYAN, "[Interactive Compare]: %s <-> %s\n\n", path1, path2);
  
  int missing_count = 0;
  int extra_count = 0;
  
  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    if (!find_value(env1, key)) {
      missing_count++;
    }
  }
  
  for (int i = 0; i < env1->count; i++) {
    const char *key = env1->pairs[i].key;
    if (!find_value(env2, key)) {
      extra_count++;
    }
  }
  
  if (missing_count == 0 && extra_count == 0) {
    print_colored(COLOR_GREEN, "✓ Files are identical!\n");
    free_env(env1);
    free_env(env2);
    return;
  }
  
  if (missing_count > 0) {
    print_colored(COLOR_YELLOW, "Found %d missing key(s) in %s:\n", missing_count, path1);
    for (int i = 0; i < env2->count; i++) {
      const char *key = env2->pairs[i].key;
      if (!find_value(env1, key)) {
        print_colored(COLOR_RED, "  ✗ %s\n", key);
      }
    }
    printf("\n");
  }
  
  if (extra_count > 0) {
    print_colored(COLOR_YELLOW, "Found %d extra key(s) in %s:\n", extra_count, path1);
    for (int i = 0; i < env1->count; i++) {
      const char *key = env1->pairs[i].key;
      if (!find_value(env2, key)) {
        print_colored(COLOR_YELLOW, "  ⚠ %s\n", key);
      }
    }
    printf("\n");
  }
  
  if (missing_count > 0) {
    char confirm_message[100];
    sprintf(confirm_message, "Would you like to sync missing keys from %s to %s?", path2, path1);
    if (confirm_action(confirm_message)) {
      print_colored(COLOR_GREEN, "Proceeding with sync...\n");
      sync_env(path1, path2);
    } else {
      print_colored(COLOR_BLUE, "Sync cancelled by user\n");
    }
  }

  free_env(env1);
  free_env(env2);
}
