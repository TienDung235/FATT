#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


static FILE* s_f;
void HAL_initalize(uint8_t file_name){
    uint8_t buffer[512];
    s_f = fopen(file_name, "rb");
    if(s_f == NULL){
        printf("Cannot open file !!!");
    }
    else{
        fread(buffer,sizeof(buffer),1,s_f);
    }
}

void HAL_de_initalize(uint8_t file_name){
    fclose(s_f);
}
