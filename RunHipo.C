int RunHipo(char * inputFilename, 
	     string outputFilename, 
	     string ptreeDir,
	     int nEvents=1000){
  // need to run LoadPi2 first to get libraries
  Pi2 fs("","ALL"); //string arguments => PID, INCLUSIVE  ("NONE", "ALL") own PID

  //output
  fs.CreateFinalTree("FinalTree",outputFilename);

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
