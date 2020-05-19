int Run_Pi2(char * inputFilename, 
	    string config, 
	    string outputDir){
  ////Set hipo file to be analysed
  HipoData hdata;
  hdata.SetFile(inputFilename); 
  hdata.Reader()->useFTBased();

  ////create FinalStateManager
  FinalStateManager fsm;
  fsm.SetBaseOutDir(outputDir); // 

  ////Connect the data to the manager
  fsm.LoadData(&hdata);
  
  ////load one or more FinalStates
  fsm.LoadFinalState("Pi2", config); //

  //Max number of particles of any 1 species
  //Whole event disgarded if this not met.
  fsm.GetEventParticles().SetMaxParticles(6);

  ////Run through all events
  fsm.ProcessAll();
  return 0;
}
