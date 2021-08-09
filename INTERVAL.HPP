// Project: "Robastnost".
// Version: 0.99.

// Header: MAIN02.CPP.

// Author(s): F. Ahmedjanov.
// Description:
//    Defines classes TInterval & TIntComp representing
//    simply the interval values with operations on them.

class TInterval
 {
   real Down;
   real Up;
  public:
   TInterval()
   {Down=Up=0;};
   TInterval(real a, real b )
   {
   Down = min( a, b ); Up = max( a, b );
   };
   TInterval(real Init)
    { Down=Up=Init; };
   TInterval(TInterval& Src)
    {Down=Src.Down;Up=Src.Up;};
   real UpLimit()
    { return Up; };
   real DownLimit()
    { return Down; };
   real& operator[] (byte LimSel)
    { return (LimSel)? Up : Down; };
   TInterval& operator=(TInterval& Src)
    { Down=Src.Down;Up=Src.Up;return *this; };
   TInterval  operator+=(TInterval& Add) {Down+=Add.Down; Up+=Add.Up; return *this; };
   TInterval  operator-=(TInterval& Sub) {Down = min( Down - Sub.Down, Down - Sub.Up,
						      Up - Sub.Down, Up - Sub.Up );
					  Up   = max( Down - Sub.Down, Down - Sub.Up,
						      Up - Sub.Down, Up - Sub.Up );
					  return *this; };
   TInterval  operator*=(TInterval& Mul) {Down = min( Down * Mul.Down, Down * Mul.Up,
						      Up * Mul.Down, Up * Mul.Up );
					  Up   = max( Down * Mul.Down, Down * Mul.Up,
						      Up * Mul.Down, Up * Mul.Up );
					  return *this; };
   TInterval  operator/=(TInterval& Div) {Down = min( Down/Div.Down, Down/Div.Up,
						      Up/Div.Down, Up/Div.Up );
					  Up = max( Down/Div.Down, Down/Div.Up,
						    Up/Div.Down, Up/Div.Up );
					  return *this; };
   TInterval  operator+ (TInterval& Add) {return TInterval( Down + Add.Down, Up + Add.Up); };
   TInterval  operator- (TInterval& Sub) {return TInterval( min( Down - Sub.Down,
								 Down - Sub.Up,
								 Up - Sub.Down,
								 Up - Sub.Up ),
							    max( Down - Sub.Down,
								 Down - Sub.Up,
								 Up - Sub.Down,
								 Up - Sub.Up ) );};
   TInterval  operator* (TInterval& Mul) {return TInterval( min( Down * Mul.Down,
								 Down * Mul.Up,
								 Up * Mul.Down,
								 Up * Mul.Up ),
							    max( Down * Mul.Down,
								 Down * Mul.Up,
								 Up * Mul.Down,
								 Up * Mul.Up ) );};
   TInterval  operator* (real Mul) { return TInterval( Down*Mul, Up*Mul ); };
   TInterval  operator/ (TInterval& Div) {return TInterval( min( Down/Div.Down,
								 Down/Div.Up,
								 Up/Div.Down,
								 Up/Div.Up ),
							    max( Down/Div.Down,
								 Down/Div.Up,
								 Up/Div.Down,
								 Up/Div.Up ) );};
  friend istream& operator >> (istream& Src,TInterval& Scanned)
   {
    return Src>>Scanned.Down>>Scanned.Up;
   };
  friend ostream& operator << (ostream& Dst,TInterval& Printed)
   {
    return Dst<<Printed.Down<<"-"<<Printed.Up<<" ";
   };
  friend int operator > ( TInterval& e1, TInterval& e2 ) { return 1;}
  friend int operator < ( TInterval& e1, TInterval& e2 ) { return 1;}
  friend int operator >= ( TInterval& e1, TInterval& e2 ) { return 1;}
  friend int operator <= ( TInterval& e1, TInterval& e2 ) { return 1;}
 };

class TIntComplex{
private:
TInterval Re;
TInterval Im;
public:

// Конструктор

TIntComplex( void ){ Re = TInterval( 0, 0 );
		     Im = TInterval( 0, 0 );}

// Второй конструктор для тупого Борланда

TIntComplex( TIntComplex& Prev ) { Re = Prev.Re;
				   Im = Prev.Im; }

// Третий конструктор

TIntComplex( TInterval& b, TInterval& c ) { Re = b; Im = c; };


   TInterval Real(){ return Re; };
   TInterval Imag(){ return Im; };

   friend TIntComplex operator + ( TIntComplex& b, TIntComplex& c ){ return TIntComplex( b.Re + c.Re, b.Im + c.Im ); };
   friend TIntComplex operator + ( TInterval& c, TIntComplex& b )  { return TIntComplex( b.Re + c, b.Im ); };
   friend TIntComplex operator + ( TIntComplex& b, TInterval& c )  { return TIntComplex( c + b.Re, b.Im ); };
   friend TIntComplex operator + ( double& c, TIntComplex& b )  { return TIntComplex( b.Re + c, b.Im ); };
   friend TIntComplex operator + ( TIntComplex& b, double& c )  { return TIntComplex( b.Re + c, b.Im ); };
//   friend TIntComplex operator - ( TIntComplex& b) { return TIntComplex( -b.Re, -b.Im ); };
//   friend IntComplex operator - ( IntComplex&, IntComplex& );
//   friend IntComplex operator - ( IntComplex&, Interval& );
//   friend IntComplex operator - ( Interval&, IntComplex& );
//   friend IntComplex operator - ( IntComplex&, double& );
//   friend IntComplex operator - ( double&, IntComplex& );
//   friend IntComplex operator * ( IntComplex&, IntComplex& );
//   friend IntComplex operator * ( IntComplex&, Interval& );
//   friend IntComplex operator * ( Interval&, IntComplex& );
//   friend IntComplex operator * ( IntComplex&, double& );
//   friend IntComplex operator * ( double&, IntComplex& );
//   friend IntComplex operator / ( IntComplex&, IntComplex& );
//   friend IntComplex operator / ( IntComplex&, Interval& );
//   friend IntComplex operator / ( Interval&, IntComplex& );
//   friend IntComplex operator / ( IntComplex&, double& );
//   friend IntComplex operator / ( double&, IntComplex& );

TInterval MakePhase( void );

TInterval MakeAmpl( void );

		 };

