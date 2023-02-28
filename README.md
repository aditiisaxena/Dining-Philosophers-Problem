# Dining Philosophers Problem
This repository contains two solutions in C language for the classic problem of the Dining Philosophers. The problem is an illustration of a deadlock scenario where multiple processes are trying to acquire resources that are limited in number.

## Problem description
The Dining Philosophers problem is a classic problem that illustrates the concept of deadlock in concurrent systems. The problem describes a scenario where five philosophers are sitting at a round table with a bowl of rice in front of each philosopher. The philosophers alternate between eating and thinking. In order to eat, a philosopher must have possession of both of the forks adjacent to their bowl. However, when a philosopher finishes eating, they release both forks, which may be then picked up by the philosopher on their left or right.
<br><br>
The problem is that if all the philosophers simultaneously pick up the left fork and wait for the right fork to be available, they will all be waiting indefinitely and none of them will be able to eat. This is known as a deadlock situation, as all the philosophers are waiting for a condition that can only be fulfilled by another philosopher releasing a fork, but that philosopher is also waiting for the same condition to be fulfilled.
<br><br>
The goal of the problem is to come up with a solution that ensures that the philosophers can eat without any of them getting into a deadlock situation. Observe the output of the program to see how the philosophers acquire and release the chopsticks

## Solution 1: Spinning Lock
This solution uses a spinning lock that is implemented by a while loop that sleeps for 1 second to prevent deadlock. The philosophers check if both forks are available before trying to acquire them.

## Solution 2: Semaphores and Odd-Even Positioning
This solution uses semaphores and odd-even positioning to prevent deadlock. The philosophers are assigned an odd or even position, and the philosophers in odd positions pick up their left fork first, while the philosophers in even positions pick up their right fork first.

## Running the code
Clone the repository to your local machine<br>
Run the c files in your linux/wsl terminal:
```
gcc Solution1.c -o Solution1.c -lpthread 
./Solution1
```
Do the same for Solution2 by switching every "Solution1" in above block with "Solution2
