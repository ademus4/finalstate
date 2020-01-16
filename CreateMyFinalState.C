//create all the classes needed for the 2pi analysis
{
  gROOT->ProcessLine(".x $HSCODE/hsskeleton/LoadSkeleton.C+");
  CLAS12Skeleton sk;
  sk.SetFinalState("Pi2");
  sk.SetFinalStateParts("Electron:e-, Proton:proton, Pip:pi+, Pim:pi-");
  sk.SetFinalStateTopo("Electron:Proton:Pip:Pim, Electron:Proton:Pip, Electron:Proton:Pim, Electron:Pip:Pim");
  sk.SetFinalStateParents("");
  sk.MakeCode();
  gROOT->ProcessLine(".x LoadPi2.C+");
}
