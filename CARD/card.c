#include <stdio.h>
#include <string.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	char name[50] = {'/0'};
	int i;
	char ch;
	// will ask for the cardholder's name and store it into card data
	printf("Enter card holder name : ");
	i = 0;
	while ((ch = getchar()) != '\n') {
		name[i] = ch;
		i++;
	}
	
	//If the cardholder name is NULL, less than 20 characters or more than 24 will return WRONG_NAME error, else return OK.
	if (name[20] == '\0' || name[24] != '\0' || !name) {
		return WRONG_NAME;
	}
	else {
		//PUT NMAE INTO cardHolderName BY FOT LOOP 
		strcpy(cardData->cardHolderName , name);
		printf("name entered is: %s\n", cardData->cardHolderName);
		return CARD_OK;
	}
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	
	// This function will ask for the card expiry date and store it in card data
	printf("Enter expiry date [MM/YY]: ");
	scanf("%s", cardData->cardExpirationDate);

	//If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return WRONG_EXP_DATE error, else return OK.
	if (cardData->cardExpirationDate[5] != '\0'  || cardData->cardExpirationDate[2] != '/'/*wrong format*/ || !cardData->cardExpirationDate) {
		return WRONG_EXP_DATE;
	}
	else {
		printf("card Expiration entered:  %s\n", cardData->cardExpirationDate);
		return CARD_OK;
	}

}

// get card pan from user , 
//If the panis NULL, less than 16 or more than 19 characters, or has the wrong format will return WRONG_PAN error, else return OK.
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

    printf("Enter card pan : ");
	scanf("%s", cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber[16] == '\0' || cardData->primaryAccountNumber[19] != '\0' || !(cardData->primaryAccountNumber)) {
		return WRONG_PAN ;
	}
	printf("%s\n", cardData->primaryAccountNumber);
	return CARD_OK;
	 
}


