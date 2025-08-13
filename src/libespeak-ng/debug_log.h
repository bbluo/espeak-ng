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
// 检查特定模块是否启用调试
static inline int is_debug_enabled(const char* module) {
    static int global_checked = 0;
    static int global_enabled = 0;
    static int synthesize_checked = 0;
    static int synthesize_enabled = 0;
    static int translate_checked = 0;
    static int translate_enabled = 0;
    static int speech_checked = 0;
    static int speech_enabled = 0;
    static int intonation_checked = 0;
    static int intonation_enabled = 0;
    
    // 检查全局调试开关
    if (!global_checked) {
        const char *env = getenv("ESPEAK_DEBUG");
        global_enabled = (env && (strcmp(env, "true") == 0 || strcmp(env, "TRUE") == 0 || strcmp(env, "1") == 0));
        global_checked = 1;
    }
    
    if (!global_enabled) return 0;
    
    // 检查模块特定的调试开关
    if (strcmp(module, "SYNTHESIZE") == 0) {
        if (!synthesize_checked) {
            const char *env = getenv("ESPEAK_DEBUG_SYNTHESIZE");
            // 默认关闭SYNTHESIZE详细日志，除非明确启用
            synthesize_enabled = (env && (strcmp(env, "true") == 0 || strcmp(env, "TRUE") == 0 || strcmp(env, "1") == 0));
            synthesize_checked = 1;
        }
        return synthesize_enabled;
    } else if (strcmp(module, "TRANSLATE") == 0) {
        if (!translate_checked) {
            const char *env = getenv("ESPEAK_DEBUG_TRANSLATE");
            // 默认启用TRANSLATE日志，除非明确禁用
            translate_enabled = !(env && (strcmp(env, "false") == 0 || strcmp(env, "FALSE") == 0 || strcmp(env, "0") == 0));
            translate_checked = 1;
        }
        return translate_enabled;
    } else if (strcmp(module, "SPEECH") == 0) {
        if (!speech_checked) {
            const char *env = getenv("ESPEAK_DEBUG_SPEECH");
            // 默认启用SPEECH日志，除非明确禁用
            speech_enabled = !(env && (strcmp(env, "false") == 0 || strcmp(env, "FALSE") == 0 || strcmp(env, "0") == 0));
            speech_checked = 1;
        }
        return speech_enabled;
    } else if (strcmp(module, "INTONATION") == 0) {
        if (!intonation_checked) {
            const char *env = getenv("ESPEAK_DEBUG_INTONATION");
            // 默认启用INTONATION日志，除非明确禁用
            intonation_enabled = !(env && (strcmp(env, "false") == 0 || strcmp(env, "FALSE") == 0 || strcmp(env, "0") == 0));
            intonation_checked = 1;
        }
        return intonation_enabled;
    }
    
    // 其他模块默认启用
    return 1;
}

#define DEBUG_LOG(module, fmt, ...) do { \
    if (is_debug_enabled(module)) { \
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