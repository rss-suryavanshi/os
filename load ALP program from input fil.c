*MOV A, B
ADD A, 5
SUB B, A
JMP 10
HLT*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY 1024   // Define the size of "main memory" (adjustable as needed)
#define MAX_INSTRUCTION_LENGTH 50   // Maximum length of each instruction

int main() {
    FILE *inputFile;
    char filePath[100];
    char memory[MAX_MEMORY][MAX_INSTRUCTION_LENGTH];  // Simulating main memory as an array of strings
    int memoryIndex = 0;  // Tracks the current position in memory

    // Get the input file path from the user
    printf("Enter the path of the ALP input file: ");
    scanf("%s", filePath);

    // Open the ALP input file
    inputFile = fopen(filePath, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Load the ALP instructions into memory, line by line
    while (fgets(memory[memoryIndex], MAX_INSTRUCTION_LENGTH, inputFile) != NULL) {
        // Remove newline character if present
        memory[memoryIndex][strcspn(memory[memoryIndex], "\n")] = '\0';

        memoryIndex++;

        // Check if memory limit is reached
        if (memoryIndex >= MAX_MEMORY) {
            printf("Memory overflow: ALP program is too large to fit in memory.\n");
            break;
        }
    }

    // Close the input file
    fclose(inputFile);

    // Display the loaded instructions in memory
    printf("Loaded ALP Program into Memory:\n");
    for (int i = 0; i < memoryIndex; i++) {
        printf("Memory[%d]: %s\n", i, memory[i]);
    }

    return 0;
}
