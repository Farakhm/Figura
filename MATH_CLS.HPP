// Project: None.
// Version: 0.93.

// Header: MATH_CLS.HPP.

// Author: A.V. Zinoviev.
// Description: Defines classes for matrix algebra operations.

// Remarks:
/*
 Needed:
  TVector(word, TBase=0)
  TMatrix(byte,byte, TBase=0)
*/

template <class TValue> TValue& min(TValue& V1, TValue& V2)
 {
  return (V1<V2)?V1:V2 ;
 };

template <class TValue> TValue& max(TValue& V1, TValue& V2)
 {
  return (V1>V2)?V1:V2 ;
 };

template <class TValue> TValue& min(TValue& V1, TValue& V2, TValue& V3, TValue& V4 )
 {
  return ((V1<V2)&&(V1<V3)&&(V1<V4))?V1:((V2<V3)&&(V2<V4))?V2:(V3<V4)?V3:V4;
 };

template <class TValue> TValue& max(TValue& V1, TValue& V2, TValue& V3, TValue& V4 )
 {
  return ((V1>V2)&&(V1>V3)&&(V1>V4))?V1:((V2>V3)&&(V2>V4))?V2:(V3>V4)?V3:V4;
 };

dword iFact( word k ); // Redefine & rewrite !!!
inline real sign(real Val)
 {
  return (Val>0)?+1:(Val<0)?-1:0;
 };

template <class TBase> class TVector : public TArray<TBase>
 {
  public:
   TVector(word InitNumEl):TArray<TBase>(InitNumEl) {};
   TVector(TVector& Src);
   TVector(TVector& Src,TBase InitValue);
   TVector(TVector& Src,word StartElem,word InitNumEl);
   TVector(TSourceFile& Src):TArray<TBase>(Src.Get()) { Src>>(*this); };
   virtual ~TVector() {};
   TVector& operator = (TVector& Src);
   word Size() { return NumElem; };
   TBase& operator[] (word Index)
     { return (Access(Index)); };
   TVector& operator+= (TVector& Add);
   TVector& operator-= (TVector& Sub);
   TVector& operator*= (TBase& Mult);
   TVector& operator/= (TBase& Divid);
   friend TBase min(TVector& Val);
   friend TBase max(TVector& Val);
   friend TBase sum(TVector& Val);
   friend TVector operator+ (TVector& Val,TVector& Add);
   friend TVector operator- (TVector& Val,TVector& Sub);
   friend TBase operator* (TVector& Val,TVector& Mul);
   friend TVector operator* (TBase& Mult,TVector& Val);
   friend TVector operator/ (TBase& Divid,TVector& Val);
   friend istream& operator >> (istream& Src,TVector& Scanned);
   friend ostream& operator << (ostream& Dst,TVector& Printed);
 };

template <class TBase> class TPolinome : public TVector<TBase>
 {
  public:
   TPolinome(byte Power):TVector<TBase>(Power+1) {};
   TPolinome(TPolinome& Src):TVector<TBase>(Src) {};
   TPolinome(TSourceFile& Src):TVector<TBase>(Src.Get()+1) {Src>>(*this);};
   virtual ~TPolinome() {};
   TBase operator()  (TBase& Arg);
   friend byte Power(TPolinome& Src);
 };

template <class TBase> class TMatrixRow : public TVector<TBase>
 {
  friend class TMatrix<TBase>;
  private:
   TMatrixRow(TBase* pRow,word RowWidth):TVector<TBase>(0)
    {
     pArray=pRow;
     NumElem=RowWidth;
    };
  public:
   TMatrixRow(TMatrixRow& Src):TVector<TBase>(0)
    {
     pArray=Src.pArray;
     NumElem=Src.NumElem;
    };
   virtual ~TMatrixRow()
    {
     NumElem=0;
     pArray=0;
    };
 };

