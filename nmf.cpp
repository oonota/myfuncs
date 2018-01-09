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
    void test(void);
};

int main()
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> d(0,10);

    Eigen::MatrixXd A = Eigen::MatrixXd::Ones(N, N);
    Eigen::MatrixXd B = Eigen::MatrixXd::Ones(N, N);
    Eigen::MatrixXd r = Eigen::MatrixXd::Zero(4, 3);
    Eigen::MatrixXd u;
    Eigen::VectorXd err;
    int processed;;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A(i, j) = (double)d(mt);
        }
    }
    nmf a(A);
    a.fit(7,1000);

    //std::cout << A << std::endl;
    //std::cout << a.get_uv() << std::endl;
    //std::cout << a.sqerr() << std::endl;
    u = a.get_u();
    //std::cout << u(0,0) << std::endl;
    err = a.get_err();
    processed = a.get_iterend();
    for(int i=0;i<processed;i++){
std::cout << i << "," << err(i) << std::endl;
    }
    

    /*
    a.fit(2, 100);
    a.test();
    A(1,1) = 1.0;
    A(1,3) = 4.0;
    A(4,4) = 2.0;
    A(0,0) = 3.0;
    A(4,0) = 9.0;
    B(1,1) = 0.5;
    B(1,3) = 2.0;
    B(4,4) = 1.0;
    */



        //vd = this->u * this->v * this->v.transpose();
        //this->u = this->u.cwiseProduct(vn.cwiseQuotient(vd));

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
nmf::nmf(const Eigen::MatrixXd &a)
{
    this->a = a;
    this->row = a.rows();
    this->col = a.cols();
}
void nmf::test(void)
{
    std::cout << this->row << std::endl;
    std::cout << this->col << std::endl;
    std::cout << this->a << std::endl;
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
    int i;
    double error = 0.0;
    Eigen::MatrixXd un;
    Eigen::MatrixXd ud;
    Eigen::MatrixXd vn;
    Eigen::MatrixXd vd;
    this->err = Eigen::VectorXd::Zero(max_iter);
    set_k(k);
    init_uv();

    for (i = 0; i < max_iter; i++)
    {

        error = sqerr();
        this->err(i) = error;
        if (error == 0.0){
            break;
        }
        // update rules
        vn = this->u.transpose()*this->a;
        vd = this->u.transpose()*this->u*this->v;
        this->v = this->v.cwiseProduct(vn.cwiseQuotient(vd));

        un = this->a * this->v.transpose();
        ud = this->u * this->v * this->v.transpose();
        this->u = this->u.cwiseProduct(un.cwiseQuotient(ud));


    }
        this->processed_iter = i;
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
    hoge = this->a - uv;
    hoge = hoge.cwiseProduct(hoge);
    return hoge.sum();
}
Eigen::MatrixXd nmf::get_uv(void)
{
 return (this->u*this->v);
}
Eigen::MatrixXd nmf::get_u(void)
{
 return this->u;
}
Eigen::MatrixXd nmf::get_v(void)
{
 return this->v;
}
Eigen::VectorXd nmf::get_err(void)
{
    return this->err;
}
int nmf::get_iterend(void)
{
    return this->processed_iter;
}
