# Authors
Iury Lamonie - Turma 2
& 
Leonardo Igor - Turma 1


# 1. Introduction
This project is the second part of an assignment of the programming languages 1 class. It aims to make a board generator for the [Battleship game](https://en.wikipedia.org/wiki/Battleship_(game)).



# 2. Makefile/Compiling:


Will check if the setup is configured, if not, it will make a new setup by calling "make dir" and compile. it calls "make all" internally.

```
make
```

You can also pass arguments to the compiler. Example below.
```
make args="-D something=212"
```
For enabling the debug mode do:

```
make args="-D DEBUG"
```

will make all the working directories. You can do this manually or it will do automatically if you use make.
```
make dir
```

will make clean the working directory, will delete all the files contained in bin and docs.
```
make clean
```

will  make the documentation for the current project.
```
make doxy
```

will call make clean and make dir.
```
make fresh
```


# 3. Running:

Just do
```
./bin/main
```