#include <iostream>
#include <random>
#include "Core" //Eigen Library
#include "nmf.h"
//using namespace std;

#define EIGEN_NO_DEBUG         // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE   // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY        // LGPLライセンスのコードを使わない．
#define N 10 



int main()
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> d(0,10);

    Eigen::MatrixXd A = Eigen::MatrixXd::Ones(N, N);
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(N, N);
    Eigen::MatrixXd u;
    Eigen::VectorXd err;
    int processed;
    Decom hoge;

    nmf a(A);
    std::cout << A << std::endl;
    hoge = a.fit(50,1000);
    for(int i=0;i<hoge.count;i++){
        std::cout << i << "," << hoge.err(i) << std::endl;
    }

    return 0;
}
