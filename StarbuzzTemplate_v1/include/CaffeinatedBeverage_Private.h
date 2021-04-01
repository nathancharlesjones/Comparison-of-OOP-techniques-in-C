#ifndef CAFFEINATED_BEVERAGE_PRIVATE_H
#define CAFFEINATED_BEVERAGE_PRIVATE_H

typedef struct CaffeinatedBeverage_Interface_Struct* CaffeinatedBeverage_Interface;

typedef struct CaffeinatedBeverage_Data_Struct {
    CaffeinatedBeverage_Interface interface;
    //other base data
} CaffeinatedBeverage_Data_Struct;

typedef struct CaffeinatedBeverage_Interface_Struct {
    void (*brew)(CaffeinatedBeverage_Data_Struct*);
    void (*addCondiments)(CaffeinatedBeverage_Data_Struct*);
    void (*addWhip)(CaffeinatedBeverage_Data_Struct*);
} CaffeinatedBeverage_Interface_Struct;

#endif /*CAFFEINATED_BEVERAGE_PRIVATE_H*/
