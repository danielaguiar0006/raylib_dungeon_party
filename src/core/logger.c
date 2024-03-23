#include "logger.h"

b8 initialize_logging() {
    // TODO: create log file
    return TRUE;
}

void shutdown_logging() {
    // TODO: cleanup logging/write queued entries
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = { "[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: " };

    char out_message[32000];
    va_list args;
    va_start(args, message);
    vsnprintf(out_message, sizeof(out_message), message, args);
    va_end(args);

    char out_message2[32000];
    snprintf(out_message2, sizeof(out_message2), "%s%s\n", level_strings[level], out_message);

    // Output to console
    printf("%s", out_message2);
}
