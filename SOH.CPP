// Project: "Robastnost".
// Version: 0.99.

// Module: SOH.CPP.

// Author(s): F.M.Akhmedjanov.
// Description: Realize Soh-Foo's theorem.


#include<iomanip.h>

boolean TIntPolin::Soh( int p, int q , real angle )
{
boolean Result = TRUE;
real RAngle=0;
TCharPolin Sokh( NumElem-1 );
int m=0;
m=2*q;
for( int i=0; i<m; i++ ) {   // Цикл по q
  for( int k=0; k<NumElem; k++ ) {
    RAngle = p*k*M_PI/q + M_PI/q;
    if( sin( RAngle ) > 0 )  Sokh[k]=(*this)[k].UpLimit();
    else
      if( sin( RAngle ) < 0 )  Sokh[k]=(*this)[k].DownLimit();
      else
	if( cos( RAngle ) > 0 )  Sokh[k] = (*this)[k].UpLimit();
	else                     Sokh[k] = (*this)[k].DownLimit();
				  }

    if( !Sokh.RotatePol( angle ).Stable() ) { Result = FALSE; return Result; }
			 }
return Result;
}
