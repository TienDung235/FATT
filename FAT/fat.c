#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "fat.h"

/***************************************************************************************************
 * Definitions
***************************************************************************************************/

/***************************************************************************************************
 * Variables
***************************************************************************************************/

/***************************************************************************************************
* Prototype
***************************************************************************************************/

/***************************************************************************************************
* Function
***************************************************************************************************/
void read_entry(uint8_t entry[], uint32_t* count){
    uint32_t index;
    uint32_t index1;
    uint32_t temp =*count;
    Fat_entry* f1;
    f1= (Fat_entry*)malloc(240 * sizeof(Fat_entry));
    if((entry[0x00] != 0x00) && ((entry[0x0B] == 0x00) || ((entry[0x0B]&0x10) == 0x10)) &&
    entry[0x0B] != 0x0F){
        printf("%d  ", temp);
        (*count)++;
        for( index1 = 0; index1 < 8; index1 ++){
            f1[index].name[index1] = entry[index1];
            printf("%c",f1[index].name[index1]);
        }
        printf(".");
        for( index1 = 8; index1 < 11; index1 ++){
            f1[index].extension[index1-8] = entry[index1];
            printf("%c", f1[index].extension[index1-8]);
        }
        f1[index].Attribute = entry[11];
        switch(f1[index].Attribute){
            case 0x00:
                printf("      File       ");
                break;
                        
            case 0x01 :
                printf("      Read only  ");
                break;
                        
            case 0x02:
                printf("      Hidden file  ");
                break;
                        
            case 0x08:
                printf("      Volum label  ");
                break;
                        
            case 0x10:
                printf("      Subdirectory  ");
                break;
        }
        if(f1[index].Attribute == 0x00 ){

            f1[index].hour = Convert(entry[14],entry[15])>>11;
            f1[index].minute =(Convert(entry[14],entry[15])>>5)&0x3F;
            f1[index].second = (Convert(entry[14],entry[15]))&0x1F;
                    
            f1[index].year = (Convert(entry[16],entry[17]) >> 9)+1980;
            f1[index].month =(Convert(entry[16],entry[17]) >> 5)&0x3F;
            f1[index].day =(Convert(entry[16],entry[17]))&0x1F;
                    
            f1[index].size = Convert4(entry[28],entry[29],entry[30],entry[31]);
                                    
            printf("     %02d-%02d-%02d  - %02d:%02d:%02d", f1[index].year, f1[index].month, 
            f1[index].day, f1[index].hour, f1[index].minute,f1[index].second*2);
                    
            printf("        %d",f1[index].size);
        }
    }
    printf("\n");
    free(f1);
}

void lis_entry_sector( uint8_t sector[], uint32_t* count){
    uint32_t index =0;
    uint8_t* entry;
    while(index<512){
        entry = &sector[index];
        read_entry(entry,count);
        index+=32;
    }
}

uint32_t getClusof_entry(uint32_t choice, uint8_t sector[]){
    uint8_t* entry;
    uint32_t count =0;
    uint32_t index =0;
    uint32_t index1=0;
    uint32_t clusr =0;
    for(index1 =0; index1<15; index1++){
        
    }
    while((index<512) && (count != choice)){
        entry = & sector[index];
        if(entry[0x0B] !=0x0F){
            count++;
        }
        index+=32;
    }
    clusr = Convert(entry[0x1A],entry[0x1B]);
    return clusr;
}
/***************************************************************************************************
* EOF
***************************************************************************************************/




