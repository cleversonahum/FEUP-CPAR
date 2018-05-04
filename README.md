# FEUP-CPAR
Repository with Practical works from Parallel Computing - FEUP

Implementation of LU Decomposition and Sieve of Eratosthenes using C++. Different versions were implemented, having a sequential version, an OpenMP version (shared memory) and an OpenMPI version (Distributed Version).

## Running
```
make #Building Dependencies
./run #Running tests
```

## Cleaning all executable files and input files
```
make clean
```

## References:
[1]  Bokhari, S. "Multiprocessing the sieve of Eratosthenes." (1986).

[2]  Bartels, Richard H., and Gene H. Golub. "The simplex method of linear programming using LU decomposition." Communications of the ACM 12.5 (1969): 266-268.

[3] Cse.Buffalo.Edu,2018,https://www.cse.buffalo.edu//faculty/miller/Courses/CSE633/Tummala-Spring-2014-CSE633.pdf. Accessed 4 May 2018.

[4] "Platipo/MPI-LU-Fact". Github, 2018, https://github.com/platipo/MPI-LU-fact. Accessed 4 May 2018.
