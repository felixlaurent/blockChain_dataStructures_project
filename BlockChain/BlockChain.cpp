#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

char finalUsername[50] = {0};
char finalPassword[101] = {0};
int userMoney = 0;
int count = 0;
int count2 = 0;
char c;
int rangeA = 0;
int rangeB = 10;

struct account{
	char username[50];
	char password[101];
	int money;
}user[1000];

struct transaction{
	char sender[50];
	char receiver[50];
	int amount;
	int hash;
	char date[101];
}userTr[1000];

struct linkedAccount{
	char username[50];
	char password[101];
	int money;
	struct linkedAccount *next;
	struct linkedAccount *prev;
}*head, *tail;

struct linkedAccount *createLinked(char username[], char password[], int money){
	struct linkedAccount *newLinked = (struct linkedAccount*) malloc(sizeof(struct linkedAccount));
	strcpy(newLinked->username, username);
	strcpy(newLinked->password, password);
	newLinked->money = money;
	newLinked->next = NULL;
	newLinked->prev = NULL;
	return newLinked;
}

void push(char username[], char password[], int money){
	struct linkedAccount *newLinked = createLinked(username, password, money);
	if(head == NULL){
		tail = head = newLinked;
	}else{
		tail->next = newLinked;
		newLinked->prev = tail;
		tail = newLinked;
	}
}

void printList(){
	struct linkedAccount *curr = head;
	int i = 1;
	int range = 0;
	if(head == NULL){
		printf("No Data\n");
	}else{
		printf("==========================================\n");
		printf("| Num\t | Username\t\t |\n");
		printf("==========================================\n");
		while (curr != NULL){
			if(range >= rangeA && range < rangeB){
				printf("| %d\t | %s\t\t |\n", i, curr->username);
			}
			curr = curr->next;
			i++;
			range++;
		}	
		printf("==========================================\n");	
		puts("");
	}
}

void checkLatestAccount(){
	FILE *fp = fopen("accounts.txt", "r");
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
    		count++;
		}
	}
	fclose(fp);	
}

void checkLatestTransaction(){
	FILE *fp = fopen("transactions.txt", "r");
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
    		count2++;
		}
	}
	fclose(fp);	
}

void readAllAccount(){
	FILE *fp = fopen("accounts.txt", "r");
	for(int i = 1; i<= count; i++){
		fscanf(fp, "%[^,],%[^,],%d\n", user[i].username, user[i].password, &user[i].money);
	}
	fclose(fp);
}

void readAllTransaction(){
	FILE *fp = fopen("transactions.txt", "r");
	for(int i = 1; i<= count2; i++){
		fscanf(fp, "%[^#]#%[^#]#%d#%d#%[^\n]\n", userTr[i].sender, userTr[i].receiver, &userTr[i].amount, &userTr[i].hash, userTr[i].date);
	}
	fclose(fp);	
}

int checkUsername(char username[]){
	int len = strlen(username);
	if(len >= 8 && len <= 25){
		if(strchr(username,' ')){
			printf("Username's Musn't Contain Space, Press Enter to Try Again");
			getchar();
			return -1;
		}
		char fileUsername[50] = {0};
		char filePassword[101] = {0};
		int fileMoney = 0;
		FILE *fp = fopen("accounts.txt","r");
		while (!feof(fp)){
			fscanf(fp,"%[^,],%[^,],%d\n", fileUsername, filePassword, &fileMoney);
			if(strcmp(fileUsername, username) == 0){
				printf("Username Already Taken, Press Enter to Try Again");
				getchar();
				return -1;				
			}
		}
		fclose(fp);
		return 1;
	}else{
		printf("Username's Length Must be Between 8 and 25 Characters Long! Press Enter to Try Again");
		getchar();
		return -1;
	}
}

int checkPassword(char password[]){
	int len = strlen(password);
	int alpha = -1, numeric = -1;
	
	if(len >= 10){
		for(int i = 0; i<len; i++){
			if(isalpha(password[i])){
				alpha = 1;
			}
			if(isdigit(password[i])){
				numeric = 1;
			}
		}
		if(alpha == 1 && numeric == 1){
			return 1;
		}else{
			printf("Password Must Contain Alpha and Numeric Characters, Press Enter to Try Again");
			getchar();
			return -1;			
		}
	}else{
		printf("Password Must be At Least 10 Characters Long, Press Enter to Try Again");
		getchar();
		return -1;
	}	
}

void censorPassword(char password[]){
    int i = 0;
    char ch;

    while (1){
        ch = getch();
        if (ch == '\r' || ch == '\n'){
            password[i] = '\0';
            break;
        }else if (ch == '\b'){
            if (i > 0){
                i--;
                printf("\b \b");
            }
        }else{
            password[i] = ch;
            i++;
            printf("*");
        }
    }
}

