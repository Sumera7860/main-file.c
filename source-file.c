#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
#include<assert.h>
#define INITIAL 0
#define SIZE 30
struct inventory
{
        int product_id;
        char product_name[SIZE];
        char description[SIZE];
        int quantity;
};
struct sales
{
        int transaction_id;
        int quantity;
        int product_id;
};
int product_verification(int product_id,int quantity)
{
        char product[10];
        sprintf(product,"%d",product_id);
        if((strlen(product)>4 || strlen(product)<4) || (quantity<0))
        {
                printf("\nPlease Enter The Details In Correct Format\n");
                return 0;
        }
        else
        {
                return 1;
        }
}


int verification(char *id,int pass)
{char log_id[10];
        int log_pass=0;
        printf("Enter id : ");
        scanf("%s",log_id);
        printf("Enter password : ");
        scanf("%d",&log_pass);
        int cmp=strcmp(id,log_id);

        if ((cmp==0) && log_pass==pass)
        {
                printf("\nyou have successfully logged in\n");
                return 1;
        }
        else
        {
                printf("\nplease enter correct login id and password\n");
                return 0;
        }
}


void display_inventory()
{
        FILE *filepointer = NULL;
        char file_content;
        filepointer = fopen("inventorylog.csv","r");
        if(filepointer == NULL)
        {
                printf("\nFile Cannot Be Opened\n");
        }
        else
        {
                do{
                        file_content = fgetc(filepointer);
                        printf("%c",file_content);
                }
                while(file_content!=EOF);
         while(file_content!=EOF);
        }
}
void create_inventory()
{
        char ch='y';
        FILE *filepointer = NULL;
        struct inventory log;
        int var=INITIAL;
        filepointer = fopen("inventorylog.csv","a");
        if(filepointer == NULL)
        {
                printf("\nFile Cannot Be Opened\n");
        }
        else
        {
                while(ch == 'y')
                {
                        printf("\nEnter The Details\n");
                        printf(" Product id : ");
                        scanf("%d",&log.product_id);
                        printf(" Product name : ");
                        scanf("%s",log.product_name);
                        printf(" Description : ");
                        scanf(" %[^\n]s",log.description);
                        printf(" Quantity : ");
                        scanf(" %d",&log.quantity);
                        var=product_verification(log.product_id,log.quantity);
                        if(var==1)
                        {
                        fprintf(filepointer,"%d,\t%s,\t%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
                        }


                        printf("\nDo You Want To Add More Products[y/n] : ");
                        scanf(" %c",&ch);
                }
        }
fclose(filepointer);

}
void create_sales()
{
        char ch='y';
        FILE *filepointer = NULL;
        int var = INITIAL;
        struct sales slog;
        time_t ltime = time(NULL);
        struct tm *tm = localtime(&ltime);

        filepointer = fopen("saleslog.csv","a");
        if(filepointer == NULL)
        {
                printf("\nFile Cannot Be Opened\n");
        }
        else
        {
                while(ch == 'y')
                {
                        printf("\nEnter The Details\n");
                        printf(" Transaction id : ");
                        scanf("%d",&slog.transaction_id);
                        printf(" Product id : ");
                        scanf(" %d",&slog.product_id);
                        printf(" Quantity : ");
                        scanf(" %d",&slog.quantity);
                        var=product_verification(slog.transaction_id,slog.quantity);
                        if(var==1){
                        fprintf(filepointer,"%d,\t%d,\t%d,\t%s\n",slog.transaction_id,slog.product_id,slog.quantity,asctime(tm));
                        }
                        printf("\nDo You Want To Add More Products[y/n] : ");
                        scanf(" %c",&ch);
                }
        }
        fclose(filepointer);
}

void display_sales()
{
        FILE *filepointer = NULL;
        char file_content;
        filepointer = fopen("saleslog.csv","r");

        if(filepointer == NULL)
        {
                printf("\nFile Cannot Be Opened\n");
        }
        else
        {
                while(!feof(filepointer))
                {
                        file_content = getc(filepointer);
                        printf("%c",file_content);
                }
                fclose(filepointer);
        }
}

void delete_inventory()
{
        FILE *filepointer1= NULL;
        FILE *filepointer2 = NULL;
        struct inventory log;
        int product_id = INITIAL;
        char *token;
        char buffer[1024];
        char ch ='y';
        int flag=INITIAL;
        int var = INITIAL;

        while(ch == 'y')
        {
                printf("\nEnter The Product Id To Delete : ");
 scanf("%d",&product_id);
                var=product_verification(product_id,1);
                if(var == 1)
                {

                filepointer1 = fopen("inventorylog.csv","r");
                if(filepointer1 == NULL)
                {
                        printf("\nFile Cannot Be Opened\n");
                        exit(0);
                }
                filepointer2 = fopen("temperorylog.csv","a");
                if(filepointer2 == NULL)
                {
                        printf("File Cannot Be Opened\n");
                        exit(0);
                }
                while(fgets(buffer,1024,filepointer1)!=NULL)
                {
                        token = strtok(buffer,",");
                        while(token != NULL)
                        {
                                if(atoi(token) == product_id)
                                {
                                        flag=1;
                                        log.product_id = atoi(token);
                                        token=strtok(NULL,",");
                                        strcpy(log.product_name,token);
                                        token = strtok(NULL,",");
                                        strcpy(log.description, token);
                                        token = strtok(NULL,"\n");
                                        log.quantity=atoi(token);
                                        token = strtok(NULL,",");


                                }
                                else
 {

                                        log.product_id = atoi(token);
                                        token=strtok(NULL,",");
                                        strcpy(log.product_name,token);
                                        token = strtok(NULL,",");
                                        strcpy(log.description, token);
                                        token = strtok(NULL,"\n");
                                        log.quantity=atoi(token);
                                        token = strtok(NULL,",");
                                        fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
                                }
                        }
                }



                if(flag==0)
                {
                printf("Sorry Product Id Is Not Found\n");
                }
                flag=0;
                printf("Do You Want To Delete More Products[y/n] : ");
                scanf(" %c",&ch);


                fclose(filepointer1);
                fclose(filepointer2);
                remove("inventorylog.csv");
                rename("temperorylog.csv","inventorylog.csv");
                }


        }
}
void update_inventory()
{


        FILE *filepointer1= NULL;
        FILE *filepointer2 = NULL;
        struct inventory log;
        struct inventory newlog;
        int product_id = INITIAL;
        char *token;
        char buffer[1024];
        char ch ='y';
        int flag=0;
        int var =INITIAL;
        token = strtok(buffer,",");

        while(ch == 'y')
        {
                printf("\nEnter The Product Id To Update : ");
                scanf("%d",&product_id);
                var=product_verification(product_id,1);
                if(var==1)
                {
                filepointer1 = fopen("inventorylog.csv","r");
                if(filepointer1 == NULL)
                {
                        printf("File Cannot Be Opened\n");
                        exit(0);
                }
                filepointer2 = fopen("temperorylog.csv","a");
                if(filepointer2 == NULL)
                {
                        printf("File Cannot Be Opened\n");
                        exit(0);
                }
                while(fgets(buffer,1024,filepointer1)!=NULL)
                {
                        token = strtok(buffer,",");
                        while(token != NULL)
                        {
                                if(atoi(token) == product_id)
 {


                                        flag=1;
                                        printf("Enter The Details\n");
                                        printf("product name : ");
                                        scanf("%s",newlog.product_name);
                                        printf("description : ");
                                        scanf(" %[^\n]s",newlog.description);
                                        printf("quantity : ");
                                        scanf(" %d",&newlog.quantity);

                                        newlog.product_id = atoi(token);
                                        token=strtok(NULL,",");
                                        strcpy(log.product_name,newlog.product_name);
                                        token = strtok(NULL,",");
                                        strcpy(log.description,newlog.description);
                                        token = strtok(NULL,"\n");
                                        log.quantity=newlog.quantity;
                                        token = strtok(NULL,",");
                                        fprintf(filepointer2,"%d,\t%s,\t%s,\t%d\n",newlog.product_id,log.product_name,log.description,log.quantity);


                                }
                                else
                                {

                                        log.product_id = atoi(token);
                                        token=strtok(NULL,",");
                                        strcpy(log.product_name,token);
                                        token = strtok(NULL,",");
                                        strcpy(log.description, token);
                                        token = strtok(NULL,"\n");
                                        log.quantity=atoi(token);
                                        token = strtok(NULL,",");
                                        fprintf(filepointer2,"%d,%s,%s,\t%d\n",log.product_id,log.product_name,log.description,log.quantity);
                                }         
                        }


                }
                if(flag==0)
                {
                printf("Sorry Product Id Is Not Found\n");
                }
                flag=0;
                printf("Do You Want To Update More Products[y/n] : ");
                scanf(" %c",&ch);


                fclose(filepointer1);
                fclose(filepointer2);
                remove("inventorylog.csv");
                rename("temperorylog.csv","inventorylog.csv");
        }

        }



}


