#include "complier+.h"

#include <fstream>
#include <iostream>
#include <time.h>

#define ERROR   0
#define WARN    1
#define INFO    2
#define DEBUG   3

void init_log();
void end_log();
void log(int type, const char * message);
void log_out(int type, const char * message);
void log_int(int type, const char * message, int i);
void log_out_int(int type, const char * m1, int i, const char * m2);
void log_bin32(int type, const char * message, command cmd);