int transactionHash(char text[]){
	int key = 0;
	int len = strlen(text);
	
	for(int i=0; i<len; i++){
		key += text[i] * (i+1);
	}
	
	return key;
}

char *generateTime(){
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    char formattedDateTime[100];
    strftime(formattedDateTime, sizeof(formattedDateTime), "%a %b %d %H:%M:%S %Y", localTime);

    return formattedDateTime;
}

void deposit(){
	system("cls");
	fflush(stdin);
    printf(" /$$$$$$$$                        /$$\n");
    printf("| $$_____/                       | $$\n");
    printf("| $$    /$$   /$$ /$$$$$$$   /$$$$$$$  /$$$$$$$\n");
    printf("| $$$$$| $$  | $$| $$__  $$ /$$__  $$ /$$_____/\n");
    printf("| $$__/| $$  | $$| $$  \\ $$| $$  | $$|  $$$$$$\n");
    printf("| $$   | $$  | $$| $$  | $$| $$  | $$ \\____  $$\n");
    printf("| $$   |  $$$$$$/| $$  | $$|  $$$$$$$ /$$$$$$$/\n");
    printf("|__/    \\______/ |__/  |__/ \\_______/|_______/\n");	
	puts("");	
	printf("Enter Deposit Amount [0 to Cancel]: ");
	int amount = 0, hashCode = 0;
	scanf("%d", &amount);
	if(amount == 0){
		return;
	}
	char time[50];
	strcpy(time,generateTime());
	fflush(stdin);
	int senderHash = transactionHash(finalUsername);
	int timeHash = transactionHash(time);
	hashCode = senderHash + timeHash;
	
	FILE *fp = fopen("transactions.txt","a+");
	fprintf(fp,"DP#%s#%d#%d#%s\n", finalUsername, amount, hashCode, time);
	fclose(fp);
	
	printf("Transaction Created with Hash: %d\n", hashCode);
	printf("Blue Token(s) Added to Transactions!\n");
	getchar();
}

void withdraw(){
	system("cls");
	fflush(stdin);
    printf(" /$$$$$$$$                        /$$\n");
    printf("| $$_____/                       | $$\n");
    printf("| $$    /$$   /$$ /$$$$$$$   /$$$$$$$  /$$$$$$$\n");
    printf("| $$$$$| $$  | $$| $$__  $$ /$$__  $$ /$$_____/\n");
    printf("| $$__/| $$  | $$| $$  \\ $$| $$  | $$|  $$$$$$\n");
    printf("| $$   | $$  | $$| $$  | $$| $$  | $$ \\____  $$\n");
    printf("| $$   |  $$$$$$/| $$  | $$|  $$$$$$$ /$$$$$$$/\n");
    printf("|__/    \\______/ |__/  |__/ \\_______/|_______/\n");	
	puts("");	
	printf("Enter Withdraw Amount [0 to Cancel]: ");
	int amount = 0, hashCode = 0;
	scanf("%d", &amount);
	fflush(stdin);
	if(amount == 0){
		return;
	}
	if(amount > userMoney){
		printf("You don't Have Enough Money");
		getchar();
		return;
	}
	
	userMoney-=amount;
	count = 0;
	checkLatestAccount();
	readAllAccount();

	FILE *fp = fopen("accounts.txt", "w+");
	for(int i = 1; i<= count; i++){
		if(strcmp(user[i].username,finalUsername) == 0){
			strcpy(user[i].username,finalUsername);
			user[i].money = userMoney;
		}
		fprintf(fp, "%s,%s,%d\n", user[i].username, user[i].password, user[i].money);
	}
	fclose(fp);	
	
	char time[50];
	strcpy(time,generateTime());
	fflush(stdin);
	int senderHash = transactionHash(finalUsername);
	int timeHash = transactionHash(time);
	hashCode = senderHash + timeHash;
	
	FILE *dp = fopen("transactions.txt","a+");
	fprintf(dp,"%s#WD#%d#%d#%s\n", finalUsername, amount, hashCode, time);
	fclose(dp);
	
	printf("Transaction Created with Hash: %d\n", hashCode);
	printf("Blue Token(s) Added to Transactions!\n");
	getchar();	
}

int searchUsername(char inputUsername[]){
	count = 0;
	checkLatestAccount();
	readAllAccount();

	for(int i = 1; i<= count; i++){
		if(strcmp(user[i].username,inputUsername) == 0){
			return 1;
		}
	}
	return -1;	
}

