# 3. SYSTEM DESIGN

## Architecture Overview

The system follows a modular architecture with clear separation of concerns using Model-View-Controller pattern adapted for CLI.

## Core Classes

1. **Task** - Individual work items
2. **TaskManager** - System orchestrator
3. **TaskExecutor** - Execution engine
4. **Scheduler** (Abstract) - Scheduling interface
5. **PriorityScheduler** - Priority-based scheduling
6. **DeadlineScheduler** - Deadline-based scheduling
7. **HierarchicalScheduler** - Hierarchy-based scheduling

## Utility Classes

1. **Statistics** - Template for statistical calculations
2. **Container** - Template for generic storage
3. **Comparator** - Template for comparison operations

## Class Details

### Task Class

**Files:** task.h, task.cpp (378 LOC)

**Members:**

- `int id, priority, deadline, estimated_time`
- `string name`
- `TaskStatus status`
- `vector<Task*> subtasks, dependencies`

**Methods:**

- Getters: `getId()`, `getName()`, `getPriority()`, etc.
- Relationships: `addSubtask()`, `addDependency()`
- State: `isReady()`, `execute()`, `markComplete()`
- Display: `displayInfo()`, `displayHierarchy()`
- Operators: `<`, `>`, `==`, `+`, `+=`, `++`, etc.

### TaskManager Class

**Files:** task_manager.h, task_manager.cpp (733 LOC)

**Members:**

- `vector<unique_ptr<Task>> all_tasks`
- `map<int, Task*> task_map`
- `unique_ptr<Scheduler> current_scheduler`
- `TaskExecutor executor`

**Methods:**

- UI: `printHeader()`, `printMenu()`, `displayMenu()`
- Features: `addNewTask()`, `addSubtaskToTask()`, `setTaskDependency()`
- Scheduling: `chooseSchedulingStrategy()`, `executeAllTasks()`
- Demos: `compareTasksDemo()`, `statisticsDemo()`, etc.
- Validation: `findTaskById()`, `hasCircularDependencies()`

### TaskExecutor Class

**Files:** task_executor.h, task_executor.cpp (203 LOC)

**Methods:**

- `runTasks()` - Execute scheduled tasks
- `showProgressAnimation()` - Visual progress
- `executeTaskWithSubtasks()` - Recursive execution

### Scheduler Classes

**Scheduler (Abstract):**

```cpp
class Scheduler {
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
};
```

**PriorityScheduler:** Sorts by priority (highest first)

**DeadlineScheduler:** Sorts by deadline (earliest first)

**HierarchicalScheduler:** Depth-first traversal respecting hierarchy

## Data Structures

### Storage Strategy

1. `vector<unique_ptr<Task>>` - Task ownership
2. `map<int, Task*>` - Fast O(log n) lookup
3. `set<int>` - Cycle detection tracking

### Relationships

- **Composition:** TaskManager HAS-A TaskExecutor
- **Inheritance:** Schedulers IS-A Scheduler
- **Aggregation:** Task HAS-A vector of subtasks

## Control Flow

### Program Execution

1. `main()` creates TaskManager
2. `run()` starts CLI loop
3. Display menu, get choice
4. Execute selected feature
5. Repeat until exit

### Task Execution

1. User selects "Execute All Tasks"
2. Scheduler sorts tasks
3. TaskExecutor processes sorted list
4. Check dependencies for each task
5. Execute ready tasks with progress animation
6. Mark complete, update statistics

### Dependency Resolution

1. Check circular dependencies using DFS
2. If cycle found, abort with error
3. For each task, verify `isReady()`
4. Task ready when all dependencies completed
5. Defer unready tasks to next pass

## Build Configuration

**Compile Command:**

```bash
g++ -std=c++17 -Wall -Wextra -O2 src/*.cpp -o htse.exe
```

**Features:**

- All 13 menu options
- Polymorphic scheduler selection
- Full template demonstrations
- Zero warnings compilation

## Implementation Details

### Progress Animation

```cpp
void showProgressAnimation(Task* task, int indent) {
    output << "Progress: [";
    output.flush();  // Force immediate display
    for (int i = 0; i < steps; i++) {
        output << "=";
        output.flush();
        Sleep(delayPerStep);
    }
    output << "] 100%" << endl;
}
```

### Memory Management

Smart pointers prevent leaks:

- `unique_ptr<Task>` - Automatic cleanup
- `unique_ptr<Scheduler>` - RAII principle

### Input Validation

```cpp
int getValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (!(cin >> value) || value < min || value > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[!] Invalid! Enter " << min << "-" << max << ": ";
    }
    return value;
}
```

Prevents crashes from invalid input.
