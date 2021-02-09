/*запретить копи-конструктор
запретить оператор присваивания
сделать доступ на последий элемент массива после симуляции
занулить массив исходно
объявить деструктор
*/

#pragma once
#include <cmath>
#include <ctime>
#include <stdexcept>
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
public:
  MCEngine1D(long a_MaxL, long a_MaxB):
    m_MaxL(a_MaxL), m_MaxP(a_MaxB),
    m_paths(new double[m_MaxL * m_MaxP])
  {
      if(m_MaxL <= 0 || m_MaxP <= 0){
        throw std::invalid_argument("invalid maxL or maxP\n");
      }
  }
  void Simulate(time_t  a_t0, // current (pricing) time
                time_t a_T,   // Expir. time
                int a_tau_min,
                long a_P,
                double a_S0,
                Diffusion1D const a_diff,
                AProvider const * a_rateA,
                BProvider const * a_rateB,
                AssetClassA a_A,
                AssetClassB a_B,
                bool a_isRN);
};
}
