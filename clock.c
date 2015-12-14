// Note: to successfully use printf(%c,13), 13 if carriage return, and gotoxy
// do NOT put \n at the end of the printf
// flicker ELIMINATED

#include <stdio.h>
#include <tcconio.h>
#include <time.h>
#include <process.h>

#define MAX_CHAR    19

#define BOLD        219
#define TRANS       178
#define SEMI        177
#define WEAK        176
#define INV_SMILEY  1
#define SMILEY      2
#define HEART       3
#define DIAMOND     4
#define CLUB        5
#define SPADE       6
#define MALE        11
#define FEMALE      12
#define MUSIC_NOTE  14
#define SUN         15
#define RIGHT_ARROW 16
#define LEFT_ARROW  17
#define SYMBOL      21
#define UP_ARROW    30
#define DOWN_ARROW  31

unsigned char cs[MAX_CHAR] = {
    BOLD, 
    TRANS, 
    SEMI, 
    WEAK, 
    INV_SMILEY,
    SMILEY,
    HEART,     
    DIAMOND,     
    CLUB,        
    SPADE,       
    MALE,        
    FEMALE,      
    MUSIC_NOTE,  
    SUN,         
    RIGHT_ARROW, 
    LEFT_ARROW,  
    SYMBOL,      
    UP_ARROW,    
    DOWN_ARROW  
    };

void DrawSmallClock (void);
void DrawLargeClock (void);


char month[12][4] = {{"Jan"},{"Feb"},{"Mar"},{"Apr"},
                    {"May"},{"Jun"},{"Jul"},{"Aug"},
                    {"Sep"},{"Oct"},{"Nov"},{"Dec"},};

#define SEQ_RANDOM  112
#define SEQ_ORDER   121
#define SEQ_NONE    87
unsigned char sequence = SEQ_NONE;

unsigned char small = 0;

unsigned char x = 0;
unsigned char y = 1;
int font = 3;
char next = 3;

#define MX_IN_USE   843
#define MX_FREE     648
int mutex = MX_FREE;

struct tm * my_clock;

void Usage(void)
{
    int i;
    
    printf("Usage : Clock [X] [Y] [FONT] [START SMALL]\n");
    printf("      - X [1..16]\n");
    printf("      - Y [1..15]\n");
    printf("      - FONT [1..19]\n");
    printf("      - START SMALL [1] - YES [OTHERWISE] - NO\n\n");
    printf("Keyboard Setting:\n");
    printf("      - [A] RANDOM FONT\n");
    printf("      - [S] PREVIOUS FONT\n");
    printf("      - [W] NEXT FONT\n");
    printf("      - [D] SEQUENTIAL FONT\n");
    printf("      - [X] NORMAL FONT\n");
    printf("      - [SPACE] TOGGLE SMALL FONT\n");
    printf("      - [ESC] EXIT\n\n");
    printf("Font List:\n      -");
    for (i = 0;i < MAX_CHAR ;i++)
        printf("%2.d ",i + 1);
    printf("\n      - ");
        
    for (i = 0;i < MAX_CHAR;i++)
        printf("%c  ",cs[i]);
    printf("\n");
}

void WaitKey(void *dummy)
{
    unsigned char ch;
    while (1)
    {
        ch = (unsigned char) getch();
        if (ch == 'a' || ch == 'A')
        {
            sequence = SEQ_RANDOM;
        }
        else if (ch == 's' || ch == 'S')
        {
            next--;
            if (next < 0)
                next = MAX_CHAR - 1;
        }
        else if (ch == 'w' || ch == 'W')
        {
            next++;
            if (next >= MAX_CHAR)
                next = 0;
        }
        else if (ch == 'd' || ch == 'D')
        {
            sequence = SEQ_ORDER;
        }
        else if (ch == 'x' || ch == 'X')
        {
            next = font;
            sequence = SEQ_NONE;
        }
        else if (ch == ' ')
        {
            while (mutex != MX_FREE);
                
            mutex = MX_IN_USE;
                
            if (small == 0)
            {
                system("cls");
                small = 1;
                DrawSmallClock();
            }
            else if (small == 1)
            {
                system("cls");
                small = 0;
                DrawLargeClock();
            }
            
            mutex = MX_FREE;
        }
        else if (ch == 27)
        {
            system("cls");
            _setcursortype(_NORMALCURSOR);
            exit(1);
        }
    }
}

