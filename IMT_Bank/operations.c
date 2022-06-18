#include "Bank.h"
#include "Configurtion.h"
extern u16 client_number                   ;
extern client Client_Acc[NUMBER_OF_CLIENTS];
extern u32 password                        ;//Random Password
extern u32 client_id                       ;//Base id starts 1000000000
extern u8  check_id                        ;//Flag to check client if exist on system or not
extern u8  user                            ;//User client or admin


void transaction(u16 client_num)
{
    /**this function for transaction from account to anther account
       ask user to enter id of receiver client then check if receiver account is active or not **/
    printf("********************************************************\n"                                      );
    u8  choice                                                                                                ;
    u32 amount                                                                                                ;
    u32 reciever_client_ID                                                                                    ;
    u16 reciever_client_num                                                                                   ;
    do
    {
        printf("Please Bank Account ID of the receiver:"                                                     );
        scanf("%lu",&reciever_client_ID                                                                      );
        fflush(stdin)                                                                                         ;
        reciever_client_num=check_client_acc_id(reciever_client_ID                                           );
        if(reciever_client_num==NOT_FOUND                                                                    ) //check if receiver account is exist
        {
            /**ID of Receiver client  is NOT found
            Receiver client   Account is NOT exist **/
            printf("Invalid ID.                           \n"                                                );
            printf("Enter\n1-Exit.\n2-Re enter the ID.    \n"                                                );//ask user to reenter the id or exit this transaction
            scanf("%c",&choice                                                                               );
            fflush(stdin                                                                                     );
            if(choice==CHOICE2                                                                               )
            {
                continue                                                                                      ;//user want to reenter id
            }
            else
            {

            }
        }
        else if(reciever_client_ID==Client_Acc[client_num].Client_ID                                         ) //check receiver and sender id are not the same
        {
            printf("You entered your id.                   \n"                                               );
            printf("Enter\n1-Exit.\n2-Re enter the ID.     \n"                                               );//ask user to reenter the id or exit this transaction
            scanf("%c",&choice                                                                               );
            fflush(stdin                                                                                     );
            if(choice==CHOICE2                                                                               )
            {
                continue                                                                                      ;//user want to reenter id
            }
            else
            {

            }
        }
        else
        {
            /**ID of Receiver client is found
            Receiver client Account is exist**/
            printf("Receiver client is:%s\n",Client_Acc[reciever_client_num].Name                            );
            printf("Enter\n1-Exit.\n2-Re enter the ID.\n3-Confirm\n"                                         );
            scanf("%c",&choice                                                                               );//ask user to confirm found id or reenter anther one
            fflush(stdin                                                                                     );
            if(choice==CHOICE2                                                                               )
            {
                continue                                                                                      ;//user want to reenter id
            }
            else
            {

            }
            if(Client_Acc[reciever_client_num].Account_Status==ACTIVE                                        ) //check if Receiver account is active or not
            {
                switch(choice                                                                                ) //if id is correct and user confirmed it and received account is active
                        {                                                                                      // CHOICE3 if user confirmed
                            case CHOICE3:printf("Please enter the amount :"                                  );//ask him about amount
                                         scanf("%lu",&amount                                                 );
                                         fflush(stdin                                                        );
                                         if((amount<=Client_Acc[client_num].Balance)&&(amount>0)             ) //amount should be equal or more than his balance and not equal zero
                                         {
                                            Client_Acc[client_num].Balance-=amount                            ;//transfer money from sender
                                            Client_Acc[reciever_client_num].Balance+=amount                   ;//to receiver
                                            printf("Your New Balance is %lu\n",Client_Acc[client_num].Balance);
                                            printf("Transaction Completed Successfully.    \n"               );
                                         }
                                         else if( amount>Client_Acc[client_num].Balance                      )//amount is more than the balance sender
                                         {
                                            printf("Your Balance is less than the amount.  \n"               );
                                            printf("Your balance is %lu.\n",Client_Acc[client_num].Balance   );
                                            printf("Transaction failed.                    \n"               );
                                         }
                                         else
                                         {
                                            printf("Invalid input.                         \n"               );//user enter a negative or zero amount
                                            printf("Transaction failed.                    \n"               );
                                         }
                                         break                                                                ;
                            default     :printf("Transaction failed.                       \n"               );
                                         break                                                                ;
                      }
            }
            else                                                                                             //receiver account not active
            {
               printf("Receiver client account is Not Activated.               \n"                           );
               printf("Transaction failed.                                     \n"                           );
            }
        }
        if(choice==CHOICE1                                                                                   ) //user want to exit loop without correct id
        {
            break                                                                                             ;
        }
    }while(choice==CHOICE2 || reciever_client_num==NOT_FOUND                                                 );//exit loop if user confirm id or exit if user want that





    /** After completing transaction successfully or not
        ask user whe he want to do **/

    printf("Enter\n1-New Transaction.                                  \n"                                   );
    printf("2-New Operation\n3-User Menu.\n4-Return to Main menu.      \n"                                   );
    scanf("%c",&choice                                                                                       );
    fflush(stdin                                                                                             );
    switch(choice)
    {
        case CHOICE1 :transaction(client_num                                                                 );
                      break                                                                                   ;
        case CHOICE2 :switch(user                                                                            ) //user chose to return to previous menu or enter wrong choice
                        {
                            case ADMIN :admin_account_operation(client_num                                   );
                                        break                                                                 ;
                            case CLIENT:client_account_operation(client_num                                  );
                                        break                                                                 ;
                            default    :break                                                                 ;
                        }
                      break                                                                                   ;
        case CHOICE4 :main_window(                                                                           );
                      break                                                                                   ;
        case CHOICE3 :
        default      :switch(user                                                                            ) //user chose to return to previous menu or enter wrong choice
                        {
                            case ADMIN :admin_access(                                                        );
                                        break                                                                 ;
                            case CLIENT:client_window(                                                       );
                                        break                                                                 ;
                            default    :break                                                                 ;
                        }
                      break                                                                                   ;

    }
}

