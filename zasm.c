#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* instructions[] = {
    "ADD", "SUB", "MUL", "DIV", "MOD", "STP", "LDI", "ADR",
    "SUR", "INC", "DEC", "JMP", "CMP", "JE",  "STI",
    "LDM", "PUSH", "POP" 
};
int total_instructions = sizeof(instructions) / sizeof(instructions[0]);

int get_opcode(const char *opcode_str) {
    for (int i = 0; i < total_instructions; i++) {
        if (strcmp(opcode_str, instructions[i]) == 0) {
            return i;
        }
    }
    return -1; 
}

int parse_operand(const char *op) {
    if (op[0] == 'R') {
        return atoi(op + 1); 
    }
    return atoi(op); 
}

int main() {
    FILE *in_file = fopen("example.zasm", "r");
    FILE *out_file = fopen("example.zx", "w");

    if (!in_file || !out_file) {
        printf("Error: Could not open files.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), in_file)) {
        for (char *p = line; *p != '\0'; p++) {
            if (*p == ',') *p = ' ';
        }

        char opcode_str[16] = {0};
        char operand1_str[16] = {0};
        char operand2_str[16] = {0};

        int tokens = sscanf(line, "%s %s %s", opcode_str, operand1_str, operand2_str);
        if (tokens < 1) continue; 

        int opcode = get_opcode(opcode_str);

        if (opcode == -1) {
            printf("Warning: Unknown instruction '%s'\n", opcode_str);
            continue;
        }

        int op1 = (tokens >= 2) ? parse_operand(operand1_str) : 0;
        int op2 = (tokens >= 3) ? parse_operand(operand2_str) : 0;

        fprintf(out_file, "%d, %d, %d,\n", opcode, op1, op2);
    }

    fclose(in_file);
    fclose(out_file);

    return 0;
}