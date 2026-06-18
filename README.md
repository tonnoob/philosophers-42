*This project has been created as part of the 42 curriculum by osousa-d.*

[Versão em português 🇧🇷](docs/README-ptbr.md)

# Philosophers

## Description

The **Philosophers (philo)** project is a classic concurrent programming exercise based on the philosophers' dining problem.

- Imagine you have X number of philosophers sitting at a table.
- Each philosopher brings **1 fork** to the table and leaves it beside them, i.e., 1 fork, 1 philosopher, 1 fork, 1 philosopher...
- However, to **eat**, the philosopher needs **2 forks**, one fork from the left and one from the right.
- The philosophers can perform 4 actions:
	- **Take the forks**
	- **Eat**
	- **Sleep**
	- **Think**

- The philosopher, after **eating**, is required to **sleep** to aid digestion, then he **thinks**, and afterwards he can **eat** again, but only with **2 forks**.

- The challenge is precisely to play with the time it takes philosophers to perform actions using **threads**.

- What are **Threads**?
In simple terms, they are **subprocesses** within a **process**.
Because each philosopher executes the actions simultaneously, however, what makes them differentiate if a **process** (philosopher) is using a fork, making the fork unavailable, is the **mutex**, so when a **process** (philosopher) uses a **fork** it locks the **mutex** of that **fork** and no other **process** (philosopher) can pick up that same fork (remembering that they pick up the forks that are next to them).

- In the project input, we put the following data:
	- **Number of philosophers** at the table.
	- **Time to die** of the philosophers (in milliseconds), if a philosopher goes without eating within this time, he dies.
	- **Time to eat** (in milliseconds), that is, the time the philosopher will take to eat.
	- **Time to sleep** (in milliseconds), the time the philosopher spends sleeping.
	- **[Number of meals]**, how many times the philosophers have to eat to feel satiated (this input is optional).

---
### Implementation Details
This implementation uses:
- **Threads** which are the philosophers.
- **Mutexes** to lock the forks.
- **Two Structs**
	- **t_philo** containing all the data of the individual philosopher:
		- **id** (whether it's philosopher 1, 2, 3...);
		- **thread** (subprocess to be created);
		- **last_meal_time** (time of the last meal);
		- **meals_eaten** (how many meals have been eaten);
		- **philo_is_full** (to know if all meals have been eaten);
		- **meal_mutex**; (mutex for the philosopher's meals);
		- **left_fork** (pointer to the left fork);
		- **right_fork** (pointer to the right fork);
		- **p_data** (pointer to the struct with all the global data);

	- **t_data** Containing all global data:
		- **n_philo** (number of philosophers);
		- **time_to_die** (time to die);
		- **time_to_eat** (time to eat);
		- **time_to_sleep** (time to sleep);
		- **times_a_philo_must_eat** (number of meals a philosopher must have);
		- **time_start** (start time);
		- **print_mutex** (mutex for the print statement to control who prints what);
		- **death_mutex** (mutex to change the death variable);
		- **philos** (pointer to the philosophers);
		- **forks** (pointer to the forks);
		- **someone_died** (checks if someone died);

---
### Compilation

In the project root, go to the "philo" folder:
```bash
➜ philosophers git:(main) ✗ ls
philo README.md
➜ philosophers git:(main) ✗ cd philo
➜ philo git:(main) ✗ 
➜ philo git:(main) ✗ ls
inc Makefile obj philo src
```

After entering the folder, type the command to generate the project executable:

```bash
make
```

Other commands:
| Command | Description |
|---------|-----------|
| make clean | Clears .o files |
| make fclean | Clears .o files and executable files. |
| make re | Recompiles everything |
| make valgrind ARGS="input" | Checks for memory leaks |

## Instructions ##

After compiling the project, you must run the generated **philo** file with the following arguments:

```bash
./philo "<number of philosophers> <time to die> <time to eat> <time to sleep> <optional argument [number of times a philosopher has to eat to get full]>"
```
Example:
```bash
./philo 3 410 200 200
```
or

```bash
./philo 3 410 200 200 3
```

Arguments are not passed randomly, the following entries are not allowed:

- Only the program name;
- Empty strings or strings containing only spaces;
- Arguments that are not numbers;
- A sign (+ or -) without a number;
- Negative numbers;
- Values ​​equal to zero (for required arguments);
- Incorrect number of arguments;
- Numbers greater than the limit of an int (overflow);
- Invalid optional argument (n_meals) or less than or equal to zero;

---
After running the program with the arguments, it will print the actions that each philosopher is performing:

```bash
➜ philo git:(main) ✗ ./philo 3 410 200 200 3
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleepingsopher’s death must be displayed within 10 ms of
their actual de
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
200 3 has taken a fork
400 1 is thinking
400 1 has taken a fork
400 2 is sleeping
400 3 has taken a fork
400 3 is eating
410 1 died
```

The program only ends when a philosopher dies or when all philosophers have finished all their meals (if specified).

## Evaluation Criteria ##
The project is evaluated based on its logic and behavior:

- It cannot crash, segfault, or enter a strange state.

- A philosopher dies exactly when they should. If the death input is ~400ms and a philosopher dies, there must be a "died" in exactly ~400ms.

- Consistent values, meaning no one dies "while eating".

- The program cannot deadlock; all philosophers take only 1 fork (this locks the system, as no one will "let go" of the fork until they have eaten, but they can only eat if they have 2 forks).

- All philosophers eat; no one is "forgotten" until they die (starvation).

- Correct printouts; messages don't get mixed up. If someone dies, nothing else can be printed after "died," or if all messages are "full," they are printed as follows:
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died

- No data race, which would occur when one of the subprocesses accesses a variable, but when that subprocess enters the function, the variable has one value, and before the function finishes, it receives another value from another subprocess (this can be tested with helgrind).

- There should be no memory leaks (this is tested with valgrind).

- Another cool thing to test is that if the input is one where it's possible for all the philosophers to have their meals until they are "full/satisfied," the quantity must be exactly (number of philosophers * number of meals) until they are satisfied. This can be tested with the following input:

```bash
./philo <input> | grep eating | wc -l
```
Example:
```bash
➜ philo git:(main) ✗ ./philo 2 800 200 200 5 | grep eating | wc -l
10
```
(2 * 5 = 10)

---

## Resources ##
I used ChatGPT (https://chatgpt.com/) to help me understand the concepts of threads and mutexes, organize the project (defining the next steps), and debug a deadlock issue I was experiencing.
