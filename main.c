/*
===Program: PA01
===Programmer: William Youse
===Date Due: 2/8/2023
===Purpose: To create a doubly linked list to (currently) store 'songs', travsersable, able to add and delete.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "song.h"

//temp variables for user input
int userInput = -1;
char artName[4096], songName[4096];
int songLength = 0;

//creates a new song node, throws in data collected from user, ammends linked list at the end
void insertEnd(struct song** head, char *artName, char *songName, int time){

    struct song* newNode = (struct song*) malloc(sizeof(struct song));
    
    newNode->artist = malloc(strlen(artName) + 1);
    newNode->name = malloc(strlen(songName) + 1);

    strcpy(newNode->artist, artName);
    strcpy(newNode->name, songName);
    newNode->length = time;
    newNode->next = NULL;
    newNode->prev = NULL;

    if(*head==NULL){
        *head = newNode;
        return;
    }

    struct song *temp = *head;

    while(temp->next!=NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

//allows for a single node deletion/ammend after deletion
void deleteUnit(struct song** head, struct song* temp)
{

    if (*head == NULL || temp == NULL) {
        return;
    }

    if (*head == temp) {
        *head = temp->next;
    }
 
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
 
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    free(temp);
}

void deleteArtist(struct song** head, char *artistCheck)
{
    if ((*head) == NULL)
        return;
 
    struct song* ptr = *head;
    struct song* next;
 
    while (ptr != NULL) {
 
        if (strcmp(ptr->artist, artistCheck) == 0) {
            next = ptr->next;
            deleteUnit(head, ptr);
            ptr = next;
        } else {
            ptr = ptr->next;
        }
    }
}

void deleteSong(struct song **head, char *songCheck)
{
    if ((*head) == NULL)
        return;
 
    struct song *ptr = *head;
    struct song *next;
 
    while (ptr != NULL) {
        if (strcmp(ptr->name, songCheck) == 0) {
            next = ptr->next;
            deleteUnit(head, ptr);
            ptr = next;
        } else {
            ptr = ptr->next;
        }
    }
}

void deleteAll(struct song** head)
{
    if ((*head) == NULL)
        return;
 
    struct song* ptr = *head;
    struct song* next;
 
    while (ptr != NULL) {
 
        if (ptr->length >= 0) {
            next = ptr->next;
            deleteUnit(head, ptr);
            ptr = next;
        } else {
            ptr = ptr->next;
        }
    }
}

void displayList(struct song *hold) {
  struct song *last;

  while (hold != NULL) {
    
    printf("Artist: %s\n", hold->artist);
    printf("Song: %s\n", hold->name);
    printf("Time: %d seconds\n", hold->length);
    printf("----------\n");

    last = hold;
    hold = hold->next;
  }
}

int main() {
    struct song *head = NULL;
 
    while (userInput != -99) {

        strcpy(artName, "");
        strcpy(songName, "");

    printf("=====Song Menu=====\n");
    printf("\n");
    printf("1) Add a Song\n");
    printf("2) Delete a song\n");
    printf("3) Delete an Artist\n");
    printf("4) Print Songs\n");
    printf("5) Exit\n\n");
    printf("Choice: ");
    scanf("%d", &userInput);

/*!!!!!REQUIRED - INPUT NON-FUNCTIONAL WITHOUT IT!!!!!*/
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    switch (userInput)
    {
    case (1):
        printf("Enter Artists Name: ");
        fgets(artName, sizeof(artName), stdin);

        printf("Enter Songs Name: ");
        fgets(songName, sizeof(songName), stdin);

        printf("Enter Songs Length (in seconds): ");
        scanf("%d", &songLength);
        
        insertEnd(&head, artName, songName, songLength);
        break;
    
    case (2):
        printf("Enter song name: ");
        fgets(songName, sizeof(songName), stdin);
        deleteSong(&head, songName);
        break;

    case (3):
        printf("Enter artist name: ");
        fgets(artName, sizeof(artName), stdin);
        deleteArtist(&head, artName);
        break;

    case (4):
        displayList(head);
        break;

    case (5):
        printf("Exiting Program, hope you enjoyed!\n");
        deleteAll(&head);
        userInput = -99;
        break;

    default:
        break;
    }
    }

    return 0;
}