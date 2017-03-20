//------------------------------------------------------------------------------
// Main - Linear Regressors, Lasso, Ridge and Elastic Net
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------

#include <iostream>
#include "gflags/gflags.h"

DEFINE_string(task, "train,pred", "specific task of learner doing");
DEFINE_string(learner, "linear,lasso,ridge,elsnet", "regressors for training or predicting");
DEFINE_double(coef_l1, 0.1, "coefficient of L1 regularization terms, only effective when learner is 'lasso' and 'elsnet'");
DEFINE_double(coef_l2, 0.1, "coefficient of L2 regularization terms, only effective when learner is 'ridge' and 'elsnet'");
DEFINE_string(train_data, "", "data for training model");
DEFINE_string(test_data, "", "data for evaluating model");
DEFINE_string(pred_data, "", "data for predicting labels");
DEFINE_string(model_out, "", "trained model for dumping");
DEFINE_string(model_in, "", "saved model for loading");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "Build success." << std::endl;
    return 0;
}
