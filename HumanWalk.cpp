#include<iostream>
#include<cstdlib>
#include<cstdio>
#define OBJECT_NUMBER 3

using namespace std;



struct Position{
	int x,y;
};

struct stack{
	int x;
	int y;
	
};


class Room{
	public:
	int map[10][10];
	friend class Object;
	friend class Human;
};



class Object{
	public:
	char name[20];
	int len;
	Position *ObjectPos;
	friend class Human;
	void Set(Room &room);
	
};

void Object::Set(Room &room){
	
	cout<<"Please Input the Object characteristic :";
	gets(name);
	cout<<endl;
	
	cout<<"Please Input the Object len :";
	cin>>len;
	cout<<endl;
	
	ObjectPos = (struct Position*)malloc(sizeof(struct Position)*(len));
	
	cout<<"Please Input the Object Position :";

	for(int i = 0; i < len; i++){
		cout<<"X:";
	    cin>>ObjectPos[i].x;
	    cout<<endl;
	    cout<<"Y:";
	    cin>>ObjectPos[i].y;
	    cout<<endl;
    }
	 
	for(int i = 0; i < 10; i++)
	 for(int j = 0; j < 10; j++)room.map[i][j] = 0;
	 
	 
	for(int i = 0; i < 10; i++)
	 for(int j = 0; j < 10; j++)
	   for(int k = 0; k < len; k++){
	   	   if( (i == ObjectPos[k].x) && (j == ObjectPos[k].y) )room.map[i][j] = 1;
	   	   
	   }
    
}

struct memory{
	char name[20];
	int x;
	int y;
};



class Human{
	public:
	int StartX;
	int StartY;
	int stackIndex;
	int FindFlag;
	int MinStep;
	bool visit[10][10];
	enum direction{foward = -1,right = 1,back = 1,left = -1};
    struct stack Trace[100];
	void Set(int x,int y,int MinStep);
	void Walk(Room &room,int POS_X,int POS_Y);
	memory remember[OBJECT_NUMBER];
	
	
};

void Human::Set(int x,int y,int MinStep){
	StartX = x;
	StartY = y;
	stackIndex = 0;
	for(int i = 0; i < 100; i++){
		Trace[i].x = 0;
		Trace[i].y = 0;
	}
	FindFlag = 0;
	this->MinStep = MinStep;
}

void Human::Walk(Room &room,int POS_X,int POS_Y){
	
	int Next_X;
	int Next_Y;
	
	
	//cout<<stackIndex<<" X: "<<POS_X<<" Y: "<<POS_Y<<endl;
	/*for(int i = 0; i < stackIndex; i++)
    {
      cout<<i<<" : ";
      cout<<" X: "<<Human::Trace[i].x<<endl;
      cout<<" Y: "<<Human::Trace[i].y<<endl;
     
    }
	
	cout<<endl;
      cout<<endl;
      cout<<endl;
	getchar();*/
	
	
	
	Human::Trace[stackIndex].x = POS_X;
	Human::Trace[stackIndex++].y = POS_Y;
	
	if(POS_X+foward >= 0 && FindFlag!=1 && visit[POS_X+foward][POS_Y] ==false)//up
	{
		Next_X = POS_X+foward; 
	    Next_Y = POS_Y;
	    visit[Next_X][Next_Y] = true;
	    
		if(room.map[Next_X][Next_Y] == 1){
	         FindFlag = 1;
	  		 return;
          }
		
		room.map[Next_X][Next_Y] = 2;
		Human::Walk(room,Next_X,Next_Y);
	    if(FindFlag == 1)return;
	
	   
	   
	   visit[Next_X][Next_Y] = false;	
	   Human::Trace[--stackIndex].x = 0;	
	   Human::Trace[stackIndex].y = 0;	
//		return;
	}

	
	if(POS_Y+left >= 0 && FindFlag!=1 && visit[POS_X][POS_Y+left] ==false)//down
	{
	  	Next_X = POS_X; 
	    Next_Y = POS_Y+left;
		visit[Next_X][Next_Y] = true;
		
		 if(room.map[Next_X][Next_Y] == 1){
	         FindFlag = 1;
	  		 return;
          }
		
		
		room.map[Next_X][Next_Y] = 2;
		Human::Walk(room,Next_X,Next_Y);
	   
	    if(FindFlag == 1)return;
	
	
	   
	   visit[Next_X][Next_Y] = false;		
	   Human::Trace[--stackIndex].x = 0;	
	   Human::Trace[stackIndex].y = 0;	
//		return;
	}
	
	
	if(POS_X+back < 10 && FindFlag!=1 && visit[POS_X+back][POS_Y] ==false)//right
	{
       	Next_X = POS_X+back; 
	    Next_Y = POS_Y;
	    visit[Next_X][Next_Y] = true;
		
		if(room.map[Next_X][Next_Y] == 1){
	         FindFlag = 1;
	  		 return;
        }
		
		
		
		room.map[Next_X][Next_Y] = 2;
		Human::Walk(room,Next_X,Next_Y);	
	   
	     if(FindFlag == 1)return;
	
	   
	   visit[Next_X][Next_Y] = false;
	   Human::Trace[--stackIndex].x = 0;	
	   Human::Trace[stackIndex].y = 0;	
	   
//		return;
	}


	
	if(POS_Y+right < 10 && FindFlag!=1 && visit[POS_X][POS_Y+right] ==false)//left
	{
	    Next_X = POS_X; 
	    Next_Y = POS_Y+right;
	    visit[Next_X][Next_Y] = true;
		
		if(room.map[Next_X][Next_Y] == 1){
	         FindFlag = 1;
	  		 return;
        }
		
	   room.map[Next_X][Next_Y] = 2;
	   Human::Walk(room,Next_X,Next_Y);	
	   if(FindFlag == 1)return;
	
	   
	   
	   visit[Next_X][Next_Y] = false;
	   Human::Trace[--stackIndex].x = 0;	
	   Human::Trace[stackIndex].y = 0;	
	   
//		return;
	}

	
	if( (POS_X+foward < 0 || POS_X+back >= 10 || POS_Y+right >= 10 || POS_Y+left < 0 && FindFlag!=1)
	    || visit[POS_X+foward] || visit[POS_X+back] || visit[POS_Y+right] || visit[POS_Y+left]
	  ){
	   return;
		
	}
	
	
	
}


int main()
{
		
	
  Room bedroom;
  Human Tom;
  Object Obj[OBJECT_NUMBER];
  
  Obj[0].Set(bedroom);
  Tom.Set(4,4);
  Tom.Walk(bedroom,Tom.StartX,Tom.StartY);
  
   for(int i = 0; i < Tom.stackIndex; i++)
  			{	
  	 	  	  cout<<i<<" : ";
     	  	  cout<<" X: "<<Tom.Trace[i].x<<endl;
     	  	  cout<<" Y: "<<Tom.Trace[i].y<<endl;
     	  	  cout<<endl;
  			}
  			cout<<"Total step :"<<Tom.stackIndex<<endl;
 
  
	return 0;
}
