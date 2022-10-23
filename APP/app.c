#ifndef _APP_C_
#define _APP_C_

#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
#include "app.h"

EN_cardError_t handle_card_err;
ST_cardData_t cardData;
EN_terminalError_t handle_term_err;
ST_terminalData_t termData;
EN_transState_t handle_SERV_err;
ST_transaction_t transData = { 0 };


void appStart(void) {

	 handle_card_err = getCardHolderName(&(transData.cardHolderData));
	
		while (handle_card_err == WRONG_NAME) {
			printf("\nWRONG_NAME\n");
			printf("Re-enter:\n");
			handle_card_err = getCardHolderName(&(transData.cardHolderData));
		}
		if (handle_card_err == CARD_OK) {
			printf("\CARD_OK\n");
		}

		handle_card_err = getCardExpiryDate(&(transData.cardHolderData));
		
		while (handle_card_err == WRONG_EXP_DATE) {
			printf("\nWRONG_EXP_DATE\n");
			printf("Re-enter:\n");
			handle_card_err = getCardExpiryDate(&(transData.cardHolderData));
		}
		if (handle_card_err == CARD_OK) {
			printf("\CARD_OK\n");
		}

		handle_card_err = getCardPAN(&(transData.cardHolderData));
		
		while (handle_card_err == WRONG_PAN) {
			printf("\nWRONG_PAN\n");
			printf("Re-enter:\n");
			handle_card_err = getCardPAN(&(transData.cardHolderData));
		}
		if (handle_card_err == CARD_OK) {
			printf("\CARD_OK\n");
		}
		
		/////////////////////////////////////////////

		handle_term_err = getTransactionDate(&(transData.terminalData));
		if (handle_term_err == WRONG_DATE) {
			printf("\WRONG_DATE\n");
		}
		else if (handle_term_err == TERMINAL_OK) {
			printf("\nTERMINAL_OK\n");

		}

		handle_term_err = isCardExpired(transData.cardHolderData, transData.terminalData);
		if (handle_term_err == EXPIRED_CARD) {
			printf("\nEXPIRED_CARD\n");
			return; 
		}
		else if (handle_term_err == TERMINAL_OK) {
			printf("\nTERMINAL_OK(NOT_EXPIRED_CARD)\n");

		}
		
		handle_term_err = setMaxAmount(&(transData.terminalData));
	    while (handle_term_err == INVALID_MAX_AMOUNT) {
		printf("\nINVALID_MAX_AMOUNT\n");
		printf("Re-enter:\n");
		handle_term_err = setMaxAmount(&(transData.terminalData));
	     }
	     if (handle_term_err == TERMINAL_OK)
	      {
		     printf("\nTERMINAL_OK\n");
	      }

		handle_term_err = getTransactionAmount(&(transData.terminalData));
		while (handle_term_err == INVALID_AMOUNT) {
			printf("\nINVALID_AMOUNT\n");
			printf("Re-enter:\n");
			handle_term_err = getTransactionAmount(&(transData.terminalData));
		}
		if (handle_term_err == TERMINAL_OK)
		{
			printf("\nTERMINAL_OK(getTransactionAmount)\n");
		}

		handle_term_err = isBelowMaxAmount(&(transData.terminalData));
		while (handle_term_err == EXCEED_MAX_AMOUNT) {
			printf("\nEXCEED_MAX_AMOUNT\n");
			printf("Re-enter(getTransactionAmount)-:\n");
			handle_term_err = getTransactionAmount(&(transData.terminalData));
			handle_term_err = isBelowMaxAmount(&(transData.terminalData));
			
		}
		 if (handle_term_err == TERMINAL_OK)
		{
			printf("\nTERMINAL_OK(NOT_EXCEED_MAX_AMOUNT)\n");
		}

		

		//////////////////////////////////////////////////
		handle_SERV_err = recieveTransactionData(&transData);
		if (handle_SERV_err == FRAUD_CARD) {
			printf("\nFRAUD_CARD\n");
		}
		if (handle_SERV_err == DECLINED_INSUFFECIENT_FUND) {
			printf("\nDECLINED_INSUFFECIENT_FUND\n");
		}
		if (handle_SERV_err == INTERNAL_SERVER_ERROR) {
			printf("\n INTERNAL_SERVER_ERROR\n");
		}
		if (handle_SERV_err == APPROVED) {
			printf("\nAPPROVED\n");
		}

		cardData = transData.cardHolderData;
		handle_SERV_err = isValidAccount(&(cardData));
		if (handle_SERV_err == ACCOUNT_NOT_FOUND) {
			printf("\ACCOUNT_NOT_FOUND\n");
		}
		
		handle_SERV_err = isBlockedAccount();
		if (handle_SERV_err == BLOCKED_ACCOUNT) {
			printf("\BLOCKED_ACCOUNT\n");
		}
		handle_SERV_err = isAmountAvailable(&(transData.terminalData));
		if (handle_SERV_err == LOW_BALANCE) {
			printf("\nLOW_BALANCE\n");
		}
		else {
			printf("\SERVER_OK(NOT_low_balance)\n");

		}
		handle_SERV_err = saveTransaction(&(transData));


		listSavedTransactions();
}
#endif