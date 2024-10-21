#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to represent a parsing table entry
typedef struct {
    char non_terminal;
    char terminal;
    char* production;
} ParsingTableEntry;

// Structure to represent the parsing table
typedef struct {
    ParsingTableEntry* entries;
    int size;
} ParsingTable;

// Function to create a new parsing table entry
ParsingTableEntry* createParsingTableEntry(char non_terminal, char terminal, char* production) {
    ParsingTableEntry* entry = (ParsingTableEntry*) malloc(sizeof(ParsingTableEntry));
    entry->non_terminal = non_terminal;
    entry->terminal = terminal;
    entry->production = production;
    return entry;
}

// Function to create a new parsing table
ParsingTable* createParsingTable(int size) {
    ParsingTable* table = (ParsingTable*) malloc(sizeof(ParsingTable));
    table->entries = (ParsingTableEntry*) malloc(size * sizeof(ParsingTableEntry));
    table->size = size;
    return table;
}

// Function to add an entry to the parsing table
void addEntryToParsingTable(ParsingTable* table, char non_terminal, char terminal, char* production) {
    for (int i = 0; i < table->size; i++) {
        if (table->entries[i].non_terminal == non_terminal && table->entries[i].terminal == terminal) {
            table->entries[i].production = production;
            return;
        }
    }
    table->entries[table->size].non_terminal = non_terminal;
    table->entries[table->size].terminal = terminal;
    table->entries[table->size].production = production;
    table->size++;
}

// Function to perform LL(1) parsing
void ll1Parse(ParsingTable* table, char* input) {
    char stack[100];
    int top = 0;
    stack[top++] = 'S'; // Start symbol

    for (int i = 0; i < strlen(input); i++) {
        char current_symbol = input[i];
        char top_symbol = stack[--top];

        for (int j = 0; j < table->size; j++) {
            if (table->entries[j].non_terminal == top_symbol && table->entries[j].terminal == current_symbol) {
                char* production = table->entries[j].production;
                for (int k = strlen(production) - 1; k >= 0; k--) {
                    stack[top++] = production[k];
                }
                break;
            }
        }
    }

    if (top == 0) {
        printf("String accepted\n");
    } else {
        printf("String rejected\n");
    }
}

int main() {
    // Example grammar:
    // E -> E + T | T
    // T -> 0 | 1

    ParsingTable* table = createParsingTable(10);

    addEntryToParsingTable(table, 'E', '0', "TE'");
    addEntryToParsingTable(table, 'E', '1', "TE'");
    addEntryToParsingTable(table, 'E', '+', "E+T");
    addEntryToParsingTable(table, 'T', '0', "0");
    addEntryToParsingTable(table, 'T', '1', "1");

    char* input = "1+0";
    ll1Parse(table, input);

    return 0;
}