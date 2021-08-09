// Project: "Robastnost".
// Version: 0.99.

// Module: POLIN'S.CPP.

// Author(s): F. Akhmedjanov, A.V. Zinoviev.
// Description: Defines classes to operate with __________.

//#include "std.h"

real const w1Step = 0.1;   // The value of w's step when Ach compute
real const w2Step = 0.001; // The value of w's step when Vch compute
real const tStep = 0.1;

struct Srur
 {
  TInterval Arg;
  TInterval Phase;
  int Limit;
  int Cons;
  real Freq;
 };

dword iFact( word k ) // Redefine & rewrite !!!
{
 long l=1, i=1;
 if (k!=0) for(i=1; i<=k; i++) l*=i;
 return l;
};


 TKharPolins::TKharPolins(TIntPolin& Src)
  {
   byte LimPtr=0x0C;
   PKharPol[0]=new TCharPolin(Power(Src));
   PKharPol[1]=new TCharPolin(Power(Src));
   PKharPol[2]=new TCharPolin(Power(Src));
   PKharPol[3]=new TCharPolin(Power(Src));
   for(int PCt=Power(Src);PCt>=0;PCt--)
    {
     PKharPol[0]->operator[](PCt)=Src.operator[](PCt)[(LimPtr&1)];
     PKharPol[1]->operator[](PCt)=Src.operator[](PCt)[(LimPtr&2)>>1];
     PKharPol[2]->operator[](PCt)=Src.operator[](PCt)[(LimPtr&4)>>2];
     PKharPol[3]->operator[](PCt)=Src.operator[](PCt)[(LimPtr&8)>>3];
     LimPtr=((LimPtr<<1)|((LimPtr&8)>>3))&0x0F;
    };
  };

 boolean TKharPolins::Stable()
  {
   boolean Result=TRUE;
   for(byte PCt=0;PCt<4;PCt++)
    Result=Result&&(PKharPol[PCt]->Stable());
   return Result;
  };

 TIntPolin::TIntPolin(TTransmFunc& TrSrc)
  :TPolinome<TInterval>(max(Power(TrSrc.PolNumerator()),Power(TrSrc.PolDenominator())))
  {
   this->TVector<TInterval>::operator=(TrSrc.PolNumerator()+TrSrc.PolDenominator());
  };

 boolean TIntPolin::Stable()
  {
   return TKharPolins(*this).Stable();
  };

 boolean TCharPolin::Stable()
  {
   boolean Result=TRUE;
   // Метод Раусса
   int n1=0, n2=0, n3=0, i=0, j=0, k=0;
   TMatrix<real> art(30,60);
//   TVector<real> arr(NumElem+1);
   TCharPolin arr(NumElem+1);
   n1=(int)( NumElem/2 );
   n3 = NumElem-1;
   n2 = n1 + 1;
   k=NumElem - 1;
   for( i=0; i < n2; i++ )
     for( j=0; j<2; j++ )
      {
       if ( k < 0 )
         art[i][j] = 0;
        else
         art[i][j] = (*this)[k];
       k--;
      };
   for( k = 2; k< n3; k++ )
    {
     arr[k-2] = art[0][k-2]/art[0][k-1];
      for( i=0; i<n2; i++ )
       {
        if ( i>n1 )
          art[i][k] = 0;
         else
          {
	   art[i][k] = art[i+1][k-2] - art[i+1][k-1]*arr[k-2];
	   if ( art[0][k]<=0 ) Result = FALSE;
	  };
       };
    };
   return Result;
  };

