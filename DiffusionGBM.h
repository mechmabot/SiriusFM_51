#pragma once
#include<stdexcept>
namespace SiriusFM{
class DiffusionGBM{
private:
  double const m_mu;
  double const m_sigma;
  double const m_S0;
public:
  DiffusionGBM(double a_mu, double a_sigma, double a_S0):m_mu(a_mu),m_sigma(a_sigma), m_S0(a_S0){
    if(m_sigma <= 0|| m_S0 <= 0) throw std::invalid_argument("invalid sigma or S0");
  }
  double mu(double a_s, double a_t)const{
    return (a_s < 0 ? 0 : m_mu*a_s);
  }
  double sigma(double a_s, double a_t)const{
    return (a_s < 0 ? 0 : m_sigma*a_s);
  }
  double S0()const{
    return m_S0;
  }
};
}