void enterUsername(){
	char inputUsername[50];
	int searchValid;
	do{
		system("cls");
		fflush(stdin);
		printf("  /$$$$$$                            /$$\n");
		printf(" /$$__  $$                          | $$\n");
		printf("| $$  \\__/  /$$$$$$  /$$$$$$$   /$$$$$$$\n");
		printf("|  $$$$$$  /$$__  $$| $$__  $$ /$$__  $$\n");
		printf(" \\____  $$| $$$$$$$$| $$  \\ $$| $$  | $$\n");
		printf(" /$$  \\ $$| $$_____/| $$  | $$| $$  | $$\n");
		printf("|  $$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$\n");
		printf(" \\______/  \\_______/|__/  |__/ \\_______/\n");
		puts("");
			
		printList();
		printf("Enter Username [0 to Cancel]: ");
		scanf("%s", inputUsername);
		fflush(stdin);
		if(strcmp(inputUsername, "0") == 0){
			return;
		}
		
		searchValid = searchUsername(inputUsername);
		if(searchValid == -1){
			printf("Username Not Found! Press Enter to Try Again");
			getchar();
		}		
	}while (searchValid == -1);

	system("cls");
	fflush(stdin);
	printf("  /$$$$$$                            /$$\n");
	printf(" /$$__  $$                          | $$\n");
	printf("| $$  \\__/  /$$$$$$  /$$$$$$$   /$$$$$$$\n");
	printf("|  $$$$$$  /$$__  $$| $$__  $$ /$$__  $$\n");
	printf(" \\____  $$| $$$$$$$$| $$  \\ $$| $$  | $$\n");
	printf(" /$$  \\ $$| $$_____/| $$  | $$| $$  | $$\n");
	printf("|  $$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$\n");
	printf(" \\______/  \\_______/|__/  |__/ \\_______/\n");
	puts("");
	printList();
	
	printf("Your Blue Tokens: %d\n", userMoney);
	printf("Enter Amount to Send [0 to Cancel]: ");
	int amount = 0, hashCode = 0;
	scanf("%d", &amount);
	fflush(stdin);
	if(amount == 0){
		return;
	}
	if(amount > userMoney){
		printf("You don't Have Enough Money! Press Enter to Continue");
		getchar();
		return;
	}
	
	userMoney-=amount;

	FILE *fp = fopen("accounts.txt", "w+");
	for(int i = 1; i<= count; i++){
		if(strcmp(user[i].username,finalUsername) == 0){
			user[i].money = userMoney;
		}
		if(strcmp(user[i].username,inputUsername) == 0){
			user[i].money += amount;
		}		
		fprintf(fp, "%s,%s,%d\n", user[i].username, user[i].password, user[i].money);
	}
	fclose(fp);	

	char time[50];
	strcpy(time,generateTime());
	fflush(stdin);
	int senderHash = transactionHash(finalUsername);
	int timeHash = transactionHash(time);
	int recipientHash = transactionHash(inputUsername);
	hashCode = senderHash + timeHash + recipientHash;
	
	FILE *dp = fopen("transactions.txt","a+");
	fprintf(dp,"%s#%s#%d#%d#%s\n", finalUsername, inputUsername, amount, hashCode, time);
	fclose(dp);
	
	printf("Transaction Created with Hash: %d\n", hashCode);
	printf("Transaction Inserted Succesfully\n");
	getchar();
}

void sendMoney(){
	while (1){
		system("cls");
		fflush(stdin);
	    printf("  /$$$$$$                            /$$\n");
	    printf(" /$$__  $$                          | $$\n");
	    printf("| $$  \\__/  /$$$$$$  /$$$$$$$   /$$$$$$$\n");
	    printf("|  $$$$$$  /$$__  $$| $$__  $$ /$$__  $$\n");
	    printf(" \\____  $$| $$$$$$$$| $$  \\ $$| $$  | $$\n");
	    printf(" /$$  \\ $$| $$_____/| $$  | $$| $$  | $$\n");
	    printf("|  $$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$\n");
	    printf(" \\______/  \\_______/|__/  |__/ \\_______/\n");
		puts("");
		
		printList();
		printf("1. Prev\n");
		printf("2. Next\n");
		printf("3. Enter Username\n");
		printf("4. Back\n");
		printf(">> ");
		
		int input;
		scanf("%d", &input);
		
		if(input == 1){
			rangeA -= 10;
			rangeB -= 10;
		}else if(input == 2){
			rangeA += 10;
			rangeB += 10;
		}else if(input == 3){
			enterUsername();
		}else if(input == 4){
			return;	
		}
	}
}

void pChangePass(){
	printf(" /$$$$$$$                                                                      /$$\n");
    printf("| $$__  $$                                                                    | $$\n");
    printf("| $$  \\ $$ /$$$$$$   /$$$$$$$ /$$$$$$$ /$$  /$$  /$$  /$$$$$$   /$$$$$$   /$$$$$$$\n");
    printf("| $$$$$$$/|____  $$ /$$_____//$$_____/| $$ | $$ | $$ /$$__  $$ /$$__  $$ /$$__  $$\n");
    printf("| $$____/  /$$$$$$$|  $$$$$$|  $$$$$$ | $$ | $$ | $$| $$  \\ $$| $$  \\__/| $$  | $$\n");
    printf("| $$      /$$__  $$ \\____  $$\\____  $$| $$ | $$ | $$| $$  | $$| $$      | $$  | $$\n");
    printf("| $$     |  $$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$/$$$$/|  $$$$$$/| $$      |  $$$$$$$\n");
    printf("|__/      \\_______/|_______/|_______/  \\_____\\____/  \\______/ |__/       \\_______/\n");
	puts("");
}

