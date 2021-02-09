#pragma once
inline double YearFrac(time_t a_t0){
  constexpr double SecY = 365.25*886400;
  return 19700 +double(a_t0)/SecY;
}
