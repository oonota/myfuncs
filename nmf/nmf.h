#ifndef NMF_H
#define NMF_H
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

  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    nmf(const Eigen::MatrixXd &a);
    void fit(int k, int max_iter);
    void init_uv(void);
    void set_k(int k);
    double sqerr(void);
    Eigen::MatrixXd get_u(void); 
    Eigen::MatrixXd get_v(void); 
    Eigen::MatrixXd get_uv(void); 
    Eigen::VectorXd get_err(void);
    int get_iterend(void);
    void normalize(void);
    void test(void);
};
#endif 
