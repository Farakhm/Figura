// Project: "Robastnost".
// Version: 0.99.

// Header: MEMARRAY.HPP.

// Author: A.V. Zinoviev.
// Description: Defines of classes for matrix algebra operations.

template <class TBase> class TArray
{
 protected:
  TBase far* pArray;
  word NumElem;
 public:
  TArray (word NumEl);
  TArray () { pArray=0; NumElem=0; };
  TBase far& Access(word Index);
  virtual ~TArray();
};

 template <class TBase> TArray<TBase>::TArray(word NumEl)
  {
   pArray=0;
   if (NumElem = NumEl)
    pArray = (TBase far*)farcalloc((unsigned long)NumElem,sizeof(TBase));
   if (!pArray) NumElem=0;
  };

 template <class TBase> TBase far& TArray<TBase>::Access(word i)
  {
   return (i<NumElem) ?
    *(TBase far*) ((dword)pArray+
     (((dword)(i)*sizeof(TBase)&0x000F0000L)<<12)+(word)(i*sizeof(TBase))) :
    *(TBase far*) ((dword)pArray+
     (((dword)(i)*sizeof(TBase)&0x000F0000L)<<12)+(word)((NumElem-1)*sizeof(TBase)));
  };

 template <class TBase> TArray<TBase>::~TArray()
  {
   if (pArray)
    farfree(pArray);
   pArray=NULL;
  };
