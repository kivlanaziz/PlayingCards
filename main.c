/* PROGRAM PERMAINAN KARTU ROYAL REMI
 * PROGRAM UNTUK MEMENUHI SALAH SATU TUGAS BESAR MATA KULIAH DDP PRAKTIK 
 * KELOMPOK 2 KARTU REMI - KELAS 1A/D3-Teknik Informatika
 * ANGGOTA KELOMPOK : 
 *.===================================================
 * =		Nama : KIVLAN AZIZ AL-FALAAH			 =
 * =		NIM  : 161511016						 =
 * =		Kelas: 1A/D3-Teknik Informatika			 =
 * =												 =
 * =		Nama : FADHIL ....						 =
 * =		NIM  : 151511012						 =
 * =		Kelas: 1A/D3-Teknik Informatika			 =
 * =												 =
 * =		Nama : AGIT PRASETYA					 =
 * =		NIM  : 151511005						 =
 * =		Kelas: 1A/D3-Teknik Informatika			 =
 * =												 =
 *==================================================== 
 * Compiler : TDM-GCC 4.9.2 64 Bit Release ( Dev-C++ 5.11)
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#ifndef boolean_h
#define boolean_h
#define true 1
#define false 0
#define boolean unsigned char
#endif

#define panjang 256

// ASCII Code untuk  3=Hati  4=Wajik 5=keriting 6=sekop

typedef struct
	{
		int nilai_kartu; //SubVar untuk Menampung Nilai Angka dari Kartu
		int jenis_kartu; //SubVar untuk Menampung Jenis Kartu
		boolean status_GL;
		boolean cardstat;
		
	} kartu; //Variabel Komposit untuk Menyimpan Nilai Angka kartu dan Jenis Kartu( ASCII Code untuk  3=Hati 4=Wajik 5=keriting 6=sekop)
	
//typedef struct 
//	{
//		int nilai;
//		int jenis;
//		int letter;	
//		int array;
//	} temp_kartu;

typedef struct 
{
		char Nama[256];
		int Score;
} HighScore;

kartu Dek[52]; // Variabel Array 1 Dimensi Bersifat Global Untuk Menampung Kartu Pada Dek Sudah Diisi Secara Random
kartu Player[11]; //Variabel Array 1 Dimensi Bersifat Global Untuk Menampung Kartu Player
kartu Player_Comp[11]; // Variabel Array 1 Dimensi Bersifat Global Untuk Menampung Kartu Computer
kartu Tempat_Buangan[6]; // Variabel Array 1 Dimensi Bersifat Global Untuk Menampung Kartu Buangan
kartu black[52];

int Posisi_Dek;		//Variabel Bersifat Global Untuk Mengetahui Posisi Dek yang masih terisi
int Score_Comp=0;  //Variabel Bersifat Global Untuk Menampung Score Computer
int Score_Player=0; // Variabel Bersifat  Global untuk Menampung Score Player
int Total_KartuMati_Player=0; // Variabel Bersifat  Global untuk Menampung Total Nilai Kartu Mati Player
int Total_KartuMati_Comp=0; // Variabel Bersifat  Global untuk Menampung Total Nilai Karu Mati Computer
int  CountingGrup[14];
int  CountingGrup_Comp[14];
int n;
char NamaPemain[256];
int buangan[6];
int k=0,z=1;
int PlayerScore=0;
int CompScore=0;

int Temp_dek [52] =	{ 	13,14,15,16,       //Sebagai Penyimpanan Dek Sebelum Dirandom/Diacak
						23,24,25,26,	   // Variabel Sementara untuk Menyimpan Nilai Dek Sebelum Dirandom
			  			33,34,35,36,
			  			43,44,45,46,
			  			53,54,55,56,
			  			63,64,65,66,
			  			73,74,75,76,
			  			83,84,85,86,
			  			93,94,95,96,
			  			103,104,105,106,
			  			113,114,115,116,
			  			123,124,125,126,
			  			133,134,135,136,
						};
						
						
void gotoxy(short x, short y) //Sebagai Koordinat 
{
	
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(unsigned short color)
{
	
HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsoleOutput,color);

}



void MaximizeOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); // This gets the value Windows uses to identify your output window 
    ShowWindow(consoleWindow, SW_MAXIMIZE); // this mimics clicking on its' maximize button
}
 

void Tukar (int *a, int *b) // Modul Prosedur untuk menukarkan isi Variabel
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void Random_Dek() // Untuk Merandom atau Meng-acak Isi Array Dari Variabel Temp_Dek ( Variabel Penampung Sementara Untuk Dek)
{
	int i, j;
	
	int panjang_array = sizeof(Temp_dek) / sizeof(Temp_dek[0]); // Untuk Mengitung Panjang Array
	
	srand ( time(NULL) );
	
	for (i = panjang_array-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
         j = rand() % (i+1);
 
        // Tukar Dek_Rand[i] with the element at random index
        Tukar(&Temp_dek[i], &Temp_dek[j]);
           
    }

}


void Isi_Dek() // Mengisi Variabel Dek dengan Nilai dari Temp_Dek yang sudah Dirandom
{	
	int i;
	int panjang_array = sizeof(Temp_dek) / sizeof(Temp_dek[0]); // Untuk Mengitung Panjang Array
	
	for (i=0; i < panjang_array; i++) //Mengisi Seluruh Array Dek dari Nilai Temp_dek yang sudah diRandom
	{
		Dek[i].nilai_kartu = Temp_dek[i] / 10;
		Dek[i].jenis_kartu = Temp_dek[i] % 10;	
		
	}			
}

void Bagi_Kartu ()  //membagi kartu kepada setiap player
{	
	int i;	
	for (i=0; i < 10; i++)  //Membagi Kartu Kepada Player 
	{
		/*Player[i].nilai_kartu = Dek[i].nilai_kartu;
		Player[i].jenis_kartu = Dek[i].jenis_kartu;
		Dek[i].nilai_kartu = 0;
		Dek[i].jenis_kartu = 0;*/
		Player[i]=Dek[i];
		Dek[i].nilai_kartu = 0;
		Dek[i].jenis_kartu = 0;	
	}
	
		for (i=10; i < 20; i++) //Membagi Kartu Kepada Computer
		{
		/*	Player_Comp[i-10].nilai_kartu = Dek[i].nilai_kartu;
			Player_Comp[i-10].jenis_kartu = Dek[i].jenis_kartu;
			Dek[i].nilai_kartu = 0;
			Dek[i].jenis_kartu = 0;*/	
			Player_Comp[i-10]=Dek[i];
			Dek[i].nilai_kartu = 0;
			Dek[i].jenis_kartu = 0;	
		}
		
		/*Tempat_Buangan[0].nilai_kartu = Dek[i].nilai_kartu; //Mengisi Tempat Buangan
		Tempat_Buangan[0].jenis_kartu = Dek[i].jenis_kartu;
		Dek[i].nilai_kartu = 0;
		Dek[i].jenis_kartu = 0;	*/
		Tempat_Buangan[0]=Dek[i];
		Dek[i].nilai_kartu = 0;
		Dek[i].jenis_kartu = 0;
		i+=1; //posisi kartu yang masih tersisa di dek
		Posisi_Dek = i;		//Untuk Mengetahui Posisi Kartu yang tersisa di Dek 
}

void Inisialisasi_Status ()
{
	int i;
	for(i=0; i < 11 ; i++)
	{
		Player[i].status_GL=false;
		Player_Comp[i].status_GL=false;
			
	}
}


void IntroGame()
{
	int i;
	
	system("COLOR 4F");

	gotoxy(25,4);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}
	gotoxy(78,5);
	printf("WELCOME");
	
	gotoxy(25,6);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
gotoxy(40,10);printf("	%c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c            %c%c%c%c%c%c%c   %c%c%c%c%c\n", 3,3,3,3,3,3,3,3   ,4,4,4,4,4,4,4,4,4,4,4  ,6,6,6,6,6,6,6,6,6,6,6,6,6,6 ,4,4,4,4,4);
gotoxy(40,11);printf("	%c%c%c%c%c%c%c%c%c      %c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c          %c%c%c%c%c%c%c%c    %c%c%c \n",3,3,3,3,3,3,3,3,3 ,4,4,4,4,4,4,4,4,4,4,4  ,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,12);printf("	%c%c%c    %c%c%c     %c%c%c             %c%c%c   %c%c%c        %c%c%c   %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,13);printf("	%c%c%c    %c%c%c     %c%c%c             %c%c%c    %c%c%c      %c%c%c    %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,14);printf("	%c%c%c    %c%c%c     %c%c%c%c%c%c%c%c%c%c%c     %c%c%c     %c%c%c    %c%c%c     %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,15);printf("	%c%c%c%c%c%c%c%c%c      %c%c%c%c%c%c%c%c%c%c%c     %c%c%c      %c%c%c%c%c%c%c%c      %c%c%c    %c%c%c \n",3,3,3,3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6,6,6,6,6,6,6,6,6 ,4,4,4,4) ;
gotoxy(40,16);printf("	%c%c%c%c%c%c%c%c       %c%c%c             %c%c%c        %c%c%c%c        %c%c%c    %c%c%c \n", 3,3,3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,17);printf("	%c%c%c    %c%c%c     %c%c%c             %c%c%c         %c%c         %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6 ,4,4,4,4);
gotoxy(40,18);printf("	%c%c%c     %c%c%c    %c%c%c%c%c%c%c%c%c%c%c     %c%c%c                    %c%c%c    %c%c%c \n",3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6 ,4,4,4,4);
gotoxy(40,19);printf("	%c%c%c      %c%c%c   %c%c%c%c%c%c%c%c%c%c%c     %c%c%c                    %c%c%c   %c%c%c%c%c\n\n\n",3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6 ,4,4,4,4,4);

gotoxy(28,24);printf("    **********        **     **     ***               ***    ***               ***      **          ** ");   
gotoxy(28,25);printf("    ***********       **     **     ** **           ** **    ** **           ** **       **        **  ");  
gotoxy(28,26);printf("    **       **       **     **     **  **         **  **    **  **         **  **        **      **   ");   
gotoxy(28,27);printf("    **       **       **     **     **   **       **   **    **   **       **   **         **    **    ");    
gotoxy(28,28);printf("    **      **        **     **     **    **     **    **    **    **     **    **          **  **     ");
gotoxy(28,29);printf("    *********         **     **     **     **   **     **    **     **   **     **            **       ");
gotoxy(28,30);printf("    ***********       **     **     **      ** **      **    **      ** **      **            **       "); 
gotoxy(28,31);printf("    **        **      **     **     **       ***       **    **       ***       **            **       ");
gotoxy(28,32);printf("    **         **     **     **     **                 **    **                 **            **       ");
gotoxy(28,33);printf("    **          **     *******      **                 **    **                 **            **       ");

gotoxy(25,36);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}
	gotoxy(71,37);
	printf("%c%c SELAMAT BERMAIN %c%c",3,4,5,6);
	
	gotoxy(25,38);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
printf("\n");	
}


