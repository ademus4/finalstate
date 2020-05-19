{
  auto FS = adamt::Pi2::Make("ALL","ALL");
  FS->AddTopology("Electron:Proton:Pip:Pim");
  FS->AddTopology("Electron:Proton:Pim");
  FS->AddTopology("Electron:Proton:Pip");
  FS->AddTopology("Electron:Pip:Pim");

  //Save TreeDataPi2
  FS->UseOutputRootTree();

  /////Make particle trees first in case want to add cut flags
  ParticleDataManager pdm{"particle",1};
  pdm.SetParticleOut(new CLAS12ParticleOutEvent0);
  FS->RegisterPostKinAction(pdm);


  ///start time
  StartTimeAction st("StartTime",new C12StartTimeFromParticle("Electron"));
  FS->RegisterPreTopoAction(st);

  //FT electron energy correction
  ParticleCorrectionManager pcorrm{"FTelEnergyCorrection"};
  pcorrm.AddParticle("e-",new FTel_pol4_ECorrection());
  FS->RegisterPreTopoAction(pcorrm);

  //write out config
  FS->WriteToFile("config_allall_ecorr.root");

  //Delete the final state rather than let ROOT try
  FS.reset();
}
