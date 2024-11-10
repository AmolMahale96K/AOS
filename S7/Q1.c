#include <stdio.h>

int main() {
    // Open a file for writing
    FILE *file = freopen("output.txt", "w", stdout);
    
    // Check if file opening was successful
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Printing to the file (this will be redirected to output.txt)
    printf("This will be written to the output.txt file.\n");
    printf("Another line of text to demonstrate redirection.\n");

    // Close the file
    fclose(file);

    return 0;
}
