#include "compare.h"
#include "sync.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void print_usage() {
  printf("%sEnvSync - .env Diff & Sync Tool%s\n", COLOR_BOLD, COLOR_RESET);
  printf("Usage:\n");
  printf("  %senvsync compare%s file1 file2          Compare two .env files\n", COLOR_CYAN, COLOR_RESET);
  printf("  %senvsync compare-i%s file1 file2       Interactive compare mode\n", COLOR_CYAN, COLOR_RESET);
  printf("  %senvsync sync%s file1 file2             Sync missing keys from file2 -> file1\n", COLOR_GREEN, COLOR_RESET);
  printf("  %senvsync sync-i%s file1 file2          Interactive sync mode with backups\n", COLOR_GREEN, COLOR_RESET);
  printf("  %senvsync backup%s file                  Create backup of file\n", COLOR_YELLOW, COLOR_RESET);
  printf("  %senvsync restore%s file                 Restore file from backup\n", COLOR_YELLOW, COLOR_RESET);
  printf("  %senvsync help%s                         Show this help message\n", COLOR_MAGENTA, COLOR_RESET);
  printf("\n%sInteractive modes%s provide step-by-step guidance and confirmation prompts.\n", COLOR_BOLD, COLOR_RESET);
  printf("%sBackup functionality%s automatically creates timestamped backups before modifications.\n", COLOR_BOLD, COLOR_RESET);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    return 1;
  }

  if (strcmp(argv[1], "compare") == 0) {
    if (argc != 4) {
      print_colored(COLOR_RED, "✗ Error: compare needs 2 files\n");
      return 1;
    }
    compare_env(argv[2], argv[3]);
  } else if (strcmp(argv[1], "compare-i") == 0) {
    if (argc != 4) {
      print_colored(COLOR_RED, "✗ Error: compare-i needs 2 files\n");
      return 1;
    }
    compare_env_interactive(argv[2], argv[3]);
  } else if (strcmp(argv[1], "sync") == 0) {
    if (argc != 4) {
      print_colored(COLOR_RED, "✗ Error: sync needs 2 files\n");
      return 1;
    }
    sync_env(argv[2], argv[3]);
  } else if (strcmp(argv[1], "sync-i") == 0) {
    if (argc != 4) {
      print_colored(COLOR_RED, "✗ Error: sync-i needs 2 files\n");
      return 1;
    }
    sync_env_interactive(argv[2], argv[3]);
  } else if (strcmp(argv[1], "backup") == 0) {
    if (argc != 3) {
      print_colored(COLOR_RED, "✗ Error: backup needs 1 file\n");
      return 1;
    }
    if (create_backup(argv[2])) {
      print_colored(COLOR_GREEN, "✓ Backup completed successfully\n");
    } else {
      print_colored(COLOR_RED, "✗ Backup failed\n");
      return 1;
    }
  } else if (strcmp(argv[1], "restore") == 0) {
    if (argc != 3) {
      print_colored(COLOR_RED, "✗ Error: restore needs 1 file\n");
      return 1;
    }
    if (confirm_action("Are you sure you want to restore this file from backup?")) {
      if (restore_backup(argv[2])) {
        print_colored(COLOR_GREEN, "✓ Restore completed successfully\n");
      } else {
        print_colored(COLOR_RED, "✗ Restore failed\n");
        return 1;
      }
    } else {
      print_colored(COLOR_BLUE, "Restore cancelled by user\n");
    }
  } else if (strcmp(argv[1], "help") == 0) {
    print_usage();
  } else {
    print_colored(COLOR_RED, "✗ Unknown command: %s\n", argv[1]);
    print_usage();
    return 1;
  }

  return 0;
}
