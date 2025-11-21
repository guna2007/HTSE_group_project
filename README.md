# Hierarchical Task Scheduling Engine (HTSE)

## Project Documentation

### Team Members

- Kanishka T - CS24B2046
- L Guna - CS24B2043
- B Rakesh - CS24B2039
- I V S Akhil - CS24B2005
- K Siva - CS24B2048

---

## Table of Contents

1. [Introduction](#1-introduction)
   - 1.1 [Project Overview](#11-project-overview)
   - 1.2 [Objectives](#12-objectives)
2. [OOP Features Implementation](#2-oop-features-implementation)
   - 2.1 [Encapsulation](#21-encapsulation)
   - 2.2 [Abstraction](#22-abstraction)
   - 2.3 [Inheritance](#23-inheritance)
   - 2.4 [Polymorphism](#24-polymorphism)
   - 2.5 [Operator Overloading](#25-operator-overloading)
   - 2.6 [Templates](#26-templates)
   - 2.7 [Exception Handling](#27-exception-handling)
3. [System Design](#3-system-design)
   - 3.1 [Architecture Overview](#31-architecture-overview)
   - 3.2 [Class Hierarchy](#32-class-hierarchy)
   - 3.3 [Core Components](#33-core-components)
4. [Implementation Details](#4-implementation-details)
   - 4.1 [Task Management](#41-task-management)
   - 4.2 [Scheduling Strategies](#42-scheduling-strategies)
   - 4.3 [Dependency Resolution](#43-dependency-resolution)
5. [Source Code Samples](#5-source-code-samples)
6. [Project Timeline](#6-project-timeline)
7. [Compilation and Execution](#7-compilation-and-execution)
8. [Testing and Validation](#8-testing-and-validation)
9. [Conclusion](#9-conclusion)

---

## 1. Introduction

### 1.1 Project Overview

The Hierarchical Task Scheduling Engine (HTSE) is a comprehensive C++ application designed to demonstrate advanced Object-Oriented Programming concepts through a practical task management system. The system implements intelligent task scheduling algorithms, hierarchical task relationships, dependency management, and progress tracking with a command-line interface.

**Key Features:**

- Multi-strategy task scheduling (Priority, Deadline, Hierarchical)
- Parent-child task relationships with unlimited nesting depth
- Dependency management with circular dependency detection
- Real-time progress visualization during task execution
- Interactive CLI with input validation and error handling
- Comprehensive operator overloading for intuitive task manipulation
- Generic template utilities for statistics and comparisons

### 1.2 Objectives

#### Primary Objectives

- Demonstrate all seven fundamental OOP concepts in a single cohesive application
- Implement a functional task scheduling system with multiple scheduling strategies
- Provide interactive command-line interface for task management
- Support hierarchical task structures with parent-child relationships
- Handle task dependencies with circular dependency detection

#### Secondary Objectives

- Implement operator overloading for intuitive task manipulation
- Utilize template programming for generic utility functions
- Provide visual progress tracking during task execution
- Ensure clean compilation with zero warnings using strict compiler flags
- Maintain modular, extensible architecture for future enhancements

---

## 2. OOP Features Implementation

This project implements seven fundamental Object-Oriented Programming concepts. Each concept is strategically utilized in specific components of the system to demonstrate both theoretical understanding and practical application.

### 2.1 Encapsulation

**Definition:** Encapsulation is the bundling of data and methods that operate on that data within a single unit (a class), restricting direct access to internal object state.

**Implementation in HTSE:**

The Task class encapsulates all task-related data with private member variables:

```cpp
class Task {
private:
    int id;
    string name;
    int priority;
    int deadline;
    TaskStatus status;
    int estimated_time;
    vector<Task*> subtasks;
    vector<Task*> dependencies;

public:
    int getId() const;
    string getName() const;
    int getPriority() const;
    void addSubtask(Task* t);
    void addDependency(Task* t);
};
```

All member variables are private, accessible only through public getter methods. This prevents external code from directly modifying a task object's state, ensuring data integrity and controlled access.

### 2.2 Abstraction

**Definition:** Abstraction involves hiding complex implementation details and exposing only essential features through simplified interfaces.

**Implementation in HTSE:**

The Scheduler abstract class defines a pure virtual interface for scheduling algorithms:

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

Users interact with the Scheduler interface without needing to understand internal sorting algorithms. The TaskManager's run() method abstracts away all complexity of the CLI loop, input validation, and feature execution behind a simple interface.

### 2.3 Inheritance

**Definition:** Inheritance allows a class to derive properties and behaviors from another class, promoting code reuse and hierarchical relationships.

**Implementation in HTSE:**

Three concrete scheduler classes inherit from the abstract Scheduler base class:

```cpp
class PriorityScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};

class DeadlineScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};

class HierarchicalScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};
```

Each derived class inherits the interface contract from Scheduler and provides its own specific implementation, demonstrating IS-A relationships.

### 2.4 Polymorphism

**Definition:** Polymorphism enables objects of different classes to be treated through a common interface, with behavior determined at runtime.

**Implementation in HTSE:**

The TaskManager uses polymorphism to work with different schedulers via a base class pointer:

```cpp
class TaskManager {
private:
    unique_ptr<Scheduler> current_scheduler;

public:
    void setScheduler(unique_ptr<Scheduler> sched) {
        current_scheduler = move(sched);
    }

    void executeAll() {
        vector<Task*> scheduled = current_scheduler->schedule(tasks);
        executor.runTasks(scheduled);
    }
};
```

Users can switch schedulers dynamically, and the TaskManager calls the correct schedule() method at runtime through dynamic dispatch.

### 2.5 Operator Overloading

**Definition:** Operator overloading allows custom definitions of standard operators for user-defined types, enabling intuitive syntax.

**Implementation in HTSE:**

The Task class overloads 15+ operators for comparisons and arithmetic operations:

```cpp
class Task {
public:
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }

    bool operator>(const Task& other) const {
        return priority > other.priority;
    }

    Task& operator+=(int value) {
        priority = min(10, priority + value);
        return *this;
    }

    Task operator+(int value) const {
        Task temp = *this;
        temp.priority = min(10, priority + value);
        return temp;
    }

    friend ostream& operator<<(ostream& os, const Task& t);
};
```

This enables natural task manipulation like `task1 < task2` for priority comparison and `task += 2` for priority increments.

### 2.6 Templates

**Definition:** Templates enable generic programming by allowing functions and classes to operate with generic types.

**Implementation in HTSE:**

Generic template utilities demonstrate type-independent algorithms:

```cpp
template <typename T>
class Statistics {
public:
    static double average(const vector<T>& data) {
        if (data.empty()) throw runtime_error("Empty dataset");
        T total = accumulate(data.begin(), data.end(), T(0));
        return static_cast<double>(total) / data.size();
    }

    static T median(vector<T> data) {
        if (data.empty()) throw runtime_error("Empty dataset");
        sort(data.begin(), data.end());
        size_t mid = data.size() / 2;
        return (data.size() % 2 == 0)
            ? (data[mid - 1] + data[mid]) / 2
            : data[mid];
    }
};
```

Template classes work with any numeric type (int, double, float) without code duplication.

### 2.7 Exception Handling

**Definition:** Exception handling provides a structured way to handle runtime errors and exceptional conditions.

**Implementation in HTSE:**

Template methods throw exceptions for invalid operations:

```cpp
template <typename T>
static double average(const vector<T>& data) {
    if (data.empty()) {
        throw runtime_error("Cannot calculate average of empty dataset");
    }
    // ... calculation
}

// Usage with exception handling
void TaskManager::statisticsDemo() {
    try {
        vector<int> priorities = {1, 5, 3, 9, 2};
        double avg = Statistics<int>::average(priorities);
        cout << "Average: " << avg << endl;
    } catch (const runtime_error& e) {
        printError(string("Error: ") + e.what());
    }
}
```

Exceptions prevent crashes from invalid operations and provide descriptive error messages.

---

## 3. System Design

### 3.1 Architecture Overview

HTSE follows a layered architecture with clear separation of concerns:

**Presentation Layer:**

- TaskManager CLI interface
- Menu system and user input handling
- Output formatting and visualization

**Business Logic Layer:**

- Scheduling algorithms (Priority, Deadline, Hierarchical)
- Dependency resolution and cycle detection
- Task execution orchestration

**Data Layer:**

- Task entity with hierarchical relationships
- In-memory storage using STL containers
- Smart pointer-based memory management

### 3.2 Class Hierarchy

**Core Classes:**

- Task - Represents individual work items
- TaskManager - Orchestrates the entire system
- TaskExecutor - Handles task execution logic
- Scheduler (Abstract) - Defines scheduling interface
- PriorityScheduler - Priority-based scheduling
- DeadlineScheduler - Deadline-based scheduling
- HierarchicalScheduler - Parent-first scheduling

**Utility Classes:**

- Statistics - Template class for statistical calculations
- Container - Template class for generic storage
- Comparator - Template class for comparison operations
- Pair - Template class for key-value pairs

### 3.3 Core Components

#### Task Class

**Purpose:** Represents a single task with properties and relationships.

**Private Members:**

```cpp
int id;                      // Unique task identifier
string name;                 // Task name/description
int priority;                // Priority level (1-10)
int deadline;                // Days until deadline
TaskStatus status;           // PENDING/RUNNING/COMPLETED
int estimated_time;          // Execution time in units
vector<Task*> subtasks;      // Child tasks
vector<Task*> dependencies;  // Tasks that must complete first
```

**Public Methods:**

- Task construction and initialization
- Getter methods for all properties
- Subtask and dependency management
- Status tracking and execution
- 15+ overloaded operators

#### TaskManager Class

**Purpose:** Central controller managing all tasks and user interaction.

**Private Members:**

```cpp
vector<unique_ptr<Task>> all_tasks;     // Owns all task objects
map<int, Task*> task_map;                // Quick ID lookup
int next_task_id;                        // Auto-increment counter
unique_ptr<Scheduler> current_scheduler; // Polymorphic scheduler
TaskExecutor executor;                   // Execution engine
```

**Key Responsibilities:**

- Task creation and lifecycle management
- User interface and menu presentation
- Input validation and error handling
- Scheduler selection and task execution
- Dependency and cycle detection

#### Scheduler Hierarchy

**Abstract Base Class:**

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

**Concrete Implementations:**

1. **PriorityScheduler** - Sorts tasks by priority (highest first)
2. **DeadlineScheduler** - Sorts tasks by deadline (earliest first)
3. **HierarchicalScheduler** - Executes parent tasks before children

---

## 4. Implementation Details

### 4.1 Task Management

**Task Creation:**
Tasks are created through a factory method in TaskManager:

```cpp
Task* TaskManager::createTask(const string& name, int priority,
                               int deadline, int time) {
    auto task = make_unique<Task>(next_task_id, name, priority,
                                   deadline, time);
    Task* task_ptr = task.get();
    all_tasks.push_back(move(task));
    task_map[next_task_id] = task_ptr;
    next_task_id++;
    return task_ptr;
}
```

**Hierarchical Relationships:**
Tasks support unlimited nesting depth through parent-child relationships:

```cpp
void Task::addSubtask(Task* subtask) {
    subtasks.push_back(subtask);
}

void Task::displayHierarchy(int indent) const {
    // Display current task
    printTaskInfo(indent);
    // Recursively display subtasks
    for (const Task* child : subtasks) {
        child->displayHierarchy(indent + 1);
    }
}
```

### 4.2 Scheduling Strategies

**Priority Scheduler:**
Executes tasks in order of priority (highest to lowest):

```cpp
vector<Task*> PriorityScheduler::schedule(const vector<Task*>& tasks) {
    vector<Task*> sorted = tasks;
    sort(sorted.begin(), sorted.end(),
         [](Task* a, Task* b) { return a->getPriority() > b->getPriority(); });
    return sorted;
}
```

**Deadline Scheduler:**
Executes tasks in order of deadline urgency:

```cpp
vector<Task*> DeadlineScheduler::schedule(const vector<Task*>& tasks) {
    vector<Task*> sorted = tasks;
    sort(sorted.begin(), sorted.end(),
         [](Task* a, Task* b) { return a->getDeadline() < b->getDeadline(); });
    return sorted;
}
```

**Hierarchical Scheduler:**
Executes parent tasks before their children using recursive traversal:

```cpp
void HierarchicalScheduler::collectTasksInOrder(Task* task,
                                                 vector<Task*>& result,
                                                 set<int>& visited) {
    if (visited.count(task->getId())) return;
    visited.insert(task->getId());
    result.push_back(task);

    for (Task* child : task->getSubtasks()) {
        collectTasksInOrder(child, result, visited);
    }
}
```

### 4.3 Dependency Resolution

**Circular Dependency Detection:**
Uses depth-first search with recursion stack tracking:

```cpp
bool TaskManager::detectCycle(Task* start, set<int>& visited,
                               set<int>& rec_stack) const {
    int id = start->getId();

    if (rec_stack.count(id)) return true;  // Cycle detected
    if (visited.count(id)) return false;

    visited.insert(id);
    rec_stack.insert(id);

    for (const Task* dep : start->getDependencies()) {
        if (detectCycle(const_cast<Task*>(dep), visited, rec_stack)) {
            return true;
        }
    }

    rec_stack.erase(id);
    return false;
}
```

**Dependency Validation:**
Before execution, the system checks for circular dependencies and prevents execution if detected.

---

## 5. Source Code Samples

### Sample 1: Task Class - Core Entity

**File:** task.cpp  
**Purpose:** Demonstrates encapsulation and operator overloading.

```cpp
class Task {
private:
    int id;
    string name;
    int priority;
    int deadline;
    TaskStatus status;
    int estimated_time;

public:
    Task(int _id, string _name, int _prio, int _deadline, int _time)
        : id(_id), name(_name), priority(_prio),
          deadline(_deadline), status(PENDING), estimated_time(_time) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getPriority() const { return priority; }

    bool operator<(const Task& other) const {
        return priority < other.priority;
    }

    Task& operator+=(int value) {
        priority = min(10, priority + value);
        return *this;
    }
};
```

**Design Reasoning:**

- Private members protect data integrity
- Const methods prevent accidental modification
- Initializer list ensures efficient initialization
- Operator overloading provides intuitive task manipulation

### Sample 2: Scheduler Abstraction

**File:** scheduler.h  
**Purpose:** Demonstrates abstraction and polymorphism foundation.

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

**Design Reasoning:**

- Pure virtual methods create abstract interface
- No data members, only behavior contract
- Virtual destructor ensures proper cleanup
- Enables runtime polymorphism

### Sample 3: PriorityScheduler Implementation

**File:** priority_scheduler.cpp  
**Purpose:** Demonstrates inheritance and concrete implementation.

```cpp
class PriorityScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override {
        vector<Task*> sorted_tasks = tasks;
        sort(sorted_tasks.begin(), sorted_tasks.end(), comparePriority);
        return sorted_tasks;
    }

    string getName() const override {
        return "Priority Scheduler";
    }

private:
    static bool comparePriority(const Task* a, const Task* b) {
        return a->getPriority() > b->getPriority();
    }
};
```

**Design Reasoning:**

- Inherits from Scheduler base class
- Override keyword ensures method signature matches
- Static comparison function avoids unnecessary object context
- Simple, focused implementation of single responsibility

### Sample 4: Polymorphic Scheduler Selection

**File:** task_manager.cpp  
**Purpose:** Demonstrates runtime polymorphism.

```cpp
void TaskManager::chooseSchedulingStrategy() {
    cout << "\nAvailable Scheduling Strategies:" << endl;
    cout << "1. Priority Scheduler" << endl;
    cout << "2. Deadline Scheduler" << endl;
    cout << "3. Hierarchical Scheduler" << endl;

    int choice = getValidatedInt("\nSelect strategy (1-3): ", 1, 3);

    switch (choice) {
        case 1:
            current_scheduler = make_unique<PriorityScheduler>();
            break;
        case 2:
            current_scheduler = make_unique<DeadlineScheduler>();
            break;
        case 3:
            current_scheduler = make_unique<HierarchicalScheduler>();
            break;
    }

    printSuccess("Scheduler set to: " + current_scheduler->getName());
}
```

**Design Reasoning:**

- Base class pointer holds any derived scheduler
- make_unique ensures exception-safe allocation
- Polymorphic getName() call works on any scheduler type
- Dynamic dispatch determines correct method at runtime

---

## 6. Project Timeline

### Phase 1: Planning and Design (Days 1-3)

**Day 1: Project Setup and Planning**

- Team formation and role assignment
- Requirements gathering and analysis
- High-level architecture design
- Git repository initialization

**Day 2: Detailed Design**

- Class interface definitions
- Scheduler abstraction design
- Data structure selection
- UML diagram creation

**Day 3: Environment Setup**

- Build system configuration
- Coding standards establishment
- Development environment setup
- Project structure creation

### Phase 2: Core Implementation (Days 4-9)

**Day 4: Task Entity Implementation**

- Task class design (task.h/cpp)
- Private member variables
- Public getter methods
- Basic constructors

**Day 5: Operator Overloading**

- Comparison operators (<, >, ==, !=, <=, >=)
- Arithmetic operators (+, -, +=, -=, ++, --)
- Stream insertion operator (<<)

**Day 6: TaskManager Foundation**

- Storage containers (vector, map)
- Menu system implementation
- CLI loop structure
- Basic input handling

**Day 7: Scheduler Abstraction**

- Abstract Scheduler base class
- PriorityScheduler implementation
- DeadlineScheduler implementation

**Day 8: Hierarchical Scheduler**

- Recursive traversal algorithm
- Parent-before-child execution
- Subtask relationship handling

**Day 9: Task Executor**

- Execution logic implementation
- Dependency checking
- Progress animation
- Status tracking

### Phase 3: Advanced Features (Days 10-12)

**Day 10: Template Utilities**

- Statistics template class
- Container template class
- Comparator template class
- Pair template class

**Day 11: Exception Handling**

- Error throwing in templates
- Exception handling in TaskManager
- Input validation improvements

**Day 12: Configuration System**

- config.h creation
- ANSI color code definitions
- UI constants and formatting

### Phase 4: Integration and Testing (Days 13-14)

**Day 13: Integration Testing**

- Build verification
- Feature testing (all 13 menu options)
- Edge case identification
- Bug fixing

**Day 14: Polish and Refinement**

- Code formatting standardization
- Comment enhancement
- Warning elimination
- Performance optimization

### Phase 5: Documentation and Delivery (Day 15)

**Day 15: Final Documentation**

- README.md creation
- Technical documentation
- Presentation preparation
- Final code review

**Project Milestones:**

- **Milestone 1 (End of Day 3):** Design complete, development environment ready
- **Milestone 2 (End of Day 6):** Core Task and TaskManager classes implemented, basic menu working
- **Milestone 3 (End of Day 9):** All schedulers and executor complete, core features functional
- **Milestone 4 (End of Day 12):** Templates implemented, configuration system working, full feature set complete
- **Milestone 5 (End of Day 15):** Documentation complete, project ready for delivery

---

## 7. Compilation and Execution

### Build Command

```bash
g++ -std=c++17 src/*.cpp -o htse.exe
```

### Strict Build (with warnings)

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic src/*.cpp -o htse.exe
```

### Execution

```bash
./htse.exe
```

### Project Structure

```
OOPs-Proj/
├── src/
│   ├── main.cpp
│   ├── task.h
│   ├── task.cpp
│   ├── task_manager.h
│   ├── task_manager.cpp
│   ├── task_executor.h
│   ├── task_executor.cpp
│   ├── scheduler.h
│   ├── priority_scheduler.h
│   ├── priority_scheduler.cpp
│   ├── deadline_scheduler.h
│   ├── deadline_scheduler.cpp
│   ├── hierarchical_scheduler.h
│   ├── hierarchical_scheduler.cpp
│   ├── template_utils.h
│   └── config.h
├── docs/
│   ├── README.md
│   ├── 1_introduction.md
│   ├── 2_oop_features.md
│   ├── 3_system_design.md
│   ├── 4_source_code.md
│   └── 5_conclusion_timeline.md
└── cmds.txt
```

---

## 8. Testing and Validation

### Functional Testing

**All 13 menu options verified:**

1. Add New Task
2. Add Subtask
3. Set Task Dependency
4. Choose Scheduling Strategy
5. Display Task Hierarchy
6. Execute All Tasks
7. View Execution Report
8. Compare Tasks (Operators)
9. Modify Task Priority (Operators)
10. Display Tasks (<< Operator)
11. Task Statistics (Template)
12. Generic Container Demo (Template)
13. Generic Comparator Demo (Template)

### Edge Case Testing

**Tested Scenarios:**

- Invalid input handling (non-numeric, out-of-range)
- Self-subtask error detection
- Self-dependency error detection
- Invalid task ID handling
- Empty dataset operations
- Circular dependency detection
- Empty task list execution

### Code Quality Metrics

**Compilation:**

- C++17 standard compliance
- Zero warnings with strict flags (-Wall -Wextra -Wpedantic)
- Clean compilation verified

**Memory Safety:**

- Smart pointer usage (unique_ptr) for automatic memory management
- No manual new/delete operations
- RAII principles followed throughout

**Code Statistics:**

- Total Source Files: 16
- Total Lines of Code: 1,865
- Header Files: 8
- Implementation Files: 8

---

## 9. Conclusion

### Project Summary

The Hierarchical Task Scheduling Engine successfully demonstrates comprehensive object-oriented programming concepts through a practical command-line application. The system manages tasks with hierarchical organization, dependency tracking, and multiple scheduling strategies.

**Key Achievements:**

1. **Complete OOP Demonstration:** All seven OOP concepts (Encapsulation, Abstraction, Inheritance, Polymorphism, Operator Overloading, Templates, Exception Handling) implemented and integrated.

2. **Functional System:** Fully working task management system with 13 interactive features accessible through an intuitive CLI.

3. **Robust Architecture:** Modular design with clear separation of concerns, enabling easy extension and maintenance.

4. **Quality Assurance:** Zero-warning compilation with strict compiler flags, comprehensive edge case handling, and proper memory management.

5. **Professional Documentation:** Complete technical documentation covering design decisions, implementation details, and usage instructions.

### Technical Highlights

**Strengths:**

1. **Modular Design:** Clear separation of concerns with distinct classes for tasks, scheduling, and execution.

2. **Extensibility:** Abstract Scheduler interface allows easy addition of new scheduling algorithms.

3. **Usability:** Colored output and progress animations enhance user experience.

4. **Code Quality:** Clean compilation with zero warnings reflects attention to modern C++ standards.

5. **Educational Value:** Project serves as comprehensive reference for OOP concepts in C++.

### Learning Outcomes

This project demonstrates that OOP principles are not merely theoretical concepts but powerful tools for building robust, maintainable software. The combination of practical functionality with academic rigor provides a solid foundation for understanding advanced programming paradigms.

**Skills Developed:**

- Object-oriented design and implementation
- Template metaprogramming
- Memory management with smart pointers
- Algorithm design and optimization
- Software architecture and design patterns
- Testing and quality assurance

### Future Enhancements

Potential extensions to the system:

- Persistent storage with file I/O
- Multi-threading for parallel task execution
- Network-based distributed scheduling
- GUI interface using Qt or similar framework
- Advanced scheduling algorithms (genetic algorithms, machine learning)

---

**Project Completion Date:** Day 15  
**Final Status:** All objectives met, system fully functional and documented  
**Compilation Status:** Clean build with zero warnings  
**Test Coverage:** All features and edge cases validated

---

_This documentation represents the complete technical specification and implementation guide for the Hierarchical Task Scheduling Engine project._
