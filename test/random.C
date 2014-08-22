{
  TRandom3 r;
  TH1D*h11= new TH1D("name1","name",20,0,20) ;
  TH1D*h12= new TH1D("name2","name",20,0,20) ;
  TH2D*h2= new TH2D("name3","name",20,0,20,20,0,20);
  int i = 0;
  while(i<100)
    {
      double x2 = r.Gaus(10,3);       
      h11->Fill(x2);
      h12->Fill(x2);
      h2->Fill(x2,x2);
      i++;
    }

  TCanvas c;
  c.Divide(2);
  c.cd(1);
  h2->Draw("colz");
  TH2D*h22= new TH2D("name4","name",20,0,20,20,0,20);
  c.cd(2);
  h22->Add(h11,h12);
  h22->Draw("colz");
}
