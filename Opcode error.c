*MOV R1, R2
ADD R3, R4
XYZ R5, R6  // Invalid opcode
MUL R7, R8*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INSTRUCTION_LENGTH 50
#define MAX_OPCODE_LENGTH 10

// List of valid opcodes (extend as needed)
const char *validOpcodes[] = {"MOV", "ADD", "SUB", "MUL", "DIV", "JMP", "CMP", "LOAD", "STORE"};
int validOpcodesCount = sizeof(validOpcodes) / sizeof(validOpcodes[0]);

// Function to check if an opcode is valid
bool isValidOpcode(const char *opcode) {
    for (int i = 0; i < validOpcodesCount; i++) {
        if (strcmp(opcode, validOpcodes[i]) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE *inputFile;
    char filePath[100];
    char instruction[MAX_INSTRUCTION_LENGTH];
    char opcode[MAX_OPCODE_LENGTH];
    int lineNumber = 0;

    // Get the job (ALP file) path from the user
    printf("Enter the path of the ALP job file: ");
    scanf("%s", filePath);

    // Open the ALP job file
    inputFile = fopen(filePath, "r");
    if (inputFile == NULL) {
        perror("Error opening job file");
        return 1;
    }

    // Read instructions line by line and check for opcode validity
    while (fgets(instruction, MAX_INSTRUCTION_LENGTH, inputFile) != NULL) {
        lineNumber++;

        // Extract the opcode (first word in the instruction)
        sscanf(instruction, "%s", opcode);

        // Check if the opcode is valid
        if (!isValidOpcode(opcode)) {
            // Raise an interrupt for invalid opcode
            printf("Interrupt: Invalid Opcode '%s' found at line %d\n", opcode, lineNumber);
            continue;  // Continue checking remaining lines (or break if immediate stop is desired)
        }

        // If valid, display the instruction as is (for reference)
        printf("Line %d: %s", lineNumber, instruction);
    }

    // Close the file
    fclose(inputFile);

    return 0;
}
