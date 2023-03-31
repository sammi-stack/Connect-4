#include <iostream>
#include <stdlib.h> //needed for rand
#include <windows.h>

#define HEIGHT 6
#define WIDTH 7
using namespace std;
void draw_board();
void player_movement(int player);
bool check_for_winner(int x, int y, int player);
bool check_diagonal_combo_SW_NE(int x, int y, int player);
bool check_diagonal_combo_NW_SE(int x, int y, int player);
bool check_vertical_combo(int x, int y, int player);
bool check_horizontal_combo(int x, int y, int player);

int board_info[HEIGHT][WIDTH] = {{0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0}};
int LastMoveX, LastMoveY;
int main()
{
   int counter = 0;
   bool winner = false;
   srand(GetTickCount());   //sets randomizer as time *unique*
   cout << "Please select a number from 1-7" << endl;
   cout << "| 1| 2| 3| 4| 5| 6| 7" << endl;
   cout << "---------------------";
   draw_board();
   for (int i = 0; i < 21; i++)
   {
      player_movement(1);
      draw_board();
      winner = check_for_winner(LastMoveX, LastMoveY, 1);
      if (winner)
      {
         cout << "\nYou Win" << endl;
         break;
      }
      player_movement(2);
      draw_board();
      winner = check_for_winner(LastMoveX, LastMoveY, 2);
      if (winner)
      {
         cout << "\nYou Win" << endl;
         break;
      }
   }
   system("PAUSE");
   return 0;
}
void draw_board()
{
   cout << endl;
   for (int y = 0; y < HEIGHT; y++)
   {
      for (int x = 0; x < WIDTH; x++)
      {
         cout << "| ";
         if (board_info[y][x] == 0) cout << " ";
         else if (board_info[y][x] == 1) cout << "X";
         else if (board_info[y][x] == 2) cout << "O";
      }
      cout << "\n---------------------" << endl;
   }
}
void player_movement(int player)
{
   int choice;
   cout << "\nPlayer" << player << ", please select a number from 1 - 7: ";
   cin >> choice;
   //Error Checking
   if (cin.fail())
      cout << "Error!";
      exit(1);
   }
   while (choice > WIDTH || choice <=0)
   {
      cout << "\nPlease select again: ";
      cin >> choice;
   }
    int number = 0;
    while (board_info[(HEIGHT-1)-number][(choice-1)] != 0)
   {
      number++;
      if (number > (HEIGHT-1))
      {
         cout << "\nPlease select again: ";
         cin >> choice;
         number = 0;  //You must reset the number else it will start at the beginning of the array
      }
   };
   board_info[(HEIGHT-1)-number][choice-1] = player;
   LastMoveY = (HEIGHT-1)-number;
   LastMoveX = choice-1;
}
bool check_for_winner(int x, int y, int player)
{
   bool winner;

   if (check_diagonal_combo_SW_NE(x,y,player)) return true;
   else if (check_diagonal_combo_NW_SE(x,y,player)) return true;
   else if (check_vertical_combo(x,y,player)) return true;
   else if (check_horizontal_combo(x,y,player)) return true;
   else return false;
}
bool check_diagonal_combo_SW_NE(int x, int y, int player)
{
   int score = 1;
   int count = 1;

   while((y-count >= 0) && (x+count < WIDTH))
   {
      if (board_info[y-count][x+count] == player)  //Check SW to NE
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   count = 1;
   while((y+count < HEIGHT) && (x-count >=0))
   {
      if (board_info[y+count][x-count] == player)  //Check NE to SW
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   if (score == 4) return true;
   else return false;
}
bool check_diagonal_combo_NW_SE(int x, int y, int player)
{
   int score = 1;
   int count = 1;
   while((y+count >= 0) && (x+count < WIDTH))
   {
      if (board_info[y+count][x+count] == player)  //Check NW to SE
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   count = 1;
   while((y-count < HEIGHT) && (x-count >=0))
   {
      if (board_info[y-count][x-count] == player)  //Check SE to NW
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   if (score == 4) return true;
   else return false;
}
bool check_vertical_combo(int x, int y, int player)
{
   int score = 1;
   int count = 1;
   while(y+count >= 0 && y+count < HEIGHT)
   {
      if (board_info[y+count][x] == player)  //Check Down
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   if (score == 4) return true;
   else return false;
}
bool check_horizontal_combo(int x, int y, int player)
{
   int score = 1;
   int count = 1;
   while((x+count >= 0) && (x+count < WIDTH))
   {
      if (board_info[y][x+count] == player)  //Check Left
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   count = 1;
   while((x-count < WIDTH) && (x-count >=0))
   {
      if (board_info[y][x-count] == player)  //Check Right
      {
         score++;
         count++;
      }
      else break;  //If no combo is detected break from the loop
   }
   if (score == 4) return true;
   else return false;
}
