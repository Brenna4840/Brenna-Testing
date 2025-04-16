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

void compute8(char *testFile, int checksumSize, int textLength); 
void compute16(char *testFile, int checksumSize, int textLength); 
void compute32(char *testFile, int checksumSize, int textLength); 

//********************************************************
// int main(int argc, char **argv)  
//
// Purpose:          reads the file, prints it, and calls other compute functions     
// Output:           prints file's contents in lines of 80 characters  
// Argunments:       argc is the number of command line arguments, and argv is an array of the argunments   
// Postcondition:    1 if an error happens, else 0        
//********************************************************
int main(int argc, char **argv) 
{
    FILE *file = fopen(argv[1], "r"); 
    if(file == NULL) 
    {
        return 1; 
    }  

    char *testFile = (char *)malloc((10000) * sizeof(char)); //array to read the file to 
    if (testFile == NULL) 
    {
        fclose(file); 
        return 1; 
    }

    int counter = 0; 
    for(int i = 0; i < 500; i++) 
    { 
        int result = fscanf(file, "%c", &testFile[i]); 
        if(result == EOF)
        {
            break; 
        }
        counter++; 
    } 

    printf("\n"); 
    for (int i = 0; i < counter; i++) 
    {
        printf("%c", testFile[i]);
        if ((i + 1) % 80 == 0 && i != counter - 1) 
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
        return 1; 
    }  
    else if(checksumSize == 8) 
    {
        printf("\n"); 
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

    fclose(file); 
    free(testFile); 
    return 0; 
} 


//********************************************************
// void compute8(char *testFile, int checksumSize, int textLength) 
//
// Purpose:          computes the 8 bit checksum    
// Output:           prints the checksum size 8, the checksum, and the length of the input 
// Argunments:       char *testFile contains the input information, int checksumSize is 8  
//                   and int textLength is the length of the input   
// Postcondition:    returns nothing      
//********************************************************
void compute8(char *testFile, int checksumSize, int textLength) 
{
    unsigned int checksum = 0; 
        
    for(int i = 0; i < textLength; i++) 
    {
        unsigned int num1 = (unsigned int)testFile[i]; 
        unsigned int num2 = (unsigned int)testFile[i+1]; 
        i++; //to prevent skipping or repeating characters  
        
        checksum = checksum + (num1 + num2);             
    } 
    
    printf(" %d bit checksum is %8x for all %4d chars\n", checksumSize, (unsigned char)checksum, textLength); 
}


//********************************************************
// void compute16(char *testFile, int checksumSize, int textLength) 
//
// Purpose:          computes the 16 bit checksum    
// Output:           prints the checksum size 16, the checksum, and the length of the input 
// Argunments:       char *testFile contains the input information, int checksumSize is 16  
//                   and int textLength is the length of the input   
// Postcondition:    returns nothing      
//********************************************************
void compute16(char *testFile, int checksumSize, int textLength) 
{
    unsigned short checksum = 0; 

    for (int i = 0; i < textLength; i += 2) //moves by 2 
    {
        unsigned short word = testFile[i] << 8; //shift left eight 
        if ((i + 1) < textLength) 
        {
            word |= testFile[i + 1]; //OR 
        } 

        checksum += word; 
    }  

    if(textLength % 2 != 0) 
    {
        checksum += 88; //aka X  
        printf("X"); 
        textLength++; 
    }
    printf("\n"); 

    printf("%d bit checksum is %8x for all %d chars\n", checksumSize, checksum, textLength); 
} 


//********************************************************
// void compute32(char *testFile, int checksumSize, int textLength) 
//
// Purpose:          computes the 32 bit checksum    
// Output:           prints the checksum size, the checksum, and the length of the input 
// Argunments:       char *testFile contains the input information, int checksumSize is 32 
//                   and int textLength is the length of the input   
// Postcondition:    returns nothing      
//********************************************************
void compute32(char *testFile, int checksumSize, int textLength) 
{
    unsigned int checksum = 0;
    
    int padding = 4 - textLength % 4; 
    padding = padding % 4; //makes sure it doesn't pad if already 4 
    for (int i = textLength; i < textLength + padding; i++) 
    {
        testFile[i] = 0x58; //aka X 
        printf("X");  
    } 
    testFile[textLength + padding] = '\0'; 
    printf("\n"); 
    textLength = textLength + padding; 

    for (int i = 0; i < textLength; i += 4) //moves by 4 
    {
        unsigned int word = 0; 
        for (int j = 0; j < 4 && (i + j) < textLength; j++) 
        {
            word |= (unsigned char)testFile[i + j] << (8 * (3 - j)); 
        } 
        checksum += word; 
    } 
    
    printf("%d bit checksum is %8x for all %d chars \n", checksumSize, checksum, textLength); 
} 


/*=============================================================================
| I Brenna Aleshire (br680439) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/