void changePassword(){
	char oldPass[101] = {0};
	char newPass[101] = {0};
	char newNewPass[101] = {0};
	int valid = -1;

	system("cls");
	pChangePass();
	printf("Enter Your Old Password [0 to Cancel] >> ");
	censorPassword(oldPass);
	fflush(stdin);
	if(strcmp(oldPass,"0") == 0){
		return;
	}
	if(strcmp(oldPass, finalPassword) != 0){
		printf("Incorrect Password! Press Enter to Continue");
		getchar();
		return;
	}else{
		do{
			system("cls");
			pChangePass();
			printf("Enter Your New Password [0 to Cancel] >> ");
			censorPassword(newPass);
			fflush(stdin);
			if(strcmp(newPass,"0") == 0){
				return;
			}	
			puts(" ");
			valid = checkPassword(newPass);		
		}while (valid == -1);
		
		system("cls");
		pChangePass();
		printf("Repeat the New Password [0 to Cancel] >> ");
		censorPassword(newNewPass);
		fflush(stdin);
		if(strcmp(newNewPass,"0") == 0){
			return;
		}
		if(strcmp(newNewPass, newPass) == 0){
			count = 0;
			checkLatestAccount();
			readAllAccount();	

			FILE *fp = fopen("accounts.txt", "w+");
			for(int i = 1; i<= count; i++){
				if(strcmp(user[i].username,finalUsername) == 0){
					strcpy(user[i].username,finalUsername);
					strcpy(user[i].password,newNewPass);
					user[i].money = userMoney;
				}
				fprintf(fp, "%s,%s,%d\n", user[i].username, user[i].password, user[i].money);
			}
			fclose(fp);	
			
			strcpy(finalPassword,newNewPass);
			
			printf("Password Updated!\n");
			getchar();
		}else{
			printf("Password Doesn't Match! Press Enter to Continue");
			getchar();
			return;			
		}
	}	
}

void myAccount(){
	while(1){
		system("cls");
		fflush(stdin);
	    printf(" /$$      /$$                  /$$$$$$                                                      /$$\n");
	    printf("| $$$    /$$$                 /$$__  $$                                                    | $$\n");
	    printf("| $$$$  /$$$$ /$$   /$$      | $$  \\ $$  /$$$$$$$  /$$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$\n");
	    printf("| $$ $$/$$ $$| $$  | $$      | $$$$$$$$ /$$_____/ /$$_____/ /$$__  $$| $$  | $$| $$__  $$|_  $$_/\n");
	    printf("| $$  $$$| $$| $$  | $$      | $$__  $$| $$      | $$      | $$  \\ $$| $$  | $$| $$  \\ $$  | $$\n");
	    printf("| $$\\  $ | $$| $$  | $$      | $$  | $$| $$      | $$      | $$  | $$| $$  | $$| $$  | $$  | $$ /$$\n");
	    printf("| $$ \\/  | $$|  $$$$$$$      | $$  | $$|  $$$$$$$|  $$$$$$$|  $$$$$$/|  $$$$$$/| $$  | $$  |  $$$$/\n");
	    printf("|__/     |__/ \\____  $$      |__/  |__/ \\_______/ \\_______/ \\______/  \\______/ |__/  |__/   \\___/\n");
	    printf("              /$$  | $$\n");
	    printf("             |  $$$$$$/\n");
		puts("");
		printf("1. Change Password\n");
		printf("2. Back\n");
		printf(">> ");
		
		int input;
		scanf("%d", &input);
		
		if(input == 1){
			changePassword();
		}else if(input == 2){
			return;
		}			
	}	
}

void allOngoing(){
	fflush(stdin);
	count2 = 0;
	checkLatestTransaction();
	printf("All Transaction\n");
	printf("==================================================================================================\n");
	printf("| Sender\t\t | Receiver\t\t | Amount\t | Hash\t | Date\t\t\t |\n");
	printf("==================================================================================================\n");
	FILE *fp = fopen("transactions.txt", "r");
	for(int i = 1; i<= count2; i++){
		fscanf(fp, "%[^#]#%[^#]#%d#%d#%[^\n]\n", userTr[i].sender, userTr[i].receiver, &userTr[i].amount, &userTr[i].hash, userTr[i].date);
		printf("| %s\t\t | %s\t | %d\t | %d\t | %s |\n", userTr[i].sender, userTr[i].receiver, userTr[i].amount, userTr[i].hash, userTr[i].date);
	}
	fclose(fp);	
	printf("==================================================================================================\n");
	getchar();
}

