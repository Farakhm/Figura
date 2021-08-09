// Project: "Robastnost".
// Version: 0.99.

// Module: LINKS.CPP.

// Author(s): A.V. Zinoviev.
// Description: Defines classes to operate with interval dynamic links.

#include "std.h"

 TInterval TInertLink::operator()(TInterval Input)
  {
   return TransmCoeff/(TimeConst*Input+(TInterval)(1));
  };

 TInterval TInertLink::RealFreqFunc(real Freq)
  {
   return TransmCoeff/((TimeConst*TimeConst*Freq*Freq)+1);
  };

 TInterval TInertLink::ImagFreqFunc(real Freq)
  {
   TInterval Result;
   real w=Freq;
   real Tu=TimeConst.UpLimit();
   real Td=TimeConst.DownLimit();
   real ku=TransmCoeff.UpLimit();
   real kd=TransmCoeff.DownLimit();
   if(w<1/Tu)
    Result=TInterval(-ku*Tu*w/(Tu*Tu*w*w+1),-kd*Td*w/(Td*Td*w*w+1));
   if(1/Tu<w&&w<1/Td)
    Result=TInterval(-ku/2,max(-kd*Tu*w/(Tu*Tu*w*w+1),-kd*Td*w/(Td*Td*w*w+1)));
   if(1/Td<w)
    Result=TInterval(-ku*Td*w/(Td*Td*w*w+1),-kd*Tu*w/(Tu*Tu*w*w+1));
   return Result;
  };

 TInterval TInertLink::AmplitudeFreqFunc(real Freq)
  {
   real w=Freq;
   real Tu=TimeConst.UpLimit();
   real Td=TimeConst.DownLimit();
   real ku=TransmCoeff.UpLimit();
   real kd=TransmCoeff.DownLimit();
   return TInterval(kd/(sqrt(Td*Td*w*w)+1),ku/(sqrt(Tu*Tu*w*w)+1));
  };

 TInterval TInertLink::PhaseFreqFunc(real Freq)
  {
   real w=Freq;
   real Tu=TimeConst.UpLimit();
   real Td=TimeConst.DownLimit();
   return TInterval(-atan(Td*w),-atan(Tu*w));
  };
//=============================================================//
