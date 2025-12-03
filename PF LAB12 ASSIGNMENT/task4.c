#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *ratings;

    printf("How many movie categories? ");
    scanf("%d", &n);


    ratings = malloc(n * sizeof(int));


    // inputting ratings
    for (int i = 0; i < n; i++) {
        printf("Enter rating count for category %d: ", i + 1);
        scanf("%d", &ratings[i]);
    }

    // find total ratings
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += ratings[i];
    }

    // find avg
    float average = (float)total / n;


    // finding category with highest rating
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[maxIndex]) {
            maxIndex = i;
        }
    }

    // Display results

    printf("Total ratings: %d\n", total);
    printf("Average ratings per category: %.2f\n", average);
    printf("Category with highest rating: Category %d (Rating: %d)\n", maxIndex + 1, ratings[maxIndex]);

    
    
    //  update values if user wants to
    int updateIndex, newRating;

    printf("\nEnter category number to update (1 to %d): ", n);
    scanf("%d", &updateIndex);


    updateIndex--;

     
    printf("Enter new rating: ");
    scanf("%d", &newRating);
    ratings[updateIndex] = newRating;


    return 0;
}