TInterval TIntComplex::MakePhase( )
{

if( Re.DownLimit() >= 0 && Im.DownLimit() >= 0 ) {      // 1-й
return TInterval( atan( Im.DownLimit()/Re.UpLimit()),
                  atan( Im.UpLimit()/Re.DownLimit() ) ) ;
					       }      // квадрант

if( Re.DownLimit() >= 0 && Im.UpLimit() <= 0 ) {     // 4-й
return TInterval( 2*M_PI + atan( Im.DownLimit()/Re.DownLimit() ),
                  2*M_PI + atan( Im.UpLimit()/Re.UpLimit() ) );
					       }     // квадрант

if( Re.UpLimit() <= 0 && Im.DownLimit() >= 0 ) {     // 2-й
return TInterval( M_PI + atan( Im.UpLimit()/Re.UpLimit() ),
		  M_PI + atan( Im.DownLimit()/Re.DownLimit() ) );
						     }     // квадрант

if( Re.UpLimit() <= 0 && Im.UpLimit() <= 0 ) {    // 3-й
return TInterval( M_PI + atan( Im.UpLimit()/Re.DownLimit() ),
		  M_PI + atan( Im.DownLimit()/Re.UpLimit() ) );
                                                   }    // квадрант

if( Im.DownLimit() >= 0 ) {                            // Пересечение
return TInterval( atan( Im.DownLimit()/Re.UpLimit() ),
		  M_PI + atan( Im.DownLimit()/Re.DownLimit() ) );
			     }                            // 1 и 2
                                                          // квадрантов

if( Re.DownLimit() >= 0 ) {                            // Пересечение
return TInterval( 2*M_PI + atan( Im.DownLimit()/Re.DownLimit() ),
		  2*M_PI + atan( Im.UpLimit()/Re.DownLimit() ) );
                          }                            // 1 и 4
							  // квaдрантов

if( Re.UpLimit() <= 0 ) {                           // Пересечение
return TInterval( M_PI + atan( Im.UpLimit()/Re.UpLimit() ),
		  M_PI + atan( Im.DownLimit()/Re.UpLimit() ) );
                           }                           // 2 и 3
                                                       // квадрантов

if( Im.UpLimit() <= 0 ) {                           // Пересечение
return TInterval( M_PI + atan( Im.UpLimit()/Re.DownLimit() ),
		  2*M_PI + atan( Im.UpLimit()/Re.UpLimit() ) );
			   }                           // 3 и 4
						       // квадрантов

else {
return TInterval( 0, 2*M_PI );
     }

}

TInterval TIntComplex::MakeAmpl( )
{

real dqremax=0, dqremin=0, dqimmax=0, dqimmin=0;

if( fabs( Re.DownLimit() ) > fabs( Re.UpLimit() ) ) {  dqremax = Re.DownLimit();
    if( Re.DownLimit() < 0 || Re.UpLimit() > 0 ) dqremin = Re.UpLimit();
    else                       dqremin = 0;
				  }
else                              {  dqremax = Re.UpLimit();
    if( Re.DownLimit() < 0 || Re.UpLimit() > 0 ) dqremin = Re.DownLimit();
    else                       dqremin = 0;
				  }

if( fabs( Im.DownLimit() ) > fabs( Im.UpLimit() ) ) {  dqimmax = Im.DownLimit();
    if( Im.DownLimit() < 0 || Im.UpLimit() > 0 ) dqimmin = Im.UpLimit();
    else                       dqimmin = 0;
				  }
else                              {  dqimmax = Im.UpLimit();
    if( Im.DownLimit() < 0 || Im.UpLimit() > 0 ) dqimmin = Im.DownLimit();
    else                       dqimmin = 0;
				  }

return TInterval( sqrt( dqimmin*dqimmin + dqremin*dqremin), sqrt( dqremax*dqremax+dqimmax*dqimmax) );
}

