#define EIGEN_NO_DEBUG         // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE   // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY        // LGPLライセンスのコードを使わない．

#include <iostream>
#include <random>
#include "Core" //Eigen Library
#include "nmf.h"
//using namespace std;

#define N 100 


int main()
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> d(0,10);

    Eigen::MatrixXd A = Eigen::MatrixXd::Ones(N, N);
    Eigen::MatrixXd B = Eigen::MatrixXd::Ones(N, N);
    Eigen::MatrixXd hoge;
    Eigen::MatrixXd u;
    Eigen::VectorXd err;
    int processed;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A(i, j) = (double)d(mt);
        }
    }
    nmf a(A);
    a.fit(30,1000);
    err = a.get_err();
    processed = a.get_iterend();
    for(int i=0;i<processed;i++){
        std::cout << i << "," << err(i) << std::endl;
    }
//std::cout << err << std::endl;
//std::cout << err.transpose() << std::endl;
/*
Eigen::RowVectorXd r;
Eigen::MatrixXd s = Eigen::MatrixXd::Zero(N,N);
std::cout << A << std::endl;
r = A.colwise().sum().array().sqrt();
std::cout << A.colwise().sum() << std::endl;
std::cout << r << std::endl;
s.rowwise() = r;
//A.colwise() /= r;
std::cout << (s) << std::endl;
*/

//std::cout << A.cwiseQuotient(s) << std::endl;
     


    return 0;
}
