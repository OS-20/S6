#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], recent[f], faults = 0, time = 0;
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\nPage\tFrames\n-----------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        // Check if already in frame
        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                recent[j] = ++time;  // Update recent use time
                break;
            }
        }

        if (!found) {
            faults++;
            int replace = -1;

            // Empty frame check
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            // If full, replace the most recently used page
            if (replace == -1) {
                int max = recent[0]; replace = 0;
                for (int j = 1; j < f; j++)
                    if (recent[j] > max) {
                        max = recent[j];
                        replace = j;
                    }
            }

            frames[replace] = page;
            recent[replace] = ++time;
        }

        printf("%d\t", page);
        for (int j = 0; j < f; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        printf("\n");
    }

    printf("-----------------\nTotal Page Faults = %d\n", faults);
    return 0;
}
