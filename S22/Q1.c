#include <stdio.h>

int main() {
    // Redirect stdout to "output.txt"
    FILE *file = freopen("output.txt", "w", stdout);
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Any output that goes to stdout now goes to "output.txt"
    printf("This text will be written to output.txt\n");
    printf("Redirected output successfully!\n");

    // Close the file
    fclose(file);

    return 0;
}
