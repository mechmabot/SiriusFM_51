#pragma once
#include<stdexcept>
#include<cmath>
namespace SiriusFM{
class DiffusionCEV{
private:
  double const m_mu;
  double const m_sigma;
  double const m_betta;
public:
  DiffusionCEV(double a_mu, double a_sigma, double a_betta):m_mu(a_mu),m_sigma(a_sigma), m_betta(a_betta){
    if(m_sigma <= 0) throw std::invalid_argument("invalid sigma");
    if(m_betta <= 0) throw std::invalid_argument("invalid betta");
  }
  double mu(double a_s, double a_t)const{
    return m_mu*a_s;
  }
  double sigma(double a_s, double a_t)const{
    return (a_s < 0 ? 0 : m_sigma*pow(a_s, m_betta));
  }
};
}