void DrawLarge(int x, int y, int number, int font)
{
    unsigned char ch;

    if (sequence == SEQ_RANDOM)
        ch = cs[rand() % MAX_CHAR];
    else if (sequence == SEQ_ORDER)
        ch = cs[next];
    else if (sequence == SEQ_NONE)
        ch = cs[font];
        
    switch(number)
    {
        case 0:    
        gotoxy(x,y);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);    
        gotoxy(x,y+1);printf("%c%c    %c%c",ch,ch,ch,ch);    
        gotoxy(x,y+2);printf("%c%c   %c%c%c",ch,ch,ch,ch,ch);    
        gotoxy(x,y+3);printf("%c%c  %c %c%c",ch,ch,ch,ch,ch);    
        gotoxy(x,y+4);printf("%c%c %c  %c%c",ch,ch,ch,ch,ch);    
        gotoxy(x,y+5);printf("%c%c%c   %c%c",ch,ch,ch,ch,ch);    
        gotoxy(x,y+6);printf("%c%c    %c%c",ch,ch,ch,ch);    
        gotoxy(x,y+7);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);    
        break;
        
        case 1:
        gotoxy(x,y);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+1);printf(" %c%c%c%c   ",ch,ch,ch,ch);
        gotoxy(x,y+2);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+3);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+4);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+5);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+6);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+7);printf("%c%c%c%c%c%c%c%c",ch,ch,ch,ch,ch,ch,ch,ch);
        break;
        
        case 2:
        gotoxy(x,y);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+1);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+2);printf("      %c%c",ch,ch);
        gotoxy(x,y+3);printf("    %c%c%c ",ch,ch,ch);
        gotoxy(x,y+4);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+5);printf(" %c%c%c    ",ch,ch,ch);
        gotoxy(x,y+6);printf("%c%c      ",ch,ch);
        gotoxy(x,y+7);printf("%c%c%c%c%c%c%c%c",ch,ch,ch,ch,ch,ch,ch,ch);
        break;
        
        case 3:
        gotoxy(x,y);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+1);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+2);printf("      %c%c",ch,ch);
        gotoxy(x,y+3);printf("   %c%c%c%c ",ch,ch,ch,ch);
        gotoxy(x,y+4);printf("      %c%c",ch,ch);
        gotoxy(x,y+5);printf("      %c%c",ch,ch);
        gotoxy(x,y+6);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+7);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        break;
        
        case 4:
        gotoxy(x,y);printf("    %c%c%c ",ch,ch,ch);
        gotoxy(x,y+1);printf("   %c%c%c%c ",ch,ch,ch,ch);
        gotoxy(x,y+2);printf("  %c%c %c%c ",ch,ch,ch,ch);
        gotoxy(x,y+3);printf(" %c%c  %c%c ",ch,ch,ch,ch);
        gotoxy(x,y+4);printf("%c%c   %c%c ",ch,ch,ch,ch);
        gotoxy(x,y+5);printf("%c%c%c%c%c%c%c",ch,ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+6);printf("     %c%c ",ch,ch);
        gotoxy(x,y+7);printf("     %c%c ",ch,ch);
        break;
        
        case 5:
        gotoxy(x,y);printf("%c%c%c%c%c%c%c%c",ch,ch,ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+1);printf("%c%c      ",ch,ch);
        gotoxy(x,y+2);printf("%c%c      ",ch,ch);
        gotoxy(x,y+3);printf("%c%c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+4);printf("      %c%c",ch,ch);
        gotoxy(x,y+5);printf("      %c%c",ch,ch);
        gotoxy(x,y+6);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+7);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        break;
        
        case 6:
        gotoxy(x,y);printf("   %c%c%c%c ",ch,ch,ch,ch);
        gotoxy(x,y+1);printf("  %c%c    ",ch,ch);
        gotoxy(x,y+2);printf(" %c%c     ",ch,ch);
        gotoxy(x,y+3);printf("%c%c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+4);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+5);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+6);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+7);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        break;
        
        case 7:
        gotoxy(x,y);printf("%c%c%c%c%c%c%c%c",ch,ch,ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+1);printf("      %c%c",ch,ch);
        gotoxy(x,y+2);printf("      %c%c",ch,ch);
        gotoxy(x,y+3);printf("     %c%c ",ch,ch);
        gotoxy(x,y+4);printf("    %c%c  ",ch,ch);
        gotoxy(x,y+5);printf("   %c%c   ",ch,ch);
        gotoxy(x,y+6);printf("  %c%c    ",ch,ch);
        gotoxy(x,y+7);printf("  %c%c    ",ch,ch);
        break;
        
        case 8:
        gotoxy(x,y);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+1);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+2);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+3);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+4);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+5);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+6);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+7);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        break;
        
        case 9:
        gotoxy(x,y);printf(" %c%c%c%c%c%c ",ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+1);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+2);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+3);printf("%c%c    %c%c",ch,ch,ch,ch);
        gotoxy(x,y+4);printf(" %c%c%c%c%c%c%c",ch,ch,ch,ch,ch,ch,ch);
        gotoxy(x,y+5);printf("     %c%c ",ch,ch);
        gotoxy(x,y+6);printf("    %c%c  ",ch,ch);
        gotoxy(x,y+7);printf(" %c%c%c%c   ",ch,ch,ch,ch);
        break;

        case 10:    // colon
        gotoxy(x,y+2);printf("%c%c",ch,ch);
        gotoxy(x,y+5);printf("%c%c",ch,ch);
        break;

    }    
}

