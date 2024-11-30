# Philosophers Project

## Overview
This project is part of the 42 school curriculum aimed at learning the basics of threading a process and discovering the mutexes, semaphores, and shared memory. "Philosophers" simulates the classical dining philosophers problem to manage processes and memory sharing among threads efficiently and safely.

## Problem Statement
The Dining Philosophers problem consists of philosophers seated at a round table, with a fork between each pair. Philosophers alternate between eating, thinking, and sleeping. The challenge is to simulate this scenario while preventing deadlock, ensuring that no philosopher will starve.

## Implementation
- **Languages Used:** C
- **Concepts Applied:** Multithreading, Mutexes, Semaphores
- **Expected Outcomes:** The philosophers should perform their actions in a loop without any of them dying from starvation and without encountering a deadlock situation.

## Usage
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```
2. Compile the program:
   ```bash
   make
   ```
3. Run the simulation:
   ```bash
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
   ```
## Parameters:
***number_of_philosophers:*** The number of philosophers and forks.
***time_to_die:*** The maximum time since the start of their last meal or the beginning of the simulation, after which a philosopher must start eating.
***time_to_eat:*** The time it takes for a philosopher to eat. During this time they must keep holding two forks.
***time_to_sleep:*** The time a philosopher will spend sleeping.
***number_of_times_each_philosopher_must_eat:*** (optional) If all philosophers eat at least this number of times, the simulation will stop.

