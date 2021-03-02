# skel

Maintainers:
* Darius-Florentin Neațu (neatudarius@gmail.com)
* Radu Nichita (radunichita99@gmail.com)

Skeletons for the PA laboratories.

## skel

Skel example:
```bash
tree skel/labxy/
skel/labxy/
├── check
├── cpp
│   ├── task-1
│   │   └── main.cpp
│   ├── task-2
│   │   └── main.cpp
│   ├── task-3
│   │   └── main.cpp
│   └── task-4
│       └── main.cpp
├── java
│   ├── task-1
│   │   └── src
│   │       └── Main.java
│   ├── task-2
│   │   └── src
│   │       └── Main.java
│   ├── task-3
│   │   └── src
│   │       └── Main.java
│   └── task-4
│       └── src
│           └── Main.java
└── tests
    ├── task-1
    │   ├── 1.in
    │   ├── 1.ref
    ..................
    │   ├── 4.in
    │   ├── 4.ref
    │   ├── custom.in
    │   └── custom.ref
    ├── task-2
    │   ├── 1.in
    │   ├── 1.ref
    ..................
    │   ├── 4.in
    │   ├── 4.ref
    │   ├── custom.in
    │   └── custom.ref
    ├── task-3
    │   ├── 1.in
    │   ├── 1.ref
    ..................
    │   ├── 9.in
    │   ├── 9.ref
    │   ├── custom.in
    │   └── custom.ref
    └── task-4
        ├── 1.in
        ├── 1.ref
    ..................
        ├── 4.in
        ├── 4.ref
        ├── custom.in
        └── custom.ref
```

Description for `skel/labxy`:

* `cpp/` / `java`
  * 4 tasks (`task-1`, ..., `task-4`)
  * `cpp/$task/main.cpp`: the `C++` skeleton for the current task
  * `java/$task/main.cpp`: the `Java` skeleton for the current task
* `tests/`: each tasks can have multiple tasks (e.g. `task-1` has 4 tests `1`,`2`,`3`,`4`).
  * example `task-1` test `2`
    * `skel/labxy/task-1/2.in`: input for `task-1` test `2`
    * `skel/labxy/task-1/2.ref`: reference (expected output) for`task-1` test `2`
    * `skel/labxy/task-1/2.out`: output (actual output) `task-1` test `2`
  * `custom` test (`custom.in` / `custom.ref`) which can be used for manual testing
* `./check`: executable checker

### checks
Usage:
```bash
$ ./check
./check <lang> [task] [test_number]

Rulati ./check avand ca director curent radacina scheletului
de laborator.

<lang>: "java" sau "cpp"
Daca nu este specificat [test_number], se ruleaza toate testele
Daca nu este specificat [task], se ruleaza toate taskurile

De exemplu, pentru a rula testul 2 din taskul 1, limbajul Java:
	./check java task-1 2

De asemenea, "./check clean" curata binarele create in timpul
executiei.

De asemenea, "./check pack <nume.zip>" realizeaza o arhiva zip
in directorul parinte cu numele specificat.
Exemplu: ./check pack 321CA_GigelGigel_lab00.zip

Pentru a rula teste custom, modificati tests/<task>/custom.in si
tests/<task>/custom.ref, ruland apoi:
	./check <lang> <task> custom
```

#### Examples
##### run for C++, all tasks
```bash
$ ./check cpp
=========================================================================================
Running task-1, test 1, language cpp... Failed with status WRONG ANSWER!
Expected: 2
Got: 0

Running task-1, test 2, language cpp... Failed with status WRONG ANSWER!
Expected: 5
Got: 0

Running task-1, test 3, language cpp... Failed with status WRONG ANSWER!
Expected: 1
Got: 0

Running task-1, test 4, language cpp... Successful!

=========================================================================================
=========================================================================================
Running task-2, test 1, language cpp...
Solutia gasita nu respecta |referinta - iesire| < 1e-3	Failed with status WRONG ANSWER!
Expected: 1.000
Got: 0.0000

...
...
...


=========================================================================================
Running task-4, test 1, language cpp... Failed with status WRONG ANSWER!
Expected: 4
Got: 0

Running task-4, test 2, language cpp... Failed with status WRONG ANSWER!
Expected: 3
Got: 0

Running task-4, test 3, language cpp... Failed with status WRONG ANSWER!
Expected: 707238858
Got: 0

Running task-4, test 4, language cpp... Failed with status WRONG ANSWER!
Expected: 1
Got: 0

=========================================================================================
Rulati urmatoarea comanda pentru a vedea log-ul de compile/run:
	less .err.log
Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra.
```

##### run for C++, one task
```bash
# run 2nd task
$ ./check cpp task-2
=========================================================================================
Running task-2, test 1, language cpp...
Solutia gasita nu respecta |referinta - iesire| < 1e-3	Failed with status WRONG ANSWER!
Expected: 1.000
Got: 0.0000

Running task-2, test 2, language cpp...
Solutia gasita nu respecta |referinta - iesire| < 1e-3	Failed with status WRONG ANSWER!
Expected: 0.500
Got: 0.0000

Running task-2, test 3, language cpp...
Solutia gasita nu respecta |referinta - iesire| < 1e-3	Failed with status WRONG ANSWER!
Expected: 1.697
Got: 0.0000

Running task-2, test 4, language cpp...
Solutia gasita nu respecta |referinta - iesire| < 1e-3	Failed with status WRONG ANSWER!
Expected: 3.207
Got: 0.0000

=========================================================================================
Rulati urmatoarea comanda pentru a vedea log-ul de compile/run:
	less .err.log
Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra.
```

##### run for C++, one task, one test
```bash
# run the 2nd task, the 3rd test
$ ./check cpp task-2 3
Running task-2, test 3, language cpp...
Solutia gasita nu respecta |referinta - iesire| < 1e-3	Failed with status WRONG ANSWER!
Expected: 1.697
Got: 0.0000

Rulati urmatoarea comanda pentru a vedea log-ul de compile/run:
	less .err.log
Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra.
```

##### run for C++, one task, a custom test
```bash
# set input for custom test
$ cat tests/task-1/custom.in
5
1 2 2 3 4
2
# set ref for custom test
$ cat tests/task-1/custom.ref
2
# run the 1st task, the custom test
$ ./check cpp task-1 custom
Running task-1, test custom, language cpp... Failed with status WRONG ANSWER!
Expected: 2
Got: 0

Rulati urmatoarea comanda pentru a vedea log-ul de compile/run:
	less .err.log
Nota: In .err.log se afla si afisarile la stdout si stderr din implementarea voastra.
```

##### clean binaries
```bash
$ ./check clean
```
