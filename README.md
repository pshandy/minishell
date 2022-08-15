
# **Project description**
Цель проекта - создание простой оболочки на примере Bash.

## Командная оболочка:
* > Display a prompt when waiting for a new command.
* > Have a working history.
* > Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
* > Not use more than one global variable. Think about it. You will have to explain its purpose.
* > Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
* > Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* > Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
* > Implement redirections
* > Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
* > Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
* > Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
* > Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
* > Your shell must implement the following builtins (without options): echo (with -n), cd, pwd, export, unset, env, exit

* > Отображает подсказку при ожидании ввода (Прим. "minishell> ").
* > Имеет рабочую историю команд.
* > Ищет и выполняет исполняемые файлы (на основе переменной PATH или с использованием относительного или абсолютного пути).
* > Не интерпретирует незакрытые кавычки или специальные символы, которые не требуются по тз, такие как \ или ;.
* > Обрабатывает одинарные кавычки, которые препятствуют интерпретации метасимволов.
* > Обрабатывает двойные кавычки, которые препятствуют интерпретации метасимволов, за исключением $.
* > Обрабатывает перенаправления (<, <<, >, >>).
* > Обрабатывает каналы (символ |). Выходные данные каждой команды в конвейере соединяются со входом следующей команды через канал.
* > Обрабатывает переменные окружения (Прим. 'echo $HOME' выведет '/home/pshandy').
* > Обрабатывает $? (Показывает код завершения последней команды).
* > Поддерживает ctrl-C, ctrl-D и ctrl-\, как в Bash'e.
* > Имеет встроенные команды без параметров: echo (с -n), cd, pwd, export, unset, env, exit

## Разрешённые функции:
* readline and connected to it
* printf
* malloc, free
* write, open, read, close, unlink
* access
* fork
* wait, waitpid, wait3, wait4
* signal, sigaction, sigemptyset, sigaddset, kill
* exit
* getcdw, chdir, opendir, readdir, closedir
* stat, lstat, fstat
* execve
* dup, dup2
* pipe
* strerror, perror
* isatty, ttyname, ttyslot, ioctl
* getenv
* tcseattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs


# **Как использовать**
* *make* - компиляция
* *./minishell* - запуск

# **Подход**
* В исходной команде происходит замена всех подстрок $KEY на соответствующие значения.
* Строка разделяется на токены, каждому токену присвоен свой enum (INPUT, HEREDOC, TRUNC, APPEND, PIPE, CMD, ARG).
* Токены преобразуются в список команд (у каждой команды есть аргументы, входные, выходные дескрипторы).
* Список команд соединяется в цепочку при помощи каналов и выполняется.