void myOngoing(){
	fflush(stdin);
	count2 = 0;
	checkLatestTransaction();
	printf("Your Transaction\n");
	printf("==================================================================================================\n");
	printf("| Sender\t\t | Receiver\t\t | Amount\t | Hash\t | Date\t\t\t |\n");
	printf("==================================================================================================\n");
	FILE *fp = fopen("transactions.txt", "r");
	for(int i = 1; i<= count2; i++){
		fscanf(fp, "%[^#]#%[^#]#%d#%d#%[^\n]\n", userTr[i].sender, userTr[i].receiver, &userTr[i].amount, &userTr[i].hash, userTr[i].date);
		if(strcmp(userTr[i].sender, finalUsername) == 0 || strcmp(userTr[i].receiver, finalUsername) == 0){
			printf("| %s\t\t | %s\t | %d\t | %d\t | %s |\n", userTr[i].sender, userTr[i].receiver, userTr[i].amount, userTr[i].hash, userTr[i].date);
		}
	}
	fclose(fp);	
	printf("==================================================================================================\n");
	getchar();
}

void searchOngoing(){
	char inputUsername[50];
	count2 = 0;
	checkLatestTransaction();
	readAllTransaction();
	
	printf("Enter Username: ");
	scanf("%s", inputUsername);
	fflush(stdin);

	printf("==================================================================================================\n");
	printf("| Sender\t\t | Receiver\t\t | Amount\t | Hash\t | Date\t\t\t |\n");
	printf("==================================================================================================\n");
	for(int i = 1; i<= count2; i++){
		if(strcmp(userTr[i].sender,inputUsername) == 0 || strcmp(userTr[i].receiver,inputUsername) == 0){
			printf("| %s\t\t | %s\t | %d\t | %d\t | %s |\n", userTr[i].sender, userTr[i].receiver, userTr[i].amount, userTr[i].hash, userTr[i].date);
		}
	}
	printf("==================================================================================================\n");
	getchar();
}

void ongoing(){
	while(1){
		system("cls");
		fflush(stdin);
	    printf("  /$$$$$$                                /$$\n");
	    printf(" /$$__  $$                              |__/\n");
	    printf("| $$  \\ $$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$ /$$$$$$$   /$$$$$$\n");
	    printf("| $$  | $$| $$__  $$ /$$__  $$ /$$__  $$| $$| $$__  $$ /$$__  $$\n");
	    printf("| $$  | $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$| $$  \\ $$| $$  \\ $$\n");
	    printf("| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$| $$  | $$\n");
	    printf("|  $$$$$$/| $$  | $$|  $$$$$$$|  $$$$$$/| $$| $$  | $$|  $$$$$$$\n");
	    printf(" \\______/ |__/  |__/ \\____  $$ \\______/ |__/|__/  |__/ \\____  $$\n");
	    printf("                     /$$  \\ $$                         /$$  \\ $$\n");
	    printf("                    |  $$$$$$/                        |  $$$$$$/\n");
	    printf("                     \\______/                          \\______/\n");
		puts("");
		printf("1. My Ongoing Transactions\n");
		printf("2. All Ongoing Transactions\n");
		printf("3. Search Someone's Ongoing Transactions\n");
		printf("4. Back\n");
		printf(">> ");
		int input;
		scanf("%d", &input);
			
		if(input == 1){
			myOngoing();
		}else if(input == 2){	
			allOngoing();
		}else if(input == 3){
			searchOngoing();
		}else if(input == 4){
			return;	
		}	
	}	
}

void viewTransactions(){
	while (1){
		system("cls");
		fflush(stdin);
	    printf(" /$$$$$$$$                                                           /$$     /$$\n");
	    printf("|__  $$__/                                                          | $$    |__/\n");
	    printf("   | $$  /$$$$$$  /$$$$$$  /$$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$   /$$  /$$$$$$  /$$$$$$$   /$$$$$$$\n");
	    printf("   | $$ /$$__  $$|____  $$| $$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  | $$ /$$__  $$| $$__  $$ /$$_____/\n");
	    printf("   | $$| $$  \\__/ /$$$$$$$| $$  \\ $$|  $$$$$$   /$$$$$$$| $$        | $$    | $$| $$  \\ $$| $$  \\ $$|  $$$$$$\n");
	    printf("   | $$| $$      /$$__  $$| $$  | $$ \\____  $$ /$$__  $$| $$        | $$ /$$| $$| $$  | $$| $$  | $$ \\____  $$\n");
	    printf("   | $$| $$     |  $$$$$$$| $$  | $$ /$$$$$$$/|  $$$$$$$|  $$$$$$$  |  $$$$/| $$|  $$$$$$/| $$  | $$ /$$$$$$$/\n");
	    printf("   |__/|__/      \\_______/|__/  |__/|_______/  \\_______/ \\_______/   \\___/  |__/ \\______/ |__/  |__/|_______/\n");
		puts("");
		printf("1. Ongoing Transactions\n");
		printf("2. Back\n");;
		printf(">> ");
		int input;
		scanf("%d", &input);
		
		if(input == 1){
			ongoing();
		}else if(input == 2){	
			return;		
		}			
	}	
}

