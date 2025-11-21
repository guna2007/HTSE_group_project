# 1. INTRODUCTION

## Project Overview

The Hierarchical Task Scheduling Engine (HTSE) is a C++ application demonstrating Object-Oriented Programming concepts through a task management system with intelligent scheduling, hierarchical relationships, and dependency management.

## Team Members

| S.No | Name          | Role                | Responsibilities                        |
| ---- | ------------- | ------------------- | --------------------------------------- |
| 1    | Team Member 1 | Team Lead           | Architecture, scheduler implementations |
| 2    | Team Member 2 | Core Developer      | Task class, operator overloading        |
| 3    | Team Member 3 | Backend Developer   | TaskManager, dependency management      |
| 4    | Team Member 4 | Template Specialist | Generic programming, templates          |
| 5    | Team Member 5 | Testing Lead        | Test cases, execution framework         |

## Objectives

### Primary Goals

1. Demonstrate all seven OOP concepts in a cohesive application
2. Implement functional task scheduling with multiple strategies
3. Provide interactive CLI for task management
4. Support hierarchical task structures with dependencies
5. Handle circular dependency detection

### Secondary Goals

1. Implement operator overloading for task manipulation
2. Utilize template programming for generic utilities
3. Provide visual progress tracking during execution
4. Ensure clean compilation with zero warnings

## System Features

### Core Functionality

- Task creation with priority, deadline, and execution time
- Hierarchical task organization with parent-child relationships
- Dependency management with cycle detection
- Three scheduling algorithms: Priority, Deadline, Hierarchical
- Visual execution with animated progress bars
- Comprehensive execution reports with statistics

### User Interface

Interactive menu with 13 options:

- Tasks: Create, add subtasks, set dependencies
- Scheduling: Choose strategy, display hierarchy, execute
- Operators: Compare tasks, modify priority, display
- Templates: Statistics, container, comparator demos

## Technical Specifications

### Language and Tools

- C++17 Standard
- GCC/G++ 7.0 or higher
- Compile: `g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o htse.exe`
- Zero warnings compilation

### Project Statistics

- Total Files: 16
- Lines of Code: 1,865
- Implementation Files: 8 (.cpp)
- Header Files: 8 (.h)
- Classes: 8
- Template Classes: 3

### Platform Support

- Primary: Windows (MinGW-w64)
- Secondary: Linux (GCC), macOS (Clang)
- Terminal: Bash shell

### Dependencies

C++ Standard Library only:

- iostream, vector, string, memory, algorithm
- map, set, iomanip
- windows.h (Sleep function for Windows)

### Color Support

ANSI color codes for terminal output:

- Cyan: Headers
- Green: Success messages
- Yellow: Warnings
- Red: Errors
- Blue: Running status
- Magenta: Progress

Disable with ENABLE_COLOR flag in config.h.

## Problem Statement

Traditional task systems lack comprehensive OOP demonstration. This project addresses:

1. Showcasing all fundamental OOP concepts
2. Implementing design patterns (Strategy Pattern)
3. Demonstrating generic programming
4. Handling complex hierarchies and dependencies
5. Educational tool for OOP principles

## Scope

### In Scope

- Task creation and management
- Hierarchical organization with unlimited nesting
- Dependency management with cycle detection
- Three scheduling algorithms
- Visual execution tracking
- Template-based utilities
- Operator overloading
- Exception handling

### Out of Scope

- Persistent storage
- Multi-user support
- Network communication
- Graphical interface
- Real-time system process execution
- External tool integration

## Expected Outcomes

1. All seven OOP concepts demonstrated
2. Clean compilation with zero warnings
3. Graceful edge case handling
4. Intuitive user interface
5. Correct task execution based on dependencies
6. Comprehensive execution statistics
7. Educational reference for C++ OOP
