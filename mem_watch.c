#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *buf;
char *delta__;
char *free__;
char *total__;
FILE *mem_fp;

int process(char *src) {
  strtok(src, " ");
  char *str = strtok(NULL, " ");
  return atoi(str);
}

#define _FREE(ptr) ptr != NULL ? free(ptr) : 1

void sig_int(int sig) {
  _FREE(buf);
  _FREE(total__);
  _FREE(free__);
  _FREE(delta__);
  mem_fp != NULL ? fclose(mem_fp) : 1;
  fprintf(stderr, "\n");
  exit(0);
}

enum { KB, MB, GB };

// Takes num_ bytes and converts to a string that's len is max
char *format_num(float num_, int max) {
  float ret = num_;
  int div_c = 0;
  while ((int)(ret /= 1024) > 0)
    div_c++;
  ret *= 1024;
  char *ret_ = calloc(max, sizeof(char));
  switch (div_c) {
  case KB:
    sprintf(ret_, "%.1fKB", ret);
    return ret_;
    break;

  case MB:
    sprintf(ret_, "%.1fMB", ret);
    return ret_;
    break;

  case GB:
    sprintf(ret_, "%.1fGB", ret);
    return ret_;
    break;

  default:
    sprintf(ret_, "%.1fB", ret);
    return ret_;
    break;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  signal(SIGINT, sig_int);
  // printf("sleep(%d);\n", argc == 2 ? atoi(argv[1]) : 1);
  while (1) {
    mem_fp = fopen("/proc/meminfo", "r");
    if (!mem_fp) {
      perror("fopen");
      return -1;
    }
    buf = calloc(64, sizeof(char));
    if (!buf) {
      perror("calloc");
      return -1;
    }
    fgets(buf, 64, mem_fp);
    int total_ = process(buf);

    fgets(buf, 64, mem_fp);
    int free_ = process(buf);

    fgets(buf, 64, mem_fp);
    int delta_ = process(buf);

    total__ = format_num(total_, 10);
    free__ = format_num(total_ - delta_, 10);
    delta__ = format_num(delta_, 10);
    fprintf(stderr, "%s/%s Available: %s\n", free__, total__, delta__);

    free(total__);
    free(free__);
    free(delta__);
    free(buf);
    total__ = NULL;
    free__ = NULL;
    delta__ = NULL;
    buf = NULL;

    fclose(mem_fp);
    mem_fp = NULL;

    sleep(argc == 2 ? atoi(argv[1]) : 1);
  }
}
