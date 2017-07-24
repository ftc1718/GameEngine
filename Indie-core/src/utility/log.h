#pragma once

#include <stdio.h>

#define INDIE_FATAL(fmt, ...) do { printf("[INDIE][FATAL]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)
#define INDIE_ERROR(fmt, ...) do { printf("[INDIE][ERROR]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)
#define INDIE_WARN(fmt, ...)  do { printf("[INDIE][WARN]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)
#define INDIE_INFO(fmt, ...)  do { printf("[INDIE][INFO]: "); printf(fmt, __VA_ARGS__); printf("\n"); } while (0)