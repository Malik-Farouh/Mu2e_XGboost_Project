void convert_bdt() {
    TMVA::Experimental::RBDT bdt = 
        TMVA::Experimental::RBDT::LoadXGBoost("mu2e_project/trkQual_model.json", "myBDT");
    
    TFile f("mu2e_project/trkQual_bdt.root", "RECREATE");
    bdt.Write("myBDT");
    f.Close();
    
    std::cout << "Saved! Ready for Art module." << std::endl;
}
