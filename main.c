#include <conio.h>
#include <windows.h>
#include <time.h>
#include <curses.h>
int gameOver;
const int visina = 25;
const int sirina = 30;
int x,y,voceX,voceY,score,vRep;
int repX[100], repY[100];
enum eDirection {STOP = 0, LEVO, DESNO, GORE, DOLE};
enum eDirection dir;

void voce(){
    voceX = rand()%sirina;
    if (voceX == 0)
        voceX = 1;
    voceY = rand()%visina;
    if (voceY==0)
        voceY = 1;
}

void Setup()
{
    clear();
    refresh();
    vRep = 0;
    dir = STOP;
    long t = time(NULL);
    srand(t);
    gameOver = 0;
    x = sirina/2;
    y = visina/2;
    voce();
    score = 0;
}

void Slika()
{
    int i;
    initscr();
    curs_set(0);
    noecho();
    WINDOW* win = newwin(visina+2,sirina+1,0,0);
    doupdate();
    for(i=0;i<sirina + 2;i++){
       mvwaddch(win,0,i,'#');
    }
    for (i=1;i<visina;i++){
        mvwaddch(win,i,0,'#');
    }
    for(i=0;i<sirina + 2;i++){
       mvwaddch(win,25,i,'#');
    }
    for (i=1;i<visina;i++){
        mvwaddch(win,i,30,'#');
    }
    mvwaddch(win,y,x,'O');
    for (int k=0;k<vRep;k++)
    {
        mvwaddch(win,repY[k],repX[k],'o');
    }
    mvwaddch(win,voceY,voceX,'F');
    mvwprintw(win,visina+1,0,"Score : %d",score);
    wnoutrefresh(win);
    delwin(win);
}

void Kontrole()
{
    if(_kbhit()){
    switch(_getch()){
            case 'a': if (dir == DESNO){
            }else{
                        dir = LEVO;
            }
                      break;
            case 'd': if (dir == LEVO){
            }else{
                        dir = DESNO;
            }

                      break;
            case 'w': if (dir == DOLE){
            }else{
                        dir = GORE;
            }
                      break;
            case 's': if (dir == GORE){
            }else{
                        dir = DOLE;
            }
                      break;
            case 'x': gameOver = 1;
                      break;
    }


    }
}

void Logic()
{
    int pRepX = repX[0];
    int pRepY = repY[0];
    int pRep2X, pRep2Y;
    repX[0]=x;
    repY[0]=y;
    for(int i=1;i<vRep;i++){
        pRep2X = repX[i];
        pRep2Y = repY[i];
        repX[i] = pRepX;
        repY[i] = pRepY;
        pRepX = pRep2X;
        pRepY = pRep2Y;
    }
    switch(dir){
        case LEVO:
            x--;
            break;
        case DESNO:
            x++;
            break;
        case GORE:
            y--;
            break;
        case DOLE:
            y++;
            break;

    }
    if (x > sirina - 1 ){
        x = 1;
    }
    if (x < 1){
        x = 29;
    }
    if (y>visina-1){
        y = 1;
    }
    if (y<1){
        y = 24;
    }
    if (x == voceX && y == voceY){
       score += 100;
        voce();
        vRep++;
    }
    for(int i=0;i<vRep;i++)
    {
    if (x == repX[i] && y == repY[i]){
        gameOver = 1;
    }
    }
}

void gameOverScreen(){
        int y,x;
        char mesg[] = "Game Over!";
        clear();
        refresh();
        initscr();
        noecho();
        getmaxyx(stdscr,y,x);
        WINDOW* win = newwin(y/2,x/2,y/4,x/4);
        box(win,0,0);
        attron(A_STANDOUT);
        mvprintw(y/2-1,(x-strlen(mesg))/2,"%s",mesg);
        attroff(A_STANDOUT);
        mvprintw(y/2,(x-16)/2,"Tvoj skor je %d",score);
        mvprintw(y/2+5,x/2-28,"Pritisni Enter!");
        wnoutrefresh(win);
        getch();
        delwin(win);
}

char MenuG(){
    int y,x;
    char ch;
    char opc1[] = "1)Pokretanje";
    char opc2[] = "2)Izlaz";
    char meni[] = "---Meni---";
    clear();
    refresh();
    initscr();
    raw();
    getmaxyx(stdscr,y,x);
    WINDOW* win2 = newwin(y/2,x/2,y/4,x/4);
    box(win2,0,0);
    mvprintw(y/2-3,(x-strlen(meni))/2,"%s",meni);
    mvprintw(y/2-1,(x-strlen(opc1))/2,"%s",opc1);
    mvprintw(y/2,(x-strlen(opc2))/2,"%s", opc2);
    wnoutrefresh(win2);
    ch = getch();
    delwin(win2);
    return ch;
}

void sliping(){
    if (dir == LEVO || dir == DESNO)
{
        Sleep(10);
}

        Sleep(60);

        if (dir == GORE || dir == DOLE)
 {
        Sleep(40);
 }
}

int main()
{
    char ch;
    ch = MenuG();
    switch (ch){
        case '1':
            Setup();
            while(gameOver == 0){
            Slika();
            Kontrole();
            Logic();
            sliping();
        }
            gameOverScreen();
            main();
            break;
        case '2':
            clear();
            refresh();
            return 0;
        default:
            main();
            break;
    }
}

