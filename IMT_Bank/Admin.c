#include "Bank.h"
#include "Configurtion.h"
extern u16 client_number                   ;
extern client Client_Acc[NUMBER_OF_CLIENTS];
extern u32 password                        ;//Random Password
extern u32 client_id                       ;//Base id starts 1000000000
extern u8  check_id                        ;//Flag to check client if exist on system or not
extern u8  user                            ;//User client or admin

void admin_window()
{
    printf("********************************************************\n"    );
    /**this function for admin entry**/
    u8  attempts=INITIAL_ATTEMPTS                                           ;
    u8  Admin[LENGTH]                                                       ;
    u32 password                                                            ;

    while(attempts!=NUM_OF_ATTEMPTS                                        ) //check number of attempts
    {
        attempts++                                                          ;
        printf("User name :"                                               );
        gets(Admin                                                         );

        printf("Password :"                                                );
        scanf("%lu",&password                                              );
        fflush(stdin                                                       );
        if(  !strcmp( Admin,ADMIN_NAME)  &&  (password==ADMIN_PASSWORD)    )//check admin user name and password
        {
            printf("Welcome %s\n",ADMIN_NAME                               );
            user=ADMIN                                                      ;//set admin as the user
            admin_access(                                                  );//access to admin menu
            attempts=NUM_OF_ATTEMPTS                                        ;//terminate the loop
        }
        else
        {
            if(attempts==NUM_OF_ATTEMPTS                                   )
            {
                printf("Incorrect User please call Technical support.    \n");
                Exit(                                                       );
            }
            else
            {
                printf("Invalid User name or Password.                   \n");
                printf("Remains %d tries\n",NUM_OF_ATTEMPTS-attempts        );
                printf("please try again                                 \n");
            }
        }
    }
}
void admin_access()
{
    printf("********************************************************\n"             );
    /**this function for admin menu
      admin can create or open an existing account **/
    u8 admin_choice;

    do
    {
        printf("Please Enter :\n1-for Creating a new account \n"                    );
        printf("2-for Open an existing account               \n"                    );
        printf("3-for Main Menu                              \n"                    );
        printf("4-for Exit                                   \n"                    );
        scanf("%c",&admin_choice                                                    );
        fflush(stdin                                                                );

        switch(admin_choice                                                         )
        {
            case CHOICE1:create_account(                                            );
                         break                                                       ;
            case CHOICE2:open_acc(                                                  );
                         break                                                       ;
            case CHOICE3:main_window(                                               );
                         break                                                       ;
            case CHOICE4:Exit(                                                      );
                         break                                                       ;
            default     :printf("Invalid input\n"                                   );//admin enter not allowed number
                         break                                                       ;
       }

    }while((admin_choice!=CHOICE1)&& (admin_choice!=CHOICE2)&&( admin_choice!=CHOICE3) &&( admin_choice!=CHOICE4));

}

void admin_account_operation(u16 client_num)
{
    printf("********************************************************\n");
    /**this function for operation can done by admin**/
    u8 operation                                     ;
    printf("Please enter an operation:  \n"         );
    printf("1-Withdraw money.           \n"         );
    printf("2-Deposit money.            \n"         );
    printf("3-Change account status.    \n"         );
    printf("4-Return to admin menu.     \n"         );
    printf("5-Return to Main menu.      \n"         );
    if(Client_Acc[client_num].Account_Status==ACTIVE)
    {
        printf("6-Make transaction.     \n"         );
    }
    else
    {
    }

    scanf("%c",&operation                           );
    fflush(stdin                                    );
    switch(operation                                )
        {
            case CHOICE1 :get_cash(client_num       );
                          break                      ;
            case CHOICE2 :deposit(client_num        );
                          break                      ;
            case CHOICE3 :change_status(client_num  );
                          break                      ;
            case CHOICE5 :main_window(              );
                          break                      ;
            if(Client_Acc[client_num].Account_Status==ACTIVE )
            {
                case CHOICE6 :transaction(client_num     );
                              break                       ;
            }
            case CHOICE4 :
            default      :admin_access(                  );
                          break                           ;
        }
}

void open_acc()
{
    /**this function to open an existing account by admin
       the function ask admin for client id then open operation window **/
    printf("********************************************************\n" );
    u32 ID                                                               ;
    u16 client_num                                                       ;
    u8  choice                                                           ;
    printf("Please enter the client ID: "                               );
    scanf("%lu",&ID                                                     );
    fflush(stdin                                                        );
    client_num=check_client_acc_id(ID                                   );
    do
    {

        printf("Wrong ID.\nPlease Check ID number:%lu\n",ID             );
        printf("Enter :\n1-Re enter the ID.\n"                          );
        printf("2-Return to Previous Menu.\n"                           );
        scanf ("%c",&choice                                             );
        fflush(stdin                                                    );
        switch(choice                                                   )
        {
            case CHOICE1  : printf("Re enter ID: "                      );
                            scanf("%lu",&ID                             );
                            fflush(stdin                                );
                            client_num=client_num=check_client_acc_id(ID);
                            break                                        ;
            case CHOICE2  :
            default       :admin_access(                                );
                            break                                        ;
        }
    } while(   (client_num==NOT_FOUND)   &&   (choice!=CHOICE2)         );//break loop when id is found or admin make choice2
    if(client_num==NOT_FOUND                                            )//loop break cause admin make choice2
    {
    }
    else                                                                 //loop breaked because id is found
    {
      printf("Welcome Mr %s\n",Client_Acc[client_num].Name              );
      admin_account_operation(client_num                                );
    }


}
void create_account()
{

    /**this function to create a new account by admin**/
    printf("********************************************************\n"    );
    printf("Please enter the client full name    :                    \n"  );
    gets  (Client_Acc[client_number].Name                                  );
    /**client_number is the client number in the system**/

    printf("Please enter the client full address :                    \n"  );
    gets  (Client_Acc[client_number].Address                               );

    printf("Please enter the client age          :                    \n"  );
    scanf ("%d",&Client_Acc[client_number].Age                             );
    fflush(stdin);
    if    (Client_Acc[client_number].Age>=21)
        {
            printf("Please enter the client National ID :             \n"  );
            scanf("%llu",&Client_Acc[client_number].National_ID            );
            fflush(stdin);
        }
    else
        {
            printf("Please enter the client guardian name :           \n"  );
            gets  (Client_Acc[client_number].Guardian_Name                 );

            printf("Please enter the client guardian national id :    \n"  );
            scanf ("%llu",&Client_Acc[client_number].Guardian_National_ID  );
            fflush(stdin);
        }
    printf("Please enter the client balance :\n"                           );
    scanf ("%lu",&Client_Acc[client_number].Balance                        );
    fflush(stdin);
    /**Set password and account id and activate the account**/
    Client_Acc[client_number].Account_Status=ACTIVE                         ;
    Client_Acc[client_number].Password      =password                       ;
    Client_Acc[client_number].Client_ID     =client_id                      ;
    printf("The Account is activated successfully\n"                       );
    /**Print Client account details after creating the account **/
    account_details(client_number                                          );
    client_number++                                                         ;//increase number of clients in system by 1
    password+=RANDOM_VALUE                                                  ;//add random number to password for new client
    client_id++                                                             ;//increase id for next new ckient
    admin_access(                                                          );//back to admin menu
}
