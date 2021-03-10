#include <stdio.h>
typedef void (*Callback_Fun)(int out_var);
Callback_Fun call_back;

// 回调函数a
void Callback_A(int out_var_a){    
    printf("Call callback_A, var: %d\n\n", out_var_a);
}

// 回调函数b
void Callback_B(int out_var_b){    
    printf("Call callback_B, var: %d\n\n", out_var_b);
}

// 回调动作
void Callback_Act(int x, Callback_Fun cb){    
    printf("Call callback_act, var_x: %d\n\n", x);  
    call_back=cb; 
    call_back(x);
}


int main(){    
    int A = 1, B = 2;    
    Callback_Act(A, Callback_A);    
    Callback_Act(B, Callback_B);    
    printf("Main program has done.");
    return 0;
}
