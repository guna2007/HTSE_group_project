# 4. SOURCE CODE SAMPLES

Representative code samples with design explanations.

## Sample 1: Task Class - Encapsulation

```cpp
class Task {
private:
    int id, priority, deadline, estimated_time;
    string name;
    TaskStatus status;
    vector<Task*> subtasks, dependencies;
public:
    Task(int _id, string _name, int _prio, int _deadline, int _time)
        : id(_id), name(_name), priority(_prio),
          deadline(_deadline), status(PENDING), estimated_time(_time) {}

    int getId() const { return id; }
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};
```

Private members with public accessors enforce encapsulation.

## Sample 2: Scheduler Abstraction

```cpp
class Scheduler {
public:
    virtual vector<Task*> schedule(const vector<Task*>& tasks) = 0;
    virtual string getName() const = 0;
    virtual ~Scheduler() {}
};
```

Pure virtual interface enables polymorphism.

## Sample 3: PriorityScheduler

```cpp
class PriorityScheduler : public Scheduler {
public:
    vector<Task*> schedule(const vector<Task*>& tasks) override {
        vector<Task*> sorted = tasks;
        sort(sorted.begin(), sorted.end(), comparePriority);
        return sorted;
    }
    string getName() const override { return "Priority Scheduler"; }
private:
    static bool comparePriority(const Task* a, const Task* b) {
        return a->getPriority() > b->getPriority();
    }
};
```

Inheritance with concrete implementation.

## Sample 4: Polymorphic Scheduler Selection

```cpp
void TaskManager::chooseSchedulingStrategy() {
    int choice = getValidatedInt("Select strategy (1-3): ", 1, 3);
    switch (choice) {
        case 1: current_scheduler = make_unique<PriorityScheduler>(); break;
        case 2: current_scheduler = make_unique<DeadlineScheduler>(); break;
        case 3: current_scheduler = make_unique<HierarchicalScheduler>(); break;
    }
    printSuccess("Scheduler: " + current_scheduler->getName());
}
```

Runtime polymorphism with base class pointer.

## Sample 5: Template Statistics

```cpp
template <typename T>
class Statistics {
public:
    static double average(const vector<T>& data) {
        if (data.empty()) throw runtime_error("Empty dataset");
        T total = 0;
        for (const T& val : data) total += val;
        return static_cast<double>(total) / data.size();
    }

    static T median(vector<T> data) {
        if (data.empty()) throw runtime_error("Empty dataset");
        sort(data.begin(), data.end());
        return data[data.size() / 2];
    }
};
```

Generic programming with exception handling.

## Sample 6: Progress Animation

```cpp
void TaskExecutor::showProgressAnimation(Task* task, int indent) {
    int steps = 20;
    string indentation(indent * 2, ' ');
    output << indentation << "Progress: [";
    output.flush();  // Critical for real-time display

    for (int i = 0; i < steps; i++) {
        output << "=";
        output.flush();
        Sleep(task->getEstimatedTime() * EXEC_DELAY_MS / steps);
    }
    output << "] 100%" << endl;
}
```

Output flushing enables incremental progress display.

## Sample 7: Color Configuration

```cpp
#define ENABLE_COLOR 1

#if ENABLE_COLOR
    #define COLOR_GREEN "\033[1;32m"
    #define COLOR_RED "\033[1;31m"
    #define COLOR_RESET "\033[0m"
#else
    #define COLOR_GREEN ""
    #define COLOR_RED ""
    #define COLOR_RESET ""
#endif

// Usage
cout << COLOR_GREEN << "Success!" << COLOR_RESET << endl;
```

Preprocessor-based color management.

## Sample 8: Circular Dependency Detection

```cpp
bool TaskManager::detectCycle(Task* start, set<int>& visited,
                               set<int>& rec_stack) const {
    int id = start->getId();
    visited.insert(id);
    rec_stack.insert(id);

    for (Task* dep : start->getDependencies()) {
        if (rec_stack.find(dep->getId()) != rec_stack.end())
            return true;  // Cycle detected
        if (visited.find(dep->getId()) == visited.end())
            if (detectCycle(dep, visited, rec_stack))
                return true;
    }
    rec_stack.erase(id);
    return false;
}
```

DFS-based cycle detection prevents infinite loops.

## Sample 9: Input Validation

```cpp
int TaskManager::getValidatedInt(const string& prompt, int min, int max) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value < min || value > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[!] Invalid! Enter " << min << "-" << max << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}
```

Robust handling of invalid input.

## Sample 10: Operator Overloading Demo

```cpp
void TaskManager::modifyTaskPriorityDemo() {
    Task* task = findTaskById(id);
    cout << "[Before] Priority: " << task->getPriority() << endl;

    Task temp = *task + 2;  // operator+
    cout << "[After +2] Priority: " << temp.getPriority() << endl;

    *task += 1;  // operator+=
    cout << "[After +=1] Priority: " << task->getPriority() << endl;

    (*task)++;  // operator++
    cout << "[After ++] Priority: " << task->getPriority() << endl;
}
```

Demonstrates intuitive task manipulation.

## Sample 11: Smart Pointer Usage

```cpp
class TaskManager {
private:
    vector<unique_ptr<Task>> all_tasks;
    unique_ptr<Scheduler> current_scheduler;
};

Task* TaskManager::createTask(string name, int priority, int deadline, int time) {
    auto task = make_unique<Task>(next_task_id++, name, priority, deadline, time);
    Task* task_ptr = task.get();
    all_tasks.push_back(move(task));
    return task_ptr;
}
```

Automatic memory management with smart pointers.
