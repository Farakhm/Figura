// Project: "Robastnost".
// Version: 0.99.

// Module: POLIN'S.CPP.

// Author(s): F. Akhmedjanov, A.V. Zinoviev.
// Description: Defines classes to operate with __________.

class TCharPolin : public TPolinome<real>
 {
  public:
   TCharPolin(byte Pwr):TPolinome<real>(Pwr) {};
   TCharPolin(TCharPolin& Src):TPolinome<real>(Src) {};
   virtual ~TCharPolin() {};
   boolean Stable();
   TCharPolin ShiftPol( real );
   TCharPolin RotatePol( real );
 };

class TTransmFunc;

class TIntPolin : public TPolinome<TInterval>
 {
  public:
//   TIntPolin():TPolinome<TInterval>(1){cout<<"!!!"<<endl;};
   TIntPolin(byte Pwr):TPolinome<TInterval>(Pwr) {};
   TIntPolin(TSourceFile& PolSrc):TPolinome<TInterval>(PolSrc) {};
   TIntPolin(TTransmFunc& TrSrc);
   TIntPolin(TIntPolin& Src):TPolinome<TInterval>(Src) {};
   virtual ~TIntPolin() {};
   TIntComplex QuadroInt( real );
   boolean Stable();
   boolean StabStore( real );
   boolean StabQuality( real );
   boolean Soh( int, int, real );
 };

class TKharPolins
 {
  protected:
   TCharPolin* PKharPol[4];
  public:
   TKharPolins(TIntPolin& Src);
   virtual ~TKharPolins()
    {
     delete PKharPol[3];
     delete PKharPol[2];
     delete PKharPol[1];
     delete PKharPol[0];
    };
   boolean Stable();
   TCharPolin& operator[] (byte PolNm)
    {
     return *PKharPol[PolNm];
    };
 };

class TTransmFunc
 {
  protected:
   TIntPolin Numerator;
   TIntPolin Denominator;
  public:
   TTransmFunc(TSourceFile& Src):Numerator(Src),Denominator(Src) {};
   TTransmFunc(TIntPolin& SrcNumer,TIntPolin& SrcDenom)
    :Numerator(SrcNumer),Denominator(SrcDenom) {};
   TTransmFunc(byte Pwr):Numerator(Pwr),Denominator(Pwr) {};
   virtual ~TTransmFunc() {};
   TIntPolin& PolNumerator() { return Numerator; };
   TIntPolin& PolDenominator() { return Denominator; };
//   TIntPolin ToIKHP() {return Numerator + Denominator;}
   void AchFch( int );
   void VchPer();
   // Получение конкр. значений ВЧХ
   TInterval RePartPro( real );
   // Интегрирование
   void Integral( void );
 };
