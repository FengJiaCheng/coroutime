//
// Created by 冯加成 on 2017/12/18.
//

#include <stddef.h>
#include <cstring>
#include <cstdlib>
#include "coro.h"


ucontext_t Coro::main_ctx;

Coro::Coro(RoutineHandler fun):run(fun){
    status = COROUTINE_READY;
}
Coro::~Coro(){
    free(stack);
}

void Coro::yeild(){
    status = COROUTINE_SUSPEND;
    swapcontext(&ctx,&main_ctx);
}


void Coro::resume(){
    switch (status) {
        case COROUTINE_READY:
            getcontext(&ctx);
            ctx.uc_stack.ss_sp = stack;
            ctx.uc_stack.ss_size = STACK_SIZE;
            ctx.uc_link = &main_ctx;
            makecontext(&ctx, (void (*)(void))(Coro::mainfunc), 1, this);
            swapcontext(&main_ctx,&ctx);
            break;
        case COROUTINE_RUNNING:
            break;
        case COROUTINE_DEAD:

            break;
        case COROUTINE_SUSPEND:
            swapcontext(&main_ctx,&ctx);
            break;
    }

}
