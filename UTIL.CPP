// Project: "Robastnost".
// Version: 0.99.

// Module: UTIL.CPP.

// Author(s): F.M.Akhmedjanov.
// Description: Task management.

#include <string.h>

int FirstChar(char*);
char *AfterEq(char*);

// Флаги
int FastAct = 0; // Флаг степени устойчивости
int StbStor = 0; // Флаг быстродействия

//*********************************************
// Переменные
real SetTime=0.1; // Время регулирования
real StabInd=0;   // Степень устойчивости
real Delta  =0;   // Перерегулирование
real Oscil  =0;   // Колебательность
real DampInd=0;   // Затухание за период



int StabAnalyse( TIntPolin Test )
{
real Fi=0;


if( StbStor == 1 )
     Fi = M_PI - atan(Oscil);
else
   {
     if( DampInd <= 0 || DampInd >= 1 ) {
	cout<<"Ошибка задания значения затухания за период "<<DampInd<<endl;
	return 0;
					}
     else
	Fi = M_PI - atan( 2*M_PI/(log(1-DampInd)));
   }
if( Test.StabQuality(Fi) )
   {
   cout<<"ИХП соответствует значению колебательности, соответствующую углу "<<Fi<<endl;
   return 1;
   }
else
   {
   cout<<"ИХП не соответствует значению колебательности, соответствующую углу "<<Fi<<endl;
   return 0;
   }
}

int FastAnalyse( TIntPolin Test )
{

if( FastAct == 1 ) {
   if( StabInd <= 0 ) {
	cout<<"Ошибка задания значения степени устойчивости "<<StabInd<<endl;
	return 0;
		      }
		   }
else               {
   if( Delta <= 0 || Delta >=1 ) {
	cout<<"Ошибка задания значения перерегулирования "<<Delta<<endl;
	return 0;
				 }
   if( SetTime <= 0 ) {
	cout<<"Ошибка задания значения ремени регулирования "<<SetTime<<endl;
	return 0;
		      }
   StabInd = log(1/Delta)/SetTime;
		   }
if( Test.StabStore( StabInd ) )
   {
   cout<<"ИХП соответствует значению степени устойчивости соответствующую "<<StabInd<<endl;
   return 1;
   }
else
   {
   cout<<"ИХП не соответствует значению степени устойчивости соответствующую "<<StabInd<<endl;
   return 0;
   }
}


void StabCycle( TIntPolin Test )
{
real Stab = 0;
real StabUp = 1.572;
real StabDown = 3.139;
real StabPrec = 0.01;

word ItrCount=0;

while( (StabDown-StabUp)/2 > StabPrec ) {
  ItrCount++;
  Stab = (StabDown+StabUp)/2;
  if( Test.StabQuality(Stab))
     StabUp = Stab;
  else
     StabDown = Stab;
					 }
  real mStab=atan(M_PI-Stab);
  cout<<"ИХП имеет быстродействие соответствующее углу "<<Stab<<endl;
  cout<<"ИХП имеет колебательность "<<mStab<<endl;
  cout<<"Подсчитано за "<<ItrCount<<" итераций."<<endl;
}


void FastCycle( TIntPolin Test )
{
 real Fast = 0.00001;
 real FastStep = 2;
 real FastPrec = 0.001;

 word ItrCount = 0;

 while( FastStep >= FastPrec ) {
    ItrCount++;
    if( Test.StabStore( Fast ))
       Fast += FastStep;
    else
       {
       FastStep = FastStep/2;
       Fast -= FastStep;
       }                       }
  cout<<"ИХП соответствует степени устойчивости "<<Fast<<endl;
  cout<<"Подсчитано за "<<ItrCount<<" итераций."<<endl;

}


void Tasker( void )
{
 char *tasker[7] = { "FastAct", "StbStor", "SetTime",
		     "StabInd", "Delta", "Oscil", "DampInd" };
 char *lstr;

 ifstream fin("task.ini");

 while( !fin.eof() ){
   fin.getline( lstr,80 );
   if(FirstChar( lstr ))
     { for( int k=0; k<7; k++ ) {
	 if( strspn( lstr, tasker[k])== strlen(tasker[k]))
	    {
	    switch( k ){
	    case 0: FastAct = atoi(AfterEq(lstr)); break;
	    case 1: StbStor = atoi(AfterEq(lstr)); break;
	    case 2: SetTime = atof(AfterEq(lstr)); break;
	    case 3: StabInd = atof(AfterEq(lstr)); break;
	    case 4: Delta   = atof(AfterEq(lstr)); break;
	    case 5: Oscil   = atof(AfterEq(lstr)); break;
	    case 6: DampInd = atof(AfterEq(lstr)); break;
		       };
	    };                  };
		    };
};

}


int FirstChar( char* Line )
{
char f;
f=Line[0];
if( f=='#'|| f==';') return(0);
else return(1);

}


char* AfterEq( char *Sour )
{
int m=strlen(Sour);
int i=0;
for( i=0; i<m; i++ )
  if( Sour[i]=='=') break;
int h=m-i;
char *Ret;
Ret=new char[h];
for( int j=0; j<=h; j++) Ret[j]=Sour[j+i+1];
return Ret;
}

