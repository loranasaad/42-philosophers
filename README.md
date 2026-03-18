*This project has been created as part of the 42 curriculum by loasaad.*

# Philosophers — I never thought philosophy would be so deadly

A simulation of the dining philosophers problem in C using threads and mutexes.

## Overview

**Philosophers** is a 42 project that teaches the fundamentals of concurrent programming. N philosophers sit at a round table with N forks. Each philosopher needs two forks to eat, creating a classic deadlock scenario that must be solved with careful synchronization.

The simulation stops when a philosopher dies of starvation, or when all philosophers have eaten the required number of times.

This repository contains the **mandatory part only**. No bonus features are included.

## Features

- Each philosopher runs as a separate thread
- Each fork is protected by a mutex to prevent data races
- A dedicated monitor thread checks for death and meal completion
- Even/odd philosopher fork-pickup ordering to avoid deadlock
- Configurable thinking delay for odd philosopher counts
- Death detection within 10ms as required by the subject

## Arguments
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` (ms) | Time since last meal before a philosopher dies |
| `time_to_eat` (ms) | Time it takes to eat (holds two forks) |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional — simulation stops when all have eaten this many times |

## Build
```bash
make
```
```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # fclean + compile
```

## Usage
```bash
./philo 5 800 200 200
./philo 5 800 200 200 3
```

## Output Format

Every state change is logged as:
```
timestamp_in_ms philosopher_id state
```

Examples:
```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
800 2 died
```

## Project Structure
```
philo/
├── philo.h         # structs, typedefs, function prototypes
├── philo.c         # main entry point
├── parse.c         # argument parsing and validation
├── init.c          # mutex and philosopher initialization
├── dinner.c        # thread routines, fork pickup, sleep/think logic
├── monitor.c       # death detection and meal limit monitoring
├── utils.c         # get_time, print_status, simulation_ended
├── cleanup.c       # mutex destruction and memory cleanup
└── Makefile
```

## Testing
```bash
./philo 1 800 200 200        # one philosopher — should die
./philo 5 800 200 200        # should never die
./philo 5 800 200 200 7      # stops after each philosopher eats 7 times
./philo 4 410 200 200        # tight timing — should survive
./philo 4 310 200 100        # should result in a death
```

Also test:
- invalid or negative arguments
- zero philosophers
- very large numbers
- memory leaks with valgrind

## Notes

- Global variables are forbidden — a single `t_table` struct is passed by pointer throughout
- The subject requires no data races — all shared state is mutex-protected
- `pthread_detach` is not used — all threads are properly joined

## Author
```
loasaad
```
