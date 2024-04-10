#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int on = 1 ;

// function that execute when press right arrow key
void moveright(int *array , int size){
     HANDLE hOutput ;
     hOutput = GetStdHandle(STD_OUTPUT_HANDLE) ;
     COORD cursorPosition ;
     if (array[size-1] < 70){
        // remove first and second elements
        cursorPosition.X = array[0] ;
        cursorPosition.Y = 25 ;
        SetConsoleCursorPosition(hOutput , cursorPosition) ;
        cout << " " ;
        cursorPosition.X = array[1] ;
        SetConsoleCursorPosition(hOutput , cursorPosition) ;
        cout << " " ;

        // Draw the slider at new position
        for (int q =0 ; q < size ; q++){
            array[q] = array[q] + 2 ;
            cursorPosition.X = array[q] ;
            SetConsoleCursorPosition(hOutput , cursorPosition) ;
            cout << 'X' ;
        }
    }
}


// function that execute when press left arrow key
void moveleft(int *array , int size){
    HANDLE hOutput ;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD cursorPosition ;
    if (array[0] > 2){
         // remove last two elements
         cursorPosition.X = array[size-1] ;
         cursorPosition.Y = 25 ;
         SetConsoleCursorPosition(hOutput , cursorPosition) ;
         cout << " " ;
         cursorPosition.X = array[size-2] ;
         SetConsoleCursorPosition(hOutput , cursorPosition) ;
         cout << " " ;

         // Draw the slider at new position
         for (int q =0 ; q < size ; q++){
            array[q] = array[q] -2 ;
            cursorPosition.X = array[q] ;
            SetConsoleCursorPosition(hOutput , cursorPosition) ;
            cout << 'X' ;
         }
    }
}


int directionSelector = 1 ;

