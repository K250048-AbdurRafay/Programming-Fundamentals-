#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void longest_feedback_msg(char **feedbacks, int n){
    int j = 0 , count = 0, previous = 0 , index = 0;

    for (int i = 0; i < n; i++)
    {
        while (feedbacks[i][j] != '\0'){
            count ++;
            j++ ;
        }

        if (previous < count)
        {
            previous = count;
            index = i;
        }

        j = 0;
        count = 0;
    }

    printf("LONGEST FEEDBACK MSG IS: \n");
    printf("%s\n", feedbacks[index]);
    

}



int main(){
    
    char ** feedbacks;
    int n, count = 0;
    char buffer[1000];

    printf("How many entries to be made? ");
    scanf("%d", &n);
    getchar();

    feedbacks = malloc(n * sizeof(char *));

    // storing the feedbacks 

    for (int i = 0; i < n; i++)
    {
        printf("Feedback:\n");

        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        count += strlen(buffer);

        feedbacks[i] = malloc(strlen(buffer) + 1);
        strcpy(feedbacks[i], buffer);

    }

    printf("\nTotal no.of chars is: %d\n", count);

    printf("\n");
    longest_feedback_msg(feedbacks, n);



    // free all memory 

    for (int i = 0; i < n; i++)
    {
        free(feedbacks[i]);
    }
    free(feedbacks);
    

    return 0;
}