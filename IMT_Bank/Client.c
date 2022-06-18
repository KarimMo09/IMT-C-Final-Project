#include "Bank.h"
#include "Configurtion.h"
extern u16 client_number                   ;
extern client Client_Acc[NUMBER_OF_CLIENTS];
extern u32 password                        ;//Random Password
extern u32 client_id                       ;//Base id starts 1000000000
extern u8  check_id                        ;//Flag to check client if exist on system or not
extern u8  user                            ;//User client or admin

void client_window()
{
    printf("********************************************************\n"                   );
    /**this function for client entering**/
    u8  attempts=INITIAL_ATTEMPTS                                                          ;
    u32 password                                                                           ;
    u32 ID                                                                                 ;
    u16 client_num                                                                         ;


    while(attempts!=NUM_OF_ATTEMPTS                                                      ) //check number of attempts
    {
        attempts++                                                                         ;
        printf("Please enter the client ID:"                                              );
        scanf("%lu",&ID                                                                   );
        fflush(stdin                                                                      );
        printf("Please enter Password :"                                                  );
        scanf("%lu",&password                                                             );
        fflush(stdin                                                                      );
        client_num=check_client_acc_id(ID                                                 );
        if( ( client_num !=NOT_FOUND ) && ( password == Client_Acc[client_num].Password ) )
        {
            printf("Welcome  Mr %s\n",Client_Acc[client_num].Name                         );
            user=CLIENT                                                                    ;//set client as the user
            client_account_operation(client_num                                                  );//open operation window for client
            attempts=NUM_OF_ATTEMPTS                                                       ;
        }
        else                                                                                //client id or password was wrong so ask client to enter id and password again
        {
            printf("Invalid ID or Password\n"                                             );
            if(attempts<NUM_OF_ATTEMPTS                                                   )
            {
                printf("Remains %d tries\n",NUM_OF_ATTEMPTS -attempts                     );
                printf("please try again\n"                                               );
            }
            else
            {
                printf("Please Call Bank support\n"                                       );//client enter his password and id 4 times incorrectly so system closed frond of him.
                main_window(                                                              );
            }
        }
    }
}

void client_account_operation(u16 client_num)
{

    /**this function for operation can done by client**/
    printf("********************************************************\n");
    u8 operation                                                        ;
    printf("Please enter an operation:  \n"                            );
    printf("1-Withdraw money.           \n"                            );
    printf("2-Deposit money.            \n"                            );
    printf("3-Change account password.  \n"                            );
    printf("4-Return to  client menu.   \n"                            );
    printf("5-Return to Main menu.      \n"                            );
    if(Client_Acc[client_num].Account_Status==ACTIVE                   )
    {
        printf("6-Make transaction.     \n"                            );
    }

    scanf("%c",&operation                                              );
    fflush(stdin                                                       );
    switch(operation                                                   )
        {
            case CHOICE1 :get_cash(client_num                          );
                          break                                         ;
            case CHOICE2 :deposit(client_num                           );
                          break                                         ;
            case CHOICE3 :change_password(client_num                   );
                          break                                         ;
            case CHOICE5 :main_window(                                 );
                          break                                         ;
            if(Client_Acc[client_num].Account_Status==ACTIVE           )
            {
            case CHOICE6 :transaction(client_num                       );
                          break                                         ;
            }
            case CHOICE4 :
            default      :client_window(                               );
                              break                                     ;
        }
}

