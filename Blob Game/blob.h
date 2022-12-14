#include <iostream>

using namespace std;

class Blob 
{  
   friend ostream& operator<<(ostream&, Blob);
   //+ overload is in driver

   public:
      Blob(); 
      Blob(char c);
      Blob(int h, int p, char c);
      void Spawn();
      void MoveNorth();
      void MoveSouth();
      void MoveEast();
      void MoveWest();
      void Attack();
      int GetXCoord();
      void SetXCoord(int x);
      int GetYCoord();
      void SetYCoord(int y);
      char GetColor();
      int GetHealth();
      void SetHealth(int h);
      int GetPower();
      void SetIsAlive(bool b);
      bool GetIsAlive();

   private: 
      int Health; 
      int Power;
      char Color; 
      int xCoord;
      int yCoord;
      bool isAlive; 

};
