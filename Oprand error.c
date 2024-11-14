MOV R1, R2
ADD R3, R4
SUB R5, R6
MUL R7, R8
DIV R9, R10
JMP 10
CMP R11, R12
LOAD R13, R14
STORE R15, R16
NOP                             
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INSTRUCTION_LENGTH 50
#define MAX_OPCODE_LENGTH 10
#define MAX_OPERANDS 3

// Define valid opcodes and their operand requirements
typedef struct {
    char opcode[MAX_OPCODE_LENGTH];
    int expectedOperands;
} OpcodeInfo;

// Array of opcodes and their expected operand counts
const OpcodeInfo validOpcodes[] = {
    {"MOV", 2},
    {"ADD", 2},
    {"SUB", 2},
    {"MUL", 2},
    {"DIV", 2},
    {"JMP", 1},
    {"CMP", 2},
    {"LOAD", 2},
    {"STORE", 2},
    {"NOP", 0}  // Example of an opcode that takes no operands
};
int validOpcodesCount = sizeof(validOpcodes) / sizeof(validOpcodes[0]);

// Function to get the expected operand count for an opcode
int getExpectedOperands(const char *opcode) {
    for (int i = 0; i < validOpcodesCount; i++) {
        if (strcmp(opcode, validOpcodes[i].opcode) == 0) {
            return validOpcodes[i].expectedOperands;
        }
    }
    return -1;  // Return -1 if the opcode is invalid
}

int main() {
    FILE *inputFile;
    char filePath[100];
    char instruction[MAX_INSTRUCTION_LENGTH];
    char opcode[MAX_OPCODE_LENGTH];
    char operand1[MAX_OPCODE_LENGTH], operand2[MAX_OPCODE_LENGTH];
    int lineNumber = 0;

    // Get the ALP job file path from the user
    printf("Enter the path of the ALP job file: ");
    scanf("%s", filePath);

    // Open the ALP job file
    inputFile = fopen(filePath, "r");
    if (inputFile == NULL) {
        perror("Error opening job file");
        return 1;
    }

    // Read instructions line by line and check for operand errors
    while (fgets(instruction, MAX_INSTRUCTION_LENGTH, inputFile) != NULL) {
        lineNumber++;
        
        // Extract the opcode and operands (if any)
        int operandCount = sscanf(instruction, "%s %s %s", opcode, operand1, operand2);

        // Get the expected number of operands for the opcode
        int expectedOperands = getExpectedOperands(opcode);
        
        if (expectedOperands == -1) {
            // Invalid opcode found, report it
            printf("Interrupt: Invalid Opcode '%s' found at line %d\n", opcode, lineNumber);
            continue;
        }

        // Check if the actual operand count matches the expected operand count
        if (operandCount - 1 != expectedOperands) {  // -1 to exclude opcode itself
            printf("Interrupt: Operand error for Opcode '%s' at line %d. Expected %d operand(s), found %d.\n",
                   opcode, lineNumber, expectedOperands, operandCount - 1);
            continue;
        }

        // If valid, display the instruction as is (for reference)
        printf("Line %d: %s", lineNumber, instruction);
    }

    // Close the file
    fclose(inputFile);

    return 0;
}