void transactions(){
	while (1){
		system("cls");
		fflush(stdin);
	    printf(" /$$$$$$$$                                                           /$$     /$$\n");
	    printf("|__  $$__/                                                          | $$    |__/\n");
	    printf("   | $$  /$$$$$$  /$$$$$$  /$$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$   /$$  /$$$$$$  /$$$$$$$   /$$$$$$$\n");
	    printf("   | $$ /$$__  $$|____  $$| $$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  | $$ /$$__  $$| $$__  $$ /$$_____/\n");
	    printf("   | $$| $$  \\__/ /$$$$$$$| $$  \\ $$|  $$$$$$   /$$$$$$$| $$        | $$    | $$| $$  \\ $$| $$  \\ $$|  $$$$$$\n");
	    printf("   | $$| $$      /$$__  $$| $$  | $$ \\____  $$ /$$__  $$| $$        | $$ /$$| $$| $$  | $$| $$  | $$ \\____  $$\n");
	    printf("   | $$| $$     |  $$$$$$$| $$  | $$ /$$$$$$$/|  $$$$$$$|  $$$$$$$  |  $$$$/| $$|  $$$$$$/| $$  | $$ /$$$$$$$/\n");
	    printf("   |__/|__/      \\_______/|__/  |__/|_______/  \\_______/ \\_______/   \\___/  |__/ \\______/ |__/  |__/|_______/\n");
		puts("");
		printf("1. View Transactions\n");
		printf("2. Send Money\n");
		printf("3. Back\n");
		printf(">> ");
		int input;
		scanf("%d", &input);
		
		if(input == 1){
			viewTransactions();
		}else if(input == 2){
			count = 0;
			checkLatestAccount();
			FILE *fp = fopen("accounts.txt", "r");
			for(int i = 1; i<= count; i++){
				fscanf(fp, "%[^,],%[^,],%d\n", user[i].username, user[i].password, &user[i].money);
				push(user[i].username, user[i].password, user[i].money);
			}
			fclose(fp);	
			rangeA = 0; rangeB = 10;
			sendMoney();		
		}else if(input == 3){
			return;	
		}			
	}
}

void funds(){
	while (1){
		system("cls");
		fflush(stdin);
	    printf(" /$$$$$$$$                        /$$\n");
	    printf("| $$_____/                       | $$\n");
	    printf("| $$    /$$   /$$ /$$$$$$$   /$$$$$$$  /$$$$$$$\n");
	    printf("| $$$$$| $$  | $$| $$__  $$ /$$__  $$ /$$_____/\n");
	    printf("| $$__/| $$  | $$| $$  \\ $$| $$  | $$|  $$$$$$\n");
	    printf("| $$   | $$  | $$| $$  | $$| $$  | $$ \\____  $$\n");
	    printf("| $$   |  $$$$$$/| $$  | $$|  $$$$$$$ /$$$$$$$/\n");
	    printf("|__/    \\______/ |__/  |__/ \\_______/|_______/\n");	
		puts("");
		printf("Blue Tokens: %d\n", userMoney);
		printf("1. Deposit\n");
		printf("2. Withdraw\n");
		printf("3. Back\n");
		printf(">> ");
		
		int input;
		scanf("%d", &input);
		
		if(input == 1){
			deposit();
		}else if(input == 2){
			withdraw();
		}else if(input == 3){
			return;	
		}		
	}
}

void mainMenu(char username[], char password[]){
	while (1){
		system("cls");
		fflush(stdin);
	    printf(" /$$      /$$           /$$                 /$$      /$$\n");
	    printf("| $$$    /$$$          |__/                | $$$    /$$$\n");
	    printf("| $$$$  /$$$$  /$$$$$$  /$$ /$$$$$$$       | $$$$  /$$$$  /$$$$$$  /$$$$$$$  /$$   /$$\n");
	    printf("| $$ $$/$$ $$ |____  $$| $$| $$__  $$      | $$ $$/$$ $$ /$$__  $$| $$__  $$| $$  | $$\n");
	    printf("| $$  $$$| $$  /$$$$$$$| $$| $$  \\ $$      | $$  $$$| $$| $$$$$$$$| $$  \\ $$| $$  | $$\n");
	    printf("| $$\\  $ | $$ /$$__  $$| $$| $$  | $$      | $$\\  $ | $$| $$_____/| $$  | $$| $$  | $$\n");
	    printf("| $$ \\/  | $$|  $$$$$$$| $$| $$  | $$      | $$ \\/  | $$|  $$$$$$$| $$  | $$|  $$$$$$/\n");
	    printf("|__/     |__/ \\_______/|__/|__/  |__/      |__/     |__/ \\_______/|__/  |__/ \\______/\n");
		puts("");
		strcpy(finalUsername, username);
		strcpy(finalPassword, password);
		printf("Welcome, %s\n", finalUsername);
		puts("");
		printf("1. Funds\n");
		printf("2. Transactions\n");
		printf("3. My Account\n");
		printf("4. Log Out\n");
		printf(">> ");
		
		int input;
		scanf("%d", &input);
		
		if(input == 1){
			funds();
		}else if(input == 2){
			transactions();
		}else if(input == 3){
			myAccount();
		}else if(input == 4){
			memset(finalUsername, 0, sizeof(finalUsername));
			return;
		}		
	}
}

