# PA setup

## Compilers
### C++
Use a recent `g++` version: at least `g++-7`, recommended `g++-10`.
```bash
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test
$ sudo apt-get update
$ sudo apt install g++-10
# optional: install gcc-10
```

### Java
Use Java 10 or later.
```bash
$ sudo add-apt-repository ppa:openjdk-r/ppa
$ sudo apt-get update
$ sudo apt install openjdk-11-jdk
```

## IDE: VSCode

Use `Visual Studio Code` for all languages.

### Installation
```bash
# download https://code.visualstudio.com/docs/?dv=linux64_deb

$ sudo dpkg -i ~/Downloads/code_<version>.deb
```

### VSCode C++ extension
* open VSCode
* open command shell `CTRL + SHIFT + P`
* type "install" and select `Extensions: Install Extensions`
* search for `C++`
* select `C/C++ Intellisense` from Microsoft (~18M users)
* install
* restart the IDE

### VSCode Java extension
* open VSCode
* open command shell `CTRL + SHIFT + P`
* type "install" and select `Extensions: Install Extensions`
* search for `Java`
* select `Language Support for Java` from Red Hat (~9M users)
* install
* restart the IDE

### VSCode Markdown extension (local rendering)
* open VSCode
* open command shell `CTRL + SHIFT + P`
* type "install" and select `Extensions: Install Extensions`
* search for `Markdown`
* select `Markdown Preview Enhanced` from Yiyi Wang (~2M users)
* install
* restart the IDE
