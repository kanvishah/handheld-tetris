/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit 16x8 LED Matrix backpacks
  ----> http://www.adafruit.com/products/2035
  ----> http://www.adafruit.com/products/2036
  ----> http://www.adafruit.com/products/2037
  ----> http://www.adafruit.com/products/2038
  ----> http://www.adafruit.com/products/2039
  ----> http://www.adafruit.com/products/2040
  ----> http://www.adafruit.com/products/2041
  ----> http://www.adafruit.com/products/2042
  ----> http://www.adafruit.com/products/2043
  ----> http://www.adafruit.com/products/2044
  ----> http://www.adafruit.com/products/2052

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

int UD = A2;
int LR = A1;
int UDval;
int LRval;

Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

void setup() {
  Serial.begin(9600);
  pinMode(UD, INPUT);
  pinMode(LR, INPUT);
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
},

Iblock[] =
{ B11110000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},

Jblock[] =
{
  B10000000,
  B11100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},

Lblock[] =
{
  B00100000,
  B11100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},

Oblock[] =
{
  B11000000,
  B11000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},

Sblock[] =
{
  B01100000,
  B11000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},

Tblock[] =
{
  B01000000,
  B11100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},

Zblock[] =
{
  B11000000,
  B01100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};


//static const uint8_t PROGMEM pieces[] = { Iblock, Jblock };

