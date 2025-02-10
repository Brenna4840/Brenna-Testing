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

int *readKeyFile(char *fileName); 
char *readTextFile(char *fileName); 
void simplifyFormat(int *keyFile, char *textFile); 
void multiplyMatrixes(int *keyFile, char *textFile, int textLength); 

int main(int argc, char **argv) 
{
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

    simplifyFormat(keyFile, textFile);  

    return 0; 
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
    //printf("int n = %d \n", n);   
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

    printf("Key matrix: \n"); 
    for(int i = 1; i < (n*n)+1; i++) 
    {
        printf("%4d", keyFile[i]); 
        if(i % n == 0)
        {
            printf("\n"); 
        }
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

    return textFile; 
}


void simplifyFormat(int *keyFile, char *textFile) 
{
    int position = 0; 
    for(int i = 0; i < 10000; i++) 
    {
        if(((textFile[i] >= 65 && textFile[i] <= 90) || (textFile[i] >= 97 && textFile[i] <= 122))) 
        // if the ascii is between 65-90 or 97-122 
        {
            textFile[position++] = textFile[i]; //essentially skips the numbers and symbols  
        } 
    } 
    for(int i = position; i < 10000; i++) 
    {
        textFile[i] = '\0'; //gets ride of extra characters at the end 
    }

    for(int i = 0; i < position; i++) 
    {
        if(textFile[i] >= 65 && textFile[i] <=90) 
        {
            textFile[i] = (textFile[i] + 32); //converts uppercase to lowercase 
        }
    }

    //add x 
    if(position % keyFile[0] != 0) 
    {
        //
    }

    printf("Plaintext: \n"); 
    for(int i = 0; i < 150; i++) 
    {
        printf("%c", textFile[i]); 
        if((i+1) % 80 == 0) //if a factor of 80 
        {
            printf("\n"); 
        }
    } 
    printf("\n \n");

    multiplyMatrixes(keyFile, textFile, position); 
}


void multiplyMatrixes(int *keyFile, char *textFile, int textLength) 
{
    // 

    printf("Ciphertext: \n"); 
}


/*=============================================================================
| I Brenna Aleshire (br680439) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/