#ifndef UTILS_H
#define UTILS_H

#include "parser.h"

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_BOLD    "\033[1m"

const char *find_value(EnvFile *env, const char *key);
char *strdup(const char *s);
int create_backup(const char *filepath);
int restore_backup(const char *filepath);
int confirm_action(const char *message);
void print_colored(const char *color, const char *format, ...);

#endif
