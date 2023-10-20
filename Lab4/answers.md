# CS 425 Lab 4

Matt Irizarry

10/19/23

matthew.irizarry745@topper.wku.edu

## Task 1

1. ### Are there any shared variable in the programs? If any, list all shared variables?

    The only difference between the two programs are the amount of computation the two perform. As a result of this, we can see that the numbers printed to the screen for each algorithm differ vastly. 

    In the first algorithm, it only returns either `0` or `10`, and nothing in between. This is because this computation can be completed quickly, and therefore there is not much overlap.

    However, this is not the case for the second problem, which is why we see the number increasing to `1e8` each time the consumer prints the value to the screen. Why is it so different? The value of `n` is being shared by multiple threads, so therefore the value may have already been changed by the time the consumer recognizes it. So instead of getting consistent `0` or `10`, we get a snapshot at how close it is to completing the computation.

2. ### What is the output of `lab4_task1.1.c`? Is it the same, or different per round of execution?

    In the first example, the output of my 10 iterations was recorded in `1.1.output.txt` and we can see there is only ever two numbers: `0` and `10`. This is because there is no synchronization between the processes. The `consumer()` will print the value of `n` at each iteration of the loop, but it may do so at different stages of the `producer()` thread. This is why the values are `0` or `10`.

3. ### What is the output of `lab4_task1.2.c`

    In this example, we do not produce the consistent race condition of `0` or `10`, we encounter different numbers on the way up to `1e8` as the `consumer()` is accessing `n` after the `producer()` has modified it. With the increased workload, there is an increased probability that a race condition will occur, which is why the numbers are never the same for each iteration. For the 10 iterations I performed, I stored the output in `1.2.output.txt` and we can see that no number is repeated. This is because there is no synchronization between the threads, and thus the `n` variable is accessed at different points in the `producer()` thread.

## Task 2

4. ### In `producer()`, which statements are the entry section, critical section, and the exit section?

    In this function, these three sections all occur during the `for` loop.

    #### Entry Section

    `sem_wait(&psem)` - This blocks the thread from moving forward into the critical section until the semaphore is met.

    ### Critical Section
    `n++` - This is the critical section, as the data is being modified here. This is protected by the above entry section and ensures that only one thread at a time is modifiying `n`

    ### Exit Section
    `sem_post(&csem)` - This is responsible for letting other threads know that they can enter their critical section now, and that `n` is ready to be modified.

5. ### How many context switches between the producer thread and the consumer thread in the execution of the program? Justify your answer.

    To my knowledge, there is no way to exactly know this, as this depends on several factors of the host PC. For example, the scheduling policy of the OS. For Windows, this program may behave differently than on Linux. Moreover, the number of cores available will impact this number as well.

    However, in my instance, I was able to use some built in linux tools to get an answer to this. After running the command `sudo perf stat -e context-switches ./lab4_task2` it gave me 21 context switches. I initally had guessed `20` but I guess the last context switch is switching back to the main thread to clean up for the function.

6. ### What is the first value printed? Will it be changed if you execute the two `pthread_create` statements? Explain why.

    The first value printed is `1`.

    In the provided code, the consumer is created first and then the producer is created. Even if we change them around, they will still have the same values, as they are protected by the semaphore condition.

7. ### What will be the first value printed if you exchange initialization values for `psem` and `csem`? Explain why.

    The first value if you change the initialization values for `psem` and `csem` is `0`. 

    This is because these values behave similar to the `z-index` property in CSS. The higher the value, the closer to the foreground the element will be. 

    In this case, because the `csem` has a higher value than `psem`, the consumer will enter its critical section before the producer will, thus observing `n` as `0` instead of `1`.

8. ### In either cases, are the values of `n` printed consecutively? Justify your answer.

    In either case, the values of `n` are printed consecutively because they are protected by the semaphores `psem` and `csem`. 

9. ### If psem is set to 3, and csem is set to 0, do you observe any pattern in the output? If so, explain why.

    By setting the `psem` to `3` and `csem` to `0`, we effectively allow the `producer()` to enter its critical section `3` times before the `consumer()` is allowed to enter its critical section. This is why we observe the pattern `3 3 3 6 6 6 9 9 9 10`

    We can see other patterns by changing the value of `psem` to say, `2`. We observe the pattern `2 2 4 4 6 6 8 8 10 10`. This is because the `producer()` accesses its critical section twice before the `consumer()` has a change to enter its critical section. Thus, the value has been incremented twice, giving us this pattern.

## Task 3

10. ### What is the median elapsed time under the first setting? What is the median elapsed time under the second setting? Which one is smaller, and why?

    #### First Setting

    The median time elapsed during the first setting is `4.660006` and I have recorded all five runs in `3.1.output.txt`. 

    #### Second Setting

    The m