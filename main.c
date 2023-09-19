#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void toMorseCode(char ch, char* code) {
    // Tabela de codificação Morse (caracteres e seus equivalentes)
    const char* morse[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",   // A-I
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",         // S-Z
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",  // 0-9
        " "  
    };

    if (isalpha(ch)) {
        ch = toupper(ch); 
        code = strcpy(code, morse[ch - 'A']);
    } else if (isdigit(ch)) {
        code = strcpy(code, morse[ch - '0' + 26]);
    } else if (ch == ' ') {
        code = strcpy(code, " / ");  
    } else {
        code = strcpy(code, ""); 
    }
}



void textToMorseCode(FILE* in, FILE* out) {
    char ch;
    char code[10]; 
    int firstCh = 1;

    while ((ch = fgetc(in)) != EOF) {
        if (firstCh) {
            firstCh = 0;
        } else {
            fprintf(out, "   ");
        }

        toMorseCode(ch, code);
        fprintf(out, "%s", code);
    }
}

int main() {
    FILE* in;
    FILE* out;
    char inFileName[50];
    char outFileName[50];

    printf("Input file: ");
    scanf("%s", inFileName);

    in = fopen(inFileName, "r");
    if (in == NULL) {
        printf("Could'nt open the file.\n");
        return 1;
    }

    printf("Output file: ");
    scanf("%s", outFileName);

    out = fopen(outFileName, "w");
    if (out == NULL) {
        printf("Could'nt open the file.\n");
        fclose(in);
        return 1;
    }

    textToMorseCode(in, out);

    printf("Text translated to morse code %s.\n", outFileName);

    fclose(in);
    fclose(out);

    return 0;
}
