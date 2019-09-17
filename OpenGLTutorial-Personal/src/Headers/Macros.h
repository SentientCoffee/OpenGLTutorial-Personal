#ifndef MACROS_H
#define MACROS_H


#include <windows.h>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

#if _DEBUG

#define DEBUG_LOG(message, ...)			printf(message, ##__VA_ARGS__)

#define DEBUG_LOG_N(message, ...)		printf(message, ##__VA_ARGS__); printf("\n")

#define DEBUG_LOG_ERROR(message, ...)	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);\
										printf(message, ##__VA_ARGS__);\
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);\
										printf("\n")

#define SYS_EXIT(code)					system("pause"); exit(code)

#else

#define DEBUG_LOG						__noop
#define DEBUG_LOG_N						__noop
#define DEBUG_LOG_ERROR					__noop
#define SYS_EXIT						__noop

#endif


// This piece of code was given to us by Shawn Matthews
// Auto-magically changes OpenGL to use the high performance GPU to render rather than the iGPU
// (for dual GPU systems)
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x01;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x01;
}


#endif