void TTransmFunc::AchFch( int filer )
{
TInterval argcoor;
TInterval fascoor;
Srur structfull[6];
TIntComplex Arg1, Arg2;
TInterval fasenum, argnum;
TInterval faseden, argden;
real w=0.1;
int Troubl = 0;
int ifonedown=0;
int ifoneup =0;
int CountCons = 0;

ofstream out1( "argument.out" );
ofstream out2( "fase.out" );
while( Troubl<20 ){
//  Обрабатываем числитель
Arg1 = Numerator.QuadroInt( w );
argnum = Arg1.MakeAmpl();
fasenum = Arg1.MakePhase();
//  Обрабатываем знаменатель
Arg2 = Denominator.QuadroInt(w);
argden = Arg2.MakeAmpl();
faseden = Arg2.MakePhase();
//  Вычисление аргумента и фазы
argcoor = argnum/argden;
fascoor = fasenum - faseden;
if( filer ) {
out1<<w<<"  "<<argcoor.DownLimit()<<"  "<<argcoor.UpLimit()<<endl;
out2<<w<<"  "<<fascoor.DownLimit()<<"  "<<fascoor.UpLimit()<<endl;
	    }

w = w + w1Step;
cout<<w<<"\b\b\b\b\b\b";

if(ifonedown==1){ //  если выше 1
  if( argcoor.DownLimit()<=1){
    structfull[CountCons].Arg = argcoor;
    structfull[CountCons].Limit = 0;
    structfull[CountCons].Cons    = 1;
    structfull[CountCons].Phase = fascoor;
    structfull[CountCons].Freq = w;
    CountCons++; ifonedown=0;}
                }
else         {
  if( argcoor.DownLimit()>=1){
    structfull[CountCons].Arg = argcoor;
    structfull[CountCons].Limit = 0;
    structfull[CountCons].Cons    = 0;
    structfull[CountCons].Phase = fascoor;
    structfull[CountCons].Freq = w;
    CountCons++; ifonedown=1;}
             }
if(ifoneup==1){
  if( argcoor.UpLimit()<=1){
    structfull[CountCons].Arg = argcoor;
    structfull[CountCons].Limit = 1;
    structfull[CountCons].Cons    = 1;
    structfull[CountCons].Phase = fascoor;
    structfull[CountCons].Freq = w;
    CountCons++;ifoneup=0; }
           }
else{          //  если ниже 1
  if( argcoor.UpLimit()>=1 ) {
    structfull[CountCons].Arg = argcoor;
    structfull[CountCons].Limit = 1;
    structfull[CountCons].Cons = 0;
    structfull[CountCons].Phase = fascoor;
    structfull[CountCons].Freq = w;
    CountCons++;ifoneup=1;   }
    }

if( fabs( argcoor.DownLimit())<=0.0001 && fabs( argcoor.UpLimit())<= 0.0001 ) Troubl ++;
else Troubl = 0;
if( w>200 ) break;


}
cout<<endl;
if(!CountCons){
ofstream out6("result.res");
for( int i=0; i<CountCons; i++){
  out6<<"****- "<<i<<" -****"<<endl;
  out6<<structfull[i].Freq<<endl;
  out6<<structfull[i].Arg.DownLimit()<<" "<<structfull[i].Phase.DownLimit()<<endl;
  out6<<structfull[i].Arg.UpLimit()<<" "<<structfull[i].Phase.UpLimit()<<endl;
  out6<<structfull[i].Cons<<" "<<structfull[i].Limit<<endl;
  out6<<"********----*********"<<endl;
			   }
	      }

}


TInterval TTransmFunc::RePartPro( real w )
{
TIntComplex Num, Den;
int i=0, j=0, k=0, l=0;
TInterval f, d;
real Re1[2]={ 0, 0 };
real Re2[2]={ 0, 0 };
real Im1[2]={ 0, 0};
real Im2[2]={ 0, 0 };
real min = 10;
real max = -10;
real m=0;

Num = Numerator.QuadroInt( w );
Den = Denominator.QuadroInt( w );

Re1[0]=Num.Real().DownLimit();
Re1[1]=Num.Real().UpLimit();
Re2[0]=Den.Real().DownLimit();
Re2[1]=Den.Real().UpLimit();

Im1[0]=Num.Imag().DownLimit();
Im1[1]=Num.Imag().UpLimit();
Im2[0]=Den.Imag().DownLimit();
Im2[1]=Den.Imag().UpLimit();

for( i=0; i<2; i++ ){
for( j=0; j<2; j++ ){
for( k=0; k<2; k++ ){
for( l=0; l<2; l++ ){
  m=(Re1[i]*Re2[j]+Im1[k]*Im2[l])/(Re2[j]*Re2[j]+Im2[l]*Im2[l]);
  if( max < m ) max = m;
  if( min > m ) min = m;
		    }
		    }
		    }
		    }

return TInterval( min, max );
}


