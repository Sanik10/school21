#include "logger.h"

FILE *log_init(char *filename) {
    FILE *logfile = fopen(filename, "a");
    if (logfile == NULL) {
        perror("Error opening log file");
        logfile = fopen(filename, "w");
    }
    return logfile;
}

int logcat(FILE *log_file, char *message, log_level level) {
    if (log_file == NULL) {
        return 1;
    }

    char *level_str;
    switch (level) {
        case debug:
            level_str = "DEBUG";
            break;
        case trace:
            level_str = "TRACE";
            break;
        case info:
            level_str = "INFO";
            break;
        case warning:
            level_str = "WARNING";
            break;
        case error:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }

    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char timestr[20];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(log_file, "[%s] [%s] %s\n", timestr, level_str, message);
    fflush(log_file);
    return 0;
}

int log_close(FILE *log_file) {
    if (log_file != NULL) {
        return fclose(log_file);
    }
    return 0;
}