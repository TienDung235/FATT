/***************************************************************************************************
* Include
***************************************************************************************************/
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include "HAL.h"
#include "fat.h"
/***************************************************************************************************
 * Definitions
***************************************************************************************************/

/***************************************************************************************************
 * Variables
***************************************************************************************************/

/***************************************************************************************************
* Main
***************************************************************************************************/
int main(){
    FILE* f;
    uint8_t sector[1000000];
    uint32_t Bytes_per_sector =0;
    uint32_t sectors_per_cluster =0;
    uint32_t Reserved_sectors =0;
    uint32_t NumberofFATs =0;
    uint32_t Root_entries =0;
    uint32_t Total_sectors =0;
    uint32_t  sectors_FAT =0;
    uint32_t root_of_set =0;
    uint32_t Addr_data=0;
    uint32_t Addr_File_data=0;
    uint32_t root_dir=0;
    int32_t count =1;
    uint8_t* entry;
    uint16_t choice;
    uint32_t cluster =0;
    uint32_t add_sector =0;
    uint32_t index;

  
    f= fopen("G://file2.ima","rb");
    if(f == NULL){
        printf("Cannot open file");
    }
    else{
        fread(sector, sizeof(sector),1,f);
         
        Bytes_per_sector    = Convert(sector[0x0B], sector[0x0C]);
        sectors_per_cluster = Convert(sector[0x0D], 0);
        Reserved_sectors    = Convert(sector[0x0E], sector[0x0F]);
        NumberofFATs        = Convert(sector[0x10], 0);
        Root_entries        = Convert(sector[0x11], sector[0x12]);
        Total_sectors       = Convert(sector[0x13], sector[0x14]);
        sectors_FAT         = Convert(sector[0x16], sector[0x17]);
        
        root_of_set = (Reserved_sectors + NumberofFATs * sectors_FAT)*Bytes_per_sector;
        Addr_data   = (Reserved_sectors + NumberofFATs * sectors_FAT)+Root_entries*32/
        Bytes_per_sector;
        root_dir    = 32*Root_entries/512;
        
        fseek(f,root_of_set, SEEK_SET); 
        
        printf("No Name              attribule             created                size\n\n");
        for(index =0; index< root_dir; index++){
            fseek(f,root_of_set+index*512, SEEK_SET);
            fread(sector, 512, 1,f);
            if(sector[0x00] != 0x00){
                lis_entry_sector(sector,&count);
            }
        }
        
  
        do{
            printf("Enter option: ");
            scanf("%d",&choice);
            system("cls");
            cluster = getClusof_entry(choice, sector);
            if( cluster != 0){
                add_sector = ClustoSector(Addr_data, cluster,sectors_per_cluster);
            }
            else{
                add_sector = (Reserved_sectors + NumberofFATs * sectors_FAT)*Bytes_per_sector;
            }
            fseek(f,add_sector,SEEK_SET);
            fread(sector,512*root_dir,1,f);
            printf("No Name              attribule             created                size\n\n");
            lis_entry_sector(sector,&count);
        }while(choice !=0);
    }
             
    fclose(f);
    return 0;
}
/***************************************************************************************************
* EOF
***************************************************************************************************/