void TTransmFunc::VchPer( void )
{
TInterval recoor;
real w=0.0001;
int Troubl = 0;

ofstream out1( "repart.out" );

while( w<10 ){

recoor = RePartPro( w );

out1<<w<<"  "<<recoor.DownLimit()<<"  "<<recoor.UpLimit()<<endl;

w = w + w2Step;
cout<<w<<"\b\b\b\b\b\b\b";

if( fabs( recoor.DownLimit())<=0.001 && fabs( recoor.UpLimit())<= 0.001 ) Troubl ++;
if( Troubl > 10 ) break;
else Troubl = 0;

}
cout<<endl;
Integral();
}


void TTransmFunc::Integral( void )
{
real t=0.001, n;
real ws=0;
TInterval pFunk;
TInterval incoor, recoor;
real recoor1, recoor2;
TInterval pOld;
TInterval Delta;
int Troubl=0;

ofstream out1( "integ.out" );
ifstream in( "repart.out" );
in.seekg( 0, ios::beg );


while( t<8 ){   // Цикл по времени

 incoor=TInterval( 0, 0);
 pOld = TInterval( 0, 0);
 ws = 0.0001;
 in.seekg( 0, ios::beg );
 while( ws <= 10 ){
   in>>recoor1;
   in>>recoor1;
   in>>recoor2;
   recoor = TInterval( recoor1, recoor2 );
   pFunk = recoor*(sin(ws*t)/ws);
   Delta = pOld;
   Delta +=pFunk;
   Delta = Delta*(w2Step/M_PI);
   pOld = pFunk;
   incoor=incoor + Delta;
   ws = ws + w2Step;

   if( fabs( Delta.DownLimit() ) <= 0.000001 && fabs( Delta.UpLimit() ) <= 0.000001 && ws > 1 ) {
	       Troubl++;
	       if( Troubl > 26 ) break;                                     }
   else  Troubl = 0;
			      }

  out1<<t<<"  "<<incoor.DownLimit()<<"  "<< incoor.UpLimit()<<endl;

  t=t+tStep;
  cout<<incoor.DownLimit()<<"     "<<incoor.UpLimit()<<"  " <<t<<"  "<<ws<<endl;
			     }
cout<<endl<<"Кончено."<<endl;

}


TIntComplex TIntPolin::QuadroInt ( real w )
{
   int i=0;
   real q=1;
   real Re1=0, Re2=0, Im1=0, Im2=0;

   for( i=0; i<NumElem ; i++ ) {
      if(i&1){
      if(i&2){
 		  Im1 = Im1 - (*this)[i].DownLimit()*q;
		  Im2 = Im2 - (*this)[i].UpLimit()*q;
	     }
      else   {
		  Im1 = Im1 + (*this)[i].UpLimit()*q;
		  Im2 = Im2 + (*this)[i].DownLimit()*q;
	     }
             }
      else   {
      if(i&2){
		  Re1 = Re1 - (*this)[i].DownLimit()*q;
		  Re2 = Re2 - (*this)[i].UpLimit()*q;
	     }
      else   {
		  Re1 = Re1 + (*this)[i].UpLimit()*q;
		  Re2 = Re2 + (*this)[i].DownLimit()*q;
	     }
             }
   q=q*w;
   }
   return TIntComplex( TInterval( Re1, Re2 ), TInterval( Im1, Im2 ) );
}



