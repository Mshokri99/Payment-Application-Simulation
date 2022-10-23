
#ifndef _SERVER_H_
#define _SERVER_H_
#include "terminal.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;


typedef struct ST_accountsDB
{
	uint8_t primaryAccountNumber[20];
	float balance ;
	EN_accountState_t state;
}ST_accountsDB;


 
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;



EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t*);
EN_serverError_t isBlockedAccount();
EN_serverError_t isAmountAvailable(ST_terminalData_t*);
EN_serverError_t saveTransaction(ST_transaction_t*);
void listSavedTransactions(void);

#endif 
