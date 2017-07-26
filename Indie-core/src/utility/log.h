#pragma once

#include <stdio.h>

//TODO:
// write a better log system!

#define INDIE_ASSERT(fmt, mess) \
do \
{ \
	if(!(fmt)) \
	{ \
		char* fp = __FILE__; \
		unsigned int lastSepaPos = 0; \
		char* c; \
		for (c = fp; *c != '\0'; c++) \
		{ \
			if (*c == '\\' || *c == '/') \
				lastSepaPos = c - fp; \
		} \
		printf("\n"); \
		printf("*************************\n"); \
		printf("    ASSERTION FAILED!    \n"); \
		printf("*************************\n"); \
		printf("%s\n", #fmt); \
		printf("%s", mess); \
		printf("-> "); \
		for (int i = lastSepaPos + 1; i < c - fp; i++) \
			printf("%c", fp[i]); \
		printf(":%d\n", __LINE__); \
		abort(); \
	} \
} while (0)

#define INDIE_LOG_LEVEL_FATAL 0
#define INDIE_LOG_LEVEL_ERROR 1
#define INDIE_LOG_LEVEL_WARN  2
#define INDIE_LOG_LEVEL_INFO  3

#ifndef INDIE_LOG_LEVEL
	#define INDIE_LOG_LEVEL INDIE_LOG_LEVEL_INFO
#endif

#if INDIE_LOG_LEVEL >= INDIE_LOG_LEVEL_FATAL
#define INDIE_FATAL(fmt, ...) do { printf("[INDIE][FATAL]: "); printf(fmt, __VA_ARGS__); printf("\n"); INDIE_ASSERT(false, "");} while (0)
#else
	#define INDIE_FATAL(fmt, ...)
#endif
#if INDIE_LOG_LEVEL >= INDIE_LOG_LEVEL_ERROR
	#define INDIE_ERROR(fmt, ...) do { printf("[INDIE][ERROR]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)
#else
	#define INDIE_ERROR(fmt, ...)
#endif
#if INDIE_LOG_LEVEL >= INDIE_LOG_LEVEL_WARN
	#define INDIE_WARN(fmt, ...)  do { printf("[INDIE][WARN]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)
#else
	#define INDIE_WARN(fmt, ...)
#endif
#if INDIE_LOG_LEVEL >= INDIE_LOG_LEVEL_INFO
	#define INDIE_INFO(fmt, ...)  do { printf("[INDIE][INFO]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)
#else
	#define INDIE_INFO(fmt, ...)
#endif
