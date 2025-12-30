#include<math.h>
//paddles
int inp;
int pl1rt=1, pl1l=1, pl2rt=1, pl2l=1;
int speed=500; //select b/w 1 and 100

int pl1PadCen=4;//this should be b/w 1 and 6
int pl2PadCen=4;//"                         "


int
/*
_______________
pin0=6;
pin1=8;
pin2=9;
pin3=7;
pin4=13;
pin5=10;
pin6=12;
pin7=11;
_______________
**/

pinRow[8]={6,8,9,7,13,10,12,11},

/*
_______________
pinA=2;
pinB=A2;
pinC=A3;
pinD=5;
pinE=A4;
pinF=A5;
pinG=3;
pinH=4;
_______________
**/

pinCol[8]={2,A2,A3,5,A4,A5,3,4};

bool disPinRow[8], disPinCol[8];

int row=0, lineCol=1, i2=0, i1, del=0,i3=0;
int pro=1;//progress of the ball towards the left or right


int center=3, pA=45;   //center is a row number and pA is path angle

float lineRow=(float)center;
float deviation=pA/45.0;

void setup() {
  for(i1 =0; i1<=7; i1++ )
  {
    
    pinMode(pinRow[i1],OUTPUT);
    pinMode(pinCol[i1],OUTPUT);
  }
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() 
{
  
  delayMicroseconds(100);
  frameClear();
  inp = analogRead(A0); //reads input for the paddles
  checkMove();  //for the paddles
  move(); //""
  loadPaddles();
  printLine();   //pA is path angle in degrees
  //printAll();  //test to see if all leds are functioning
  loadRow();
  del+=1;
  i3++;

}

void frameClear()
{
  i2=0;
  while(i2<=7)
  {
    digitalWrite(pinRow[i2],LOW);
    digitalWrite(pinCol[i2],HIGH);
    disPinRow[i2]=false;
    disPinCol[i2]=false;
    i2++;
  }
}


void printLine()
{
  //digitalWrite(pinRow[(int)lineRow], HIGH);
  if(i3==(int)lineRow)
  {  
    disPinRow[(int)lineRow]=true;
    disPinCol[lineCol]=true;
  }
  //digitalWrite(pinCol[lineCol], LOW);
  if(del==0||del%1000==0)
  {
    lineCol=lineCol+pro;
    lineRow=lineRow+deviation;
    collisionDetection();
  }
}


void loadRow()
{
  if(disPinRow[i3]==true)
  {
    digitalWrite(pinRow[i3],HIGH);
    
    for(int i4=0; i4<8; i4++)
    {
      if(disPinCol[i4]==true)
      {
        digitalWrite(pinCol[i4], LOW);
      }
    }
  }
  if(i3==7)
  {
    i3=-1;
  }
}

void printAll()
{
  for(int i5; i5<8; i5++)
  {
    disPinRow[i5]=true;
    disPinCol[i5]=true;
  }
}

void collisionDetection()
{
  switch((int)lineRow)
  {
    case 0:
    deviation= fabs(deviation);
    Serial.println("Bottom row collision");
    break;

    case 7:
    
    deviation=-fabs(deviation);
    Serial.println("Top row collision");
    break;

    default:
    break;
  }
  switch(lineCol)
  {
    case 0:
    pro=1;
    break;

    case 6:
    if((int)lineRow==pl1PadCen||(int)lineRow==pl1PadCen-1||(int)lineRow==pl1PadCen+1)
    {
      pro=-1;
    }
    else
    {
      Serial.println("GAME OVER");
      gameOver();
    }
    break;

    default:
    break;
  }
}


void checkMove()
{
  if(inp>40&&inp<49)
  {
    //PL1 INPUTS RIGHT
    pl1rt++;
  }

  else if(inp>193&&inp<218)
  {
    //pl1 inputs left
    pl1l++;
  }

  else if(inp>370&&inp<380)
  {
    //pl 2 inputs right
    pl2rt++;
  }

  else if(inp>499&&inp<506)
  {
    //pl 2 inputs left
    pl2l++;
  }
  else if(inp>414&&inp<417)
  {
    //pl 1 and pl2 inputs right
    pl1rt++; pl2rt++;
  }
  else if(inp>533&&inp<545)
  {
    //pl1 and pl2 input left
    pl1l++; pl2l++;
  }
  else if(inp>467&&inp<473)
  {
    //pl1 inputs left and pl2 inputs right
    pl1l++; pl2rt++;
  }

  else if(inp>479&&inp<499)
  {
    //pl1 inputs right and pl2 inputs left
    pl1rt++; pl2l++;
  }
  else
  {
    pl1rt=1; pl1l=1; pl2rt=1; pl2l=1;
  }
}

void move()
{
  if(pl1rt%speed==0&&pl1PadCen<6)
  {
    Serial.println("pl1 moves left");
    pl1PadCen++;
  }
  if(pl1l%speed==0&&pl1PadCen>1)
  {
    Serial.println("pl1 moves right");
    pl1PadCen--;
  }

  if(pl2rt%speed==0&&pl2PadCen>1)
  {
    Serial.println("pl2 moves right");
    pl2PadCen++;
  }
  if(pl2l%speed==0&&pl2PadCen<6)
  {
    Serial.println("pl2 moves left");
    pl2PadCen--;
  }
  else
  {}
}

void loadPaddles()
{
  if(i3==pl1PadCen+1)
  {
    disPinCol[7]=true;
    disPinRow[pl1PadCen+1]=true;
  }
  if(i3==pl1PadCen)
  {
    disPinCol[7]=true;
    disPinRow[pl1PadCen]=true;
  }
  if(i3==pl1PadCen-1)
  {
    disPinCol[7]=true;
    disPinRow[pl1PadCen-1]=true;
  }
  
  if(i3==pl2PadCen)
  {
    disPinCol[0]=true;
    disPinRow[pl2PadCen]=true;
  }
  if(i3==pl2PadCen-1)
  {
    disPinCol[0]=true;
    disPinRow[pl2PadCen-1]=true;
  }
  /*
  if(i3==pl2PadCen+1)
  {
    disPinCol[0]=true;
    disPinRow[pl2PadCen+1]=true;
  }
  **/
}


int lightUp=0;
int iteration=0;
int ver=1;

void gameOver()
{
  while(true==true)
  {
    if(iteration==ver)
    {
      Serial.println(iteration);
      disPinRow[0]=true;
      for(int a=0; a<=7; a++)
      {
        disPinCol[a]=true;
      }
    }
    
    display_2();
  
    delayMicroseconds(100);
    
    frameClear();
    iteration++;
  }
}

void display_2()
{
  if(disPinRow[iteration]==true)
  {
    digitalWrite(pinRow[iteration],HIGH);
    
    for(int i4=0; i4<8; i4++)
    {
      if(disPinCol[i4]==true)
      {
        digitalWrite(pinCol[i4], LOW);
      }
    }
  }
  
  if(iteration==7)
  {
    iteration=-1;
  }
}