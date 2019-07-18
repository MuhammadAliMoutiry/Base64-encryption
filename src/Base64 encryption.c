/*
 ============================================================================
 Name        : Base64.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void encryptget6bit(unsigned char arr[], unsigned char *buffer);
void base64Encryption(unsigned char *buffer, unsigned char *encryption);
void decrypt8bitget(unsigned char * buffer, unsigned char *arr);
void base64EncryptionForFiles(FILE *source, FILE *dest);
void base64DecryptionForFile(FILE *source, FILE *dest);
char linearSearch(unsigned char *arr,int arraySize, unsigned char value);

unsigned char base64chars[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
		'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
		'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };
int main(void) {
	setbuf(stdout, NULL);
	FILE *encrypt, *decrypt;
	encrypt = fopen("encrypt.txt", "w");
	decrypt = fopen("decrypt.txt", "r");
	//base64EncryptionForFiles(encrypt, decrypt);
	base64DecryptionForFile(decrypt, encrypt);
	return EXIT_SUCCESS;
}
/****************************************************************/
/**
 * 01010101 01010101 01010101
 * 010101    shift right by 2
 * 010101    shift right by 4
 * 010101    shift right by 6
 * 010101
 */
void encryptget6bit(unsigned char arr[], unsigned char *buffer) {
	buffer[0] = arr[0] >> 2;
	buffer[1] = ((arr[1] & 0xf0) >> 4) | ((arr[0] & 0x03) << 4);
	buffer[2] = ((arr[2] & 0xC0) >> 6) | ((arr[1] & 0x0F) << 2);
	buffer[3] = arr[2] & 0x3F;
	buffer[4] = '\0';
}
/*************************************************************************/

void base64Encryption(unsigned char *buffer, unsigned char *encryption) {

	encryption[0] = base64chars[buffer[0]];
	encryption[1] = base64chars[buffer[1]];
	encryption[2] = base64chars[buffer[2]];
	encryption[3] = base64chars[buffer[3]];
}
/**************************************************************************/
void decrypt8bitget(unsigned char * buffer, unsigned char *arr) {
	unsigned char temp[4];
	temp[0] = linearSearch(base64chars,64,buffer[0]);
	temp[1] = linearSearch(base64chars,64,buffer[1]);
	temp[2] = linearSearch(base64chars,64,buffer[2]);
	temp[3] = linearSearch(base64chars,64,buffer[3]);
	arr[0] = (temp[0] << 2) | (temp[1] >> 4);
	arr[1] = (temp[1] << 4) | (temp[2] >> 2);
	arr[2] = (temp[2] << 6) | (temp[3]);
	arr[3] = '\0';
}
/*************************************************************************/

/******************************************************************************/
void base64EncryptionForFiles(FILE *source, FILE *dest) {
	unsigned char arr[4], buffer[4], encrypt[4];
	int x = 1;
	while (x > 0) {
		x = fread(arr, sizeof(char), 3, source);
		if (x == 2) {
			arr[2] = ' ';
		} else if (x == 1) {
			arr[1] = ' ';
			arr[2] = ' ';
		}

		encryptget6bit(arr, buffer);
		base64Encryption(buffer, encrypt);
		fwrite(encrypt, 1, 4, dest);
		if (feof(source)) {
			break;
		}
	}
	fclose(source);
	fclose(dest);
}
/********************************************************************************/
void base64DecryptionForFile(FILE *source, FILE *dest) {
	unsigned char arr[4], decrypt[4];
	int x = 1;
	while (x > 0) {
		x = fread(arr, sizeof(char), 4, source);
		decrypt8bitget(arr, decrypt);
		//fprintf(dest,"%c%c%c",decrypt[0],decrypt[1],decrypt[2]);
		fwrite(decrypt, 1, 3, dest);
		if (feof(source)) {
			break;
		}
	}
	fclose(source);
	fclose(dest);
}
/*****************************************************************************/
char linearSearch(unsigned char *arr,int arraySize, unsigned char value) {
	unsigned char i = 0;
	for(i=0 ; i<arraySize ; i++){
		if(arr[i] == value){
			break;
		}


	}return i;

}
