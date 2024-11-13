#include <stdio.h>
#include <stdlib.h>

void copy_char_by_char(FILE *source, FILE *destination);
void copy_line_by_line(FILE *source, FILE *destination);

int main() {
    FILE *sourceFile, *destFileChar, *destFileLine;
    char sourcePath[100], destPathChar[100], destPathLine[100];

    // Get the source file path and destination file paths
    printf("Enter the source file path: ");
    scanf("%s", sourcePath);

    printf("Enter the destination file path for character-by-character copy: ");
    scanf("%s", destPathChar);

    printf("Enter the destination file path for line-by-line copy: ");
    scanf("%s", destPathLine);

    // Open the source file
    sourceFile = fopen(sourcePath, "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination files
    destFileChar = fopen(destPathChar, "w");
    if (destFileChar == NULL) {
        perror("Error opening destination file for character-by-character copy");
        fclose(sourceFile);
        return 1;
    }

    destFileLine = fopen(destPathLine, "w");
    if (destFileLine == NULL) {
        perror("Error opening destination file for line-by-line copy");
        fclose(sourceFile);
        fclose(destFileChar);
        return 1;
    }

    // Copy contents character by character
    copy_char_by_char(sourceFile, destFileChar);
    printf("File copied character by character to %s\n", destPathChar);

    // Rewind source file pointer to beginning for line-by-line copy
    rewind(sourceFile);

    // Copy contents line by line
    copy_line_by_line(sourceFile, destFileLine);
    printf("File copied line by line to %s\n", destPathLine);

    // Close all files
    fclose(sourceFile);
    fclose(destFileChar);
    fclose(destFileLine);

    return 0;
}

void copy_char_by_char(FILE *source, FILE *destination) {
    char ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }
}

void copy_line_by_line(FILE *source, FILE *destination) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, destination);
    }
}
