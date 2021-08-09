// Project: "Robastnost".
// Version: 0.99.

// Module: MAIN01.CPP.

// Author(s): F. Ahmedjanov.
// Description:
//    Simple program to test features of interval polinomials classes.
//

#include "std.h"
#include "polin's.cpp"
#include "util.cpp"


void main()
 {
  cout << "                     -++*** Робастность - 1 (пакет)***++-" << endl;
  TSourceFile Src("polinom.ini");
  TIntPolin Test(Src);
  cout<<"Расчет пошел..."<<endl;
  if ( Test.Stable() ) {
  cout<< "ИХП устойчив. Программа продолжает работу."<<endl;
  cout<<Test[0]<<endl;
  cout<<Test[1]<<endl;
  cout<<Test[2]<<endl;
  cout<<Test[3]<<endl;

  Tasker();
  if( FastAct != 0 )
   {
    if( FastAct == 3 ) {cout<<"Минутку..."<<endl;
			FastCycle(Test);}
    else                FastAnalyse(Test);
   }
  if( StbStor != 0 )
   {
    if( StbStor == 3 ) {cout<<"Минутку..."<<endl;
			StabCycle(Test);}
    else               StabAnalyse(Test);
   }
   }
   else cout<< "ИХП неустойчив. Программа закончила работу."<<endl;
 }