void get_cash(u16 client_num)
{
    /**this function to withdraw money from bank to client
       ask user the id of client**/
    printf("********************************************************\n"               );
    u32 amount                                                                         ;
    u8  choice                                                                         ;
    printf("Please enter the amount :"                                                );
    scanf("%lu",&amount                                                               );
    fflush(stdin                                                                      );
    if(amount<=Client_Acc[client_num].Balance && amount>0                             )//amount should be equal or more than his balance and not equal zero
    {
        Client_Acc[client_num].Balance-=amount                                         ;
        printf("Withdraw Completed Successfully.    \n"                               );
        printf("Your Balance after operation is %lu.\n",Client_Acc[client_num].Balance);

    }
    else if(amount>Client_Acc[client_num].Balance                                     )
    {
        printf("Your Balance is less than the amount\n"                               );
        printf("Your balance is %lu.                \n",Client_Acc[client_num].Balance);
        printf("Withdraw failed.                    \n"                               );
    }
    else
    {
        printf("Invalid input.                      \n"                               );
        printf("Withdraw failed.                    \n"                               );
    }
    /** After completing transaction successfully or not
        ask user whe he want to do **/
    printf("Enter\n1-New withdraw.                   \n"                              );
    printf("2-New Operation\n3-User Menu.\n4-Return to Main menu.\n"                  );
    scanf("%c",&choice                                                                );
    fflush(stdin                                                                      );
    switch(choice)
    {
        case CHOICE1:get_cash(client_num);
                     break;
        case CHOICE2 :switch(user                                                      ) //user chose to return to previous menu or enter wrong choice
                        {
                            case ADMIN :admin_account_operation(client_num             );
                                        break                                           ;
                            case CLIENT:client_account_operation(client_num            );
                                        break                                           ;
                            default    :break                                           ;
                        }
                      break                                                             ;
        case CHOICE4 :main_window();
                      break;
        case CHOICE3 :
        default      :switch(user                                                       ) //user chose to return to previous menu or enter wrong choice
                        {
                            case ADMIN :admin_access(                                   );
                                        break                                            ;
                            case CLIENT:client_window(                                  );
                                        break                                            ;
                            default    :break                                            ;
                        }
                      break                                                              ;
    }
}

void deposit(u16 client_num)
{
    /**this function to deposit in the account **/
    printf("********************************************************\n"                          );
    u32 amount                                                                                    ;
    u8 choice                                                                                     ;
    printf("Please enter the amount :"                                                           );
    scanf("%lu",&amount                                                                          );
    fflush(stdin                                                                                 );
    Client_Acc[client_num].Balance+=amount                                                       ;
    printf("Deposit Completed Successfully.                                                   \n");
    printf("Your New Balance is %lu \n",Client_Acc[client_num].Balance                           );

    printf("Enter\n1-New Deposit\n2-New Operation\n3-User Menu.\n4-Return to Main menu.       \n");
    scanf("%c",&choice                                                                           );
    fflush(stdin                                                                                 );
    switch(choice)
    {
        case CHOICE1 :deposit(client_num                                                         );
                      break                                                                       ;
        case CHOICE2 :switch(user                                                                ) //user chose to return to previous menu or enter wrong choice
                        {
                            case ADMIN :admin_account_operation(client_num                       );
                                        break                                                     ;
                            case CLIENT:client_account_operation(client_num                      );
                                        break                                                     ;
                            default    :break                                                     ;
                        }
                      break                                                                       ;
        case CHOICE4 :main_window(                                                               );
                      break                                                                       ;
        case CHOICE3 :
        default      :switch(user                                                                ) //user chose to return to previous menu or enter wrong choice
                        {
                            case ADMIN :admin_access(                                            );
                                        break                                                     ;
                            case CLIENT:client_window(                                           );
                                        break                                                     ;
                            default    :break                                                     ;
                        }
                      break                                                                       ;
    }

}

