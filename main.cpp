//#include "Core" //Eigen Library
#include "Eigen/Core" //Eigen Library
#include "nmf.h"
#include "decomposition_result.h"
#include <iostream>
#include <random>
// using namespace std;

#define EIGEN_NO_DEBUG         // コード内のassertを無効化．
#define EIGEN_DONT_VECTORIZE   // SIMDを無効化．
#define EIGEN_DONT_PARALLELIZE // 並列を無効化．
#define EIGEN_MPL2_ONLY // LGPLライセンスのコードを使わない．
#define N 10

int main() {

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::uniform_int_distribution<int> d(0, 10);

  Eigen::MatrixXd A = Eigen::MatrixXd::Zero(N, N);
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(N, N);
  Eigen::MatrixXd u;
  Eigen::VectorXd err;
  int processed;
  Decom hoge;
  nmf a;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A(i, j) = d(mt);
    }
  }

  std::cout << A << std::endl;
  hoge = a.fit(A, N / 2, 1000);
  for (int i = 0; i < hoge.count; i++) {
    std::cout << i << "," << hoge.err(i) << std::endl;
  }

  return 0;
}
