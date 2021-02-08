#pragma once
#include "MCEngine1D.h"
namespace SiriusFM{
  template <typename Diffusion1D,
            typename AProvider,
            typename BProvider,
            typename AssetClassA,
            typename AssetClassB>
  inline
  void MCEngine1D <Diffusion1D,
                   AProvider,
                   BProvider,
                   AssetClassA,
                   AssetClassB>
  ::Simulate(time_t  a_t0, // current (pricing) time
             time_t a_T,   // Expir. time
             int a_tau_min,
             Diffusion1D const a_diff,
             AProvider const * a_rateA,
             BProvider const * a_rateB,
             AssetClassA a_A,
             AssetClassB a_B,
             bool a_isRN)
  { // Checks
    assert(a_diff!=nullptr and
           a_rateA != nullptr &&
           a_rateB!=nullptr &&
           a_A != AssetClassA::UNDEFINED &&
           a_B != AssetClassB::UNDEFINED &&
           a_t0 <= a_T &&
           a_tau_min >0);
  }
}
