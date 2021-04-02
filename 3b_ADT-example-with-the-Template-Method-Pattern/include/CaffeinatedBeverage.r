#ifndef CAFFEINATED_BEVERAGE_R
#define CAFFEINATED_BEVERAGE_R

#define MAX_CHARS_NAME 20

typedef struct CaffeinatedBeverage_Interface_Struct* CaffeinatedBeverage_Interface;

typedef struct CaffeinatedBeverage_Data_Struct {
    CaffeinatedBeverage_Interface interface;
    char name[MAX_CHARS_NAME];
} CaffeinatedBeverage_Data_Struct;

typedef struct CaffeinatedBeverage_Interface_Struct {
    void (*brew)(CaffeinatedBeverage_Data_Struct*);
    void (*addCondiments)(CaffeinatedBeverage_Data_Struct*);
    void (*addWhip)(CaffeinatedBeverage_Data_Struct*);
} CaffeinatedBeverage_Interface_Struct;

void caffeinatedBeverageDeinit( CaffeinatedBeverage_Data_Struct * _self );

#endif /*CAFFEINATED_BEVERAGE_R*/
