#ifndef _fat_H_
#define _fat_H_

/***************************************************************************************************
* Macro
***************************************************************************************************/
#define Convert(x1,x2) ((x2<<8) + (x1))
#define Convert4(x1,x2,x3,x4)  ((x4<<24) +(x3<<16) +(x2<<8) +(x1))
#define ClustoSector(x1,x2,x3) (((x1)+(x2-2)*(x3))*512)
/***************************************************************************************************
 * Definitions
***************************************************************************************************/

typedef struct{
    uint8_t name[8];
    uint8_t extension[3];
    uint8_t Attribute;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint32_t size;
    uint32_t year;
    
}Fat_entry;
/***************************************************************************************************
* API
***************************************************************************************************/
/* @brief :The function prints out the parameters of the entry
 * @param :array passed in 
 * @param :counting variable
 * @return: None
 */

void read_entry(uint8_t entry[], uint32_t *count);
/* @brief :function reads entry in 1 sector
 * @param :array passed in
 * @param :counting variable
 * @return: None
 */
void lis_entry_sector( uint8_t sector[], uint32_t* count);

/* @brief : function to get cluster of entry
 * @param :array passed in
 * @param :counting variable
 * @return: cluster to find
 */
uint32_t getClusof_entry(uint32_t choice, uint8_t sector[]);

#endif /* _FAT_H */

/***************************************************************************************************
* EOF
***************************************************************************************************/
