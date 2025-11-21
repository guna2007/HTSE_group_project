#ifndef CONFIG_H
#define CONFIG_H

#ifndef ENABLE_COLOR
#define ENABLE_COLOR 1
#endif

// Delay in milliseconds for task execution animation
#ifndef EXEC_DELAY_MS
#define EXEC_DELAY_MS 500
#endif

// ANSI escape codes for colored terminal output
#if ENABLE_COLOR
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RED "\033[1;31m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"

#endif

//  UI CONSTANTS
#define UI_WIDTH 62
#define UI_BORDER "+============================================================+"
#define UI_LINE "+--------------------------------------------------------------+"

#endif // CONFIG_H
