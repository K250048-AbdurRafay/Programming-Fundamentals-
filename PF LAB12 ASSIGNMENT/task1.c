#include <stdio.h>
#include <stdlib.h>

int calc_tot_stock(int *books, int count) {
    int tot = 0;
    for (int i = 0; i < count; i++) {
        tot += books[i];
    }
    printf("Total stock is %d\n", tot);
    return tot;
}

void avg_stock(int count, int total) {
    printf("%.2f\n", (float)total / count);
}

void lowest_category(int *books, int count) {
    int min = books[0], index = 0;
    
    for (int i = 1; i < count; i++) {
        if (min > books[i]) {
            min = books[i];
            index = i;
        }
    }
    printf("Lowest stock at index %d\n", index);
}

int main() {
    int count;
    int *books;

    printf("How many categories: \n");
    scanf("%d", &count);

    books = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        printf("How many books for category %d : \n", i + 1);
        scanf("%d", &books[i]);
    }

    int tot = calc_tot_stock(books, count);
    avg_stock(count, tot);
    lowest_category(books, count);

    free(books);
    return 0;
}