boolean TIntPolin::StabStore( real Etta )
 {
  boolean Result = TRUE;
  long h=0, k=0;
  real l;
  int m=0,j=0;
  long i=0;

//  Получаем полином границы
//  сдвигаем
//  проверяем устойчивость

  k=NumElem;
  TCharPolin Qual(k-1);
  l = pow(2, (real)k) + 1;
  while(i<l)
   {
    m=1;
    for( j=0; j<k; j++ )
     {
      if( h & m )
       Qual[j]=(*this)[j].UpLimit();
      else
       Qual[j]=(*this)[j].DownLimit();
      m=m<<1;
     };
    if(!Qual.ShiftPol(Etta).Stable()){ Result=FALSE; return Result;}
    h++;
    i++;
   };
  return Result;
 };

boolean TIntPolin::StabQuality( real Angle )
{
boolean Result = TRUE;
TCharPolin Uder(4);
real porks=0, delta=1, ResHoles=0;
int Ups=0, Downs=0;

if( Angle <= M_PI/2 || Angle > M_PI )
cout<<"Unfortunately, this angle cannot be proceed..."<<endl;

for( int i=0; i<15; i++) {
  for( int j=int(i/2)+1; j<i; j++){
     porks = (M_PI*j/i);
     if( porks > Angle )
       if( (porks - Angle) < delta ) { delta = porks - Angle;
				       ResHoles = porks;
				       Ups = j; Downs = i; }
				  }
			 }
if( Ups!=0 ) Result=Soh( Ups, Downs, Angle );
else cout<<"Unfortunately, this angle cannot be proceed..."<<endl;
  cout<<Ups<<"  "<<Downs<<"  "<<Angle<<endl;
  return Result;            // Возвращаем результат
 };

#include"soh.cpp"


TCharPolin TCharPolin::ShiftPol( real Etta )
 {
  int a1, j, a3;
  real kl;
  TCharPolin Result(j=NumElem-1);
  for( int i=0; i<NumElem; i++ )
   {
    Result[j] = 0;
    for( int l = 0; l <= i; l++ )
     {
      a1 = (int)pow( -1, i-l );
      a3 = ( iFact( NumElem-l-1 )/(iFact(i-l)*iFact(NumElem-i-1)));
      Result[j] = Result[j] + (*this)[NumElem-l-1]*a1*a3*pow(Etta, i-l );
     };
    j--;
   };
  return Result;
 };

TCharPolin TCharPolin::RotatePol( real Angle )
 {
  int i, j, k;
  real l;
  TMatrix<real> a(NumElem,NumElem);
//  TVector<real> p1(NumElem-1);
//  TVector<real> p2(NumElem-1);
  real nSos=0;
  TCharPolin p1(NumElem-1);
  TCharPolin p2(NumElem-1);
  word newlevel = 2*(NumElem-1);
  TCharPolin AngPol(newlevel);
  for( i=0; i<NumElem; i++ )
   {
    for( j=0; j<NumElem; j++ )
     {
      l = abs( i-j );
      nSos =cos( (Angle-M_PI/2)*l);
      a[j][i] = (*this)[NumElem-i-1]*(*this)[NumElem-j-1]*nSos;
     };
   };
  for( k=0; k<NumElem; k++ )
   {
    p1[k]=0;
    for( j=0; j<=k; j++ )
     p1[k]=p1[k]+a[j][k-j];
   };
  for( k=0; k<NumElem; k++ )
   {
    p2[k]=0;
    for( j=0; j<NumElem-k; j++ )
     {
      p2[k]=p2[k]+a[(k+j)][NumElem-j-1];
     };
   };
  for( i=0; i<=newlevel; i++ )
   {
    if( i<NumElem )
     AngPol[i]=p2[NumElem-i-1];
    else AngPol[i]=p1[newlevel-i];
   };
  return AngPol;
 };
