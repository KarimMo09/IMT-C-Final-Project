#ifndef Bank_H
#define Bank_H

#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"
#include "Configurtion.h"

typedef struct client
                    {
                        u8   Name[LENGTH]           ;
                        u8   Address[LENGTH]        ;
                        u8   Age                    ;
                        u8   Guardian_Name[LENGTH]  ;
                        u8   Account_Status         ;
                        u32  Password               ;
                        u32  Balance                ;
                        u32  Client_ID              ;
                        u64  Guardian_National_ID   ;
                        u64  National_ID            ;

                    }client                         ;

void client_account_operation  (u16);
void admin_account_operation   (u16);
u16  check_client_acc_id       (u32);
void account_details           (u16);
void create_account            (   );
void client_window             (   );
void admin_window              (   );
void admin_access              (   );
void main_window               (   );
void transaction               (u16);
void get_cash                  (u16);
void open_acc                  (   );
void deposit                   (u16);
void Exit                      (   );
#endif // Bank_H


