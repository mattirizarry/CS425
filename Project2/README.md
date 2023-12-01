# CS 425 Project 2

This project will look at solving the producers - consumer problem with `pthread`.

## 1. Description of the problem

In this project, you will solve a producers-consumers problem with the pthread library, which is formulated as follows:
- there are multiple producers and multiple consumers;
- there is a bounded buffer shared among producers and consumers;
- there is an integer variable only shared among producers;
- each producer thread repeatedly inserts the current value of the interger variable to the bounded buffer if the buffer is not full, and then increases the value of the integer variable by one;
- each consumer thread repeatedly picks up an integer value from the bounded buffer and print the value such that integer values are printed consecutively, i.e, 0, 1, 2, ...up to a certain integer (specified by a user). To have a better idea of the behavior of consumers, the consumer ID should be
display along with the buffered integers, showing which consumer thread prints which buffered
integer. So the output looks like the following:
    ```
    0, 1
    1, 1
    2, 1
    3, 2
    4, 2
    5, 3
    ```
    where the first column is a buffered integer, and the second column is a user-friendly consumer ID.

You need to apply the following principles and concepts to analyze the producers-consumers problem and design.
- minimize the number of shared variables.
- critical section problem: shared variables should be placed into a critical section, and mutual exclusion is applied to threads that are sharing the variable.
- busy waiting and blocking wait: acquiring a spinlock can lead to busy waiting, while calling a blocking wait operation of a semaphore won’t.
- overflow issue and underflow issue: a producer should avoid overflow, while a consumer should avoid underflow.
- only non-shared variables of the main thread are needed to be passed into a producer or a consumer thread.This project also includes an experimental assessment of the performance of busy waiting and blocking wait in varied settings, including buffer size, the number of producer threads, the number of consumer threads, the largest number to print. All these settings are input in the command line and stored in some variables. So the execution of your code should follow the user input format below:
    ```
    ./a.out <buffer_size> <num_producers> <num_consumers> <upper_limit>
    ```
**Note that the buffer size in textbook is a constant, while it is a variable in this project.**

## Problem Analysis

#### 1. Analyze the relationship between producer consumer problem and critical section problem.  Relationship includes similarity and difference, but more importantly the hierarchy.

#### 2. Analyze the difference between the single producer-consumer and multiple producer-consumer problem

## Design

#### 1. How many critical sections should the producer function have, why?

#### 2. How many critical sections should the consumer function have, why?

## Experimental Results

## References

1. https://www.mathcs.duq.edu/simon/Primer/essential/threads/synchronization.html
2. https://cs.brown.edu/courses/cs033/lecture/34Threads3.pdf
3. https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ProdCons.html
4. https://www.tutorialspoint.com/producer-consumer-problem-in-c
5. https://code-vault.net/lesson/tlu0jq32v9:1609364042686
 https://medium.com/@sohamshah456/producer-consumer-programming-with-c-d0d47b8f103f