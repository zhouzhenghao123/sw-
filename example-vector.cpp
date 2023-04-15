#define syncall() asm volatile();
#include "hthread.hpp"
#include "iterate-vector.hpp"
//#include <iostream>
#include "dataset.hpp"
#include "operator-helper.hpp"
#include <tuple>
using namespace unatpp;
void athread_init();
struct ArrayOpt {
  void operator()(int IDX, DataSet<Vec, In, double> a1, DataSet<Vec, In, double> b1,
                  DataSet<Vec, In, double> c1, DataSet<Vec, In, double> a2,
                  DataSet<Vec, In, double> b2, DataSet<Vec, In, double> c2,
                  DataSet<Vec, In, double> c3, DataSet<Vec, Out, double> d1,
                  DataSet<Vec, Out, double> d2)
  {
    d1[IDX] = a1[IDX] + b1[IDX] - c1[IDX] * c3[IDX];
    d2[IDX] = a2[IDX] * c3[IDX] + b2[IDX] / c3[IDX] - c2[IDX];
  }
};
template <typename ArrayOpt, typename... Args, int... Is>
void __iterateV(int n, ArrayOpt &&opt, seq_t<Is...> seq, Args... sets)
{
  constexpr int BLKSZ = 4;
  auto buffer = std::make_tuple(sets.template vec_make_buffer<BLKSZ>()...);
  for (int ist = _MYID*BLKSZ; ist < n; ist += BLKSZ*64) {
    int ied = ist + BLKSZ;
    if (ied > n) ied = n;
    runall(sets.template enter_range<Vec>(std::get<Is>(buffer), ist, ied));
    for (int i = ist; i < ied; i++) {



 opt(i, std::get<Is>(buffer).pseudo_dataset()...); }
    runall(sets.template leave_range<Vec>(std::get<Is>(buffer), ist, ied));
  }
}


 template <typename ArrayOpt, typename... Args, int... Is>
 void __iterateVP(int n, ArrayOpt &&opt, seq_t<Is...> seq, Args *...sets)
 {
   auto oparg_list = get_args<1>(opt);
     auto datasets = oparg_list.convert_pointers(std::make_tuple(sets...));
       __iterateV(n, opt, seq, std::get<Is>(datasets)...);
       }


       template <typename ArrayOpt, typename... Args> void iterateV(int n, ArrayOpt &&opt, Args *...sets){
         __iterateVP(n, opt, get_args<1>(opt).iseq, sets...);
         }

  int main(){
 ArrayOpt aaaa;
  DataSet<Vec, In, double> a1;
  DataSet<Vec, In, double> b1;
  DataSet<Vec, In, double> c1;
  DataSet<Vec, Out, double> d1;
  DataSet<Vec, In, double> a2;
  DataSet<Vec, In, double> b2;
  DataSet<Vec, In, double> c2;
  DataSet<Vec, Out, double> d2;
  DataSet<Vec, In, double> c3;
  double aa1[1024] = {1.2};
  double ab1[1024] = {1.1};
  double ac1[1024] = {0.3};
  double ad1[1024] = {0};
  double ac3[1024] = {1};
  double aa2[1024] = {1.2};
  double ac2[1024] = {1.1};
  double ab2[1024] = {0.3};
  double ad2[1024] = {0};
for(int i=0;i<1024;i++)
{
  aa1[i] = 1.2;
  ab1[i] = 1.1;
  ac1[i] = 0.3;
  ad1[i] = 0;
  ac3[i] = 1;
  aa2[i] = 1.2;
  ac2[i] = 1.1;
  ab2[i] = 0.3;
  ad2[i] = 0;
}
  a1.val = aa1;
  b1.val = ab1;
  c1.val = ac1;
  d1.val = ad1;
  a2.val = aa2;
  b2.val = ab2;
  c2.val = ac2;
  d2.val = ad2;
  c3.val = ac3;    
//iterateV(10,aaaa, aa1, ab1, ac1, aa2, ab2, ac2, ac3, ad1, ad2); 
      hthread_init();
        hparallel([&]  {
              
/**  constexpr int BLK = 128;
                for (int ist = _MYID*BLK; ist < 65536; ist += 64*BLK) {
                        int a_ldm[BLK];
                        int b_ldm[BLK];
                        int c_ldm[BLK];
                        dma_getn(a+ist, a_ldm, BLK);
                        dma_getn(b+ist, b_ldm, BLK);
                        for (int i = 0; i < BLK; i ++) {
                                c_ldm[i] = a_ldm[i] + b_ldm[i];
                        }
                        dma_putn(c+ist, c_ldm, BLK);}
**/
//iterateV(10,aaaa, aa1, ab1, ac1, aa2, ab2, ac2, ac3, ad1, ad2);
/**template <typename ArrayOpt, typename... Args, int... Is>
void __iterateV(int n, ArrayOpt &&opt, seq_t<Is...> seq, Args... sets)
{
  constexpr int BLKSZ = 4;
  auto buffer = std::make_tuple(sets.template vec_make_buffer<BLKSZ>()...);
  for (int ist = 0; ist < n; ist += BLKSZ) {
    int ied = ist + BLKSZ;
    if (ied > n) ied = n;
    runall(sets.template enter_range<Vec>(std::get<Is>(buffer), ist, ied));
    for (int i = ist; i < ied; i++) { opt(i, std::get<Is>(buffer).pseudo_dataset()...); }
    runall(sets.template leave_range<Vec>(std::get<Is>(buffer), ist, ied));
  }
}
**/
//template <typename ArrayOpt, int... DPs, int... CPs, typename... TPs>
//void iterateV(int n, ArrayOpt &&opt, DataSet<DPs, CPs, TPs>... sets)
//{
 // __iterateV(n, opt, get_args<1>(opt).iseq, sets...);
//}
/**
template <typename ArrayOpt, typename... Args, int... Is>
void __iterateVP(int n, ArrayOpt &&opt, seq_t<Is...> seq, Args *...sets)
{
  auto oparg_list = get_args<1>(opt);
  auto datasets = oparg_list.convert_pointers(std::make_tuple(sets...));
  __iterateV(n, opt, seq, std::get<Is>(datasets)...);
}


template <typename ArrayOpt, typename... Args> void iterateV(int n, ArrayOpt &&opt, Args *...sets){
  __iterateVP(10, opt, get_args<1>(opt).iseq, sets...);
}
**/
iterateV(1024,aaaa, aa1, ab1, ac1, aa2, ab2, ac2, ac3, ad1, ad2);


        });
printf("%lf\n",ad1[134]);
}
 
