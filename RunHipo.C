int RunHipo(char * inputFilename, 
	     string outputFilename, 
	     string ptreeDir,
	     int nEvents=1000){
  // need to run LoadPi2 first to get libraries
  //string arguments => PID, INCLUSIVE  ("NONE", "ALL")=own PID, ("ALL" ,"ALL")=event builder
  //pi2("","ALL"); => Use Pid (from RECFT) and have no limit on the number of tracks per event (i.e. ALL)
  Pi2 fs("ALL" ,"ALL"); // PID, INCLUSIVE

  //output
  fs.CreateFinalTree("FinalTree",outputFilename);

  //add some cuts
  auto cutsman=make_shared<ParticleCutsManager>();
  auto eCut=make_shared<CLAS12DeltaTime>(10,10,0,0); //FT,FD,CD,??
  cutsman->AddParticleCut("e-",eCut); //assign to manager
  cutsman->ConfigureCuts(&fs);   
  fs.RegisterPostTopoAction(cutsman);

  auto treeman=make_shared<ParticleDataManager>(ptreeDir);
  treeman->ConfigureTreeParticles(&fs); //propogate through topologies
  treeman->AddFinal(); // add final state data into particile trees. optional!
  fs.RegisterPostWorkAction(treeman); //register post-work i.e. after

  auto dm=std::make_shared<HipoToolsReader>();
  TChain chain("HSParticles");
  chain.Add(inputFilename);
  dm->InitChain(&chain);

  //connect FinalState to Data by moving the pointer
  fs.SetDataManager(dm);
  fs.ProcessData(nEvents); //number of events to read

  //write file out
  fs.EndAndWrite();

  return 0;
}
