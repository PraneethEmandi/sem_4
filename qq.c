#include <stdio.h>

int main() {
    int var=1,sum=0;
    {
        int var;
        for(var=0;var<10;var++)
            sum+=var;
        
    }
    printf("sum=%d var=%d",sum,var);
    return 0;
}