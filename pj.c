#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int try_again(){
	int choice;
	do{
		choice=getch();			
	}while(choice!=89 && choice!=121 && choice!=78 && choice!=110);
	return choice;	
}

void blue () {
  printf("\033[1;34m");
};

void green () {
  printf("\033[1;32m");
};

void red () {
  printf("\033[1;31m");
};

void yellow (){
  printf("\033[1;33m");
};

void reset () {
  printf("\033[0m");
};

int nb_hint(int x){
    int i;
    if (x<=5)
    {
        i=1;
    }
    else if (x>5 && x<=8)
    {
        i=2;
    }
    else
    {
        i=3;
    }
    return i; 
};

int random_char(int n){
    int  r;
    srand(time(NULL));
    r =rand() % n;
return r;
}

FILE *file;

struct list{
	char word[500];	
};

//Choosing Category of game
void choose_game_word(){
    int nb;
	yellow();
	printf("CHOOSE CATEGORY :   \n\n");
	reset();
	printf("|1| - ANIMALS \n\n");
	printf("|2| - COUNTRIES\n\n");

    while(nb!= 1 && nb!=2){
		scanf("%d",&nb);	
		switch(nb){
		case 1:
			file=fopen("animals.txt","r+");
			break;	
		case 2:
			file=fopen("country.txt","r+");	
			break;
		default:
			printf("PLEASE SELECT VALID CHOICE  [1] or [2] \n");
			break;
		}
	}
}

void game_Words(){
	red();
	printf("------------------GUESS THE WORD----------------------- ");
	reset();
	fseek(file,0,SEEK_SET);
	struct list tab[500];
	int i=-1;
	char code[500];
	int index;
	char random_word[30];
	char crypt[30];
	int tries,longeur,result;
	char trying[30];
	int hints;
	int caractere_hinted;

	while( fscanf(file,"%s",code) != EOF){
		i++;
		strcpy(tab[i].word,code);	
	}
	fclose(file);	


	srand ( time(NULL) );
	index = (rand() % (i - 0 + 1)) + 0;
	strcpy(random_word,tab[index].word);
	printf("\n le mot a chercher %s",random_word);


	for(int j=0;j<strlen(random_word);j++){
		crypt[j]='-';	
	}
	printf(" \n le mot a chercher est compose de %d  ",strlen(crypt));
	//printf("\n \t %s",crypt);

	hints=nb_hint(strlen(crypt));




	longeur=strlen(random_word);
    if (longeur<=5)
    {
        tries=3;
    }
    else if (longeur>5 && longeur<=8)
    {
        tries=5;
    }
    else
    {
        tries=8;
    }


	yellow();
	printf("%s                 NUMBER OF TRIES :%d 		NUNBER OF HINTS : %d    ",crypt,tries,hints);
	reset();
	do{
		
        printf("\n\n GIVE A WORD : \n ");
        scanf(" %s",trying);
        result=strcmp( trying, random_word);
        if(strcmp( trying, random_word ) == 0){
			green();
            printf("\n CONGRATULATIONS  YOU GUESSED THE WORD !!!!   ");
			reset();
        }else{
			red();
            printf("\n WRONG WORD \n \n "); 
			reset();
			printf("\n %s ",crypt);
            tries--;
			yellow();
            printf(" 			NUMBER OF TRIES :  %d    			NUMBER OF HINTS : %d  ",tries,hints);
			reset();
			if(tries<=3 &&hints !=0 ){
				caractere_hinted=random_char(strlen(random_word));
				blue();
				printf("\n \n THERE ARE  ** %c **  IN POSITION NUMBER  ** %d **   ",random_word[caractere_hinted],(caractere_hinted+1));
				reset();
				crypt[caractere_hinted]=random_word[caractere_hinted];
				green();
				printf("\n\n HINT RESULT :   %s ",crypt);
				reset();
				hints--;

			}else if(tries==0){
				
				printf("\n \n		 THE WORD IS  ");
				green();
				printf(" %s ",random_word);
				reset();
				red();
				printf("\n \n 			GAME OVER");
				reset();
			}
        }
    }while(result!=0 && tries>=1);
	

}



