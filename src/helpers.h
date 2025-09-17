// ---- spdlog config ----
#define SPDLOG_HEADER_ONLY
#define SPDLOG_NO_ATOMIC_LEVELS
#define SPDLOG_NO_THREAD_ID
#define SPDLOG_DEBUG_ON 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


// Short-hand logging macros
#define LOG_TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_DEBUG(...)  SPDLOG_DEBUG(__VA_ARGS__)
#define LOG_WARN(...)  SPDLOG_WARN(__VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_CRIT(...)  SPDLOG_CRITICAL(__VA_ARGS__)