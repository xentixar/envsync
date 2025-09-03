#include "compare.h"
#include <stdio.h>
#include <string.h>

void print_usage() {
  printf("EnvSync - .env Diff & Sync Tool\n");
  printf("Usage:\n");
  printf("  envsync compare file1 file2   Compare two .env files\n");
  printf("  envsync sync file1 file2      Sync missing keys from file2 -> "
         "file1\n");
  printf("  envsync help                  Show this help message\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    return 1;
  }

  if (strcmp(argv[1], "compare") == 0) {
    if (argc != 4) {
      print_usage();
      return 1;
    }

    compare_env(argv[2], argv[3]);
  } else if (strcmp(argv[1], "sync") == 0) {
    if (argc != 4) {
      printf("Error: sync needs 2 files\n");
      return 1;
    }

    // sync_env(argv[2], argv[3]);
  } else {
    print_usage();
  }

  return 0;
}
