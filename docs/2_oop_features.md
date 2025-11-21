# 2. OOP FEATURES IMPLEMENTATION

## Overview

This project implements all seven fundamental Object-Oriented Programming concepts. Each concept is strategically utilized in specific components demonstrating both theoretical understanding and practical application.

## 1. Encapsulation

### Definition

Bundling data and methods within a single unit, restricting direct access to internal state.

### Implementation

**Task Class:**

```cpp
class Task {
private:
    int id, priority, deadline, estimated_time;
    string name;
    TaskStatus status;
    vector<Task*> subtasks, dependencies;
public:
    int getId() const;
    string getName() const;
    void addSubtask(Task* t);
};
```

All members private, accessible only through public methods ensuring data integrity.

## 2. Abstraction

### Definition

Hiding complex implementation details, exposing only essential features.

### Implementation

**Scheduler Interface:**

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

Users interact without understanding internal sorting algorithms.

## 3. Inheritance

### Definition

Deriving properties and behaviors from parent class, promoting code reuse.

### Implementation

**Scheduler Hierarchy:**

```cpp
class PriorityScheduler : public Scheduler {
    vector<Task*> schedule(const vector<Task*>& tasks) override;
    string getName() const override;
};

class DeadlineScheduler : public Scheduler { /* ... */ };
class HierarchicalScheduler : public Scheduler { /* ... */ };
```

Three concrete schedulers inherit from abstract base.

## 4. Polymorphism

### Definition

Objects of different classes treated through common interface, behavior determined at runtime.

### Implementation

**Runtime Scheduler Selection:**

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
    }
};
```

Actual algorithm determined at runtime based on user selection.

## 5. Operator Overloading

### Definition

Custom definitions of standard operators for user-defined types.

### Implementation

**Task Comparison:**

```cpp
bool Task::operator<(const Task& other) const {
    return this->priority < other.priority;
}

Task Task::operator+(int value) const {
    Task result = *this;
    result.priority = min(10, max(1, this->priority + value));
    return result;
}

Task& Task::operator++() {
    if (priority < 10) priority++;
    return *this;
}
```

Usage: `if (t1 > t2) { }`, `t1 += 2;`, `++t1;`, `Task t3 = t1 + 5;`

## 6. Templates

### Definition

Generic code working with any data type, promoting reusability and type safety.

### Implementation

**Statistics Template:**

```cpp
template <typename T>
class Statistics {
public:
    static double average(const vector<T>& data);
    static T median(vector<T> data);
    static T range(const vector<T>& data);
};
```

**Container Template:**

```cpp
template <typename T>
class Container {
    vector<T> items;
public:
    void add(const T& item);
    void display() const;
    T get(size_t index) const;
};
```

Usage with multiple types: `Statistics<int>`, `Container<string>`

## 7. Exception Handling

### Definition

Mechanism to handle runtime errors gracefully.

### Implementation

**Template Operations:**

```cpp
template <typename T>
static T median(vector<T> data) {
    try {
        if (data.empty()) {
            throw runtime_error("Cannot calculate median of empty dataset");
        }
        sort(data.begin(), data.end());
        return data[data.size() / 2];
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return T();
    }
}
```

Prevents crashes, provides informative error messages.

## Summary

| OOP Concept          | Primary Implementation        | Files                  |
| -------------------- | ----------------------------- | ---------------------- |
| Encapsulation        | Task, TaskManager             | task._, task_manager._ |
| Abstraction          | Scheduler interface           | scheduler.h            |
| Inheritance          | Scheduler hierarchy           | _\_scheduler._         |
| Polymorphism         | Runtime scheduler selection   | task_manager.cpp       |
| Operator Overloading | Task operators                | task.\*                |
| Templates            | Generic utilities             | template_utils.h       |
| Exception Handling   | Error management in templates | template_utils.h       |
