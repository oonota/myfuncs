#define EIGEN_NO_DEBUG         // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE   // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY        // LGPLライセンスのコードを使わない．

#include <iostream>
#include <random>
#include "Core" //Eigen Library
#include "nmf.h"
//using namespace std;

#define N 10 


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
    int processed;
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
