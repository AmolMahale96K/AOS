#include <stdio.h>

int main() {
    // Redirect stdout to "output.txt"
    FILE *file = freopen("output.txt", "w", stdout);
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Now, any output to stdout goes to "output.txt" instead of the console
    printf("This text will be written to output.txt\n");
    printf("Redirection of standard output successful!\n");

    // Close the file
    fclose(file);

    return 0;
}
