// Project: "Robastnost".
// Version: 0.99.

// Module: UTIL.CPP.

// Author(s): F.M.Akhmedjanov.
// Description: Task management.

#include <string.h>

int FirstChar(char*);
char *AfterEq(char*);

// �����
int FastAct = 0; // ���� �⥯��� ��⮩稢���
int StbStor = 0; // ���� ����த���⢨�

//*********************************************
// ��६����
real SetTime=0.1; // �६� ॣ㫨஢����
real StabInd=0;   // �⥯��� ��⮩稢���
real Delta  =0;   // ���ॣ㫨஢����
real Oscil  =0;   // ������⥫쭮���
real DampInd=0;   // ����堭�� �� ��ਮ�



int StabAnalyse( TIntPolin Test )
{
real Fi=0;


if( StbStor == 1 )
     Fi = M_PI - atan(Oscil);
else
   {
     if( DampInd <= 0 || DampInd >= 1 ) {
	cout<<"�訡�� ������� ���祭�� ����堭�� �� ��ਮ� "<<DampInd<<endl;
	return 0;
					}
     else
	Fi = M_PI - atan( 2*M_PI/(log(1-DampInd)));
   }
if( Test.StabQuality(Fi) )
   {
   cout<<"��� ᮮ⢥����� ���祭�� ������⥫쭮��, ᮮ⢥�������� 㣫� "<<Fi<<endl;
   return 1;
   }
else
   {
   cout<<"��� �� ᮮ⢥����� ���祭�� ������⥫쭮��, ᮮ⢥�������� 㣫� "<<Fi<<endl;
   return 0;
   }
}

int FastAnalyse( TIntPolin Test )
{

if( FastAct == 1 ) {
   if( StabInd <= 0 ) {
	cout<<"�訡�� ������� ���祭�� �⥯��� ��⮩稢��� "<<StabInd<<endl;
	return 0;
		      }
		   }
else               {
   if( Delta <= 0 || Delta >=1 ) {
	cout<<"�訡�� ������� ���祭�� ���ॣ㫨஢���� "<<Delta<<endl;
	return 0;
				 }
   if( SetTime <= 0 ) {
	cout<<"�訡�� ������� ���祭�� ६��� ॣ㫨஢���� "<<SetTime<<endl;
	return 0;
		      }
   StabInd = log(1/Delta)/SetTime;
		   }
if( Test.StabStore( StabInd ) )
   {
   cout<<"��� ᮮ⢥����� ���祭�� �⥯��� ��⮩稢��� ᮮ⢥�������� "<<StabInd<<endl;
   return 1;
   }
else
   {
   cout<<"��� �� ᮮ⢥����� ���祭�� �⥯��� ��⮩稢��� ᮮ⢥�������� "<<StabInd<<endl;
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
  cout<<"��� ����� ����த���⢨� ᮮ⢥�����饥 㣫� "<<Stab<<endl;
  cout<<"��� ����� ������⥫쭮��� "<<mStab<<endl;
  cout<<"�����⠭� �� "<<ItrCount<<" ���権."<<endl;
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
  cout<<"��� ᮮ⢥����� �⥯��� ��⮩稢��� "<<Fast<<endl;
  cout<<"�����⠭� �� "<<ItrCount<<" ���権."<<endl;

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

