#ifndef DECOMPOSITION_RESULT
#define DECOMPOSITION_RESULT

typedef struct {
    Eigen::MatrixXd u;
    Eigen::MatrixXd v;
    Eigen::VectorXd err;
    int count;
} Decom;

#endif
