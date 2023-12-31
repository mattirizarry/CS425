# CS 425 Project 2

This project will look at solving the producers - consumer problem with `pthread` library.

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

The `producer()` has two critical sections. The first critical section is the `while` loop that checks if the buffer is full. If it is not, then the `producer()` will wait. The second critical section is where the `producer()` actually increments the value. This is to ensure that the `producer()` does not increment the value if the buffer is full. Then, it keeps track of how many values have been produced. Once the `producer()` has produced all the values, it will signal to the `consumer()` That it is ready for it to start consuming values from the buffer.  

#### 2. How many critical sections should the consumer function have, why?

The consumer also has two critical functions, but the check is a bit different than the producer. The first critical section checks if the number of `produced` is equal to the number of `consumed`. This tells the consumer that the `producer()` is still producing values and to wait until the `producer()` is full to start consuming values.

Once the `producer()` is full, the consumer will start consuming values from the buffer. Once all this is done, it will increment the consumed value, and signal to the `producer()` that it is ready to start producing values again.

## Experimental Results

### Mutex.c

#### Upper Limit of 1 Million, 1 Producer, 1 Consumer

| Buffer Size | Time Elapsed (s) |
|-----|-----|
| 10 | 3.91 |
| 20 | 3.92 |
| 30 | 3.85 |
| 40 | 3.92 |
| 50 | 3.92 |
| 100 | 3.88 |

#### Upper Limit of 1 Million, 1 Producer, 5 Consumers

| Buffer Size | Time Elapsed (s) |
|-----|-----|
| 10 | 7.68 |
| 20 | 7.53 |
| 30 | 7.43 |
| 40 | 7.50 |
| 50 | 7.41 |
| 100 | 7.44 |

### Spinlock.c
 
#### Upper Limit of 1 Million, 1 Producer, 1 Consumer

| Buffer Size | Time Elapsed (s) |
|-----|-----|
| 10 | 5.41 |
| 20 | 5.54 |
| 30 | 5.52 |
| 40 | 5.64 |
| 50 | 5.59 |
| 100 | 5.58 |

#### Upper Limit of 1 Million, 1 Producer, 5 Consumers

| Buffer Size | Time Elapsed (s) |
|-----|-----|
| 10 | 9.13 |
| 20 | 9.10 |
| 30 | 8.85 |
| 40 | 9.03 |
| 50 | 9.24 |
| 100 | 8.99 |

## Experimental Analysis

#### 1. Compare the performance of the two implementations, which one is better? Why?

The `mutex` implementation is better than the `spinlock` implementation. This is because the `spinlock` implementation has to wait for the lock to be released, while the `mutex` implementation does not. This is because the `mutex` implementation uses a blocking wait, while the `spinlock` implementation uses a busy wait. This means that the `spinlock` implementation will have to wait for the lock to be released, while the `mutex` implementation will not. This is why the `mutex` implementation is better than the `spinlock` implementation.

#### 2. Compare the performance of the two implementations in different settings, which one is better? Why?

We know from above that the `mutex` is categorically faster because of the differences in busy wait vs blocked wait. However, we can see that in both instances, adding more consumers increases the time nearly two fold for both situations. This is because the consumers have to wait for the producers to produce the values before they can consume them. This is why the time increases nearly two fold when we add more consumers.

## Conclusion

`mutex` and `spinlock` both have advantages with regards to the problems they solve. In this case, `mutex` simply outperforms `spinlock`. One disadvantage to a busy wait is that the thread is completely stopped while waiting for the block to be released. This can be a problem if the thread is waiting for an extended period of time.

A disadvantage of a busy wait is that the thread is constantly checking to see if the lock has been released. This can be a problem if the thread is checking for an extended period of time, or if there is a lot of contention for the lock.

## References

1. https://www.mathcs.duq.edu/simon/Primer/essential/threads/synchronization.html
2. https://cs.brown.edu/courses/cs033/lecture/34Threads3.pdf
3. https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/ProdCons.html
4. https://www.tutorialspoint.com/producer-consumer-problem-in-c
5. https://code-vault.net/lesson/tlu0jq32v9:1609364042686
6. https://medium.com/@sohamshah456/producer-consumer-programming-with-c-d0d47b8f103f
