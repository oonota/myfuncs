#ifndef NMF_H
#define NMF_H
typedef struct {
    Eigen::MatrixXd u;
    Eigen::MatrixXd v;
    Eigen::VectorXd err;
    int count;
} Decom;


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
    Decom fit(int k, int max_iter);
    void init_uv(void);
    void set_k(int k);
    double sqerr(void);
    void normalize(void);
};
#endif 
