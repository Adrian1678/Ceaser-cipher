// libraries 
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//end

//                                                          running the actual encryption
//TXT
void process(FILE * readfile, FILE * writefile, int shift ){
     int c;
        while ((c=fgetc(readfile))!=EOF){
            //printf("%c", c);
            // CODE FOR OUTPUT GOES HERE
            //encryption ceaser cipher by 3 places
            if (islower(c)){
              c = 'a' + ((c - 'a' + shift) % 26 + 26) % 26;//shift will take the value of whatever is in process function for shift
            }
            if (isupper(c)){
                c = 'A' + ((c - 'A' + shift) % 26 + 26) % 26;;
            }
            //writing the encrypted text to a new encrypted file
            fputc(c, writefile);  
                  
        }
}


// making a function for the image encrypt/decrypt// in/out file to make it esier to understand
void image_process(FILE * in_File, FILE *out_file, int shift){
    int i;
    while((i=fgetc(in_File))!=EOF){
        //printf("%d", i);
        //code for output goes here
        //encryption
        i= (((i + shift)% 256 +256)% 256);
        //creating the encrypted image
        fputc(i, out_file);
    }


}
//enc



//                                          all of the funtion TXT, IMAGES
//function if they choose text
void if_text(int shift, char *input_file, char *output_file){
    //opeing the required files
    //opeing the read and write file and TXT
    FILE *readfile=fopen(input_file, "r");
    FILE *writefile=fopen(output_file,"w");
    //opening it again so i can read it TXT
    FILE *decrypt=fopen("decryption.txt", "w");
    FILE * encrypteed=NULL;
    //end
    
    if (readfile!= NULL && writefile != NULL ){
            //printing if files opened or not
            
            printf("\n1: FIles opened successfully \n");
            process(readfile, writefile, +shift);//encrypt]
            printf("\n2: encrypted\n");
        
            fflush(writefile);//emptying the file
            encrypteed=fopen(output_file, "r");
            process(encrypteed, decrypt, -shift);//decrypt 
            printf("\n3: file encrypted");
        
        }
        else {
            printf("files could not be opened\n");
        }
        //closing files
    fclose(readfile);
    fclose(writefile);
    fclose(encrypteed);
    fclose(decrypt);
    
}
//function if they choose image
void if_image(int shift, char *input_file, char *output_file){
    //opening the files 
    FILE * plain_image=fopen(input_file, "rb");
    FILE *encrypted_image=fopen(output_file, "wb");
    //reopening encrypted file to read
    FILE *read_image_encrypted=NULL;
    FILE *decrypted_image=fopen("decrypted_image.HEIC", "wb");
    //end
    if (plain_image!=NULL){
            //confirmation it opened successfully
            printf("\n");
            printf("1: image file opened successfully\n");
            //calling a function that does all of the encryption and decryptin
            //encyption first
            image_process(plain_image, encrypted_image, +shift);
            fflush(encrypted_image);
            printf("2: file encrypted\n");
            read_image_encrypted =fopen("encrypted_image.HEIC","rb");
            printf("3: file decrypted");
            //decryption now

            image_process(read_image_encrypted, decrypted_image, -shift);
        }
        else {
            printf("files couln not be opened");
            
        }


   //closing files IMAGES
    fclose(plain_image);
    fclose(encrypted_image);
    fclose(decrypted_image);
    fclose(read_image_encrypted);
    
}

//function if user choose both
void if_both(int shift, char *input_file, char *output_file){
   if_text(shift, input_file, output_file);
   if_image(shift, input_file, output_file);
//end
    
}

int password_to_shift(char *password){
    int total=0;
    int i;
    for(i=0; password[i]!= '\0'; i++){

        total+= password[i];
    
    }

    return total;
    
}





//                              OPENING THE MAIN FILE
int main(int argc, char *argv[]){
    // leting the user use it from the terminal

    if (argc<5){//if the user doesnt pass anything
        printf("./encrypt[keyword][Text/image] [input file] [output file]");
        return 1;
    }
    char *intput_file=argv[3];
    char *output_file=argv[4];

    int shift= password_to_shift(argv[1]);
    printf("key shift: ");
    printf("%d", shift);

    //                  creating the if statements
    //for text
    if (strcmp(argv[2], "text")==0){
        if_text(shift, intput_file, output_file);
    }

    else if (strcmp(argv[2], "image")==0){
        if_image(shift,intput_file, output_file);
    }
    
    else if (strcmp(argv[2], "both")==0){
        if_both(shift, intput_file, output_file);
    }

    return 0;
}