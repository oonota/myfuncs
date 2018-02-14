#ifndef NMF_H
#define NMF_H

#include "decomposition_result.h"

class nmf
{
  private:
    Eigen::MatrixXd a;
    Eigen::MatrixXd u;
    Eigen::MatrixXd v;
    Eigen::VectorXd err;
    int row, col;
    int k;
    int processed_iter;
		int hoge;

  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    nmf();
    Decom fit(const Eigen::MatrixXd &a,int k, int max_iter);
    void init_uv(void);
    void set_k(int k);
    double sqerr(void);
    void normalize(void);
};
#endif 
