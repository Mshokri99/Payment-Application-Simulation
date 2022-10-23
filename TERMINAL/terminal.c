#include<stdio.h>
#include <time.h>
#include  "card.h"
#include "terminal.h"




EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    
    // The function will read the current date from your computer and store it into terminal data with the mentioned size and format
    time_t tt = time(NULL);
    struct tm* dt = localtime(&tt);
    int year = dt->tm_year + 1900;
    int month = dt->tm_mon + 1;
    int day = dt->tm_mday;
    termData->transactionDate[0] = day / 10 + '0';
    termData->transactionDate[1] = day % 10 + '0';
    termData->transactionDate[2] = '/';
    termData->transactionDate[3] = month / 10 + '0';
    termData->transactionDate[4] = month % 10 + '0';
    termData->transactionDate[5] = '/';
    termData->transactionDate[6] = '0' + year / 1000;
    termData->transactionDate[7] = '0' + (year % 1000) / 100;
    termData->transactionDate[8] = '0' + (year % 100) / 10;
    termData->transactionDate[9] = '0' + year % 10;
    termData->transactionDate[10] = '\0';

    if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || termData->transactionDate[10] != '\0') {
        return WRONG_DATE;
    }
    else {

        printf("Retrieved system date : %s\n", termData->transactionDate);
            return TERMINAL_OK;
    }


}
//This function compares the card expiry date with the transaction date.
// If the card expiration date is before the transaction date will return EXPIRED_CARD, else return OK_TERM_TERM_TERM_TERM_TERM_TERM.

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {

    uint32_t cyear, cmonth, tmonth, tyear , tday;

    sscanf(&(cardData.cardExpirationDate), "%d/%d", &cmonth, &cyear);
    cyear += 2000;
    sscanf(&(termData.transactionDate), "%d/%d/%d", &tday, &tmonth, &tyear);
    if (cyear < tyear) {
        return EXPIRED_CARD;
        
    }
    else if (cyear == tyear && cmonth < tmonth) {
        return EXPIRED_CARD;
        

    }
    else if (cmonth > 12 || tmonth > 12) {
        return EXPIRED_CARD;
    }
    return TERMINAL_OK;
    
}

//This function sets the maximum allowed amount into terminal data.
//Transaction max amount is a float number.
//If transaction max amount less than or equal to 0 will print INVALID_MAX_AMOUNT error, else return OK_TERM_TERM_TERM_TERM_TERM.
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {

    printf("Enter maxAmount for a transaction: ");
    float maxamount;
    scanf("%f", &maxamount);
    if (maxamount <= 0) {
        return INVALID_MAX_AMOUNT;
    }
    else {
        termData->maxTransAmount = maxamount;
        return TERMINAL_OK;
    }
}


//This function asks for the transaction amount and saves it into terminal data.
//If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK_TERM_TERM_TERM_TERM_TERM.
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

    float amount = 0;
    printf("Enter transaction amount : ");
    scanf("%f", &(termData->transAmount));
    if (termData->transAmount <= 0) {
        return INVALID_AMOUNT;
    }
    else {
        return TERMINAL_OK; 
    }
}

//This function compares the transaction amount with the terminal max amount.
//If the transaction amount is larger than the terminal max amount will return EXCEED_MAX_AMOUNT, else return OK_TERM_TERM_TERM_TERM_TERM.
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

    if (termData->transAmount > termData->maxTransAmount) {
        return EXCEED_MAX_AMOUNT;
    }
    else {
        return TERMINAL_OK;
    }
}







