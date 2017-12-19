
#include "coro.h"
#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <cstdlib>


void fn(){
    printf("hello world\n");
}

void fun1(Coro *co){
    for (int i =0;i<10;i++){
        printf("before fun1----- i=%d \n",i);
        co->yeild();
        printf("after  fun1----- i=%d \n",i);
    }
    printf("fun1 endl\n");
}



void fun2(Coro *co){
    for (int i =0;i<10;i++){
        printf("before fun2----- i=%d \n",i);
        co->yeild();
        printf("after  fun2----- i=%d \n",i);
    }
    printf("fun2 endl\n");
}

int main(){
    Coro *c1 = new Coro(fun1);
    Coro *c2 = new Coro(fun2);

    while (c1->status!=COROUTINE_DEAD || c2->status!=COROUTINE_DEAD) {
        c1->resume();
        c2->resume();
    }

    printf("----->endl\n");
}


