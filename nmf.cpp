#define EIGEN_NO_DEBUG         // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE   // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY        // LGPLライセンスのコードを使わない．

#include <iostream>
#include <random>
#include "Eigen/Core"
//using namespace std;

#define N 10

class nmf
{
  private:
    Eigen::MatrixXd x;
    Eigen::MatrixXd u;
    Eigen::MatrixXd v;
    int row, col;
    int k;
    int processed_iter;

  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    nmf(const Eigen::MatrixXd &x);
    void fit(int k, int max_iter);
    void init_uv(void);
    void set_k(int k);
    double sqerr(void);
    void test(void);
};

int main()
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(2, 5);
    Eigen::MatrixXd r = Eigen::MatrixXd::Zero(4, 3);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            r(i, j) = dist(mt);
        }
    }
    nmf a(r);

    std::cout << r << std::endl;
    a.fit(2, 100);
    a.test();

    /*
    double d = 0.0;
    for(int i=0;i<N;i++){
        //cout << mt() << endl;
        //cout << rd() << endl;
        //d = dist(mt);
        //cout << d << endl;
    }
    */

    return 0;
}
nmf::nmf(const Eigen::MatrixXd &x)
{
    this->x = x;
    this->row = x.rows();
    this->col = x.cols();
}
void nmf::test(void)
{
    std::cout << this->row << std::endl;
    std::cout << this->col << std::endl;
    std::cout << this->x << std::endl;
    std::cout << this->u << std::endl;
    std::cout << this->v << std::endl;
}
void nmf::init_uv(void)
{
    int row, col;
    row = this->row;
    col = this->col;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    this->u = Eigen::MatrixXd::Zero(row, k);
    this->v = Eigen::MatrixXd::Zero(k, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < k; j++)
        {
            this->u(i, j) = dist(mt);
        }
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < col; j++)
        {
            this->v(i, j) = dist(mt);
        }
    }
}
void nmf::fit(int k, int max_iter)
{
    double err = 0.0;
    set_k(k);
    init_uv();

    for (int i = 0; i < max_iter; i++)
    {

        err = sqerr();
        if (err == 0.0)
        {
            this->processed_iter = i;
            break;
        }
        // update rules
    }
}
void nmf::set_k(int k)
{
    this->k = k;
}
double nmf::sqerr(void)
{
    Eigen::MatrixXd hoge;
    Eigen::MatrixXd uv;

    uv = this->u * this->v;
    hoge = x - uv;
    hoge.prod();
    return hoge.sum();
}