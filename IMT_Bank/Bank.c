#include "Bank.h"
#include "Configurtion.h"

client Client_Acc[NUMBER_OF_CLIENTS]={{"Karim Mohamed","6th Of October City",21,.Account_Status=ACTIVE,.Balance=50000 ,.Password=369852,.Client_ID=1000000000,.National_ID=30011092600255},
                                      {"Ali Khaled   ","Cairo City         ",37,.Account_Status=ACTIVE,.Balance=100000,.Password=258741,.Client_ID=1000000001,.National_ID=28525873614958}};
/*Create Two Clients*/
u16 client_number=BASE_CLIENT_NUMBER+EXIST_CLIENTS  ;//Number of exist clients in system
u32 password =BASE_PASSWORD                         ;//Random Password
u32 client_id=BASE_ID       + EXIST_CLIENTS         ;//Base id starts 1000000000
u8  check_id  =NOT_FOUND                            ;//Flag to check client if exist on system or not
u8  user                                            ;//User client or admin


void main_window()
{
    /**this function is main window
      main window is starting window
      it is displayed for user to choice the user**/
    printf("********************************************************\n");
    u8 menu;
    do
    {
        printf("Please enter  \n1-Admin Menu.\n2-Client Menu         \n");
        scanf("%c",&menu                                                );
        fflush(stdin                                                    );
        switch(menu                                                     )
        {
            case CHOICE1 :admin_window(                                 );
                          break                                          ;
            case CHOICE2 :client_window(                                );
                          break                                          ;
            default      :printf("Invalid input please try again     \n");
                          break                                          ;
        }

    }while( (menu!=CHOICE1) && (menu!=CHOICE2)                          );

}

u16 check_client_acc_id(u32 id)
{
    /**this function to check id of client is it exist in system
       the function take an id and return number of client in the system**/
    u16 client_num                                                   ;

    if( (id>=BASE_ID) && (id<client_id)                              )
    {
        client_num=id-BASE_ID                                        ;
    }
    else
    {
        client_num=NOT_FOUND                                         ;//id not exist in the system
    }

    return client_num                                                ;
}

void account_details(u16 client_num)
{
    /**this function to print client account details**/
    printf("********************************************************\n"                          );
    printf("The account details is             \n"                                               );
    printf("Name: %s                           \n",Client_Acc[client_num].Name                   );
    printf("Address: %s                        \n",Client_Acc[client_num].Address                );
    printf("Age: %d                            \n",Client_Acc[client_num].Age                    );
    if    (Client_Acc[client_num].Age>=21                                                        )
          {
            printf("National ID: %llu          \n",Client_Acc[client_num].National_ID            );
          }
    else
          {
            printf("Guardian Name: %s          \n",Client_Acc[client_num].Guardian_Name          );
            printf("Guardian National ID: %llu \n",Client_Acc[client_num].Guardian_National_ID   );
          }
    printf("Bank Account ID : %d               \n",Client_Acc[client_num].Client_ID              );
    printf("Balance: %d                        \n",Client_Acc[client_num].Balance                );
    printf("Account Status: Active             \n"                                               );

}


void Exit()
{
    /**Terminate the system**/
    printf("********************************************************\n");
    printf("System shutdown.\n                                        ");
}
