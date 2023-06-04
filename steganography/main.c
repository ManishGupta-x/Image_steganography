#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_bytes(int start, int end, FILE *src, FILE *dest)
{

    fseek(src, start, SEEK_SET);
    do
    {
        fputc(fgetc(src), dest);
        if (ftell(src) == end)
        {
            break;
        }

    } while (1);
}

int insert_byte(int file_wali_bit, int generating_byte)
{

    file_wali_bit = file_wali_bit << 7;
    generating_byte = generating_byte >> 1;
    generating_byte = file_wali_bit | generating_byte;
    return generating_byte;
}

int encoder(char *msg, FILE *src, FILE *fp)
{

    int ch;
    copy_bytes(0, 54, src, fp);
    int i = 0;
    int j = 0;
    int msg_length = strlen(msg);
    while (i < msg_length)
    {

        ch = fgetc(src);
        if (ch == EOF)
        {
            break;
        }
        int demo = ch & 0xfe;
        ch = demo | ((msg[i] >> j) & 1);
        fputc(ch, fp);
        j++;
        if (j == 8)
        {
            j = 0;
            i++;
        }
    }

    printf("Message Encoded\n");
    //**-------------------Calculating size of the file-------------------**//
    // fseek(fp, 0, SEEK_END);
    // long int size;
    // size = ftell(fp);
    // image = (unsigned char *)malloc(ftell(fp));
    // int message_Length = strlen(msg);
    // for (int i = 0; i < strlen(pass); i++)
    // {
    //     encode_char(pass[i], image,fp);
    // }
    // //encode_char((char)message_Length, image,fp);
    // for (int i = 0; i < message_Length; i++)
    // {
    //     encode_char(msg[i], image,fp);
    // }

    return ftell(fp);
}

void decoder(FILE * image, int num){

    int ch;
    int generating_byte = 0;
    for (int i = 0; i < num; i++)
    {

        for (int i = 0; i < 8; i++)
        {   
            ch = fgetc(image) & 1;
            generating_byte = insert_byte(ch, generating_byte);
        }
        printf("%c", (char)generating_byte);
        generating_byte = 0;
    }    

}


void main()
{

    printf("Choose the option : \n1. Encryption\n2. Decryption\n");
    int choice;
    scanf("%d", &choice);
    getchar();

    //=======================================Opening files=======================================//
    
     FILE *read = fopen("text.txt", "r");
     FILE *pass_file = fopen("pass.txt", "r");
     FILE *src = fopen("ST.bmp", "rb");
     FILE *fp;
     FILE *image;

     // other Declarations;
     char ch;
     
     switch (choice)
     {
     case 1:

        fp = fopen("copy.bmp", "wb");
        printf("Reading Message..\n\n");
        char msg[1000];
        int i = 0;
        while ((ch = fgetc(read)) != EOF)
        {

            msg[i] = ch;
            i++;
        }
        msg[i] = '\0';
        fclose(read);

        // printf("Create a Password for future Decryption : ");

        char pass[7];
        
        i = 0;
        while ((ch = fgetc(pass_file)) != EOF)
        {

            pass[i] = ch;
            i++;
        }

        pass[i] = strlen(msg) + 48;
        pass[i + 1] = '\0';

        fclose(pass_file);
        // append msg to pass
        strcat(pass, msg);

        

        fseek(src, 0, SEEK_END);
        int file_size = ftell(src);
        int last_location = encoder(pass, src, fp);
        copy_bytes(last_location, file_size, src, fp);
        fclose(src);
        fclose(fp);
        break;

    case 2:


        image = fopen("copy.bmp", "rb");
        fseek(pass_file, 0, SEEK_SET);
        printf("Decryption\n");
        i = 0;
        char character;
        char password[7];
        while ((character = fgetc(pass_file)) != EOF)
        {

            password[i] = character;
            i++;
        }
        password[i] = '\0';

        // check password
        fseek(image, 54, SEEK_SET);

        //------------------------------------------Checking Password------------------------------------------//
        int generating_byte = 0;
        char pass_compare[6]={};
        char op = 1;

        for (int k = 0; k < strlen(password); k++)
        {
            
            for (int j = 0; j < 8; j++)
            {  
                ch = fgetc(image) & 1;
                printf("\nch = %d", ch);
                printf("\nposition = %d", ftell(image));
                generating_byte = insert_byte(ch, generating_byte);
                printf("\ngenerating_byte = %d\n", generating_byte);
            }
            pass_compare[k] = (char)generating_byte;
            generating_byte = 0;
        }
       
        //print password and pass compare
        printf("Pass_compare : ");
        for (int i = 0; i < strlen(pass_compare); i++)
        {
            printf("%c", pass_compare[i]);
        }
        printf("\nPassword : ");
        for (int i = 0; i < strlen(password); i++)
        {
            printf("%c", password[i]);
        }
        
        pass_compare[strlen(pass_compare)] = '\0';
        if (strcmp(password, pass_compare) != 0)
        {
            printf("\nWrong Password\n");
            exit(0);
        }
        

        //get Decoded Length
        generating_byte = 0;
        for (int i = 0; i < 8; i++)
        {
            ch = fgetc(image) & 1;
            generating_byte = insert_byte(ch, generating_byte);
        }
        int msg_length = (int)generating_byte - 48;
        
        printf("\nPassword Matched\n\n");
        decoder(image, msg_length);


        break;
    default:
        printf("Invalid Choice\n");
        break;
    }
}
