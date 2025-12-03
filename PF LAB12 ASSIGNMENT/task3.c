#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_digit(char buffer[]){

    for (int i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            return 1;
        }
        
    }

    return 0;
    
}

int main(){
    int n;
    char ** usernames;
    char buffer[100];

    printf("How many users? ");
    scanf("%d", &n);
    getchar();

    usernames = malloc(n * sizeof(char *));

    // read usernames dynamically

    for (int i = 0; i < n; i++)
    {
        printf("Username: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';


        usernames[i] = malloc(strlen(buffer) + 1);
        strcpy(usernames[i], buffer);

    }



    // removes usernames with digits 
    for (int i = 0; i < n; i++)
    {
        if (contains_digit(usernames[i]) == 1)
        {
            free(usernames[i]);
            usernames[i] = NULL;
        }}

    // display all usernames 
    for (int i = 0; i < n; i++)
    {
        if (usernames[i] != NULL)
        {
            printf("%d. %s\n", i+1, usernames[i]);
            
        }
    }
    return 0;
}