template <class TBase> class TMatrix : public TArray<TBase>
 {
  protected:
   byte NumRows;
   word NumCols;
  public:
   TMatrix(byte InitNumRows,word InitNumCols);
   TMatrix(TMatrix& Src);
   TMatrix(TMatrix& Src,word DelRow,word DelCol);
   TMatrix(TSourceFile& Src)
    :TArray<TBase>((NumRows=Src.Get())*(NumCols=Src.Get()))
    { Src>>(*this); };
   virtual ~TMatrix() {};
   word Width() { return NumCols; };
   word Height() { return NumRows; };
   word Size() { return NumElem; };
   TMatrixRow<TBase> operator[](byte RowNumber);
   TMatrix& operator= (TMatrix& Src);
   TMatrix& operator+=(TMatrix& Add);
   TMatrix& operator-=(TMatrix& Sub);
   TMatrix& operator*=(TBase& Mult);
   TMatrix& operator/=(TBase& Div);
   friend TMatrix operator* (TMatrix& Mx,TBase& Mult);
   friend TMatrix operator/ (TMatrix& Mx,TBase& Div);
   friend TMatrix operator+ (TMatrix& Mx,TMatrix& Add);
   friend TMatrix operator- (TMatrix& Mx,TMatrix& Sub);
   friend TMatrix operator* (TMatrix& Mx,TMatrix& Mult);
   friend TVector<TBase> operator* (TMatrix& Mx,TVector<TBase>& Mult);
   friend TMatrix operator! (TMatrix& Src);
   friend TMatrix operator~ (TMatrix& Src);
   friend TBase det(TMatrix& Src);
   friend TBase& min(TMatrix& Src);
   friend TBase& max(TMatrix& Src);
   friend TBase& absmin(TMatrix& Src);
   friend TBase& absmax(TMatrix& Src);
   friend TBase sum(TMatrix& Src);
   friend istream& operator >> (istream& Src, TMatrix& Scanned);
   friend ostream& operator << (ostream& Dst, TMatrix& Printed);
 };

 template <class TBase> TVector<TBase>::TVector(TVector<TBase>& Src)
  :TArray<TBase>(Src.NumElem)
  {
   if (pArray)
     for (word i=0;i<NumElem;i++) Access(i)=Src.Access(i);
  };

 template <class TBase> TVector<TBase>& TVector<TBase>::operator=(TVector<TBase>& Src)
  {
   if (pArray)
     for (word i=0;i<min(NumElem,Src.NumElem);i++) Access(i)=Src.Access(i);
   return *this;
  };

 template <class TBase> TVector<TBase>& TVector<TBase>::operator+=(TVector<TBase>& Add)
  {
   if (pArray)
     for (word i=0;i<min(NumElem,Add.NumElem);i++)
      Access(i)+=Add.Access(i);
   return *this;
  };

 template <class TBase> TVector<TBase>& TVector<TBase>::operator-=(TVector<TBase>& Sub)
  {
   if (pArray)
     for (word i=0;i<min(NumElem,Sub.NumElem);i++)
      Access(i)-=Sub.Access(i);
   return *this;
  };

 template <class TBase> TVector<TBase>& TVector<TBase>::operator*=(TBase& Mult)
  {
   if (pArray)
     for (word i=0;i<NumElem;i++)
      Access(i)*=Mult;
   return *this;
  };

 template <class TBase> TVector<TBase>& TVector<TBase>::operator/=(TBase& Divid)
  {
   if (pArray)
     for (word i=0;i<NumElem;i++)
      this->Access(i)/=Divid;
   return *this;
  };

 template <class TBase> TVector<TBase> operator+ (TVector<TBase>& Vec,TVector<TBase>& Add)
  {
   TVector<TBase> Result(max(Vec.NumElem,Add.NumElem));
   Result=Vec;
   Result+=Add;
   return Result;
  };

 template <class TBase> TVector<TBase> operator- (TVector<TBase>& Vec,TVector<TBase>& Sub)
  {
   TVector<TBase> Result(max(Vec.NumElem,Sub.NumElem));
   Result=Vec;
   Result-=Sub;
   return Result;
  };

 template <class TBase> TVector<TBase> operator/ (TVector<TBase>& Vec,TBase& Divid)
  {
   TVector<TBase> Result(Vec);
   Result/=Divid;
   return Result;
  };

 template <class TBase> TVector<TBase> operator* (TVector<TBase>& Vec,TBase& Mult)
  {
   TVector<TBase> Result(Vec);
   Result*=Mult;
   return Result;
  };

 template <class TBase> TBase operator* (TVector<TBase>& Vec,TVector<TBase>& Mul)
  {
   TBase Result;
   for (byte ECt=0;ECt<min(Vec.Size(),Mul.Size());ECt++)
    Result+=Vec[ECt]*Mul[ECt];
   return Result;
  };

 template <class TBase> TBase min (TVector<TBase>& Src)
  {
   TBase Result=Src[0];
   for (byte ECt=1;ECt<Src.NumElem;ECt++)
    Result=min(Src[ECt],Result);
   return Result;
  };

 template <class TBase> TBase max (TVector<TBase>& Src)
  {
   TBase Result=Src[0];
   for (byte ECt=1;ECt<Src.NumElem;ECt++)
    Result=max(Src[ECt],Result);
   return Result;
  };

 template <class TBase> TBase sum (TVector<TBase>& Src)
  {
   TBase Result=Src[0];
   for (byte ECt=1;ECt<Src.NumElem;ECt++)
    Result+=Src[ECt];
   return Result;
  };

 template <class TBase> ostream& operator<< (ostream& Dst,TVector<TBase>& Vec)
  {
   Dst.precision(3);
   Dst.setf(ios::internal|ios::showpoint|ios::fixed);
   Dst << endl;
   for (byte ECt=0;ECt<Vec.NumElem;ECt++)
    {
     Dst.width(8);
     Dst<<Vec[ECt]<<" ";
    };
   Dst << endl;
   return Dst;
  };

 template <class TBase> istream& operator>> (istream& Src,TVector<TBase>& Vec)
  {
   for (byte ECt=0;ECt<Vec.NumElem;ECt++) Src>>Vec[ECt];
   return Src;
  };

 template <class TBase> TBase TPolinome<TBase>::operator ()(TBase& Arg)
  {
   TBase Result=pArray[NumElem-1];
   for (byte PCt=NumElem-2;PCt!=255;PCt--)
     Result=Result*Arg+pArray[PCt];
   return Result;
  };

 template <class TBase> byte Power(TPolinome<TBase>& Arg)
  {
   return Arg.NumElem-1;
  };

 template <class TBase> TMatrix<TBase>::TMatrix(byte InitNumRows,word InitNumCols)
   : TArray<TBase>(InitNumRows*InitNumCols)
  {
     NumRows=(pArray)?InitNumRows:0;
     NumCols=(pArray)?InitNumCols:0;
  };

 template <class TBase> TMatrix<TBase>::TMatrix(TMatrix<TBase>& Src)
    : TArray<TBase>(Src.NumRows*Src.NumCols)
  {
   if(pArray)
    {
     NumRows=Src.NumRows;
     NumCols=Src.NumCols;
     for (byte Row=0;Row<NumRows;Row++)
      for (word Col=0;Col<NumCols;Col++)
       Access(Row*NumCols+Col)=Src.Access(Row*NumCols+Col);
    }
   else NumRows=NumCols=0;
  };

 template <class TBase> TMatrix<TBase>::TMatrix(TMatrix<TBase>& Src,word DelRow,word DelCol)
   : TArray<TBase>((Src.NumRows-1)*(Src.NumCols-1))
  {
   if(pArray)
    {
     NumRows=Src.NumRows-1;
     NumCols=Src.NumCols-1;
     for (byte Row=0;Row<DelRow;Row++)
      {
       for (word Col=0;Col<DelCol;Col++)
        (*this)[Row][Col]=Src[Row][Col];
       for (Col=DelCol+1;Col<NumCols+1;Col++)
        (*this)[Row][Col-1]=Src[Row][Col];
      };
     for (Row=DelRow+1;Row<NumRows+1;Row++)
      {
       for (word Col=0;Col<DelCol;Col++)
        (*this)[Row-1][Col]=Src[Row][Col];
       for (Col=DelCol+1;Col<NumCols+1;Col++)
        (*this)[Row-1][Col-1]=Src[Row][Col];
      };
    }
   else NumRows=NumCols=0;
  };

 template <class TBase> TMatrix<TBase>& TMatrix<TBase>::operator = (TMatrix<TBase>& Src)
  {
   if (pArray)
    {
     byte RowLim=min(NumRows,Src.NumRows);
     byte ColLim=min(NumCols,Src.NumCols);
     for (byte RCt=0;RCt<RowLim;RCt++)
      for (byte CCt=0;CCt<ColLim;CCt++)
       Access(RCt*NumRows+CCt)=Src.Access(RCt*Src.NumRows+CCt);
    };
   return *this;
  };

 template <class TBase> TMatrix<TBase>& TMatrix<TBase>::operator +=(TMatrix<TBase>& Add)
  {
   if (pArray)
    {
     byte RowLim=min(NumRows,Add.NumRows);
     byte ColLim=min(NumCols,Add.NumCols);
     for (byte RCt=0;RCt<RowLim;RCt++)
      for (byte CCt=0;CCt<ColLim;CCt++)
       Access(RCt*NumRows+CCt)+=Add.Access(RCt*Add.NumRows+CCt);
    };
   return *this;
  };

 template <class TBase> TMatrixRow<TBase> TMatrix<TBase>::operator [](byte Row)
  {
   if ((pArray!=0)&&(Row<NumRows))
    return TMatrixRow<TBase>(&Access(NumCols*Row),NumCols);
   else
    return TMatrixRow<TBase>(0,0);
  };

 template <class TBase> TMatrix<TBase>& TMatrix<TBase>::operator -=(TMatrix<TBase>& Sub)
  {
   if (pArray)
    {
     byte RowLim=min(NumRows,Sub.NumRows);
     byte ColLim=min(NumCols,Sub.NumCols);
     for (byte RCt=0;RCt<RowLim;RCt++)
      for (byte CCt=0;CCt<ColLim;CCt++)
       Access(RCt*NumRows+CCt)+=Sub.Access(RCt*Sub.NumRows+CCt);
     };
   return *this;
  };

 template <class TBase> TMatrix<TBase>& TMatrix<TBase>::operator*=(TBase& Mult)
  {
   if (pArray)
    {
     for (byte RCt=0;RCt<NumRows;RCt++)
      for (byte CCt=0;CCt<NumCols;CCt++)
       Access(RCt*NumRows+CCt)*=Mult;
    };
   return *this;
  };

 template <class TBase> TMatrix<TBase>& TMatrix<TBase>::operator/=(TBase& Div)
  {
   if (pArray)
    {
     for (byte RCt=0;RCt<NumCols;RCt++)
      for (byte CCt=0;CCt<NumRows;CCt++)
       Access(RCt*NumRows+CCt)/=Div;
    };
   return *this;
  };

 template <class TBase> TMatrix<TBase> operator* (TMatrix<TBase>& Mx,TBase& Mult)
  {
   return TMatrix<TBase>(Mx)*=Mult;
  };

 template <class TBase> TMatrix<TBase> operator/ (TMatrix<TBase>& Mx,TBase& Div)
  {
   return TMatrix<TBase>(Mx)/=Div;
  };

 template <class TBase> TMatrix<TBase> operator+ (TMatrix<TBase>& Mx,TMatrix<TBase>& Add)
  {
   return TMatrix<TBase>(Mx)+=Add;
  };

 template <class TBase> TMatrix<TBase> operator- (TMatrix<TBase>& Mx,TMatrix<TBase>& Sub)
  {
   return TMatrix<TBase>(Mx)-=Sub;
  };

 template <class TBase> TMatrix<TBase> operator* (TMatrix<TBase>& Mx,TMatrix<TBase>& Mult)
  {
   byte ELim=min((byte)Mx.NumCols,(byte)Mult.NumRows);
   TMatrix<TBase> Res(Mx.NumRows,Mult.NumCols);
   for(byte RCt=0;RCt<Res.NumRows;RCt++)
    for(byte CCt=0;CCt<Res.NumCols;CCt++)
     for(byte ECt=0;ECt<ELim;ECt++)
      Res[RCt][CCt]+=Mx[RCt][ECt]*Mult[ECt][CCt];
   return Res;
  };

 template <class TBase> TVector<TBase> operator* (TMatrix<TBase>& Mx,TVector<TBase>& Mult)
  {
   byte ELim=min((byte)Mx.NumCols,(byte)Mult.Size());
   TVector<TBase> Res(Mx.NumRows);
   for(byte RCt=0;RCt<Mx.NumRows;RCt++)
     for(byte ECt=0;ECt<ELim;ECt++)
      Res[RCt]+=Mx[RCt][ECt]*Mult[ECt];
   return Res;
  };

 template <class TBase> TMatrix<TBase> operator! (TMatrix<TBase>& Mx)
  {
   TMatrix<TBase> Res(Mx.NumCols,Mx.NumRows);
   for(byte RCt=0;RCt<Res.NumRows;RCt++)
    for(byte CCt=0;CCt<Res.NumCols;CCt++)
     Res[RCt][CCt]=Mx[CCt][RCt];
   return Res;
  };

 template <class TBase> TMatrix<TBase> operator~ (TMatrix<TBase>& Mx)
  {
   word ELim=min((byte)Mx.NumCols,(byte)Mx.NumRows);
   TMatrix<TBase> Res(ELim,ELim);
   int Sign=1;
   for(byte RCt=0;RCt<ELim;RCt++)
    for(byte CCt=0;CCt<ELim;CCt++)
     {
      Res[CCt][RCt]=det(TMatrix<TBase>(Mx,RCt,CCt))*Sign;
      Sign=-Sign;
     };
   TBase MxDet=0;
   for(byte CCt=0;CCt<ELim;CCt++) MxDet+=Mx[0][CCt]*Res[CCt][0];
   Res/=MxDet;
   return Res;
  };

 template <class TBase> TBase det(TMatrix<TBase>& Mx)
  {
   word ELim=min((byte)Mx.NumCols,(byte)Mx.NumRows);
   TBase Res=0;
   switch(ELim)
    {
     case 0: break;
     case 1: Res=Mx[0][0];break;
     case 2: Res=Mx[0][0]*Mx[1][1]-Mx[0][1]*Mx[1][0];break;
     default:
      {
       int Sign=1;
       for(byte CCt=0;CCt<ELim;CCt++)
        {
         Res+=Mx[0][CCt]*det(TMatrix<TBase>(Mx,0,CCt))*Sign;
         Sign=-Sign;
        };
      };
    };
   return Res;
  };

 template <class TBase> istream& operator >> (istream& Src, TMatrix<TBase>& Scanned)
  {
   if(Scanned.pArray)
    for(byte RCt=0;RCt<Scanned.NumRows;RCt++)
     for(byte CCt=0;CCt<Scanned.NumCols;CCt++)
      Src >> Scanned[RCt][CCt];
   return Src;
  };

 template <class TBase> ostream& operator << (ostream& Dst, TMatrix<TBase>& Printed)
  {
   Dst.precision(3);
   Dst.setf(ios::internal|ios::showpoint|ios::fixed);
   for(byte RCt=0;RCt<Printed.NumRows;RCt++)
    {
     for(byte CCt=0;CCt<Printed.NumCols;CCt++)
      {
       Dst.width(8);
       Dst << Printed[RCt][CCt] << " ";
      };
     Dst << endl;
    };
   return Dst;
  };