void Print_Computer ()
{	

	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	
	absis=8;
	
	gotoxy(8,5);
	printf("= Kartu Komputer =");
	gotoxy(78, 5);
	printf ("Total Nilai Kartu Mati = %d", Total_KartuMati_Comp);
	gotoxy(110,5);
	printf("Skor = %d",CompScore);
	
for (Loop_Write=0; Loop_Write < 11; Loop_Write++)		
{
 
 if (Player_Comp[Loop_Write].nilai_kartu !=0 )
 {
 
 	ordinat=8;
	for (n=1; n<=7; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=7; j++)
		{	
			
			if (n==1 || n==7 || j==1|| j==7)
			{	
				if (Player_Comp[Loop_Write].nilai_kartu==10 )
				{	
					if (n==3 && j==1 || n==3 && j==7)
					{
						printf(" ");
						
					}
					else
					{
						printf ("=");
					}
				}
				else
				{
					printf ("=");	
				}			
			}
			else
			{	
				if (n==3 && j==3 )
				{	
					if (Player_Comp[Loop_Write].nilai_kartu==1 || Player_Comp[Loop_Write].nilai_kartu > 10)
					{
						switch (Player_Comp[Loop_Write].nilai_kartu)
						{
							case 1 : printf ("A");
								break;
							case 11 : printf ("J");
								break;
							case 12 : printf ("Q");
								break;
							case 13 : printf ("K");
								break;			
						}
					}
					else
					{
						printf("%d", Player_Comp[Loop_Write].nilai_kartu);
					}	
				}
				else if (n==5 && j==5)
				{	
					if ( Player_Comp[Loop_Write].jenis_kartu==3 ||  Player_Comp[Loop_Write].jenis_kartu==4)
					{
							SetColor(4);
							printf("%c", Player_Comp[Loop_Write].jenis_kartu);
					}
					else
					{
						printf("%c", Player_Comp[Loop_Write].jenis_kartu);
					}
					
					SetColor(7);
				}
				else
				{	
					printf (" ");	
				}	
			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
	
gotoxy(absis, ordinat-8);
printf ("Kartu %d", Loop_Write+1);
 }
absis=absis+10;	
}
	
}

void OutGame()
{
	int i;
	
	system("COLOR 4F");

	gotoxy(25,4);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}
	gotoxy(69,5);
	printf("%c %c SAMPAI JUMPA LAGI %c %c",3,4,5,6);
	
	gotoxy(25,6);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
gotoxy(40,10);printf("	%c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c            %c%c%c%c%c%c%c   %c%c%c%c%c\n", 3,3,3,3,3,3,3,3   ,4,4,4,4,4,4,4,4,4,4,4  ,6,6,6,6,6,6,6,6,6,6,6,6,6,6 ,4,4,4,4,4);
gotoxy(40,11);printf("	%c%c%c%c%c%c%c%c%c      %c%c%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c          %c%c%c%c%c%c%c%c    %c%c%c \n",3,3,3,3,3,3,3,3,3 ,4,4,4,4,4,4,4,4,4,4,4  ,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,12);printf("	%c%c%c    %c%c%c     %c%c%c             %c%c%c   %c%c%c        %c%c%c   %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,13);printf("	%c%c%c    %c%c%c     %c%c%c             %c%c%c    %c%c%c      %c%c%c    %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,14);printf("	%c%c%c    %c%c%c     %c%c%c%c%c%c%c%c%c%c%c     %c%c%c     %c%c%c    %c%c%c     %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,15);printf("	%c%c%c%c%c%c%c%c%c      %c%c%c%c%c%c%c%c%c%c%c     %c%c%c      %c%c%c%c%c%c%c%c      %c%c%c    %c%c%c \n",3,3,3,3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6,6,6,6,6,6,6,6,6 ,4,4,4,4) ;
gotoxy(40,16);printf("	%c%c%c%c%c%c%c%c       %c%c%c             %c%c%c        %c%c%c%c        %c%c%c    %c%c%c \n", 3,3,3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6,6,6 ,4,4,4,4);
gotoxy(40,17);printf("	%c%c%c    %c%c%c     %c%c%c             %c%c%c         %c%c         %c%c%c    %c%c%c \n", 3,3,3,3,3,3  ,3,3,3 ,6,6,6, 6,6,6,6,6 ,4,4,4,4);
gotoxy(40,18);printf("	%c%c%c     %c%c%c    %c%c%c%c%c%c%c%c%c%c%c     %c%c%c                    %c%c%c    %c%c%c \n",3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6 ,4,4,4,4);
gotoxy(40,19);printf("	%c%c%c      %c%c%c   %c%c%c%c%c%c%c%c%c%c%c     %c%c%c                    %c%c%c   %c%c%c%c%c\n\n\n",3,3,3,3,3,3  ,4,4,4,4,4,4,4,4,4,4,4 ,6,6,6, 6,6,6 ,4,4,4,4,4);

gotoxy(28,24);printf("    **********        **     **     ***               ***    ***               ***      **          ** ");   
gotoxy(28,25);printf("    ***********       **     **     ** **           ** **    ** **           ** **       **        **  ");  
gotoxy(28,26);printf("    **       **       **     **     **  **         **  **    **  **         **  **        **      **   ");   
gotoxy(28,27);printf("    **       **       **     **     **   **       **   **    **   **       **   **         **    **    ");    
gotoxy(28,28);printf("    **      **        **     **     **    **     **    **    **    **     **    **          **  **     ");    
gotoxy(28,29);printf("    *********         **     **     **     **   **     **    **     **   **     **            **       ");
gotoxy(28,30);printf("    ***********       **     **     **      ** **      **    **      ** **      **            **       "); 
gotoxy(28,31);printf("    **        **      **     **     **       ***       **    **       ***       **            **       ");
gotoxy(28,32);printf("    **         **     **     **     **                 **    **                 **            **       ");
gotoxy(28,33);printf("    **          **     *******      **                 **    **                 **            **       ");

gotoxy(25,36);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}
	gotoxy(70,37);
	printf("%c%c SELAMAT TINGGAL %c%c",3,4,5,6);
	
	gotoxy(25,38);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
printf("\n");	
}


void Print_Player ()
{
	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	

	absis=8;
	
	gotoxy(8, 28);
	printf ("= Kartu %s =", NamaPemain);
	
	gotoxy(78, 28);
	printf ("Total Nilai Kartu Mati = %d", Total_KartuMati_Player);
	gotoxy(108,28);
	printf("Skor = %d",PlayerScore);
for (Loop_Write=0; Loop_Write < 11; Loop_Write++)		
{
	ordinat=30;

 if (Player[Loop_Write].nilai_kartu !=0 )
 {

	for (n=1; n<=7; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=7; j++)
		{	
			
			if (n==1 || n==7 || j==1|| j==7)
			{	
				if (Player[Loop_Write].nilai_kartu==10 )
				{	
					if (n==3 && j==1 || n==3 && j==7)
					{
						printf(" ");
						
					}
					else
					{
						printf ("=");
					}
				}
				else
				{
					printf ("=");	
				}				
			}
			
			else
			{	
				if (n==3 && j==3 )
				{	
					if (Player[Loop_Write].nilai_kartu==1 || Player[Loop_Write].nilai_kartu > 10)
					{
						switch (Player[Loop_Write].nilai_kartu)
						{
							case 1 : printf ("A");
								break;
							case 11 : printf ("J");
								break;
							case 12 : printf ("Q");
								break;
							case 13 : printf ("K");
								break;			
						}
					}
					else
					{
						printf("%d", Player[Loop_Write].nilai_kartu);
					}	
				}
				else if (n==5 && j==5)
				{	
					if ( Player[Loop_Write].jenis_kartu==3 ||  Player[Loop_Write].jenis_kartu==4)
					{
							SetColor(4);
							printf("%c", Player[Loop_Write].jenis_kartu);
					}
					else
					{
						printf("%c", Player[Loop_Write].jenis_kartu);
					}
					
					SetColor(7);	
				}
				else
				{	
					printf (" ");	
				}	
			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	

 }
gotoxy(absis, ordinat);
printf ("Kartu %d", Loop_Write+1);

}
absis=absis+10;	
}
	
}

void Print_ComputerHidden()
{
	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	
	absis=8;
	
	gotoxy(8,5);
	printf("= Kartu Komputer =");
	gotoxy(78, 5);
	printf ("Total Nilai Kartu Mati = XXXX");
	gotoxy(108,5);
	printf("Skor = XXX");
	
for (Loop_Write=0; Loop_Write < 11; Loop_Write++)		
{
 
 if (Player_Comp[Loop_Write].nilai_kartu !=0 )
 {
 
 	ordinat=8;
	for (n=1; n<=7; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=7; j++)
		{	
				
				if (n==1 || n==7 || j==1|| j==7)
				{	
				printf ("=");
				}
					else
					{	
					
						if (n==5 && j==5||n==6 && j==6||n==2 && j==2||n==3 && j==3||n==4 && j==4)
						{	
							printf("x");
						}
						else if (n==6 && j==2||n==5 && j==3||n==4 && j==4||n==3 && j==5||n==2 && j==6)
						{
							printf ("x");
						}	
						else
						{
							printf(" ");	
						}	
					}	
				
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
	
gotoxy(absis, ordinat-8);
printf ("Kartu %d", Loop_Write+1);
 }
absis=absis+10;	
}
	
}
void AmbilKartu()
{	
	int i;
	
	gotoxy(8,39);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
	
	gotoxy(55,40);
	printf("AMBIL KARTU");
	
	gotoxy(8,41);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
	gotoxy(49,43);
	printf("Silahkan Ambil Kartu Dari :\n");
	gotoxy(49,44);
	printf("1. Dari DEK\n");
	gotoxy(49,45);
	printf("2. Dari Buangan\n");
	gotoxy(49,46);
	printf("Ambil Kartu Dari : ");
}

int Pilih()
{
	int pilihan;
	scanf("%d", &pilihan);
	return pilihan;
}

int cursor(int option,int x,int y)												//modul menggerakan cursor ke atas / ke bawah
{
	int select=1;
	int input;
	
	gotoxy(x,y);printf("%c",26);
	do
	{
		input=getch();															//mengisi nilai input
		if(input==80)															//input key bergerak ke bawah
		{
			gotoxy(x,y);printf(" ");
			y++;select++;
			if(select>option)
			{
				y=y-option;
				select=1;
			}
			gotoxy(x,y);printf("%c",26);
		}
		if(input==72)															//input key bergerak ke atas 
		{
			gotoxy(x,y);printf(" ");
			y--;select--;
			if(select<1)
			{
				y=y+option;
				select=option;
			}
			gotoxy(x,y);printf("%c",26);			
		}															
	}
	while(input!=13);															//berakhir saat input berisi enter
	return select;																//modul memberikan output nilai select
}

int menu_game()																	//modul menampilkan menu permainan
{
	system("COLOR 4F");
	int menu;
	int i;
	//setcolor(14);
		
	gotoxy(35,10);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
	gotoxy(75,11);
	printf("MENU REMI RUMMY");
	
	gotoxy(35,12);	
	for (i=0; i<100; i++)
	{
		printf("อ");	
	}
	
	gotoxy(65,16);printf("ษอออออออออออออออออออออออออออออออออป\n");
	gotoxy(65,17);printf("บ            MENU GAME            บ\n");
	gotoxy(65,18);printf("บ                                 บ\n");
	gotoxy(65,19);printf("บ        1 PLAY GAME              บ\n");
	gotoxy(65,20);printf("บ        2 HIGH SCORE             บ\n");
	gotoxy(65,21);printf("บ        3 HELP                   บ\n");
	gotoxy(65,22);printf("บ        4 ABOUT                  บ\n");
	gotoxy(65,23);printf("บ        5 EXIT GAME              บ\n");
	gotoxy(65,24);printf("บ                                 บ\n");
	gotoxy(65,25);printf("บ        CHOOSE THE MENU          บ\n");
	gotoxy(65,26);printf("บ                                 บ\n");
	gotoxy(65,27);printf("ศอออออออออออออออออออออออออออออออออผ\n");
	
	gotoxy(35,33);	
	for (i=0; i<100; i++)
	{
		printf("อ");	
	}


	return cursor(5,70,19);														//memilih menu dengan kursor
	
	
}

void about_us()
{
	FILE *file_aboutus;
	char about[panjang];
	
		system("cls");
		file_aboutus = fopen("about__us.txt", "rt");
				
		while((fgets(about, panjang, file_aboutus)) != NULL)
		printf("%s\r", about);
}

void help()
{
	FILE *file_help;
	char about[panjang];
	
		system("cls");
		file_help = fopen("help.txt", "rt");
				
		while((fgets(about, panjang, file_help)) != NULL)
		printf("%s\r", about);
}

//void Print_Status()
//{
//	gotoxy(8, 39);
//	printf("Urutan Lengkap = %d", Cek_UrutanLengkap());
//	gotoxy(28, 39);
//	printf("Grup Lengkap = %d", Cek_GrupLengkap());
//	gotoxy(48, 39);
//	printf("Urutan Parsial = %d", Cek_UrutanParsial());
//	gotoxy(68, 39);
//	printf("Grup Parsial = %d", Cek_GrupParsial());
//}


void Print_Dek ()
{
	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	
	
	absis=44;
	gotoxy (46, 17);
	printf ("Dek");	
for (Loop_Write=1; Loop_Write <=1; Loop_Write++)		
{
	ordinat=19;
	for (n=1; n<=7; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=7; j++)
		{	
			
			if (n==1 || n==7 || j==1|| j==7)
			{	
				printf ("=");
			}
			else
			{	
				
				if (n==5 && j==5||n==6 && j==6||n==2 && j==2||n==3 && j==3||n==4 && j==4)
				{	
					printf("x");
				}
				else if (n==6 && j==2||n==5 && j==3||n==4 && j==4||n==3 && j==5||n==2 && j==6)
				{
					printf ("x");
				}	
				else
				{
					printf(" ");	
				}	
			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
absis=absis+10;	
}
		gotoxy (41,26);
		printf ("Sisa Kartu Dek : %d", HitungSisa_Dek());
	
}

void Print_Buangan ()             //Kivlan Aziz
{
	int j,n,c=0;
	int Loop_Write;
	int absis;
	int ordinat;
	
	absis=64;
	
	gotoxy (61,17);
	printf("Kartu Buangan");
	
for (Loop_Write=1; Loop_Write <=z; Loop_Write++)		
{
	ordinat=19;
	if (Tempat_Buangan[c].nilai_kartu!=0){
		
	for (n=1; n<=7; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=7; j++)
		{	
			
			if (n==1 || n==7 || j==1|| j==7)
			{	
				if (Tempat_Buangan[c].nilai_kartu==10 )
				{	
					if (n==3 && j==1 || n==3 && j==7)
					{
						printf(" ");
						
					}
					else
					{
						printf ("อ");
					}
				}
				else
				{
					printf ("อ");	
				}			
			}
			else
			{	
				if (n==3 && j==3 )
				{	
					if (Tempat_Buangan[c].nilai_kartu==1 || Tempat_Buangan[c].nilai_kartu > 10)
					{
						switch (Tempat_Buangan[c].nilai_kartu)
						{
							case 1 : printf ("A");
								break;
							case 11 : printf ("J");
								break;
							case 12 : printf ("Q");
								break;
							case 13 : printf ("K");
								break;			
						}
					}
					else
					{
						printf("%d", Tempat_Buangan[c].nilai_kartu);
					}	
				}
				else if (n==5 && j==5)
				{	
					if ( Tempat_Buangan[c].jenis_kartu==3 ||  Tempat_Buangan[c].jenis_kartu==4)
					{
							SetColor(4);
							printf("%c", Tempat_Buangan[c].jenis_kartu);
					}
					else
					{
						printf("%c", Tempat_Buangan[c].jenis_kartu);
					}
					
					SetColor(7);
				}
				else
				{	
					printf (" ");	
				}	
			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
absis=absis+10;
gotoxy(absis-10, ordinat);
printf ("Kartu %d", Loop_Write);
}

c++;
}
	
}

void Print_Judul()
{
	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	
	absis=28;
		
	
for (Loop_Write=1; Loop_Write <=1; Loop_Write++)		
{
	ordinat=0;
	for (n=1; n<=4; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=68; j++)
		{	
			
			if (n==1 || n==4 || j==1|| j==68)
			{	
				if (n==2 || n==3 || j==3 || j==66)
				{
					printf (" ");
				}
				else
				{
					printf ("อ");	
				}
				
			}
			else
			{	
				if (n==3 && j==26)
				{
					printf ("%c %c REMI RUMMY %c %c", 3,5,4,6);
				}
				if (n==2 && j==30)
				{
					printf ("%c K.A.A %c", 3,6);
				}
				else
				{
					printf (" ");
				}		

			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
absis=absis+10;	
}
	
}

void Print_ScoreComputer()
{
	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	
	absis=127;
	
	gotoxy(123,30);
	printf ("= Score Komputer =");
	
	gotoxy(140,32);
	printf (" %c Vs %c", 3,6);
	

for (Loop_Write=1; Loop_Write <=1; Loop_Write++)		
{
	ordinat=32;
	for (n=1; n<=5; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=9; j++)
		{	
			
			if (n==1 || n==5 || j==1|| j==9)
			{	
				if (n==3 && j==9 || n==3 && j==1)
				{
					printf (" ");
				}
				else
				{
					printf ("*");
				}
				
			}
			else
			{	
				if (n==3 && j==5)
				{	
					printf("%d", Score_Comp);
				}
				else
				{	
					printf (" ");	
				}	
			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
absis=absis+10;	
}
}

void Print_ScorePlayer()
{
	int j,k,n;
	int Loop_Write;
	int absis;
	int ordinat;
	
	absis=150;
	
	gotoxy(148,30);
	printf ("= Score %s =", NamaPemain);
	
for (Loop_Write=1; Loop_Write <=1; Loop_Write++)		
{
	ordinat=32;
	for (n=1; n<=5; n++)	
	{	
		gotoxy (absis, ordinat);
		for (j=1; j<=9; j++)
		{	
			
			if (n==1 || n==5 || j==1|| j==9)
			{	
				if (n==3 && j==9 || n==3 && j==1)
				{
					printf (" ");
				}
				else
				{
					printf ("*");
				}
				
			}
			else
			{	
				if (n==3 && j==5)
				{	
					printf("%d", Score_Player);
				}
				else
				{	
					printf (" ");	
				}	
			}	
		}
		
	printf ("\n");
	ordinat=ordinat+1;
	}
absis=absis+10;	
}
}

void Print_Win ()
{
int i;
system("cls");
system("COLOR 2F");

gotoxy(25,4);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}
	gotoxy(71,5);
	printf("%c %c CONGRATULATION !! %c %c ", 3,4,5,6);
	
	gotoxy(25,6);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
gotoxy(58,14);printf("  ***     ***         *** ***          ***        ***    \n");
gotoxy(58,15);printf("  ***     ***       ***      ***       ***        ***    \n");
gotoxy(58,16);printf("   ***   ***        ***      ***       ***        ***    \n");
gotoxy(58,17);printf("      ***           ***      ***       ***        ***    \n");
gotoxy(58,18);printf("      ***           ***      ***       ***        ***    \n");
gotoxy(58,19);printf("      ***           ***      ***        ***      ***     \n");
gotoxy(58,20);printf("      ***             *** ***            *** ** ***      \n");


                                                                                   
gotoxy(58,24);printf("       0                   0    00  00      00    ");                           
gotoxy(58,25);printf("        0                 0     00  000     00    ");                     
gotoxy(58,26);printf("         0       0       0      00  00 0    00    ");                     
gotoxy(58,27);printf("          0     0 0     0       00  00  0   00    ");                       
gotoxy(58,28);printf("           0   0   0   0        00  00   0  00    ");                       
gotoxy(58,29);printf("            0 0     0 0         00  00    0 00    ");                      
gotoxy(58,30);printf("             0       0          00  00     000    ");       
gotoxy(25,36);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}

	
	gotoxy(25,38);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
	
					
printf("\n\n\n");
gotoxy(71,37);
system("PAUSE");		
}

void Isi_High_Score () // Isi HighScore Kalau nilai dari file lebih Kecil Dari SCore Sekarang
{
	HighScore temp;
	FILE *Note_HighScore;
	
	Note_HighScore=fopen("file_HighScore.DAT" ,"wb+");
	
	
	fread(&temp, sizeof(HighScore) ,1,Note_HighScore);
	//----------------------------------------------------
	
	
	
	if(temp.Score < Score_Player)
	{		
		strcpy(temp.Nama,NamaPemain);
    	temp.Score=Score_Player;    
		
					
		fwrite (&temp,sizeof(HighScore),1,Note_HighScore);	
		//----------------------------------------------------	
	}
					
	fclose(Note_HighScore);
	
}

void ResetHighScore ()// Saya Ingin Reset isi File jadi : "Reset" "0";
{
	FILE *Note_HighScore;
	HighScore temp;

	
	
	Note_HighScore=fopen("file_HighScore.DAT" ,"wb");
	temp.Score=0;
	strcpy(temp.Nama, "N/A Reset");
	
	// saya biasana make fwrite jang nyimpen can pernah make fprint... ieu bieu ges diuji hade make fwrite....
	fwrite (&temp,sizeof(HighScore),1,Note_HighScore);
	//----------------------------------------------------
	
	fclose(Note_HighScore);	
}

void Print_HighScore() 
{
	system("cls");
	int i;
	HighScore temp;
	FILE *Note_HighScore;
	
	Note_HighScore=fopen("file_HighScore.DAT" ,"rb");
	fread(&temp, sizeof(HighScore) ,1,Note_HighScore);
	
	gotoxy(55,10);
	for (i=0; i<50; i++)
	{
		printf("%c", 240);		
	}
	gotoxy(75,11);
	printf("HIGHSCORE");
	
	gotoxy(55,12);	
	for (i=0; i<50; i++)
	{
		printf("%c", 240);		
	}
	
	gotoxy(61,16);printf("ษอออออออออออออออออออออออออออออออออป\n");
	gotoxy(61,17);printf("บ            HIGH SCORE           บ\n");
	gotoxy(61,18);printf("                                   \n");
	gotoxy(61,19);printf("             						 \n");
	gotoxy(61,20);printf("   \t%s\t%d                        \n",temp.Nama,temp.Score);
	gotoxy(61,21);printf("                                   \n");
	gotoxy(61,22);printf("                                   \n");
	gotoxy(61,23);printf("                                   \n");
	gotoxy(61,24);printf("                                   \n");
	gotoxy(61,25);printf("                                   \n");
	gotoxy(61,26);printf("บ                                 บ\n");
	gotoxy(61,27);printf("ศอออออออออออออออออออออออออออออออออผ\n");
	gotoxy(61,29);printf("Apakah HIGHSCORE ingin di Reset ??\n\n");
	gotoxy(61,30);printf("Jika direset HIGHSCORE akan terhapus dan kembali lagi menjadi NOL (0)\n");
	gotoxy(61,32);printf("1. Ya Reset Sekarang\n");
	gotoxy(61,33);printf("2. Tidak, Kembali Ke menu \n");
	gotoxy(61,34);printf("Pilih Nomor <1-2> : ");	
	
	fclose(Note_HighScore);	
		
}

void Print_Lose()
{
int i;
system("cls");
system("COLOR 4F");

gotoxy(25,4);
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}
	gotoxy(74,5);
	printf("%c %c SORRY !! %c %c ", 3,4,5,6);
	
	gotoxy(25,6);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}

gotoxy(58,14);printf("  ***     ***         *** ***          ***        ***    \n");
gotoxy(58,15);printf("  ***     ***       ***      ***       ***        ***    \n");
gotoxy(58,16);printf("   ***   ***        ***      ***       ***        ***    \n");
gotoxy(58,17);printf("      ***           ***      ***       ***        ***    \n");
gotoxy(58,18);printf("      ***           ***      ***       ***        ***    \n");
gotoxy(58,19);printf("      ***           ***      ***        ***      ***     \n");
gotoxy(58,20);printf("      ***             *** ***            *** ** ***      \n");


                                                                                   
gotoxy(58,24);printf("   * *               * * * * *        * * * * *     * * * * *   \n");
gotoxy(58,25);printf("   * *             * *       * *      * *           * *         \n");
gotoxy(58,26);printf("   * *             * *       * *      * *           * *         \n");
gotoxy(58,27);printf("   * *             * *       * *      * * * * *     * * * * *   \n");
gotoxy(58,28);printf("   * *             * *       * *            * *     * *         \n");
gotoxy(58,29);printf("   * * * * * *     * *       * *            * *     * *         \n");
gotoxy(58,30);printf("   * * * * * *       * * * * *        * * * * *     * * * * *   \n");

	gotoxy(25,38);	
	for (i=0; i<111; i++)
	{
		printf("อ");		
	}

	
	gotoxy(25,40);	
	for (i=0; i<111; i++)
	{
		printf("อ");	
	}
	
					
printf("\n\n\n");
gotoxy(71,39);
system("PAUSE");		
}
 
int HitungSisa_Dek () //Mengitung Jumlah Sisa Kartu Yang Ada Pada Dek
{	
	int Count_Sisa_Dek=0;
	int i=0;
	while (i < 52)
	{
		if (Dek[i].nilai_kartu != 0)
		{
			Count_Sisa_Dek++;
		}
	i++;
	}
	return Count_Sisa_Dek;	
}


void SortingBy_NilaiPlayer()
{
	int i, j;
	int imaks;
	int panjang_array = sizeof(Player) / sizeof(Player[0]); // Untuk Mengitung Panjang Array
	
		for (i=0; i < panjang_array-1; i++ )
		{
			imaks=i;
				
				for (j=i+1; j < panjang_array; j++)
				{
						if (Player[j].nilai_kartu > Player[imaks].nilai_kartu )
						{
							imaks=j;
						}
				}
				
			Tukar (&Player[i].nilai_kartu,&Player[imaks].nilai_kartu);
			Tukar (&Player[i].jenis_kartu,&Player[imaks].jenis_kartu);
		}
}


void SortingBy_JenisPlayer()
{
	int i, j;
	int imaks;
	int panjang_array = sizeof(Player) / sizeof(Player[0]); // Untuk Mengitung Panjang Array
	
		for (i=0; i < panjang_array-1; i++ )
		{
			imaks=i;
				
				for (j=i+1; j < panjang_array; j++)
				{
						if (Player[j].jenis_kartu > Player[imaks].jenis_kartu )
						{
							imaks=j;
						}
				}
				
			Tukar (&Player[i].nilai_kartu,&Player[imaks].nilai_kartu);
			Tukar (&Player[i].jenis_kartu,&Player[imaks].jenis_kartu);
		}
}

void SortingBy_NilaiComputer()
{
	int i, j;
	int imaks;
	int panjang_array = sizeof(Player_Comp) / sizeof(Player_Comp[0]); // Untuk Mengitung Panjang Array
	
		for (i=0; i < panjang_array-1; i++ )
		{
			imaks=i;
				
				for (j=i+1; j < panjang_array; j++)
				{
						if (Player_Comp[j].nilai_kartu > Player_Comp[imaks].nilai_kartu )
						{
							imaks=j;
						}
				}
				
			Tukar (&Player_Comp[i].nilai_kartu,&Player_Comp[imaks].nilai_kartu);
			Tukar (&Player_Comp[i].jenis_kartu,&Player_Comp[imaks].jenis_kartu);
		}
}

void SortingBy_JenisComputer()
{
	int i, j;
	int imaks;
	int panjang_array = sizeof(Player_Comp) / sizeof(Player_Comp[0]); // Untuk Mengitung Panjang Array
	
		for (i=0; i < panjang_array-1; i++ )
		{
			imaks=i;
				
				for (j=i+1; j < panjang_array; j++)
				{
						if (Player_Comp[j].jenis_kartu > Player_Comp[imaks].jenis_kartu )
						{
							imaks=j;
						}
				}
				
			Tukar (&Player_Comp[i].nilai_kartu,&Player_Comp[imaks].nilai_kartu);
			Tukar (&Player_Comp[i].jenis_kartu,&Player_Comp[imaks].jenis_kartu);
		}
}

void SortingNilai ()
{
	SortingBy_NilaiComputer();
	SortingBy_NilaiPlayer();
	
}

void SortingJenis()
{
	SortingBy_JenisComputer();
	SortingBy_JenisPlayer();
	
}

void SortingAll()
{
	SortingNilai();
	SortingJenis();	
}


void Tampil_Utama()
{
	Print_ScoreComputer();
	Print_ScorePlayer();
	Print_Judul ();
	Print_ComputerHidden();
	Print_Dek();
	Print_Buangan();
	Print_Player();
		
}

void CountingGL()
{
	int i;
	for(i=0; i<11; i++)
	{
		
		CountingGrup[Player[i].nilai_kartu];
		
	}
}

void SetZero()
{

	int i;
	for(i=1; i<=13; i++)
	{
		CountingGrup[i]=0;
	}
	
	Total_KartuMati_Player=0;
}


void BeriStatus()
{
	int i,j;
	
	for(i=1; i<=13; i++)
	{
		if(CountingGrup[i]>=3)
		{
			for(j=0; j<11; j++)
			{
				if( i == Player[j].nilai_kartu)
				{
					Player[j].status_GL=true;
				}
			
			}
		}
	
	}
	
}

int Hitung_Kartu_Mati()                             //Kivlan Aziz
{
	
	int  i;
	for (i=0; i<11; i++)
	{
		if(Player[i].status_GL==false)
		{
			if(Player[i].nilai_kartu >=11)
			{
				Total_KartuMati_Player+=10;
			}
			else if(Player[i].nilai_kartu>1)
			{
				
				Total_KartuMati_Player+=5;
			}
			else if(Player[i].nilai_kartu==1){
				Total_KartuMati_Player+=15;
			}
		}
		
	}
	
	
return Total_KartuMati_Player;
	
}

void scoring(){                              //Kivlan Aziz
	int i=0,c,d,a;
	boolean s=false;
	while (i<12){                 // Skor Untuk Nilai Yang berurut
//		s=false;
		c=i;
		d=c+1;
		while (c<12){
			c++;
			if ((Player[i].jenis_kartu==Player[c].jenis_kartu)&&Player[c].cardstat==false){
				while(d<12){
					d++;
					if((Player[i].jenis_kartu==Player[d].jenis_kartu)&&Player[d].cardstat==false){
						//s=true;
						if (((Player[i].nilai_kartu-1)==Player[c].nilai_kartu )&&((Player[i].nilai_kartu-2)==Player[d].nilai_kartu)){
							if ((Player[i].nilai_kartu>=11 && Player[i+1].nilai_kartu>=11) && Player[i+2].nilai_kartu>=11){
							PlayerScore+=30;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player[i].nilai_kartu>1 && Player[c].nilai_kartu>1) && Player[d].nilai_kartu>1){
							if ((Player[i].nilai_kartu>1 && Player[i+1].nilai_kartu>1) && Player[i+2].nilai_kartu>1){
							PlayerScore+=15;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						}
					}
					}
				}
			}
					else if	((Player[i].jenis_kartu==Player[c].jenis_kartu)&&Player[c].cardstat==true){
					while(d<12){
					d++;
					if((Player[i].jenis_kartu==Player[d].jenis_kartu)&&Player[d].cardstat==false){
						//s=true;
						if (((Player[i].nilai_kartu-1)==Player[c].nilai_kartu )&& ((Player[i].nilai_kartu-2)==Player[d].nilai_kartu)){
							if ((Player[i].nilai_kartu>=11 && Player[i+1].nilai_kartu>=11) && Player[i+2].nilai_kartu>=11){
							PlayerScore+=10;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player[i].nilai_kartu>1 && Player[c].nilai_kartu>1) && Player[d].nilai_kartu>1){
							if ((Player[i].nilai_kartu>1 && Player[i+1].nilai_kartu>1) && Player[i+2].nilai_kartu>1)
							PlayerScore+=5;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						}
					}
					}
				}
			}
		
		i++;
	}
	i=0;
	s=false;
		while (i<12){      // Skor Untuk Nilai Yang Sama
//		s=false;
		c=i;
		d=c+1;
		while (c<12){
			c++;
			if ((Player[i].nilai_kartu==Player[c].nilai_kartu)&&(Player[c].cardstat==false)){
				while(d<12){
					d++;
					if((Player[i].nilai_kartu==Player[d].nilai_kartu)&& (Player[d].cardstat==false)){
						s=true;
					//	if ((Player[i].nilai_kartu)==Player[c].nilai_kartu && (Player[i].nilai_kartu-2)==Player[d].nilai_kartu){
							if ((Player[i].nilai_kartu>=11 && Player[i+1].nilai_kartu>=11) && Player[i+2].nilai_kartu>=11){
							PlayerScore+=30;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player[i].nilai_kartu>1 && Player[c].nilai_kartu>1) && Player[d].nilai_kartu>1){
							PlayerScore+=15;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player[i].nilai_kartu==1 && Player[c].nilai_kartu==1)&& Player[d].nilai_kartu==1){
							PlayerScore+=45;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
					//	}
					}
					
				}
			}
			if ((Player[i].nilai_kartu==Player[c].nilai_kartu)&&Player[c].cardstat==true){
				while(d<12){
					d++;
					if((Player[i].nilai_kartu==Player[d].nilai_kartu)&& Player[d].cardstat==false){
						s=true;
					//	if ((Player[i].nilai_kartu)==Player[c].nilai_kartu && (Player[i].nilai_kartu-2)==Player[d].nilai_kartu){
							if ((Player[i].nilai_kartu>=11 && Player[i+1].nilai_kartu>=11) && Player[i+2].nilai_kartu>=11){
							PlayerScore+=10;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player[i].nilai_kartu>1 && Player[c].nilai_kartu>1) && Player[d].nilai_kartu>1){
							PlayerScore+=5;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player[i].nilai_kartu==1 && Player[c].nilai_kartu==1)&& Player[d].nilai_kartu==1){
							PlayerScore+=15;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player[i].cardstat=true;
							Player[c].cardstat=true;
							Player[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
					//	}
					}
					
				}
			}
		}
		i++;
	}
//	while (bool l==false){
/*		while (i<12){
		s=false;
		if(Player[i].jenis_kartu==Player[i+1].jenis_kartu && Player[i+2].jenis_kartu == Player[i].jenis_kartu){			
			if ((Player[i].nilai_kartu-1)==Player[i+1].nilai_kartu && (Player[i].nilai_kartu-2)==Player[i+2].nilai_kartu){
				if ((Player[i].nilai_kartu>=11 && Player[i+1].nilai_kartu>=11) && Player[i+2].nilai_kartu>=11){
					PlayerScore+=30;
					s=true;
				}
				else if ((Player[i].nilai_kartu>1 && Player[i+1].nilai_kartu>1) && Player[i+2].nilai_kartu>1){
					PlayerScore+=15;
					s=true;
				}
			}
		}
		else if(Player[i].jenis_kartu==Player[i+1].jenis_kartu && Player[i].jenis_kartu==Player[i+2].jenis_kartu){
			if ((Player[i].nilai_kartu>=11 && Player[i+1].nilai_kartu>=11) && Player[i+2].nilai_kartu>=11){
				PlayerScore+=30;
				s=true;
			}
			else if ((Player[i].nilai_kartu>1 && Player[i+1].nilai_kartu>1) && Player[i+2].nilai_kartu>1){
				PlayerScore+=15;
				s=true;
			}
			else if ((Player[i].nilai_kartu==1 && Player[i+1].nilai_kartu==1) && Player[i+2].nilai_kartu==1){
				PlayerScore+=45;
				s=true;
			}
		}
		if (s==true){
			i=i+3;
		}
		else if(s==false){
			i++;
		}
	}
//	bool l=true;
//}*/
}
void scoring_comp(){          //Kivlan Aziz
	int i=0,c,d,a;
	boolean s=false;
	while (i<12){
//		s=false;
		c=i;
		d=c+1;
		while (c<12){         // Skor Untuk Nilai yang berurut
			c++;
			if ((Player_Comp[i].jenis_kartu==Player_Comp[c].jenis_kartu)&&Player_Comp[c].cardstat==false){
				while(d<12){
					d++;
					if((Player_Comp[i].jenis_kartu==Player_Comp[d].jenis_kartu)&&Player_Comp[d].cardstat==false){
						//s=true;
						if (((Player_Comp[i].nilai_kartu-1)==Player_Comp[c].nilai_kartu )&& ((Player_Comp[i].nilai_kartu-2)==Player_Comp[d].nilai_kartu)){
							if ((Player_Comp[i].nilai_kartu>=11 && Player_Comp[i+1].nilai_kartu>=11) && Player_Comp[i+2].nilai_kartu>=11){
							CompScore+=30;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player_Comp[i].nilai_kartu>1 && Player_Comp[c].nilai_kartu>1) && Player_Comp[d].nilai_kartu>1){
							if ((Player_Comp[i].nilai_kartu>1 && Player_Comp[i+1].nilai_kartu>1) && Player_Comp[i+2].nilai_kartu>1){
							CompScore+=15;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						}
					}
					}
				}
			}
					else if	((Player_Comp[i].jenis_kartu==Player_Comp[c].jenis_kartu)&&Player_Comp[c].cardstat==true){
					while(d<12){
					d++;
					if((Player_Comp[i].jenis_kartu==Player_Comp[d].jenis_kartu)&&Player_Comp[d].cardstat==false){
						//s=true;
						if (((Player_Comp[i].nilai_kartu-1)==Player_Comp[c].nilai_kartu )&& ((Player_Comp[i].nilai_kartu-2)==Player_Comp[d].nilai_kartu)){
							if ((Player_Comp[i].nilai_kartu>=11 && Player_Comp[i+1].nilai_kartu>=11) && Player_Comp[i+2].nilai_kartu>=11){
							CompScore+=10;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player_Comp[i].nilai_kartu>1 && Player_Comp[c].nilai_kartu>1) && Player_Comp[d].nilai_kartu>1){
							if ((Player_Comp[i].nilai_kartu>1 && Player_Comp[i+1].nilai_kartu>1) && Player_Comp[i+2].nilai_kartu>1)
							CompScore+=5;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						}
					}
					}
				}
			}
		
		i++;
	}
	i=0;
	s=false;
		while (i<12){          // Skor Untuk Nilai Yang Sama
//		s=false;
		c=i;
		d=c+1;
		while (c<12){
			c++;
			if ((Player_Comp[i].nilai_kartu==Player_Comp[c].nilai_kartu)&&Player_Comp[c].cardstat==false){
				while(d<12){
					d++;
					if((Player_Comp[i].nilai_kartu==Player_Comp[d].nilai_kartu)&& Player_Comp[d].cardstat==false){
						s=true;
					//	if ((Player[i].nilai_kartu)==Player[c].nilai_kartu && (Player[i].nilai_kartu-2)==Player[d].nilai_kartu){
							if ((Player_Comp[i].nilai_kartu>=11 && Player_Comp[i+1].nilai_kartu>=11) && Player_Comp[i+2].nilai_kartu>=11){
							CompScore+=30;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player_Comp[i].nilai_kartu>1 && Player_Comp[c].nilai_kartu>1) && Player_Comp[d].nilai_kartu>1){
							CompScore+=15;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player_Comp[i].nilai_kartu==1 && Player_Comp[c].nilai_kartu==1)&& Player_Comp[d].nilai_kartu==1){
							CompScore+=45;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
					//	}
					}
					
				}
			}
			if ((Player_Comp[i].nilai_kartu==Player_Comp[c].nilai_kartu)&&Player_Comp[c].cardstat==true){
				while(d<12){
					d++;
					if((Player_Comp[i].nilai_kartu==Player_Comp[d].nilai_kartu)&& Player_Comp[d].cardstat==false){
						s=true;
					//	if ((Player[i].nilai_kartu)==Player[c].nilai_kartu && (Player[i].nilai_kartu-2)==Player[d].nilai_kartu){
							if ((Player_Comp[i].nilai_kartu>=11 && Player_Comp[i+1].nilai_kartu>=11) && Player_Comp[i+2].nilai_kartu>=11){
							CompScore+=10;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player_Comp[i].nilai_kartu>1 && Player_Comp[c].nilai_kartu>1) && Player_Comp[d].nilai_kartu>1){
							CompScore+=5;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
						else if ((Player_Comp[i].nilai_kartu==1 && Player_Comp[c].nilai_kartu==1)&& Player_Comp[d].nilai_kartu==1){
							CompScore+=15;
							//black[a]=Player[i];
							//black[a+1]=Player[c];
							//black[a+2]=Player[d];
							Player_Comp[i].cardstat=true;
							Player_Comp[c].cardstat=true;
							Player_Comp[d].cardstat=true;
							//a=a+3;
						//	s=true;
						}
					//	}
					}
					
				}
			}
		}
		i++;
	}
}
//}
// int Cek_UrutanLengkap ()
//{
//	char letter='a';
//	int cekletter=0;
//	int i, j, k=0,l;
//	int Cek;
//	boolean Same;
//	int Selisih ;
//	int Tot_Lengkap=0;
//	int itemp=0;
//	int Panjang_Array = sizeof(Player) / sizeof(Player[0]); // Untuk Mengitung Panjang Array
//	n=0;
//		
//		for (i=0; i < Panjang_Array-1; i++)
//		{	
//			Cek=0;
//			Selisih=1;
//			itemp=0;
//			cekletter=0;
//			for (j=i+1; j < Panjang_Array; j++)
//			{	
//				
//				if (Player[i].nilai_kartu > Player[j].nilai_kartu && Player[i].jenis_kartu == Player[j].jenis_kartu)
//				{
//					if(Player[i].nilai_kartu-Player[j].nilai_kartu==Selisih)
//					{
//						
//						Cek++;
//						Selisih++;
//						if (itemp != Player[i].nilai_kartu )
//						{
//							Posisi1_temp[k].nilai=Player[i].nilai_kartu;
//							Posisi1_temp[k].jenis=Player[i].jenis_kartu;
//							Posisi1_temp[k].letter=letter;
//							Posisi1_temp[k].array=i;
//  							k++;
//						}
//						Posisi1_temp[k].nilai=Player[j].nilai_kartu;
//						Posisi1_temp[k].jenis=Player[j].jenis_kartu;
//						Posisi1_temp[k].letter=letter;
//						Posisi1_temp[k].array=j;
//						k++;
//						itemp=Player[i].nilai_kartu;
//					}
//					
//				}		
//			}
//			if (Cek >= 2)
//			{
//				Tot_Lengkap=Tot_Lengkap+1;
//			}
//				
//			for (l=0; l<11; l++)
//			{	
//				if (Posisi1_temp[l].letter==letter)
//				{
//					cekletter++;
//				}
//				
//			}
//			
//			int batas=k;
//			if (cekletter >= 3)
//			{
//				for (l=n; l<batas; l++)
//				{
//						Posisi1[n].nilai=Posisi1_temp[l].nilai;
//						Posisi1[n].jenis=Posisi1_temp[l].jenis;
//						Posisi1[n].letter=Posisi1_temp[l].letter;
//						Posisi1[n].array=Posisi1_temp[l].array;
//						n++;	
//				}
//					
//			}
//				
//			letter++;	
//		}		
//			 
//	return Tot_Lengkap;
//}
//
//int Cek_GrupLengkap ()
//{
//	
//	int i, j,k;
//	boolean test1=false, test2=false;
//	int Cek;
//	int Tot_Lengkap=0;
//	int Posisi[11];
//	int Panjang_Array = sizeof(Player) / sizeof(Player[0]); // Untuk Mengitung Panjang Array
//	
//		
//		for (i=0; i < Panjang_Array-1; i++)
//		{	
//			Cek=0;
//			
//				for (k=0; k<11; k++ )
//				{
//					if (Posisi1[k].array == i)
//					{
//						test1=true;
//					}
//				
//				}	
//				
//		 if (test1==false)	
//		 {
//			for (j=i+1; j < Panjang_Array; j++)
//			{	
//				
//				for (k=0; k<11; k++ )
//				{
//					if (Posisi1[k].array == i)
//					{
//						test2=true;
//					}
//				
//				}	
//			  
//					if (Player[i].nilai_kartu == Player[j].nilai_kartu && test2==false)
//					{
//						Cek++;
//					}
//			  
//			}
//			 
//			if (Cek >= 2)
//			{
//				Tot_Lengkap=Tot_Lengkap+1;
//			}
//		}
//			
//		}
//		
//		return Tot_Lengkap;	
//	
//}
//
//int Cek_GrupParsial()
//{
//	int i, j;
//	int Cek;
//	int Tot_Lengkap=0;
//	int Posisi[11];
//	int Panjang_Array = sizeof(Player) / sizeof(Player[0]); // Untuk Mengitung Panjang Array
//	
//		
//		for (i=0; i < Panjang_Array-1; i++)
//		{	
//			Cek=0;
//			for (j=i+1; j < Panjang_Array; j++)
//			{	
//				
//				if (Player[i].nilai_kartu == Player[j].nilai_kartu)
//				{
//					Cek++;
//				}		
//			}
//			if (Cek == 1)
//			{
//				Tot_Lengkap=Tot_Lengkap+1;
//			}
//			
//		}
//		return Tot_Lengkap;	
//	
//	
//}
//
//int Cek_UrutanParsial ()
//{
//	
//	int i, j;
//	int Cek;
//	int Selisih;
//	int Tot_Lengkap=0;
//	int Posisi[11];
//	int Panjang_Array = sizeof(Player) / sizeof(Player[0]); // Untuk Mengitung Panjang Array
//	
//		
//		for (i=0; i < Panjang_Array-1; i++)
//		{	
//			Cek=0;
//			Selisih=1;
//			for (j=i+1; j < Panjang_Array; j++)
//			{	
//				
//				if (Player[i].nilai_kartu > Player[j].nilai_kartu && Player[i].jenis_kartu == Player[j].jenis_kartu)
//				{
//					if(Player[i].nilai_kartu-Player[j].nilai_kartu==Selisih)
//					{
//						Cek++;
//						Selisih++;
//					}
//					
//				}		
//			}
//			if (Cek == 1)
//			{
//				Tot_Lengkap=Tot_Lengkap+1;
//			}
//			
//		}
//	
//	return Tot_Lengkap;
//}

void CountingGL_Comp()
{
	int i;
	for(i=0; i<11; i++)
	{
		
		CountingGrup_Comp[Player_Comp[i].nilai_kartu];
		
	}
}

void SetZero_Comp()
{

	int i;
	for(i=1; i<=13; i++)
	{
		CountingGrup_Comp[i]=0;
	}
	
	Total_KartuMati_Comp=0;
}


void BeriStatus_Comp()
{
	int i,j;
	
	for(i=1; i<=13; i++)
	{
		if(CountingGrup_Comp[i]>=3)
		{
			for(j=0; j<11; j++)
			{
				if( i == Player_Comp[j].nilai_kartu)
				{
					Player_Comp[j].status_GL=true;
				}
			
			}
		}
	
	}
	
}

int Hitung_Kartu_Mati_Comp()
{
	
	int  i;
	for (i=0; i<11; i++)
	{
		if(Player_Comp[i].status_GL==false)
		{
			if(Player_Comp[i].nilai_kartu >=11)
			{
				Total_KartuMati_Comp+=10;
			}
			else if(Player_Comp[i].nilai_kartu>1)
			{
				
				Total_KartuMati_Comp+=5;
			}
			else if(Player_Comp[i].nilai_kartu==1){
				Total_KartuMati_Comp+=15;
			}
		}
		
	}
	
return Total_KartuMati_Comp;
	
}
void SetFalse_Comp()
{
	int i;
	for(i=0; i<11; i++)
	{
		Player_Comp[i].status_GL=false;
	}
}



void FirstStep()
{
	Random_Dek();
	Isi_Dek();
	Bagi_Kartu();
	Inisialisasi_Status ();
}

void SetFalse()
{
	int i;
	for(i=0; i<11; i++)
	{
		Player[i].status_GL=false;
	}
}

void GrupLengkap_Player()
{
	SetFalse();
	SetZero();
	CountingGL();
	BeriStatus();
	Hitung_Kartu_Mati();
}

void GrupLengkap_Comp()
{
	SetFalse_Comp();
	SetZero_Comp();
	CountingGL_Comp();
	BeriStatus_Comp();
	Hitung_Kartu_Mati_Comp();
}

void BuangKartu()
{
	int i;
	
	gotoxy(8,39);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
	
	gotoxy(55,40);
	printf("BUANG KARTU");
	
	gotoxy(8,41);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
	gotoxy(49,43);
	printf("Silahkan Pilih Kartu Untuk Dibuang  :\n");
	gotoxy(49,44);
	printf("Pilih Kartu dari No <1-11>  :  ");
	
}

int IsTutupTangan (int tot_mati)
{
	boolean Tutup=false;
	
	if (tot_mati <=10)
	{
		Tutup=true;
	}
return Tutup;	
}

void Print_TutupTangan()
{
	
	int i;	
	gotoxy(28,15);
	for (i=0; i<47; i++)
	{
		printf("%c", 240);		
	}
	gotoxy(47,16);
	printf("SCORE");
	
	gotoxy(28,17);	
	for (i=0; i<47; i++)
	{
		printf("%c", 240);		
	}
	
	gotoxy(28,18);printf("ษอออออออออออออออออออออออออออออออออออออออออออออป\n");
	gotoxy(28,19);printf("บ               Tutup Kartu                   บ\n");
	gotoxy(28,20);printf("       Total Nilai Kartu Mati Komputer         \n");
	gotoxy(28,21);printf("                    %d                          \n",Total_KartuMati_Comp);
	gotoxy(28,22);printf("       Total Nilai Kartu Mati Kamu             \n");
	gotoxy(28,23);printf("                    %d                          \n",Total_KartuMati_Player);
	gotoxy(28,24);printf("                                               \n");
	gotoxy(28,25);printf("              Score Komputer                   \n");
	gotoxy(28,26);printf("                    %d                          \n",Score_Comp);
	gotoxy(28,27);printf("                Score Kamu                     \n");
	gotoxy(28,28);printf("บ                   %d                         บ\n",Score_Player);
	gotoxy(28,29);printf("ศอออออออออออออออออออออออออออออออออออออออออออออผ\n");
	
}

void TutupTangan_Score (boolean status)         //Kivlan Aziz
{
	//if(status==true)
	//{
	//	if(Total_KartuMati_Player==0)
	//	{
	//		Score_Player = PlayerScore;
	//		Score_Comp = CompScore;
	//	}
	//	else
	//	{
			/* if(Total_KartuMati_Player < Total_KartuMati_Comp)	
			 {
		 		Score_Player = Score_Player + Total_KartuMati_Comp - Total_KartuMati_Player;
		 		Score_Comp = Score_Comp + 0;
			 }
			 else if (Total_KartuMati_Player >= Total_KartuMati_Comp)
			 {
			 	Score_Player = Score_Player + 0;
			 	Score_Comp = Score_Comp + Total_KartuMati_Player - Total_KartuMati_Comp + 25;
			 }*/
			 Score_Player += PlayerScore-Total_KartuMati_Player;//-Total_KartuMati_Player;
			 Score_Comp += CompScore-Total_KartuMati_Comp;
	//	}	
	//}
	//else
	//{
	//	if(Total_KartuMati_Comp==0)
	//	{
	//		Score_Comp = Score_Comp + Total_KartuMati_Player - Total_KartuMati_Comp + 25;
	//		Score_Player = Score_Player + 0;
	//	}
	//	else
	//	{
	//		 if(Total_KartuMati_Comp < Total_KartuMati_Player)	
	//		 {
	//	 		Score_Comp = Score_Comp + Total_KartuMati_Player - Total_KartuMati_Comp;
	//	 		Score_Player = Score_Player + 0;
	//		 }
	//		 else if (Total_KartuMati_Comp >= Total_KartuMati_Player)
	//		 {
	//		 	Score_Comp = Score_Comp + 0;
	//		 	Score_Player = Score_Player + Total_KartuMati_Comp - Total_KartuMati_Player + 25;
	//		 }
	//	
	//	}
	//}
	
	system("cls");
	Print_ScoreComputer();
	Print_ScorePlayer();
	Print_Judul ();
	Print_Computer();
	Print_TutupTangan();
	Print_Player();
}

int InputNama ()
{
	int i;	
	gotoxy(48,15);
	for (i=0; i<47; i++)
	{
		printf("%c", 240);		
	}
	gotoxy(55,16);
	printf("MASUKKAN NAMA ANDA (MAX 8 KARAKTER)");
	
	gotoxy(48,17);	
	for (i=0; i<47; i++)
	{
		printf("%c", 240);		
	}
	
	gotoxy(48,18);printf("ษอออออออออออออออออออออออออออออออออออออออออออออป\n");
	gotoxy(48,19);printf("บ          Silahkan Masukkan Nama Anda        บ\n");
	gotoxy(48,20);printf("                                    	          \n");
	gotoxy(48,21);printf("                                                \n");
	gotoxy(48,22);printf("                                                \n");
	gotoxy(69,23);fgets (NamaPemain, sizeof NamaPemain, stdin);
	NamaPemain[strlen(NamaPemain)-1]='\0';
	gotoxy(48,24);printf("                                                \n");
	gotoxy(48,25);printf("                                                 \n");
	gotoxy(48,26);printf("                                                \n");
	gotoxy(48,27);printf("                                                \n");
	gotoxy(48,28);printf("บ                                             บ\n");
	gotoxy(48,29);printf("ศอออออออออออออออออออออออออออออออออออออออออออออผ\n");
	
	printf("\n\n\n");
	system("PAUSE");
}

void Dek_Habis()
{
	system("cls");
	Print_ScoreComputer();
	Print_ScorePlayer();
	Print_Judul ();
	Print_Computer();
	int i;	
	gotoxy(28,15);
	for (i=0; i<47; i++)
	{
		printf("%c", 240);		
	}
	gotoxy(47,16);
	printf("DEK SISA DUA");
	
	gotoxy(28,17);	
	for (i=0; i<47; i++)
	{
		printf("%c", 240);		
	}
	
	gotoxy(28,18);printf("ษอออออออออออออออออออออออออออออออออออออออออออออป\n");
	gotoxy(28,19);printf("บ               DEK TERSISA DUA               บ\n");
	gotoxy(28,20);printf("                   Skor Tetap                     \n");
	gotoxy(28,21);printf("            Tidak Dapat Nilai Tambahan            \n");
	gotoxy(28,22);printf("            Tidak Ada Perhitungan Nilai           \n");
	gotoxy(28,23);printf("                Untuk Setiap Pemain               \n");
	gotoxy(28,24);printf("                                                  \n");
	gotoxy(28,25);printf("              Score Komputer                      \n");
	gotoxy(28,26);printf("                    %d                            \n",Score_Comp);
	gotoxy(28,27);printf("                Score Kamu                        \n");
	gotoxy(28,28);printf("บ                   %d                         บ\n",Score_Player);
	gotoxy(28,29);printf("ศอออออออออออออออออออออออออออออออออออออออออออออผ\n");
	Print_Player();
}
int KeputusanAmbil ()
{
	int i;
	boolean sama=false;
	
	for(i=1; i<=13; i++)
	{
		if (CountingGrup_Comp[i]>=2)
		{	
			if (Tempat_Buangan[0].nilai_kartu==i)
			{	
				sama=true;
				break;
			}
		}
		else if(CountingGrup_Comp[i]==1)
		{
			if(Tempat_Buangan[0].nilai_kartu==i)
			{
				sama=true;
				break;
			}
			
		}
	}
	
return sama;
}

int Kemenangan(int score)
{
	boolean status_kemenangan = false;
	if(score >= 100)
	{
		status_kemenangan = true;
	}
	return status_kemenangan;
}

int KeputusanBuang()
{
	
	int i,j;
	int Buang;
	boolean status=false;
	boolean status_pengulangan=false;
	
	for(i=13; i>=1; i--)
	{	
		if (CountingGrup_Comp[i]==1)
		{
			for(j=0; j<=10; j++)
			{
				if(i==Player_Comp[j].nilai_kartu)	
				{
						
					Buang=j;
					status=true;
					status_pengulangan=true;
					break;
					
				}	
				if(status_pengulangan==true)
				{
					break;
				}
					
			}
		}
	}
	
	if (status==false)
	{
		for(i=13; i>=1; i--)
		{	
	 	   if (CountingGrup_Comp[i]==2)
		   {
			for(j=0; j<=10; j++)
			{
				if(i==Player_Comp[j].nilai_kartu)	
				{
						
					Buang=j;
					status=true;
					status_pengulangan=true;
					break;
				}
				if(status_pengulangan==true)
				{
					break;
					
				}	
					
			}
	     	}
		}		
				
		
	}
return Buang;
}

void TutupKartu ()
{
	
	int i;
	
	gotoxy(8,39);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
	
	gotoxy(55,40);
	printf("TUTUP KARTU");
	
	gotoxy(8,41);
	for (i=0; i<100; i++)
	{
		printf("อ");		
	}
				
	
}

int main ()
{	
	system("MODE 168,60");
	MaximizeOutputWindow();
	int i,j,  SisaDek, Ambil, Buang,m=0;
	boolean TutupTangan=false;
	boolean Ambil_Comp;
	int Buang_Comp;
	int menu;
	int exit=0;
	int Pilihan_Tutup;
	int PilihScore;
	FILE *Note_HighScore;	


do{
intro :				system("cls");
					IntroGame();
					printf("\n\n");
					gotoxy(68,40);							
					system("PAUSE");
					
menu :				system("cls");
					menu=menu_game();
					Score_Comp=0;  
					Score_Player=0;
	
	switch(menu)
	{
		case 1:	
				system("cls");
				system("COLOR 6F");
				InputNama();
Main:			system("cls");
				for(i=0;i<=52;i++){
					Dek[i].cardstat=false;
				}
				m=0;
				k=0;
				z=1;
				Tampil_Utama();
				FirstStep();
				SisaDek=HitungSisa_Dek();
				TutupTangan=false;
				
		while (SisaDek != 2)
		{	

			if (SisaDek != 2 )
			{	
UlangAmbil:		system("cls");
				GrupLengkap_Player();
				SortingNilai();
				Tampil_Utama();
				AmbilKartu();
				fflush(stdin);
				scanf("%d", &Ambil);
				if(Ambil==1)
				{
							Player[10].nilai_kartu=Dek[Posisi_Dek].nilai_kartu;
							Player[10].jenis_kartu=Dek[Posisi_Dek].jenis_kartu;
							Dek[Posisi_Dek].nilai_kartu=0;
							Dek[Posisi_Dek].jenis_kartu=0;
							Posisi_Dek++;
				}
				else if (Ambil==2)		
					{
kardb:					printf("Pilih kartu yang ingin diambil");
						int kardb=Pilih();
							if(kardb>7){
								printf("Salah Pilih!");
								goto kardb;
							}
							else {
							
							Player[10].nilai_kartu=Tempat_Buangan[kardb-1].nilai_kartu;//Kivlan aziz
							Player[10].jenis_kartu=Tempat_Buangan[kardb-1].jenis_kartu;
							Tempat_Buangan[kardb-1].nilai_kartu=0;
							Tempat_Buangan[kardb-1].jenis_kartu=0;
						}
					}
					else
					{
					 			printf("Pilihan Anda Tidak Tersedia\n\n");
								system("PAUSE");
								goto UlangAmbil;	
					}
											
				system("PAUSE");
				system("cls");
				GrupLengkap_Player();
				Tampil_Utama();
UlangBuang:		BuangKartu();
				fflush(stdin);
				Buang=Pilih();				
				if (Buang>11)
				{
					printf("Pilihan Anda Tidak Tersedia\n\n");
					system("PAUSE");
					system("cls");
					Tampil_Utama();
					goto UlangBuang;
				}
				else
				{
				//	k++;
					Tempat_Buangan[k].nilai_kartu=Player[Buang-1].nilai_kartu;           /* Kivlan Aziz*/
					Tempat_Buangan[k].jenis_kartu=Player[Buang-1].jenis_kartu;	
					Player[Buang-1].nilai_kartu=0;
					Player[Buang-1].jenis_kartu=0;
					m++;
					if (m<=6){
					z++;
					k++;
					}
					else{
					k=0;
					}																			
					Tempat_Buangan[k].cardstat=false;         //Kivlan aziz
				} 
				GrupLengkap_Player();
				SortingNilai();
				scoring();
				TutupTangan=IsTutupTangan(Total_KartuMati_Player);
				
					if(TutupTangan==true)
					{
tutup:				system("cls");
					Tampil_Utama();
					TutupKartu ();
					gotoxy(49,43);
					printf("Total Nilai Kartu Mati Anda adalah <= 10\n");
					gotoxy(49,44);
					printf("Memenuhi Syarat Untuk Tutup Kartu\n");
					gotoxy(49,45);
					printf("Tutup Kartu Sekarang ? ");
					gotoxy(49,49);
					printf("1. Ya Sekarang\n");
					gotoxy(49,50);
					printf("2. Nanti Lagi\n");
					gotoxy(49,51);
					printf("Pilih Nomor (1-2) : ");
					scanf("%d", &Pilihan_Tutup);
						if(Pilihan_Tutup > 2 )
						{
							printf("Pilihan Tidak Tersedia !!\n");
							printf("Pilih Nomor 1-2\n");
							goto tutup;
						}
						
						else if (Pilihan_Tutup==1)
						{
							TutupTangan_Score(true);
							printf("\n\n");	
							system("PAUSE");
							if(Kemenangan(Score_Player)==true)
							{
								Print_Win();
								Isi_High_Score();
								goto intro;
							}
							goto Main;
						}
		
						
					}
				
				SisaDek=HitungSisa_Dek();
				if (SisaDek==2)
				{
				//	Dek_Habis();
				//	system("PAUSE");
				//	goto Main;
				TutupTangan_Score(true);
							printf("\n\n");	
							system("PAUSE");
							if(Kemenangan(Score_Player)==true)
							{
								Print_Win();
								Isi_High_Score();
								goto intro;
							}
							goto Main;
				}
					
			}
			
			//Giliran Komputer
			if (SisaDek!=2)
			{
					
				system("cls");
				SortingNilai();
				GrupLengkap_Comp();
				Tampil_Utama();
				Ambil_Comp=KeputusanAmbil();	
				if (Ambil_Comp==true)
				{
						Player_Comp[10].nilai_kartu=Tempat_Buangan[0].nilai_kartu;
						Player_Comp[10].jenis_kartu=Tempat_Buangan[0].jenis_kartu;
				}
				else
				{
					
							Player_Comp[10].nilai_kartu=Dek[Posisi_Dek].nilai_kartu;
							Player_Comp[10].jenis_kartu=Dek[Posisi_Dek].jenis_kartu;
							Dek[Posisi_Dek].nilai_kartu=0;
							Dek[Posisi_Dek].jenis_kartu=0;
							Posisi_Dek++;
				}
				GrupLengkap_Comp();
				Tampil_Utama();
				gotoxy(8,39);
				for (i=0; i<100; i++)
				{
						printf("อ");		
				}
	
				gotoxy(50,40);
				printf("KOMPUTER MENGAMBIL KARTU");
	
				gotoxy(8,41);
				for (i=0; i<100; i++)
				{
					printf("อ");		
				}
				Buang_Comp=KeputusanBuang();
				printf("\n\n");	
				system("PAUSE");
				
								
				Tempat_Buangan[0].nilai_kartu=Player_Comp[Buang_Comp].nilai_kartu;
				Tempat_Buangan[0].jenis_kartu=Player_Comp[Buang_Comp].jenis_kartu;	
				Player_Comp[Buang_Comp].nilai_kartu=0;
				Player_Comp[Buang_Comp].jenis_kartu=0;	
				
				system("cls");
				SortingNilai();
				GrupLengkap_Comp();
				Tampil_Utama();
				gotoxy(8,39);
				for (i=0; i<100; i++)
				{
						printf("อ");		
				}
				gotoxy(50,40);
				printf("KOMPUTER BUANG KARTU");
	
				gotoxy(8,41);
				for (i=0; i<100; i++)
				{
					printf("อ");		
				}
				
				Buang_Comp=KeputusanBuang();
				printf("\n\n");	
				system("PAUSE");
				GrupLengkap_Comp();
				SortingNilai();
				scoring_comp();
				TutupTangan=IsTutupTangan(Total_KartuMati_Comp);
					if (TutupTangan==true)
					{
					
								system("PAUSE");
								TutupTangan_Score(false);
								printf("\n\n");	
								system("PAUSE");
								if(Kemenangan(Score_Comp)==true)
								{
									Print_Lose();
									goto intro;
								}
								else
								{
									goto Main;
								}
						
					}
			
			
					SisaDek=HitungSisa_Dek();
					if (SisaDek==2)
					{
					//	Dek_Habis();
					//	printf("\n\n");	
					//	system("PAUSE");
					//	goto Main;
					TutupTangan_Score(true);
							printf("\n\n");	
							system("PAUSE");
							if(Kemenangan(Score_Comp)==true)
							{
								Print_Lose();
							//	Isi_High_Score();
								goto intro;
							}
							goto Main;
					}
			}
		}
		break;
		
		case 2: 
HighScore:		Print_HighScore();
				fflush(stdin);
				scanf("%d", &PilihScore);
				
				if(PilihScore==1)
				{
					ResetHighScore();
					printf("\n\n");
					system("PAUSE");	
					goto HighScore;
				}
				else if (PilihScore==2)
				{
					goto intro;
					printf("\n\n");
					system("PAUSE");
				}
				else if (PilihScore !=1 ||PilihScore !=2 )
					{
					printf("Pilihan Tidak Tersedia !!\n");
					printf("\n\n");
					system("PAUSE");
					goto HighScore;
					}
			
			break;
		case 3:
			help();
			printf("\n\n");
			system("PAUSE");
			goto menu;
			break;	
		case 4:
			about_us();
			printf("\n\n");
			system("PAUSE");
			goto menu;
			break;
		case 5:
			exit=1;
			system("cls");
			OutGame();
			break;
	}
} while (exit != 1);
	
		
return 0;		
}






















//	printf("\n\n");
//	for(i=0; i<sizeof(Posisi1)/sizeof(Posisi1[0]);i++)
//	{
//		printf("%d", Posisi1[i].nilai);
//		printf("%c", Posisi1[i].jenis);
//		printf("%c", Posisi1[i].letter);
//		printf("%d ", Posisi1[i].array);
//		
//	}
//	for (j=1; j<=13; j++ )
//	{
//		
//		printf ("\nKartu %d jumlah %d ", j, CountingGrup[j]);
//	}
//	Sleep(3000);
//	Player[10].nilai_kartu=4;
//	Player[10].jenis_kartu=4;
//	
//	GrupLengkap();
//	Tampil_Utama();
////	Print_Status();
//	printf("\n\n");
//	for(i=0; i<sizeof(Posisi1)/sizeof(Posisi1[0]);i++)
//	{
//		printf("%d", Posisi1[i].nilai);
//		printf("%c", Posisi1[i].jenis);
//		printf("%c", Posisi1[i].letter);
//		printf("%d ", Posisi1[i].array);
//		
//	}
//	for (j=1; j<=13; j++ )
//	{
//		
//		printf ("\nKartu %d jumlah %d ", j, CountingGrup[j]);
//	}
	
//	return 0;
//}

























//int main ()
//{
//	
//	int j=0;
//// Untuk Mengitung Panjang Array
////	Random_Dek();
//	Isi_Dek();
//		int  panjang_array = sizeof(Dek) / sizeof(Dek[0]); 
////	Bagi_Kartu();
//	while (j<panjang_array)	
//	{	if(Dek[j].nilai_kartu==1)
//		{
//			printf("A");
//		}
//		else if(Dek[j].nilai_kartu==11)
//		{
//			printf("J");	
//		}
//		else if (Dek[j].nilai_kartu==12)
//		{
//			printf("Q");	
//		}
//		else if (Dek[j].nilai_kartu==13)
//		{
//			printf("K");	
//		}
//		else
//		{
//		printf("%d", Dek[j].nilai_kartu);	
//		}
//		printf("%c",Dek[j].jenis_kartu);
//		printf("\n");
//		j++;
//	}
////	printf ("%d\n", Posisi_Dek);
////	printf ("%d", Dek[Posisi_Dek].nilai_kartu);
//return 0;
//}


