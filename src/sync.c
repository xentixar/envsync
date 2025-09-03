#include "sync.h"
#include "parser.h"
#include "compare.h"
#include "utils.h"
#include <stdio.h>

void sync_env(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  if (!env1 || !env2) {
    return;
  }

  if (!create_backup(path1)) {
    print_colored(COLOR_YELLOW, "⚠ Warning: Could not create backup for %s\n", path1);
  }

  FILE *fp = fopen(path1, "a");
  if (!fp) {
    print_colored(COLOR_RED, "✗ Error opening %s for append\n", path1);
    return;
  }

  int added_count = 0;
  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    if (!find_value(env1, key)) {
      fprintf(fp, "\n%s=\n", key);
      print_colored(COLOR_GREEN, "✓ Added %s to %s\n", key, path1);
      added_count++;
    }
  }

  fclose(fp);
  
  if (added_count == 0) {
    print_colored(COLOR_BLUE, "ℹ No new keys to add\n");
  } else {
    print_colored(COLOR_GREEN, "\n🎉 Successfully added %d key(s) to %s\n", added_count, path1);
  }

  free_env(env1);
  free_env(env2);
}

void sync_env_interactive(const char *path1, const char *path2) {
  EnvFile *env1 = parse_env(path1);
  EnvFile *env2 = parse_env(path2);

  if (!env1 || !env2) {
    return;
  }

  print_colored(COLOR_CYAN, "[Interactive Sync]: %s <- %s\n\n", path1, path2);

  int missing_count = 0;
  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    if (!find_value(env1, key)) {
      missing_count++;
    }
  }

  if (missing_count == 0) {
    print_colored(COLOR_GREEN, "✓ No missing keys found. Files are already in sync!\n");
    free_env(env1);
    free_env(env2);
    return;
  }

  print_colored(COLOR_YELLOW, "Found %d missing key(s) in %s:\n", missing_count, path1);
  for (int i = 0; i < env2->count; i++) {
    const char *key = env2->pairs[i].key;
    if (!find_value(env1, key)) {
      print_colored(COLOR_RED, "  ✗ %s\n", key);
    }
  }

  printf("\n");
  
  if (confirm_action("Would you like to sync these missing keys?")) {
    if (confirm_action("Create a backup before syncing?")) {
      if (!create_backup(path1)) {
        print_colored(COLOR_RED, "✗ Failed to create backup. Aborting sync.\n");
        free_env(env1);
        free_env(env2);
        return;
      }
    }

    FILE *fp = fopen(path1, "a");
    if (!fp) {
      print_colored(COLOR_RED, "✗ Error opening %s for append\n", path1);
      free_env(env1);
      free_env(env2);
      return;
    }

    int added_count = 0;
    for (int i = 0; i < env2->count; i++) {
      const char *key = env2->pairs[i].key;
      if (!find_value(env1, key)) {
        fprintf(fp, "\n%s=\n", key);
        print_colored(COLOR_GREEN, "✓ Added %s to %s\n", key, path1);
        added_count++;
      }
    }

    fclose(fp);
    print_colored(COLOR_GREEN, "\n🎉 Successfully synced %d key(s)!\n", added_count);
    
    if (confirm_action("Would you like to compare the files now?")) {
      printf("\n");
      compare_env(path1, path2);
    }
  } else {
    print_colored(COLOR_BLUE, "Sync cancelled by user\n");
  }

  free_env(env1);
  free_env(env2);
}
