#pragma once
#include <cmath>
#include <ctime>
#include<stdexcept>
namespace SiriusFM{
template<typename Diffusion1D,
         typename AProvider,
         typename BProvider,
         typename AssetClassA,
         typename AssetClassB>
class MCEngine1D{
private:
  long const m_MaxL;
  long const m_MaxP;
  double m_paths;
  // long m_L; // m_L <= m_MaxL
  // long m_P; // m_P <= m_MaxP
  // double m_tau;// Timestamp as YearFraction
  // double m_t0;
  // Diffusion1D const * m_diff;
  // AProvider const * m_rateA;
  // BProvider const * m_rateB;
  // AssetClassA m_A;
  // AssetClassB m_B;
  // bool m_RN;
public:
  MCEngine1D(long a_MaxL, long a_MaxB):
    m_MaxL(a_MaxL), m_MaxP(a_MaxB),
    m_paths(new double[m_MaxL * m_MaxP])
    // m_L(0), m_P(0),
    // m_tau(nan), m_t0(nan),
    // m_diff(nullptr),
    // m_rateA(nullptr), m_rateB(nullptr),
    // m_A(AssetClassA::UNDEFINED), m_B(AssetClassB::UNDEFINED)
  {
      if(m_MaxL <= 0 || m_MaxP <= 0){
        throw std::invalid_argument("invalid maxL or maxP\n");
      }
  }
  void Simulate(time_t  a_t0, // current (pricing) time
                time_t a_T,   // Expir. time
                int a_tau_min,
                Diffusion1D const a_diff,
                AProvider const * a_rateA,
                BProvider const * a_rateB,
                AssetClassA a_A,
                AssetClassB a_B,
                bool a_isRN);
};
}
