#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局调试日志控制
#ifndef DEBUG_LOG_ENABLED
#define DEBUG_LOG_ENABLED 1  // 默认启用，可通过编译时 -DDEBUG_LOG_ENABLED=0 禁用
#endif

#if DEBUG_LOG_ENABLED
#define DEBUG_LOG(module, fmt, ...) do { \
    static int debug_checked = 0; \
    static int debug_enabled = 0; \
    if (!debug_checked) { \
        const char *env = getenv("ESPEAK_DEBUG"); \
        debug_enabled = (env && (strcmp(env, "true") == 0 || strcmp(env, "TRUE") == 0 || strcmp(env, "1") == 0)); \
        debug_checked = 1; \
    } \
    if (debug_enabled) { \
        fprintf(stderr, "[DEBUG-%s] %s:%d: ", module, __FILE__, __LINE__); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
    } \
} while(0)
#else
#define DEBUG_LOG(module, fmt, ...)
#endif

// 为各个模块定义专用的调试宏
#define DEBUG_LOG_SYNTHESIZE(fmt, ...) DEBUG_LOG("SYNTHESIZE", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_SPEECH(fmt, ...) DEBUG_LOG("SPEECH", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_VOICES(fmt, ...) DEBUG_LOG("VOICES", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_INTONATION(fmt, ...) DEBUG_LOG("INTONATION", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_WAVEGEN(fmt, ...) DEBUG_LOG("WAVEGEN", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_READCLAUSE(fmt, ...) DEBUG_LOG("READCLAUSE", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_DICTIONARY(fmt, ...) DEBUG_LOG("DICTIONARY", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_TRANSLATE(fmt, ...) DEBUG_LOG("TRANSLATE", fmt, ##__VA_ARGS__)
#define DEBUG_LOG_ESPEAK(fmt, ...) DEBUG_LOG("ESPEAK", fmt, ##__VA_ARGS__)

#endif // DEBUG_LOG_H