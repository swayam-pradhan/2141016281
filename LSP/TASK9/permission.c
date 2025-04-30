#include <stdio.h>

int main() {
    FILE *file;
    char buffer[100];

    // Open or create the file
    file = fopen("data.txt", "w+"); // "w+" creates the file if it doesn't exist
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write to the file
    fputs("Hello, File Handling in C!", file);

    // Move file pointer to the beginning
    rewind(file);

    // Read the contents back
    fgets(buffer, sizeof(buffer), file);

    // Print the contents
    printf("File contents: %s\n", buffer);

    // Close the file
    fclose(file);

    return 0;
}

