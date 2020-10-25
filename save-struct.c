#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void getCards();
void create();
void delete();
void writeArrToFile();
void readAll();

//main object
typedef struct Card{
    char deno;
    int value;
    bool used;
}Card;

Card *cards;
int cards_count = 0;


int main(int argc, char *argv[]){
    char input;

    getCards();

    //main menu
    printf("Enter commando: (r)eadAll / (c)reate / (d)el\n");
    bool alive = true;
    while(alive){    
        printf("\n");
        scanf("%c", &input);

        if(input == 'c'){
            create();
        }
        else if(input == 'r'){
            readAll();
        }
        else if(input == 'd'){
            delete();
        }
    }

    return 0;
}


void create(){
    Card newCard;

    //fill struct
    printf("deno: ");
    scanf(" %c", &newCard.deno);
    printf("value: ");
    scanf(" %i", &newCard.value);
    newCard.used = false;

    //add card to card arr
    cards_count ++;
    cards = realloc(cards, cards_count * sizeof(Card));
    cards[cards_count- 1] = newCard; 

    writeArrToFile();
}

void delete(){
    int index;
    printf("Index of item to remove: ");
    scanf(" %i", &index);
    if(index < 0 || index >= cards_count){
        printf("Ur a _ stupid");
        return;
    }
    //overwrites index with stuff after
    memcpy(&cards[index], &cards[index + 1], (cards_count - index) * sizeof(Card));

    cards_count--;
    readAll();
    writeArrToFile();
}

void writeArrToFile(){
    FILE *newFile = fopen("vadsomhelst", "wb");
    fwrite(cards, sizeof(Card), cards_count, newFile);
    fclose(newFile);
}

//reads ram arr, not hdd
void readAll(){
    for(int i = 0; i < cards_count; i++){
        printf("%i  deno: %c  value: %i \n", i, cards[i].deno, cards[i].value);
    }
}

void getCards(){
    FILE *newFile;

    //open file if it exists
    newFile = fopen("vadsomhelst", "rb");
    if(newFile == NULL){
        cards = malloc(0 * sizeof(Card));
        create();
        return;   
    }

    //gets file size
    fseek(newFile, 0, SEEK_END);
    cards_count = ftell (newFile);
    rewind(newFile);

    //fills local arr with file
    cards = malloc(cards_count);
    fread(cards, sizeof(Card), cards_count, newFile);
    fclose(newFile);

    //cards_count is bytes at this point!!!
    cards_count /= sizeof(Card);
}

