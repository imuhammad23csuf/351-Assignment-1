# 351-Assignment-1
Group Members:

Ibraheem Muhammad, Luis Selgado, Luke Chua Marquez, Yonis Salah, and Simon Kang

Email: 

imuhammad23@csu.fullerton.edu, luke.chua@csu.fullerton.edu, simonkang@csu.fullerton.edu, lesalgado@csu.fullerton.edu, Yonis@csu.fullerton.edu

Contribution:
Ibraheem: Shell and serial file
Luis: Parallel
Luke: Multi-search

Statement:
All members understand the components and implications of user vs system calls in the code.

Programming Language:
Shell is in C
Serial, parallel, and multi-search is in C++


Execution Times:

Parallel:
real    0m1.268s
user    0m0.229s
sys     0m0.050s

Serial:
real    0m1.268s
user    0m0.229s
sys     0m0.050s

Questions:
1. In the output oftime, what is the difference between real, user, and sys times?
real: Time from start to finish

user: CPU time spent running the programs

sys: Total amount of time the CPU spent on system calls
2. Which is longer: user time or sys time? Use your knowledge to explain why.

User time is longer because it is used for most operations, like computations and creating variables; sys time is shorter because it is only needed when reading and writing to the hardware.

3. When fetching all of the locations in the file, which fetcher finishes faster? Why do you think that is?

Parallel fetchers finish faster because all children run simultaneously, fetching data at the same time, making better use of CPU, network, and serial resources. The parent waits for the child to finish before opening a new request.

4. Suppose one of the fetcher children crashes. Will this affect other children? Explain. What is your conclusion regarding the benefits or disadvantages of isolating each fetch task within a different process?

Even if one child process happens to crash, it won't affect others, as they have their own memory, so a crash wouldn't corrupt or stop others.

Extra Credit:

Yes, extra credit was implemented.

Anything Special:


