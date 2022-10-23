#include"card.h"
#include "terminal.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
int  i,seq ;
float new_balance = 0 ;

//database data_base;
ST_cardData_t* cardData;
ST_terminalData_t* termData;
ST_transaction_t* transData;


ST_accountsDB ST_accountsDB_t[5] = { {"2160064867123456789", 5000.0   ,RUNNING },
                                       {"1234567891234567891", 20000.0  ,RUNNING },
                                       {"1234567891234567892", 10000.0  ,BLOCKED },
                                       {"1234567891234567893", 25000.0  ,RUNNING },
                                       {"1234567891234567894", 500.0    ,RUNNING },


};




 //  This function will take all transaction data and validate its data.
//It checks the account details and amount availability.
//If the account does not exist return DECLINED_STOLEN_CARD, if the amount is not available will return DECLINED_INSUFFECIENT_FUND, if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction, else returns APPROVED.
//It will update the database with the new balance.   
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

    for (i = 0; i < 5; i++) {
        if ((strcmp(ST_accountsDB_t[i].primaryAccountNumber, transData->cardHolderData.primaryAccountNumber) == 0)) 
        {
            break;
        }
    }
    if (ST_accountsDB_t[i].state == BLOCKED) {
        transData->transState = DECLINED_STOLEN_CARD;
                    return DECLINED_STOLEN_CARD;
    }

    if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
        transData->transState = FRAUD_CARD;
             return FRAUD_CARD;
    }

    else  if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    
    else   if (!transData->terminalData.transAmount || !transData->cardHolderData.primaryAccountNumber) {
        transData->transState = INTERNAL_SERVER_ERROR;
        return  INTERNAL_SERVER_ERROR;
    }
    else {
        transData->transState =  APPROVED ;
         
         }
           
}

//This function will take card data and validate these data.
//It checks if the PAN exists or not in the server's database.
//If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return ok
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {

        if (!(strcmp(ST_accountsDB_t[i].primaryAccountNumber , cardData->primaryAccountNumber))) {

            return SERVER_OK;
        }
        else {
            return ACCOUNT_NOT_FOUND;
        }
        
   

}

EN_serverError_t isBlockedAccount() {
    
    if (ST_accountsDB_t[i].state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    }
    else {
        return SERVER_OK; 
    }

}

//This function will take terminal data and validate these data.
//It checks if the transaction's amount is available or not.
//If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return ok
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
          
    
    if ( (ST_accountsDB_t[i].balance) < (termData->transAmount) ) {
        return  LOW_BALANCE;
    }
    
      new_balance = ST_accountsDB_t[i].balance - termData->transAmount;
      return SERVER_OK; 
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
   
    transData->transactionSequenceNumber = seq;
    seq++;

    switch (transData->transState) {
        
    case DECLINED_STOLEN_CARD :
        printf("\ntransState : DECLINED_STOLEN_CARD \n");
        break;
    case FRAUD_CARD :
        printf("\n transState : FRAUD_CARD \n");
        break;
    case DECLINED_INSUFFECIENT_FUND :
        printf("\ntransState : DECLINED_INSUFFECIENT_FUND \n");
        break;
    case INTERNAL_SERVER_ERROR:
        printf("\ntransState : INTERNAL_SERVER_ERROR \n");
        break;
    }
      
      if (transData->transState == APPROVED) {
        printf("######################### \n");
        printf("********TransData********\n");
        printf("\n transState : APPROVED " );
        printf("\nbalance before transaction = %f ", ST_accountsDB_t[i].balance);
        printf("\nwithdraw amount  = %f ", transData->terminalData.transAmount);
        printf("\nbalance after transaction = %f ", new_balance);

        printf("\n transactionSequenceNumber = %d ", transData->transactionSequenceNumber);
        printf("\n transaction date = %s ", transData->terminalData.transactionDate);

        printf("\n Cardholder Name:  %s ", transData->cardHolderData.cardHolderName);
        printf("\n pan :  %s ", transData->cardHolderData.primaryAccountNumber);
        printf("\n Card Expiration Date  = %s ", transData->cardHolderData.cardExpirationDate);

        printf("\n ######################### \n");
    }
}


void listSavedTransactions( ) {
   
   

}
      

