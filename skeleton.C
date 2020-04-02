{
   //skeleton code maker
   
   FSSkeleton s;

   //Give your class a name

   s.SetFinalState("Pi2");

   //Define the possible detected particles in the final state

   s.SetFinalStateParts("Electron:e-, Proton:proton, Pip:pi+, Pim:pi-");
   

   //Define possible topologies for this final state
   //Note ',' seperates different topologies
   // ':' seperates different particle within a topology
   // Here we define 3 topologies, exclusive, 1 missin pi-, 2  missing pi-

   s.SetFinalStateTopo("Electron:Proton:Pip:Pim, Electron:Proton:Pip, Electron:Proton:Pim, Electron:Pip:Pim");

   //Define short lived parent particles which decay to
   //detected particles
   //this should not include broad resonances
   //But things like omega, phi, Lambda, K0
   //':' seperates parent name from type
   //';' seperates child particles
   //',' seperates different parents

   s.SetFinalStateParents("");

   //produce the code	
	
   s.MakeCode();
}
