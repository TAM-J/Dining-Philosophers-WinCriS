# 🍽️ Dining Philosophers Problem (Windows Critical Sections)

This repository contains a C++ implementation of the classic **Dining Philosophers Problem**, a quintessential problem in concurrent programming used to illustrate challenges like synchronization, resource contention, and deadlock prevention.

## Overview

The simulation models five philosophers sitting around a circular table. Between each pair of philosophers is a single chopstick. A philosopher must acquire **both** the left and the right chopstick to eat.

This solution uses **Windows Critical Sections (`CRITICAL_SECTION`)** as the locking primitive to represent the chopsticks and synchronizes access to them across five separate threads (representing the philosophers).

## Deadlock Prevention Strategy

The code employs an **asymmetric resource acquisition strategy** combined with non-blocking attempts to acquire the second resource (`TryEnterCriticalSection`) to ensure the system is **deadlock-free** and guarantees progress.

### The Strategy:

1.  **Asymmetric Ordering:** Philosophers follow an ordered preference when picking up sticks:
    * Even-numbered philosophers (0, 2, 4) attempt to pick up their **lower-indexed** stick first.
    * Odd-numbered philosophers (1, 3) attempt to pick up their **higher-indexed** stick first.
2.  **Try-and-Release:** The second stick is acquired using `TryEnterCriticalSection`. If the second stick is busy, the philosopher immediately releases the first stick and "thinks" (i.e., loops back to try again), preventing blocking and deadlock.

## Implementation Details

* **Concurrency Primitive:** `CRITICAL_SECTION` from `<windows.h>`.
* **Threads:** `CreateThread` and `WaitForMultipleObjects` are used to manage the 5 philosopher threads.
* **Goal:** Each philosopher attempts to "eat" (successfully acquire both sticks) $1,000,000$ times.
* **Performance Measurement:** The program measures the total time taken to complete the $5,000,000$ total eating events.

## Prerequisites

* A C++ compiler (e.g., MinGW, Visual Studio) that supports Windows API calls.
* The `<windows.h>` and `<time.h>` headers.

## Build and Run

1.  Save the code as `phCr.cpp`.
2.  Compile the code:

    ```bash
    g++ phCr.cpp -o dining_philosophers.exe -std=c++11
    ```

3.  Run the executable:

    ```bash
    ./dining_philosophers.exe
    ```

The output will display the total time taken for all philosophers to complete their meals:
