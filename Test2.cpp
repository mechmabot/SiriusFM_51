#include <iostream>
#include "DiffusionGBM.h"
#include "IRProviderConst.h"
#include "MCEngine1D.hpp"
#include "VanillaOptions.h"
using namespace SiriusFM;
using namespace std;
int main(int argc, char * argv[]){ // Diffusion: mu, sigma, S0, Option: call/put, K,  T_days, MCEngine: tau_min, P
  // S0 - параметр diffusion а не S0 (должен быть);
  if(argc != 9){
    cerr <<"PARAMS: mu, sigma, S0, T_days, tau_min, P\n";
    return 1;
  }
  double mu = atof(argv[1]);
  double sigma = atof(argv[2]);
  double S0 = atof(argv[3]);
  char const* optionType = argv[4];
  double K = atof(argv[5]);
  long T_days = atol(argv[6]);
  long tau_min = atol(argv[7]);
  long P = atol(argv[8]);
  //check all params are > 0; if(...) {cerr << "..."; return 2;}
  Option const * option = nullptr;
  if (strcmp(optionType, "Call") == 0)
            option = new EurCallOption(K, T_days);
  else if(strcmp(optionType, "Put")==0)
            option = new EurPutOption(K, T_days);
  else
    throw invalid_argument("not put & not call");

  CcyE ccyA = CcyE::USD;

  IRProvider<IRModeE::Const> irp(nullptr);
  DiffusionGBM Diff(mu, sigma, S0);
  MCEngine1D<decltype(Diff),
             decltype(irp),
             decltype(irp),
             decltype(ccyA),
             decltype(ccyA)>
  mce(20000, 20000);// в классе 20к на 20к
  time_t t0 = time(nullptr);
  time_t T = t0 + T_days*86400;
  double T_years = T_days/365.25;
  // Run MC
  mce.Simulate<false>(t0, T, tau_min, P, &Diff, &irp, &irp, ccyA, ccyA);
  // Analize the results
  auto res = mce.GetPaths();
  long L1 = get<0>(res);
  long P1 = get<1>(res);
  double const * paths = get<2>(res);
  // compute E of log(St)
  double EST = 0;
  double EST2 = 0;
  int NVP = 0; // # of valid paths
  for(long p = 0; p < P1; ++p){
    double const * path = paths + p*L1;
    double ST = path[L1 - 1];// in practice may get ST < 0
    if(ST <= 0.0){
      continue;
    }
    ++NVP;
    double PT = option->payoff(L1, nullptr, path); // payoff
    EST += PT;
    EST2 += PT*PT;

  }

  assert(NVP > 1);
  EST /= double(NVP); // + discount factor
//  double VarST = (EST2 - double(NVP)*EST*EST)/(NVP - 1); // sigma^2 * T
  cout << EST << endl;
  /*double sigma2E = VarST/T_years;
  double muE = (EST + VarST/2.0)/T_years;
  cout << "mu =  "<< mu << " muE = "<< muE << endl;
  cout << "sigma2 =  "<< sigma*sigma << " sigmaE = "<< sigma2E << endl;*/



  return 0;
}
// 0.1 0.25 100 90 5 5000
