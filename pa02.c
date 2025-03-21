/*============================================================================
| Assignment: pa02 - checksums 
|
| Author: Brenna Aleshire 
| Language: c
| To Compile: gcc -o pa02 pa02.c
| To Execute: ./pa02 inputFilename.txt checksumSize 
| where inputFilename.txt is the input file
| and checksumSize is either 8, 16, or 32
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis 
|
| Class: CIS3360 - Security in Computing - Spring 2025
| Instructor: McAlpin
| Due Date: 03/23/2025 
+===========================================================================*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  

int compute8(char *testFile, int checksumSize, int textLength); 
int compute16(char *testFile, int checksumSize, int textLength); 
int compute32(char *testFile, int checksumSize, int textLength); 

int main(int argc, char **argv) 
{
    FILE *file = fopen(argv[1], "r"); 
    if(file == NULL) 
    {
        printf("Could not open file\n"); 
        return 1; 
    }  
    char *testFile = (char *)malloc((10000) * sizeof(char)); //array to read the file to 
    if (testFile == NULL) 
    {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }
    int counter = 0; 
    for(int i = 0; i < 500; i++) 
    { 
        int result = fscanf(file, "%c", &testFile[i]);  //reading the file 
        if(result == EOF)
        {
            break; 
        }
        counter++; 
    } 
    for(int i = 0; i < counter; i++) //formatting the lines 
    {
        printf("%c", testFile[i]); 
        if((i+1) % 80 == 0) 
        {
            printf("\n"); 
        }
    } 

    int checksumSize = 0; 
    for (int i = 0; argv[2][i] != '\0'; i++) 
    {
        checksumSize = checksumSize * 10 + (argv[2][i] - '0');
    }     
    if(checksumSize != 8 && checksumSize != 16 && checksumSize != 32) //error check 
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n"); 
    }

    fclose(file);  

    if(checksumSize == 8)
    {
        compute8(testFile, checksumSize, counter); 
    }
    else if(checksumSize == 16)
    {
        compute16(testFile, checksumSize, counter); 
    }
    else if(checksumSize == 32)
    {
        compute32(testFile, checksumSize, counter); 
    }

    return 0; 
}

int compute8(char *testFile, int checksumSize, int textLength)
{
    unsigned int checksum = 0; 
        
        for(int i = 0; i < textLength; i++) 
        {
            unsigned int num1 = (unsigned int)testFile[i]; 
            unsigned int num2 = (unsigned int)testFile[i+1]; 
            i++; //to prevent skipping or repeating characters      
            
            checksum = checksum + (num1 + num2);             
        } 
        
        printf("%d bit checksum is %8x for all %d chars\n", checksumSize, (unsigned char)checksum, textLength); 
        return 0;  
}

int compute16(char *testFile, int checksumSize, int textLength) 
{
    unsigned short checksum = 0;

        for (int i = 0; i < textLength; i += 2) 
        {
            unsigned short word = testFile[i] << 8; 
            if (i + 1 < textLength) 
            {
                word |= testFile[i + 1]; 
            } 

            checksum += word;
        }  

        if(textLength % 2 != 0)
        {
            checksum += 88; 
            textLength++; 
        }
   
        printf("%d bit checksum is %8x for all %d chars\n", checksumSize, checksum, textLength); 
        return 0;  
}

int compute32(char *testFile, int checksumSize, int textLength) 
{
    int padding = (4 - textLength % 4) % 4; 
        char paddedTestFile[textLength + padding + 1];
        strcpy(paddedTestFile, testFile);
        for (int i = textLength; i < textLength + padding; i++) 
        {
            paddedTestFile[i] = 0x58; //aka X 
        }
        paddedTestFile[textLength + padding] = '\0';

        unsigned int checksum = 0;
        for (int i = 0; i < textLength + padding; i += 4) //process in words of 4 
        {
            unsigned int word = 0;  
            for (int j = 0; j < 4 && i + j < textLength + padding; j++) 
            {
                word |= (unsigned char)paddedTestFile[i + j] << (8 * (3 - j));
            }
            checksum += word;
        }

        int finalLength = textLength + padding; 
        
        printf("%d bit checksum is %8x for all %d chars \n", checksumSize, checksum, finalLength); 
        return 0;  
}


/*=============================================================================
| I Brenna Aleshire (br680439) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/