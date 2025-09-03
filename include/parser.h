#ifndef ENV_PARSER
#define ENV_PARSER

#define MAX_PAIRS 512

typedef struct {
  char *key;
  char *value;
} EnvPair;

typedef struct {
  EnvPair pairs[MAX_PAIRS];
  int count;
} EnvFile;

EnvFile *parse_env(const char *path);
void free_env(EnvFile *env);

#endif
