#include "IRProviderConst.h"
#include <cstdio>
#include <cstdlib>
namespace SiriusFM{
  IRProvider<IRModeE::Const>::IRProvider
  (char const * a_file){
    char  buff[64];
    double r;
    for(int i = 0; i < int(CcyE::N); i++){
      m_IRs[i] = 0;
    }
    if(a_file == nullptr || *a_file == '\0'){
      return;
    }
    FILE * f;
    f = fopen(a_file, "w");
    while(fgets(buff, 64, f)!=nullptr){
      buff[3]='\0';
      r = atof(buff+4);
      m_IRs[int(str2CcyE(buff))] = r;
    }
    fclose(f);
  }
}