void pLogin(){
    printf(" /$$                                 /$$$$$$\n");
    printf("| $$                                |_  $$_/\n");
    printf("| $$        /$$$$$$   /$$$$$$         | $$   /$$$$$$$\n");
    printf("| $$       /$$__  $$ /$$__  $$        | $$  | $$__  $$\n");
    printf("| $$      | $$  \\ $$| $$  \\ $$        | $$  | $$  \\ $$\n");
    printf("| $$      | $$  | $$| $$  | $$        | $$  | $$  | $$\n");
    printf("| $$$$$$$$|  $$$$$$/|  $$$$$$$       /$$$$$$| $$  | $$\n");
    printf("|________/ \\______/  \\____  $$      |______/|__/  |__/\n");
    printf("                     /$$  \\ $$\n");
    printf("                    |  $$$$$$/\n");
    printf("                     \\______/\n");
	puts("");
}

void login(){
	char username[50] = {0};
	char password[101] = {0};
	fflush(stdin);

	system("cls");
	pLogin();
	printf("Enter Username [0 to Cancel] >> ");
	scanf("%[^\n]", username);
	getchar();
	if(strcmp(username,"0") == 0){
		return;
	}

	system("cls");
	pLogin();
	printf("Enter Password [0 to Cancel] >> ");
	censorPassword(password);
	if(strcmp(password,"0") == 0){
		return;
	}
	puts(" ");
	
	char fileUsername[50] = {0};
	char filePassword[101] = {0};
	
	int accValid = -1;
	int usernameValid = -1;
	
	FILE *fp = fopen("accounts.txt","r");
	while (!feof(fp)){
		fscanf(fp,"%[^,],%[^,],%d\n", fileUsername, filePassword, &userMoney);
		if(strcmp(fileUsername, username) == 0){
			usernameValid = 1;
			if(strcmp(filePassword, password) == 0){
				accValid = 1;
				break;
			}else{
				printf("Incorrect Password! Press Enter to Continue");
				getchar();
			}	
		}
	}
	fclose(fp);	
	
	if(usernameValid == -1){
		printf("Username Not Found! Press Enter to Continue");
		getchar();
	}
	
	if(accValid == 1){
		mainMenu(username, password);
	}
}

void pRegister(){
    printf(" /$$$$$$$                      /$$             /$$\n");
    printf("| $$__  $$                    |__/            | $$\n");
    printf("| $$  \\ $$  /$$$$$$   /$$$$$$  /$$  /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$\n");
    printf("| $$$$$$$/ /$$__  $$ /$$__  $$| $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$\n");
    printf("| $$__  $$| $$$$$$$$| $$  \\ $$| $$|  $$$$$$   | $$    | $$$$$$$$| $$  \\__/\n");
    printf("| $$  \\ $$| $$_____/| $$  | $$| $$ \\____  $$  | $$ /$$| $$_____/| $$\n");
    printf("| $$  | $$|  $$$$$$$|  $$$$$$$| $$ /$$$$$$$/  |  $$$$/|  $$$$$$$| $$\n");
    printf("|__/  |__/ \\_______/ \\____  $$|__/|_______/    \\___/   \\_______/|__/\n");
    printf("                     /$$  \\ $$\n");
    printf("                    |  $$$$$$/\n");
    printf("                     \\______/\n");
    puts("");
}

void registers(){
	int valid = -1;
	char username[50] = {0};
	char password[101] = {0};
	fflush(stdin);
	do{
		system("cls");
		pRegister();
		printf("Enter Username [0 to Cancel] >> ");
		scanf("%[^\n]", username);
		fflush(stdin);
		if(strcmp(username,"0") == 0){
			return;
		}
		valid = checkUsername(username);
	}while (valid == -1);

	valid = -1;
	do{
		system("cls");
		pRegister();
		printf("Enter Password [0 to Cancel] >> ");
		censorPassword(password);
		if(strcmp(password,"0") == 0){
			return;
		}
		puts(" ");
		valid = checkPassword(password);
	}while (valid == -1);
		
	FILE *fp = fopen("accounts.txt","a+");
	fprintf(fp,"%s,%s,0\n", username, password);
	printf("Account Created!, Press Enter to Continue");
	getchar();
	fclose(fp);
}

