#include <errno.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include "stm32f4xx.h"
#include "main.h"
#include "lcd.h"

#define ECHOBACK

extern uint32_t __get_MSP(void);

int _write(int file, char *ptr, int len);

// errno
#undef errno
extern int errno;

/*
 Переменные среды - пустой список.
 */
char *__env[1] = {0};
char **environ = __env;

// exit - экстренный выход. В качестве выхода - зацикливаемся.
void _exit(__attribute__((unused)) int status)
{
    while (1)
        ;
}

// close - закрытие файла - возвращаем ошибку
int _close(__attribute__((unused)) int file)
{
    return -1;
}
/*
 execve - передача управления новому процессу - процессов нет -> возвращаем ошибку.
 */
int _execve(
    __attribute__((unused)) char *name,
    __attribute__((unused)) char **argv,
    __attribute__((unused))char **env)
{
    errno = ENOMEM;
    return -1;
}

/*
 fork = создание нового процесса
 */
int _fork()
{
    errno = EAGAIN;
    return -1;
}

/*
 fstat - состояние открытого файла
 */
int _fstat(__attribute__((unused)) int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid - получить ID текущего процесса
 */

int _getpid()
{
    return 1;
}

/*
 isatty - является ли файл терминалом.
 */
int _isatty(int file)
{
    switch (file) {
        case STDOUT_FILENO:
        case STDERR_FILENO:
        case STDIN_FILENO:
            return 1;
        default:
            //errno = ENOTTY;
            errno = EBADF;
            return 0;
    }
}

/*
 kill - послать сигнал процессу
 */
int _kill(__attribute__((unused)) int pid, __attribute__((unused)) int sig)
{
    errno = EINVAL;
    return (-1);
}

/*
 link - устанвить новое имя для существующего файла.
 */

int _link(__attribute__((unused)) char *old, __attribute__((unused)) char *new)
{
    errno = EMLINK;
    return -1;
}

/*
 lseek - установить позицию в файле
 */
int _lseek(
    __attribute__((unused)) int file,
    __attribute__((unused)) int ptr,
    __attribute__((unused)) int dir)
{
    return 0;
}

/*
 sbrk - увеличить размер области данных, использутся для malloc
 */
caddr_t _sbrk(int incr)
{
    extern char _ebss;
    static char *heap_end;
    char *prev_heap_end;
    
    if (heap_end == 0) {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;
    
    char * stack = (char*)__get_MSP();
    if (heap_end + incr > stack) {
        _write(STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return (caddr_t)-1;
        //abort ();
    }
    
    heap_end += incr;
    return (caddr_t)prev_heap_end;
    
}

/*
 read - чтение из файла, у нас пока для чтения есть только stdin
 */
int _read(int file, char *ptr, int len)
{
    int num;
    char c;
    
    switch (file) {
        case STDIN_FILENO:
            for (num = 0; num < len; num++) {
                do {
                    c = usart_getch();
                } while (c == false);
                
                *ptr++ = c;
#ifdef ECHOBACK
                usart_putch(c);
                // lcd_write(c);
#endif
                if (c == '\r' && num <= (len - 2)) { /* 0x0D */
                    *ptr = '\n'; /* 0x0A */
#ifdef ECHOBACK
                    usart_putch('\n'); /* 0x0A */
                    //lcd_write('\n');
#endif
                    return num + 2;
                }
            }
            break;
        default:
            errno = EBADF;
            return -1;
    }
    return num;
}

/*
 stat - состояние открытого файла.
 */
int _stat(__attribute__((unused)) const char *filepath, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times - временная информация о процессе (сколько тиков: системных, процессорных и т.д.)
 */
clock_t _times(__attribute__((unused))  struct tms *buf)
{
    return -1;
}

/*
 unlink - удалить имя файла.
 */
int _unlink(__attribute__((unused)) char *name)
{
    errno = ENOENT;
    return -1;
}

/*
 wait - ожидания дочерних процессов
 */
int _wait(__attribute__((unused)) int *status)
{
    errno = ECHILD;
    return -1;
}

/*
 write - запись в файл - у нас есть только stderr/stdout
 */
int _write(int file, char *ptr, int len)
{
    int n;
    
    switch (file) {
        case STDOUT_FILENO: /* stderr */
            for (n = 0; n < len; n++) {
                usart_putch((uint8_t)*ptr++);
                //lcd_write((uint8_t) *ptr++);
            }
            break;
        case STDERR_FILENO:
            for (n = 0; n < len; n++) {
                lcd_putch((uint8_t)*ptr++);
            }
            break;
        default:
            errno = EBADF;
            return -1;
    }
    return len;
}
