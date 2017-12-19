//
// Created by 冯加成 on 2017/12/18.
//

#ifndef COROUTIME_CORO_H
#define COROUTIME_CORO_H

#include "stdio.h"
#include <sys/ucontext.h>

#define COROUTINE_DEAD 0
#define COROUTINE_READY 1
#define COROUTINE_RUNNING 2
#define COROUTINE_SUSPEND 3
#define COROUTINE_PRE_SUSPEND 4

#define STACK_SIZE (1024*1024)

extern "C" {
    void getcontext(ucontext_t*);
    void makecontext(ucontext_t*, void (*)(void),int,...);
    void swapcontext(ucontext_t*,ucontext_t*);
    void setcontext(ucontext_t*);
}


class Coro;




typedef void (*RoutineHandler)(Coro*);

class Coro{
    char stack[STACK_SIZE];
    RoutineHandler run;
    ucontext_t ctx;

public:
    int status;
    Coro(RoutineHandler fun);
    void yeild();
    void resume();
    ~Coro();

    static void mainfunc(Coro * co){
        co->status = COROUTINE_RUNNING;
        co->run(co);
        co->status = COROUTINE_DEAD;
    };

    static ucontext_t main_ctx;

};


#endif //COROUTIME_CORO_H
