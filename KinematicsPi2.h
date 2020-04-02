#include "Pi2.h"
void Pi2::Kinematics(){ 
  //trigger bits, gives the bitmask
  //auto EvInfo=dynamic_cast<HS::CLAS12::EventInfo*>(fEventInfo);
  //cout<<EvInfo->fTrigBit<<endl;
  TD.TriggerElectron=fTrigger.TrigBit(0);
  TD.Trigger24=fTrigger.TrigBit(24);
  TD.TriggerMesonex=fTrigger.TrigBit(25);
  TD.TriggerFT2C=fTrigger.TrigBit(26);
  TD.TriggerFT100=fTrigger.TrigBit(27);

  TD.TriggerFDSectors=fTrigger.CheckSectorsFD(frDetParts);
  TD.TriggerTotalEnergyFT=fTrigger.GetTotalEnergyFT(frDetParts);

  //simulated mesonex trigger
  //TD.TriggerSim=fMTrigger->fire();
  
  //Calculate possible resonances
  HSLorentzVector pMeson=fPip.P4()+fPim.P4();
  HSLorentzVector pDpp=fProton.P4()+fPip.P4();
  HSLorentzVector pD0=fProton.P4()+fPim.P4();

  //invariant masses
  TD.MesonMass=pMeson.M();
  TD.DppMass=pDpp.M();
  TD.D0Mass=pD0.M();
  
  fKine.SetElecsTarget(fBeam,fElectron.P4(),fTarget);
  TD.W=fKine.W(); //photon bem energy
  TD.Q2=fKine.Q2();
  TD.Pol=fKine.GammaPol();
  TD.Egamma=fKine.GammaE();
  
  //calculate CM production kinematics for meson
  fKine.SetMesonBaryon(pMeson,fProton.P4());
  fKine.ElectroCMDecay();
  TD.MesonECosTh=fKine.CosTheta();//prefix all variables to be saved wiht TM.
  TD.MesonEPhi=fKine.Phi();

  //helicity
  fKine.SetMesonDecay(fPip.P4(),fPim.P4());
  fKine.MesonDecayHelicity();
  TD.MesonHCosTh=fKine.CosTheta();
  TD.MesonHPhi=fKine.Phi();

  //GJ
  fKine.SetMesonDecay(fPip.P4(),fPim.P4());
  fKine.MesonDecayGJ();
  TD.MesonGJCosTh=fKine.CosTheta();
  TD.MesonGJPhi=fKine.Phi();

}