void loop() {

  boolean board[16][8];
  for (int r = 0; r < 8; r++)
    for (int c = 0; c < 16; c++)
      board[c][r] = false;

  while (!loss(board))
  {

    for (int r = 0; r < 16; r++)
    {
      for (int c = 0; c < 8; c++)
      {
        Serial.print(board[r][c]);
      }
      Serial.println();
    }
    Serial.println();

    int randNum = random(0, 7);
    char block;
    int x = 2;
    int y = 0;
    int oldX = x;
    switch (randNum)
    {
      case 0:
        {
          block = 'I';
          matrix.drawBitmap(x, y, Iblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          matrix.drawBitmap(x, y, Iblock, 8, 8, LED_OFF);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 16)
          {
            matrix.drawBitmap(x, y + 1, Iblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y + 1, Iblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
      case 1:
        {
          block = 'L';
          matrix.drawBitmap(x, y, Lblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 15)
          {
            matrix.drawBitmap(x, y, Lblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y, Lblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
      case 2:
        {
          block = 'S';
          matrix.drawBitmap(x, y, Sblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 15)
          {
            matrix.drawBitmap(x, y, Sblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y, Sblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
      case 3:
        {
          block = 'J';
          matrix.drawBitmap(x, y, Jblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 15)
          {
            matrix.drawBitmap(x, y, Jblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y, Jblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
      case 4:
        {
          block = 'O';
          x = 3;
          oldX = x;
          matrix.drawBitmap(x, y, Oblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 15)
          {
            matrix.drawBitmap(x, y, Oblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y, Oblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
      case 5:
        {
          block = 'T';
          matrix.drawBitmap(x, y, Tblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 15)
          {
            matrix.drawBitmap(x, y, Tblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y, Tblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
      case 6:
        {
          block = 'Z';
          matrix.drawBitmap(x, y, Zblock, 8, 8, LED_ON);
          matrix.writeDisplay();
          while (notFloored(board, x, y, block) && y < 15)
          {
            matrix.drawBitmap(x, y, Zblock, 8, 8, LED_OFF);
            oldX = x;
            x = moveSide(x, y, block, board);
            y++;
            matrix.drawBitmap(x, y, Zblock, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(500);
          }
          updateBoard(board, y, x, block);
          updateLED(board, matrix);
          break;
        }
    }

    for (int r = 15; r >= 0; r--)
    {
      if (ifRowFull(board, r))
      {
        boardDown(board, r);
        Serial.println(r);
        matrix.clear();
        //updateLED(board, matrix);
        for (int k = 0; k < 16; k++)
        {
          for (int j = 0; j < 8; j++)
          {
            if (board[k][j] == 1)
            {
              matrix.drawPixel(k, j, LED_ON);
            }
          }
        }
        matrix.writeDisplay();
      }
    }
  }

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x = 7; x >= -36; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("GAME OVER");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
  matrix.clear();
}

boolean ifRowFull(boolean board[16][8], int r)
{
  boolean toret = true;
  for (int c = 0; c < 8; c++)
  {
    if (!board[r][c])
      toret = false;
  }
  return toret;
}

boolean loss(boolean board[16][8])
{
  for (int c = 0; c < sizeof(board[0]); c++)
  {
    if (board[0][c])
    {
      return true;
    }
  }
  return false;
}
boolean notFloored(boolean board[16][8], int x, int y, char block)
{

  if (block == 'I')
  {
    for (int k = x; k < x + 4; k++)
    {
      if (board[y+1][k] == 1)
        return false;
    }
  }
  if (block == 'S')
  {
    Serial.println(y);
    Serial.println(x);
    if (board[y+1][x] == 1 || board[y+1][x + 1] == 1 || board[y][x + 2] == 1)
      return false;
  }
  if (block == 'Z')
  {
    Serial.println(y);
    Serial.println(x);
    if (board[y][x] == 1 || board[y + 1][x + 1] == 1 || board[y + 1][x + 2] == 1)
      return false;
  }
  if (block == 'O')
  {
    if (board[y + 2][x] == 1|| board[y + 2][x + 1] == 1)
      return false;
  }
  else
  {
    for (int k = x; k < x + 3; k++)
    {
      if (board[y + 2][k] == 1)
      {
        return false;
      }
    }
  }
  return true;

}
void updateBoard(boolean board[16][8], int y, int x, char block)
{
  //y--;
  switch (block)
  {
    case 'I':
      {
        for (int k = x; k < x + 4; k++)
        {
          board[y + 1][k] = true;
        }
        break;
      }
    case 'J':
      {
        board[y][x] = true;
        board[y + 1][x] = true;
        board[y + 1][x + 1] = true;
        board[y + 1][x + 2] = true;
        break;
      }
    case 'S':
      {
        board[y][x + 1] = true;
        board[y][x + 2] = true;
        board[y + 1][x] = true;
        board[y + 1][x + 1] = true;
        break;
      }
    case 'Z':
      {
        board[y][x] = true;
        board[y][x + 1] = true;
        board[y + 1][x + 1] = true;
        board[y + 1][x + 2] = true;
        break;
      }
    case 'O':
      {
        board[y][x] = true;
        board[y][x + 1] = true;
        board[y + 1][x] = true;
        board[y + 1][x + 1] = true;
        break;
      }
    case 'L':
      {
        board[y][x] = true;
        board[y + 1][x] = true;
        board[y + 1][x + 1] = true;
        board[y + 1][x + 2] = true;
        break;
      }
    case 'T':
      {
        board[y][x + 1] = true;
        board[y + 1][x] = true;
        board[y + 1][x + 1] = true;
        board[y + 1][x + 2] = true;
        break;
      }
  }
}

void boardDown(boolean board[16][8], int r)
{
  for (int k = r; k > 0; k--)
  {
    for (int c = 0; c < 8; c++)
    {
      board[k][c] = board[k - 1][c];
    }
  }
}

void updateLED(boolean board[16][8], Adafruit_8x16matrix matrix)
{
  matrix.clear();
  for (int k = 0; k < 16; k++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[k + 1][j])
      {
        matrix.drawPixel(k, j, LED_ON);
      }
    }
  }
  matrix.writeDisplay();
}

int moveSide(int x, int y, char block, boolean board[16][8])
{
  int lim = 5;
  if (block == 'I')
  {
    lim = 4;
  }
  if (block == 'O')
  {
    lim = 6;
  }
  if (treatValue(analogRead(LR)) == 2 && x > 0 && !board[y][x - 1])
  {
    x--;
  }
  if (treatValue(analogRead(LR)) == 4  && x < lim && !board[y][x + 1])
  {
    x++;
  }
  return x;
}

int treatValue(int data) {
  return (data * 9 / 1024);
}