//--------------------------------------------------------------------------------------------------------

long random_num()
{
    long s ;
    srand((unsigned)time(NULL));

    long x = 10000000;
    long y = 99999999;

    s = (rand() % (y - x + 1) + x);

    return s;
}

//tester si le numéro entré par user est valide
int testNumbers(char str[])
{
    int count = 0;
    for(int i=0;i<8;i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            count++;
        }
    }
     if(count==8)
     {
         return 0;
     }
     else
     {
         return 1;
     }
}

//occurence d'un caractere dans tab orig
int occurence(char c,char orig[])
{
    int occur = 0;
   for(int i = 0; i<8; i++)
   {
       if(orig[i] == c)
           occur++;
   }
   return occur;
}

//existence caractere dans tab origin
int exist(char e, char *orig)
{
    int i = 0;

   while (i < 8 && e != orig[i])
    {
      i++;
    }
    if (i < 8)
    {
      return 1;
    }
   else
    {
      return 0; 
    }
}

char * test(char *orig,char *user)
{
    char result[9];
    int i,occ=0;



    for (i=0;i<8;i++)
    {
        if (exist(user[i],orig)==1)
        {
            occ = occurence(user[i],orig);
           if (orig[i] == user[i])
           {
              result[i] = user[i];
              occ=0;
           }
           else
           {
               if (occ >= 1)
                {
                    result[i] = '-';
                }
                else
                {
                    result[i] = '+';
                }
                occ--;
           }
        }
        else
        {
            result[i] = '*';
        }
    }

    printf("\n%s",result);
    char *res = result;

    return *res;
}

void game_number(){
    int trial; //nbr essais
    long s;
    char *result = malloc(sizeof(char)*8);
    char user[9];
    char orig[9];
    s = random_num();
    sprintf(orig, "%ld", s); //convertir entier long s en une string pour la mettre dans tab orig
    green();
    printf("THE RANDOM NUMBER IS :  %s",orig);
    reset();
    printf("\n");
    trial=0;
    do
    {
         do
        {
            printf("\n GIVE A NUMBER OF 8  \n");
            scanf("%s",user);

        }
        while (strlen(user) != 8 || testNumbers(user) == 1);


        if(strcmp(orig,user) !=0)
        {
            //printf("\n%s",orig);
            *result = test(orig,user);
            //printf("\n%s",*result);
            trial++;
            yellow();
            printf("\n NUMBER OF TRIES = %d ",trial);
            reset();
        }
        else
        {
            green();
            printf("\n CONGRATULATIONS  YOU GUESSED THE WORD !!!!   ");
			reset();
            break;
        }

    }
    while (trial < 8);

    if (trial>=8)
    {
       	red();
		printf("\n \n 	  GAME OVER");
        printf("THE NUMBER IS : %s ",orig);
		reset();
    }


}
//-------------------------------------------------------------------------------------------------------




















void main(){

	int key;
	int choice;
	do{
		red();
    	printf("----------------WELCOME TO THE GAME---------------------\n\n");
		yellow();
    	printf("CHOOSE WHICH GAME YOU WANT TO PLAY : \n\n ");
		reset();
    	printf("[1]        WORDS\n");
    	printf(" \n [2]        NUMBERS\n");
    	printf(" \n ENTER YOUR CHOSE \n");
		do{
			key=getch()-48;
		}while(key!=1 && key!=2);
		switch(key){
			case 1:
				system("cls");	
				red();
        		printf("--------------WELCOME TO GUESSING WORDS GAME----------------\n\n");
				reset();	
				choose_game_word();
				system("cls");
				game_Words();
				
				break;
			case 2:
				system("cls");
                red();
				printf("\n ---------------WELCOME TO NUMBERS GAME-----------------\n\n");
                reset();
                game_number();
				break;	
		}
		printf("\n\n DO YOU WANT PLAY AGAIN ? Y/N");
		do{
			choice=getch();			
		}while(choice!=89 && choice!=121 && choice!=78 && choice!=110);
		system("cls");			
	}while(choice==89 || choice==121);

}
