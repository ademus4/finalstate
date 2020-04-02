{
  auto FS = adamt::Pi2::Make("ALL","ALL");
  FS->AddTopology("Electron:Proton:Pip:Pim");

  //Save TreeDataPi2
  FS->UseOutputRootTree();

  /////Make particle trees first in case want to add cut flags
  ParticleDataManager pdm{"particle",1};
  CLAS12ParticleOutEvent0 pout;
  pdm.SetParticleOut(pout);
  FS->RegisterPostTopoAction(pdm);

  //write out config
  FS->WriteToFile("config_allall.root");

  //Delete the final state rather than let ROOT try
  FS.reset();
}