void change_status(u16 client_num)
{
    /**this function to change account status by admin**/
    printf("********************************************************\n"                            );
    u8 choice                                                                                       ;
    switch(Client_Acc[client_num].Account_Status                                                   )
           {
               case ACTIVE     :printf("Enter \n1-Restrict.\n2-Close.                       \n"    );
                                scanf("%c",&choice                                                 );
                                fflush(stdin                                                       );
                                switch(choice                                                      )
                                {
                                    case CHOICE1:Client_Acc[client_num].Account_Status=RESTRICTED   ;
                                                 printf("Account Restricted Successfully.   \n"    );
                                                 break                                              ;
                                    case CHOICE2:Client_Acc[client_num].Account_Status=CLOSED       ;
                                                 printf("Account Closed Successfully.       \n"    );
                                                 break                                              ;
                                    default     :printf("Invalid input.                     \n"    );
                                                 printf("Operation Failed.                  \n"    );

                                                 break                                              ;
                                }
                                break;
               case CLOSED     :printf("Enter \n1-Restrict.\n2-Activate.                     \n"   );
                                scanf("%c",&choice                                                 );
                                fflush(stdin                                                       );
                                switch(choice                                                      )
                                {
                                    case CHOICE1:Client_Acc[client_num].Account_Status=RESTRICTED   ;
                                                 printf("Account Restricted Successfully.   \n"    );
                                                 break                                              ;
                                    case CHOICE2:Client_Acc[client_num].Account_Status=ACTIVE       ;
                                                 printf("Account Activated Successfully.    \n"    );
                                                 break                                              ;
                                    default     :printf("Invalid input.                     \n"    );
                                                 printf("Operation Failed.                  \n"    );
                                                 break                                              ;
                                }
                                break                                                               ;
               case RESTRICTED :printf("Enter \n1-Close.\n2-Activate.                       \n"    );
                                scanf("%c",&choice                                                 );
                                fflush(stdin                                                       );
                                switch(choice                                                      )
                                {
                                    case CHOICE1:Client_Acc[client_num].Account_Status=CLOSED       ;
                                                 printf("Account Closed Successfully.       \n"    );
                                                 break                                              ;
                                    case CHOICE2:Client_Acc[client_num].Account_Status=ACTIVE       ;
                                                 printf("Account Activated Successfully.    \n"    );
                                                 break                                              ;
                                    default     :printf("Invalid input.                     \n"    );
                                                 printf("Operation Failed.                  \n"    );

                                                 break                                              ;
                                }
                                break                                                               ;
             default           :break                                                               ;
           }

    printf("Enter\n1-New Operation\n2-Admin Menu. \n3-Return to Main menu.                      \n");
    scanf("%c",&choice                                                                             );
    fflush(stdin                                                                                   );
    switch(choice)
    {
        case CHOICE1 :admin_account_operation(client_num                                           );
                      break                                                                         ;
        case CHOICE3 :main_window(                                                                 );
                      break                                                                         ;
        case CHOICE2 :
        default      :admin_access(                                                                );
                      break                                                                         ;
    }

}
void change_password(u16 client_num)
{
    /***this function to change password by the client ***/
    printf("********************************************************    \n"  );
    u32 old_password                                                          ;
    u8 attempts=INITIAL_ATTEMPTS                                              ;
    u8 choice                                                                 ;

    while(attempts!=NUM_OF_ATTEMPTS)
    {
        printf("Please enter old password:"                                  );
        scanf("%lu",&old_password                                            );
        fflush(stdin                                                         );
        attempts++                                                            ;
        if(old_password==Client_Acc[client_num].Password                     ) //check if old password is correct
        {
            printf("Please enter new password:"                              );
            printf("Password must consist of 6 digits.                    \n");
            scanf("%lu",&Client_Acc[client_num].Password                     );
            fflush(stdin                                                     );
            printf("Password updated successfully.                        \n");
            attempts=NUM_OF_ATTEMPTS                                          ;//break loop when old password is correct
        }
        else
        {
            if(attempts==NUM_OF_ATTEMPTS)
            {
                printf("Incorrect password please call bank support.      \n");
            }
            else
            {
                printf("Incorrect Password.                               \n");
                printf("Remains %d tries\n",NUM_OF_ATTEMPTS-attempts         );
                printf("please try again.                                 \n");
            }

        }
    }
    printf("Enter\n1-New Operation\n2-Client Menu.\n3-Return to Main menu.\n");
    scanf("%c",&choice                                                       );
    fflush(stdin                                                             );
    switch(choice)
    {
        case CHOICE1 :client_account_operation(client_num                    );
                      break                                                   ;
        case CHOICE3 :main_window(                                           );
                      break                                                   ;
        case CHOICE2 :
        default      :client_window(                                         );
                      break                                                   ;
    }

}