int main()
{
    HANDLE hOutput ;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD cursorPosition ;

    // Draw the frame of the game
    for (int i=1 ; i <= 77 ; i++){
        cursorPosition.X = i ;
        cursorPosition.Y = 0 ;
        SetConsoleCursorPosition(hOutput,cursorPosition) ;
        cout << "_" ;
    }

    for (int i=1 ; i <= 77 ; i++){
        cursorPosition.X = i ;
        cursorPosition.Y = 26 ;
        SetConsoleCursorPosition(hOutput,cursorPosition) ;
        cout << "_" ;
    }

    for (int i=1 ; i <= 26; i++){
        cursorPosition.X = 0 ;
        cursorPosition.Y = i ;
        SetConsoleCursorPosition(hOutput,cursorPosition) ;
        cout << "|" ;
    }

    for (int i=1 ; i <= 26; i++){
        cursorPosition.X = 78 ;
        cursorPosition.Y = i ;
        SetConsoleCursorPosition(hOutput,cursorPosition) ;
        cout << "|" ;
    }

    // Draw the ball collector
    for (int i =0 ; i < 3 ; i++){
        cursorPosition.Y = 23 + i ;
        cursorPosition.X = 71 ;
        for (int r=0 ; r< 6 ; r++){
            cursorPosition.X = cursorPosition.X  + 1 ;
            SetConsoleCursorPosition(hOutput , cursorPosition) ;
            cout << "*" ;
        }
        cout << endl ;
    }


    // Declare variables and arrays
    int noOfBalls = 1 ;                   // no of balls in the game
    int ballXarray[noOfBalls] = {1} ;     // array of X coordinate of balls
    int ballYarray [noOfBalls] = {10} ;   // array of Y coordinate of balls
    int ballDirection [noOfBalls] = {1} ; // array of direction of balls. If moving downwards value is 1. Else -1.
    int on = 1 ;
    int sliderLength = 4 ;                // length of the slider
    int sliderarray[sliderLength] ={2,3,4,5} ;  // array of X coordinate of slider elements
    int points = 0 ;

    // Draw the slider
    cursorPosition.X = 2 ;
    cursorPosition.Y = 25 ;
    SetConsoleCursorPosition(hOutput , cursorPosition) ;
    for (int o =0 ; o < sliderLength ; o++){
        cout << 'X' ;
    }

    // Write the points at the beginning
    cursorPosition.X = 81 ;
    cursorPosition.Y = 2 ;
    SetConsoleCursorPosition(hOutput , cursorPosition) ;
    cout << "POINTS : " << points ;


    // declare variables
    getch() ;
    int  addnew = 1 ;
    int newcomer ;
    int letnew = 0 ;

    while (on == true){

        int getBall = rand() % 7 ;  // Get a new ball randomly
        if (noOfBalls == 4){
            addnew = 0 ;
        }

        // If random integer is 0 and no of balls are less than 4, run this set of code
        // Add new balls at the beginning
        if (getBall == 0 && addnew == 1){
            noOfBalls = noOfBalls + 1 ;
            ballDirection [noOfBalls-1] = 1 ;
            ballXarray[noOfBalls-1] = 1 ;
            ballYarray [noOfBalls-1] = 10 ;
        }


        // If  no of balls are equal 4 and one ball reach the collector, run this set of code
        // Update reached ball coordinates and direction with the new ball coordinates and direction
        if ( addnew == 0 && letnew ==1 ) {
            ballDirection[newcomer] = 1 ;
            ballXarray[newcomer] = 1 ;
            ballYarray[newcomer] = 10 ;
            letnew = 0 ;
        }


        // if press left arrow key run moveleft function
        if (GetAsyncKeyState(VK_LEFT)){
            moveleft(sliderarray , sliderLength) ;
        }
        // if press right arrow key run moveright function
        if (GetAsyncKeyState(VK_RIGHT)){
            moveright(sliderarray , sliderLength) ;
        }


        for ( int h = 0 ; h < noOfBalls ; h = h + 1 ){
            // If any ball move beyond the frame end the game
            if (ballYarray[h] >= 25 ){
                on = 0 ;
                cout << "\a" ;
                Sleep(1000) ;
                system("cls") ;
                cout << "       *******GAME OVER*******\n" ;
                cout << "           TOTAL SCORE IS " << points ;    // show total points
                Sleep(2000) ;
                return 0 ;
            }

            // Update the X and Y positions of all balls and draw balls in their new position
            cursorPosition.X = ballXarray[h] + 1 ;
            cursorPosition.Y = ballYarray[h] + ballDirection[h] ;

            ballXarray[h] = cursorPosition.X ;
            ballYarray[h] = cursorPosition.Y ;

            SetConsoleCursorPosition(hOutput , cursorPosition ) ;
            cout << "O" ;


            // Check whether ball is on the slider. If ball is on the slider change the direction of the ball and move it upward.
            for (int s =0 ; s < sliderLength ; s++ ){
                if ( (sliderarray[s] == cursorPosition.X ) && ( cursorPosition.Y  >= 24)){
                    ballDirection[h] = -1 * ballDirection[h] ;
                    break ;
                }
            }

            // If any ball is move upward above 10 , change the direction
            if (ballYarray[h] < 10){
                ballDirection[h] = -1 * ballDirection[h] ;
            }

            // If ball reaches collector add 10 points and update points
            if (ballXarray[h] > 72 && ballYarray[h] > 20 ){
                newcomer = h ;
                letnew =1 ;
                points = points + 10 ;
                cursorPosition.X = 90 ;
                cursorPosition.Y = 2 ;
                SetConsoleCursorPosition(hOutput , cursorPosition) ;
                cout << points ;
            }
        }

        Sleep(500) ;

        // Clear last position of the balls
        for (int h = 0 ; h < (noOfBalls) ; h = h + 1){
                cursorPosition.X = ballXarray[h]   ;
                cursorPosition.Y = ballYarray[h]  ;
                SetConsoleCursorPosition(hOutput, cursorPosition);
                cout << " " ;
        }

}


    return 0;


}

