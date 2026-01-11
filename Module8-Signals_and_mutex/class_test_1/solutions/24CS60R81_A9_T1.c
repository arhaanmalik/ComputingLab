#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigint(int sig){
    printf("I am unstoppable!\n");
}

int main(){
    char inp;

    signal(SIGINT, handle_sigint);

    while(1){
        inp = getchar();
        while(getchar() != '\n'); 

        if(inp == 'x'){
            printf("Valar Morghulis\n");
            break;       
        }
        else if((inp >= 'A' && inp <= 'Z') || (inp >= 'a' && inp <= 'z')){
            printf("%c\n", inp);
        }
        else{
            printf("Do you speak my language?\n");
        }
    }
    return 0;
}
