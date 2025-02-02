// Project: "Robastnost".
// Version: 0.99.

// Header: LINKS.HPP.

// Author(s): A.V. Zinoviev.
// Description: Defines classes to operate with interval dynamic links.


class TLink
 {
  // ���� � ����ࠪ�� ������ �� ࠡ�⠥� => �� �㭪樨 - ����
  public:
   virtual TInterval operator()(TInterval Input)=0;
    // �����頥� ��室��� ���ﭨ� �� �������� ��室�
   virtual TInterval RealFreqFunc(real Freq)=0;
   virtual TInterval ImagFreqFunc(real Freq)=0;
   virtual TInterval AmplitudeFreqFunc(real Freq)=0;
   virtual TInterval PhaseFreqFunc(real Freq)=0;
 };

class TInertLink : public TLink
 {
  protected:
   TInterval TransmCoeff;
   TInterval TimeConst;
  public:
   TInertLink(TInterval k,TInterval T)
    {
     TransmCoeff=k;
     TimeConst=T;
    };
   virtual TInterval operator()(TInterval Input);
    // �����頥� ��室��� ���ﭨ� �� �������� ��室�
   virtual TInterval RealFreqFunc(real Freq);
   virtual TInterval ImagFreqFunc(real Freq);
   virtual TInterval AmplitudeFreqFunc(real Freq);
   virtual TInterval PhaseFreqFunc(real Freq);
 };