void DrawSmallClock (void)
{
    gotoxy(x,y);printf("%.2d %s %d %.2d:%.2d:%.2d%c",my_clock->tm_mday,
                                                     month[my_clock->tm_mon],
                                                     my_clock->tm_year + 1900,
                                                     my_clock->tm_hour,
                                                     my_clock->tm_min,
                                                     my_clock->tm_sec,
                                                     13);

}

void DrawLargeClock (void)
{
    DrawLarge(x + 0,y,my_clock->tm_hour/10,font);
    DrawLarge(x + 10,y,my_clock->tm_hour%10,font);
            
    DrawLarge(x + 20,y,10,font);
        
    DrawLarge(x + 24,y,my_clock->tm_min/10,font);
    DrawLarge(x + 34,y,my_clock->tm_min%10,font);
            
    DrawLarge(x + 44,y,10,font);
        
    DrawLarge(x + 48,y,my_clock->tm_sec/10,font);
    DrawLarge(x + 58,y,my_clock->tm_sec%10,font);
}

int main(int argc, char ** argv)
{
    time_t temp;
    
    if (argc != 5)
    {
        Usage();
        return 0;
    }
    
    x = atoi(argv[1]) - 1;
    y = atoi(argv[2]);
    font = atoi(argv[3]) - 1;
    
    if (atoi(argv[4]) == 1)
        small = 1;
    else if (atoi(argv[4]) != 0)
    {
        Usage();
        return 0;
    }

    if (x < 0 || x > 15 || y < 1 || y > 15 || font < 0 || font >= MAX_CHAR)
    {
        Usage();
        return 0;
    }
    
    next = font;
       
    time(&temp);
    srand(temp);
    
    beginthread(WaitKey,0,NULL);

    _setcursortype(_NOCURSOR);

    system("cls");
    while(1)
    {
		//system("cls");

        while (mutex == MX_IN_USE);
        
        time(&temp);
        my_clock = localtime(&temp);

        if (small == 1)
        {
            DrawSmallClock();
        }
        else
        {
            if (sequence == SEQ_ORDER)
            {
                next++;
                if (next >= MAX_CHAR)
                    next = 0;
            }
            
            DrawLargeClock();
        }
        
        mutex = MX_FREE;
        sleep(500);
    }
}
