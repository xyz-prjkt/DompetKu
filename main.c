#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>

int main_menu;
int income_value;
char income_category[99], income_category_menu[99];
bool income_category_exist = false;
FILE *db_read, *db_write, *db_ammend;

int main(){

    menu:
    system("cls");
    printf("=============================================\n");
    printf(" DompetKu\n");
    printf("=============================================\n");
    printf(" 1. Tambahkan Rekening\n 2. Cek Rekening");
    printf("\nPilih menu : ");
    scanf("%i", &main_menu);

    switch(main_menu){
    case 1:

        system("cls");
        printf("=============================================\n");
        printf(" Menambah Rekening\n");
        printf("=============================================\n");

        db_read = fopen("main.db", "r");
        db_ammend = fopen("main.db", "a");
        income_category_exist = false;

        printf("\nInputkan Jenis Kategori Wallet : "); fflush(stdin); scanf("%[^\n]" , income_category_menu);

        while(fscanf(db_read, "%[^|]|%d,", income_category, &income_value) != EOF){
            if(strcmp(income_category, income_category_menu) == 0){
                income_category_exist = true;
            }
        }

        if(income_category_exist == false){
            printf("Tambahkan Jumlah Harga Awal: ");
            scanf("%d", &income_value);
            strcpy(income_category, income_category_menu);
            fprintf(db_ammend,"%s|%d,", income_category, income_value);
        } else {
            printf("Rekening sudah ada, mohon untuk mengupdate rekening");
        }

        fclose(db_read); fclose(db_ammend);
        getch();
        goto menu;
        break;

    case 2:

        system("cls");
        printf("=============================================\n");
        printf(" Informasi Rekening\n");
        printf("=============================================\n");

        db_read = fopen("main.db", "r");
        income_category_exist = false;
        int info_header = 0;
        int info_total = 0;

        while(fscanf(db_read, "%[^|]|%d,", income_category, &income_value) != EOF){
            if(info_header == 0){
                printf("Rekening\t| Nilai\n");
                info_header++;
            }
            printf("%s\t\t| Rp %d\n", income_category, income_value);
            info_total = info_total + income_value;
            income_category_exist = true;
        }
        if(income_category_exist == true){
            printf("=============================================\n");
            printf("Total Jumlah\t| Rp %d\n", info_total);
        } else {
            printf("Tidak ada rekening yang ditambahkan");
        }

        fclose(db_read);
        getch();
        goto menu;
        break;

    default:
        break;
    }

}