void exit(){
	system("cls");
    printf("                                                .\n");
    printf("                                               ...\n");
    printf("                                              .....\n");
    printf("                                            ....*...\n");
    printf("                                           .....,.....\n");
    printf("                                          ....,***,....\n");
    printf("                                        ...***********..\n");
    printf("                                     ...,*.....***....,*....\n");
    printf("                                    ..**,***.,**,**..***,**..\n");
    printf("                              ...   ...*,*****..*.,*******...    ..\n");
    printf("          ..................****,..    ........***........    ...****...................\n");
    printf("           ....**..*..***..******..      ...,*******....      ..*******.,**..*..**,...\n");
    printf("             .....***,**,...****,..  . ...,*****,****#/.....  ..,****....******.....\n");
    printf("               .....*********..........,,******,, &&/*****,.........****,*****.....\n");
    printf("                ..***...,**.************,**,,*#&&#**,,**,************.**,...***..\n");
    printf("                  ..******,..,********,,,* &&&&(,,,,****,,,*********..**,*,**...\n");
    printf("                  ..,*,*,*,..,,*,*,,,** &&&&&(**,*,*,,,,,*,*%&(*,*,....*,*,*,.\n");
    printf("                   ..***,......****,, &&&&&#**,,,,,,***&&&&&&(****.......***,..\n");
    printf("                     ...    ...****, &&&&&/,,****&%%&&&&&&&,,****..     ...\n");
    printf("                     ...    ,..**** &&&&&&*,,********,&&&&& *,***,..    ...\n");
    printf("                  ...,*,... ...*,*,&&&&&&&&(*,**,***,&&&&& /*,**,*.. ...,.*...\n");
    printf("                  ..******,....***%%%(,,******,,,*&&&&&& /**,****....**,****.\n");
    printf("                  ..****,*,..,******,,**,**,,***,&&&&& (***,,******...**,****.\n");
    printf("                ..,**...**,.************,,,****&&&/(**,,,***********..**....**..\n");
    printf("              .....,,*,*,***........,***,***,&& /*,,,***,***,.......,***,***,,...\n");
    printf("             ....,******....****..  .....*%%#(***********,.......****,...,****,*....\n");
    printf("           ....***.*..**,.,******..    & ,..,*******,....    ..,******.,,*..*.,**,...\n");
    printf("          .................*****,..   ........****,......    ...*****.................\n");
    printf("                             ....  ....*,****..*,..,****,*..   ....\n");
    printf("                                   ...**,***.******,*******..\n");
    printf("                                     ...,**....***...,**,..\n");
    printf("                                        ...**********,..\n");
    printf("                                          .....,,......\n");
    printf("                                           .....*....\n");
    printf("                                            ....*...\n");
    printf("                                             .....\n");
    printf("                                               ..\n\n");
	printf("'Wondeful things can be achieved when there is teamwork, hard work, and perseverance!''\n");
	printf(" - Bluejackets 22-2\n");
}

void homePage() {
	system("cls");
    printf(" /$$$$$$$  /$$                     /$$   /$$  /$$$$$$  /$$                 /$$\n");
    printf("| $$__  $$| $$                    | $$  /$$/ /$$__  $$| $$                |__/\n");
    printf("| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$ /$$/ | $$  \\__/| $$$$$$$   /$$$$$$  /$$ /$$$$$$$\n");
    printf("| $$$$$$$ | $$ /$$__  $$ /$$_____/| $$$$$/  | $$      | $$__  $$ |____  $$| $$| $$__  $$\n");
    printf("| $$__  $$| $$| $$  \\ $$| $$      | $$  $$  | $$      | $$  \\ $$  /$$$$$$$| $$| $$  \\ $$\n");
    printf("| $$  \\ $$| $$| $$  | $$| $$      | $$\\  $$ | $$    $$| $$  | $$ /$$__  $$| $$| $$  | $$\n");
    printf("| $$$$$$$/| $$|  $$$$$$/|  $$$$$$$| $$ \\  $$|  $$$$$$/| $$  | $$|  $$$$$$$| $$| $$  | $$\n");
    printf("|_______/ |__/ \\______/  \\_______/|__/  \\__/ \\______/ |__/  |__/ \\_______/|__/|__/  |__/\n");
    puts("");
    printf("1. Log In\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf(">> ");
}

int main(){
	while (1){
		homePage();
		int input = 0;
		scanf("%d", &input);
		
		if(input == 1){
			login();
		}else if(input == 2){
			registers();
		}else if(input == 3){
			exit();
			break;
		}
	}
	return 0;
}
