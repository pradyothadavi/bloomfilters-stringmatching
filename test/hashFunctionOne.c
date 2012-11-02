#include<stdio.h>
#include<string.h>

#define DEBUG 1

unsigned long hash(unsigned char *cPtr_string,unsigned long ul_hashValue[10],int flag){
	
    int i = 0;
    int j = 0;
    int c = 0;
    int str_length = 0;

    unsigned long final_sum = 0;

    str_length = strlen(cPtr_string);
#if DEBUG    
    printf("String length: %d \n",str_length);
    printf("String is : ");
    i = 0;    
    while(*(cPtr_string+i) != '\0'){
         printf("%c",*(cPtr_string+i));
         i++;
    }
    printf("\n");
#endif	
    if(flag == 0){
#if DEBUG
         printf("----- Step 01 ----- \n");
#endif
	 for(i=0; i<=str_length; i++){
              ul_hashValue[i]=1;
#if DEBUG
              printf("ul_hashValue[%d] : %ld \n",i,ul_hashValue[i]);
#endif
	}
#if DEBUG
        printf("\n");   
        printf("----- Step 02 ----- \n");
#endif
	for(i=0;i<=str_length-1;i++){
	      ul_hashValue[i]= ul_hashValue[i] * 33;
#if DEBUG
              printf("ul_hashValue[%d] : %ld \n",i,ul_hashValue[i]);
#endif
	}
#if DEBUG
        printf("\n");
        printf("----- Step 03 ----- \n");
#endif
	for(i=0;i<=str_length-2;i++){
	      for(j=0;j<=i;j++){
	           ul_hashValue[j] = (ul_hashValue[j]<<5) + ul_hashValue[j];
	      }
#if DEBUG
              for(j=0;j<=i;j++){
	           printf("ul_hashValue[%d]: %ld \n",j,ul_hashValue[j]);
	      }
#endif                
	}
#if DEBUG
        printf("\n");
        printf("ul_hashValue[0] before : %ld \n",ul_hashValue[0]);
#endif
	ul_hashValue[0] = ul_hashValue[0] * 5381;
#if DEBUG
        printf("ul_hashValue[0] : %ld \n",ul_hashValue[0]);
        printf("\n");
        printf("----- Step 04 ----- \n");
#endif
	for(i=1;i<=str_length;i++){
              c = *(cPtr_string+i-1);
#if DEBUG
              printf("Chracter is %c \n",c);
              printf("ASCII value is %d \n",c);
#endif
	      ul_hashValue[i] = ul_hashValue[i] * c;
#if DEBUG
              printf("ul_hashValue[%d]:%ld \n",i,ul_hashValue[i]);
#endif
	}

    }
    printf("\n");   
    if(flag == 1){
#if DEBUG
         printf("Character: %c \n",*(cPtr_string+(str_length-1)));
#endif
	 ul_hashValue[str_length] = ul_hashValue[str_length] * *(cPtr_string+(str_length-1));
#if DEBUG
         printf("ul_hashValue[%d]:%ld\n",str_length,ul_hashValue[str_length]);
#endif
    }  
       
    for(i=0;i<=str_length;i++){
	 final_sum = final_sum + ul_hashValue[i];
    }
#if DEBUG
    printf("\n");
    printf("Final Sum: %ld \n",final_sum);
    printf("\n");
    printf("ul_hashValue[0] : %ld \n",ul_hashValue[0]);
#endif
    for(i=1;i<=str_length-1;i++){
         ul_hashValue[i] = ul_hashValue[i+1] *33;
#if DEBUG
         printf("ul_hashValue[%d] : %ld\n",i,ul_hashValue[i]);
#endif
    } 
    ul_hashValue[str_length] = 1;
#if DEBUG        
    printf("ul_hashValue[%d]:%ld\n",str_length,ul_hashValue[str_length]);
#endif        
    return final_sum;
}

int main(int argc,char *argv[]){

    char cArr_string[20];
    char *cPtr_string = NULL;
    unsigned long ul_retVal;
    unsigned long ul_hashIndex; 
    unsigned long ul_hashValue[10];

    printf("Enter a string : \n");
    cPtr_string = fgets(cArr_string,20,stdin);
    if( *(cPtr_string + strlen(cPtr_string)-1) == '\n'){
         *(cPtr_string + strlen(cPtr_string)-1) = '\0';
    }
    ul_retVal = hash(cPtr_string,ul_hashValue,0);
    ul_hashIndex = ul_retVal%491;
    printf("Hash Index : %ld \n",ul_hashIndex);
    printf("Enter a string : \n");
    cPtr_string = fgets(cArr_string,20,stdin);
    if( *(cPtr_string + strlen(cPtr_string)-1) == '\n'){
         *(cPtr_string + strlen(cPtr_string)-1) = '\0';
    }
    ul_retVal = hash(cPtr_string,ul_hashValue,1);
    ul_hashIndex = ul_retVal%491;
    printf("Hash Index : %ld \n",ul_hashIndex); 

    return 0;
}
