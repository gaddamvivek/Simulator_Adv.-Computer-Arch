# README for Project: Simulator for Stack-Based Duo Core Processor

## Overview

This project is a simulator for a stack-based duo core processor that includes cache memory for each core. It was developed as part of the ICSI 504 coursework at the University at Albany, under the guidance of the Department of Computer Science.

## Table of Contents
1. [System Documentation](#system-documentation)
    - [High-Level Data Flow Diagram](#high-level-data-flow-diagram)
    - [List of Routines](#list-of-routines)
    - [Implementation](#implementation)
2. [Test Documentation](#test-documentation)
    - [Testing the Program](#testing-the-program)
    - [Test Cases](#test-cases)
    - [Program Bugs and Resolution](#program-bugs-and-resolution)
    - [Executable Version](#executable-version)
    - [Difficulties and Solutions](#difficulties-and-solutions)
3. [Algorithms and Data Structures](#algorithms-and-data-structures)
    - [Algorithms](#algorithms)
    - [Data Structures](#data-structures)
4. [User Documentation](#user-documentation)
    - [Operating System Used](#operating-system-used)
    - [How to Compile the Program](#how-to-compile-the-program)
    - [Other Applications Required](#other-applications-required)
    - [How to Run the Program](#how-to-run-the-program)
    - [Parameters](#parameters)

## System Documentation

### High-Level Data Flow Diagram

The High-Level Data Flow Diagram illustrates the flow of the simulator for the stack-based duo core processor. The simulator executes .abm files through a defined instruction set, employing stack functions, hash tables, cache memory, and instructions.

### List of Routines

1. **Stack Functions**:
    - `startStack()`
    - `stackFull()`
    - `stackEmpty()`
    - `pushStack()`
    - `popStack()`
    - `peekStack()`

2. **Hash Table Functions**:
    - `hash()`
    - `create()`
    - `insert()`
    - `retrieve()`
    - `changeValue()`

3. **Queue Functions**:
    - `createCacheQueue()`
    - `EnCacheQueue()`
    - `DeCacheQueue()`
    - `CacheMemory()`

### Implementation

The simulator is implemented using the C programming language and designed for Linux Operating Systems. The structure data type is employed to facilitate stack operations and a hash table to manage data addresses effectively. The project also implements a queue mechanism for cache memory using the Least Recently Used (LRU) algorithm and supports MSI (Modified, Shared, Invalid) cache coherence.

## Test Documentation

### Testing the Program

The program's functionality is validated by executing .abm files and displaying terminal outputs for each operation performed by the duo core processor.

### Test Cases

1. **Test Case 1**: Executed `test1forP2.abm` file.
   - Input file snapshot and terminal outputs for core operations are captured.

### Program Bugs and Resolution

Identified areas for optimization include:
- Stack operations enhancement.
- Memory management resolutions.

### Executable Version

An executable version of the simulator is provided for users to run .abm code, producing outputs seamlessly.

### Difficulties and Solutions

Challenges faced during development included:
- Instruction parsing complexity.
- Memory management and handling errors effectively.

## Algorithms and Data Structures

### Algorithms

Key algorithms used include:
- **LRU (Least Recently Used)**: For managing cache memory efficiently.

### Data Structures

1. **Stack**: Implemented using a struct to manage data in LIFO order.
2. **Hash Table**: Utilized for efficient data storage and retrieval.
3. **Queue**: Managed in FIFO order for organizing tasks.

## User Documentation

### Operating System Used

The project is developed using the **Linux Operating System**, with **VS Code** as the coding platform.

### How to Compile the Program

Use the following command in the terminal to compile:
```bash
gcc Simulatordata.c StackSimulator_2.c -o StackSimulator_2
