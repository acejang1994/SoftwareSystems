#include <stdio.h>
#include <stdlib.h> 

int count = 0;

void get_card(char *card_name) {
	puts("Enter the card_name: "); 
	scanf("%2s", card_name);	
}

int counter(int val){
	if ((val > 2) && (val < 7)) {
		count++;
	} else if (val == 10) {
		count--; 
	}
	return count;
}

int set_value(char card_name[]) {
	int val;
	switch(card_name[0]) {
	case 'K':
	case 'Q':
	case 'J':
		val = 10;
	    break;
	case 'A':
		val = 11;
		break;
	default:
		val = atoi(card_name);
		if ((val < 1) || (val > 10)) {
			puts("I don't understand that value!");
		}
	}
	return val;
}

int main()
{
	char card_name[3];
	int val;
	while ( card_name[0] != 'X') {
		get_card(card_name); 
		val = set_value(card_name);
		counter(val);
		printf("Current count: %i\n", count);
	}
	return 0; 
}
