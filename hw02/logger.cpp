#include "logger.h"

#include <bitset>

const char * LOG_PATH = "./log";
std::string log_types[4] = {"ERROR", "WARN", "INFO", "DEBUG"};

void log(int type, const char * message)
{
    std::ofstream log_file;
    log_file.open(LOG_PATH, std::ios_base::app);
    log_file << '[' << log_types[type] << "]\t" << message << std::endl;
    log_file.close();
}

void log_out(int type, const char * message)
{
    std::ofstream log_file;
    log_file.open(LOG_PATH, std::ios_base::app);
    log_file << '[' << log_types[type] << "]\t" << message << std::endl;
    log_file.close();

    std::cout << '[' << log_types[type] << "]\t" << message << std::endl;
}

void log_int(int type, const char * message, int i)
{
    std::ofstream log_file;
    log_file.open(LOG_PATH, std::ios_base::app);
    log_file << '[' << log_types[type] << "]\t" << message << ' ' << i << std::endl;
    log_file.close();
}

void log_out_int(int type, const char * m1, int i, const char * m2)
{
    std::ofstream log_file;
    log_file.open(LOG_PATH, std::ios_base::app);
    log_file << '[' << log_types[type] << "]\t" << m1 <<' ' << i <<' ' << m2 << std::endl;
    log_file.close();

    std::cout << '[' << log_types[type] << "]\t" << m1 <<' ' << i <<' ' << m2 << std::endl;
}

void log_bin32(int type, const char * message, int bin)
{
    std::ofstream log_file;
    log_file.open(LOG_PATH, std::ios_base::app);
    log_file << '[' << log_types[type] << "]\t" << message << " " << std::bitset<32>(bin) << std::endl;
    log_file.close();
}

void init_log() 
{
    std::ofstream log_file;
    log_file.open(LOG_PATH);

    time_t curtime;
    time(&curtime);
    log_file << ctime(&curtime) << std::endl;

    log_file.close();
}

void end_log()
{
    log(INFO, "Execution finished successfully");
}