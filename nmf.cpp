#define EIGEN_NO_DEBUG // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．

#include<iostream>
#include<random>
#include"Eigen/Core"
using namespace std;


#define N 10

class nmf
{
    private:
        Eigen::Matrix2d u;
        Eigen::Matrix2d v;
        int row,col;
        int k;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        nmf(const Eigen::MatrixXd& x);
        void test(void);
};


int main(){

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(2,5);
    nmf a(A);
    a.test();
    Eigen::MatrixXd r = Eigen::MatrixXd::Constant(3,3,dist(mt));
    cout << r << endl;


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
nmf::nmf(const Eigen::MatrixXd& x)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0,1.0);

    this->row = x.rows();
    this->col = x.cols();

}
void nmf::test(void)
{
  cout << this->row << endl;
  cout << this->col << endl;
}
