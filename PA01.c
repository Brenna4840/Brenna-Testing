/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Brenna Aleshire 
| Language: c
| To Compile: gcc -o pa01 pa01.c
| To Execute: c -> ./pa01 kX.txt pX.txt 
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 02/23/2025 
+===========================================================================*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  

char *simplifyFormat(char *text); 
int *readKeyFile(char *fileName); 
char *readTextFile(char *fileName); 

int main(int argc, char **argv) 
{
    for (int i = 0; i < argc; i++) //prints the accepted arguments 
    {
        printf("argument %d: %s\n", i, argv[i]);
    }
    printf("\n"); 

    int *keyFile = readKeyFile(argv[1]); 
    if(keyFile == NULL)
    {
        printf("key file broken \n"); 
        return 1; 
    }
    char *textFile = readTextFile(argv[2]); 
    if(textFile == NULL)
    {
        printf("text file broken \n"); 
        return 1; 
    }

    textFile = simplifyFormat(textFile); 
    // for(int i = 0; i < 75; i++) 
    // {
    //     printf("TextFile[%d]: %c\n", i, textFile[i]); 
    // } 
    // printf("\n"); 

    return 0; 
}


char *simplifyFormat(char *text) 
{
    int position = 0; 
    for(int i = 0; i < 10000; i++) 
    {
        if(((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))) 
        // if the ascii is between 65-90 or 97-122 
        {
            text[position++] = text[i]; //moves up all the other characters 
        } 
    } 

    for(int i = 0; i < 10000; i++)
    {
        if((text[i] >= 65 && text[i] <=90)) 
        {
            text[i] = (text[i] + 32); //converts uppercase to lowercase 
        }
    }

    return text;   
}

int *readKeyFile(char *fileName) 
{
    FILE *file1 = fopen(fileName, "r"); 
    if(file1 == NULL) 
    {
        printf("Could not open file\n"); 
        return NULL; 
    } 
    int n; 
    fscanf(file1, "%d", &n);  
    printf("int n = %d \n", n);   
    int *keyFile = (int *)malloc((n*n) * sizeof(int) + 1);
    if (keyFile == NULL) {
        printf("Memory allocation failed\n");
        fclose(file1);
        return NULL;
    }
    keyFile[0] = n; 
    for(int i = 1; i < (n*n)+1; i++) 
    { 
        fscanf(file1, "%d", &keyFile[i]); 
    }
    fclose(file1); 
    for(int i = 0; i < (n*n)+1; i++) 
    {
        printf("KeyFile[%d]: %d\n", i, keyFile[i]); 
    } 
    printf("\n");  

    return keyFile; 
}

char *readTextFile(char *fileName) 
{
    FILE *file2 = fopen(fileName, "r"); 
    if(file2 == NULL) 
    {
        printf("Could not open file\n"); 
        return NULL; 
    }  
    char *textFile = (char *)malloc((10000) * sizeof(char)); 
    if (textFile == NULL) {
        printf("Memory allocation failed\n");
        fclose(file2);
        return NULL;
    }
    int counter = 0; 
    for(int i = 0; i < (10000); i++) 
    { 
        int result = fscanf(file2, " %c", &textFile[i]);  
        if(result == EOF)
        {
            break; 
        }
        counter++; 
    }
    fclose(file2); 
    // for(int i = 0; i < counter; i++) 
    // {
    //     printf("TextFile[%d]: %c\n", i, textFile[i]); 
    // } 
    // printf("\n"); 

    return textFile;  
}

/*=============================================================================
| I Brenna Aleshire (br680439) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/