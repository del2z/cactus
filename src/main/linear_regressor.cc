//------------------------------------------------------------------------------
// Main - Linear Regressors, Lasso, Ridge and Elastic Net
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include <cstddef>
#include "gflags/gflags.h"
#include "glog/logging.h"

#include "io/data_parser.h"
#include "objective/obj_mse.h"
#include "regularizer/reg_l1.h"
#include "regularizer/reg_l2.h"
#include "model/linear.h"

DEFINE_string(task, "train,pred", "specific task of learner doing");
DEFINE_string(learner, "linear,lasso,ridge,elsnet", "regressors for training or predicting");
DEFINE_double(coef_l1, 0.1, "coefficient of L1 regularization terms, only effective when learner is 'lasso' and 'elsnet'");
DEFINE_double(coef_l2, 0.1, "coefficient of L2 regularization terms, only effective when learner is 'ridge' and 'elsnet'");
DEFINE_double(rate, 1.2, "learning rate");
DEFINE_int32(epoch, 50, "max epoches for optimization");
DEFINE_string(train_data, "", "data for training model");
DEFINE_string(test_data, "", "data for evaluating model");
DEFINE_string(pred_data, "", "data for predicting labels");
DEFINE_string(model_out, "", "trained model for dumping");
DEFINE_string(model_in, "", "saved model for loading");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    FLAGS_colorlogtostderr = 1;
    FLAGS_stderrthreshold = 0;

    if (FLAGS_task.compare("train") == 0) {
        if (FLAGS_train_data.compare("") == 0) {
            LOG(ERROR) << "No training data specified with '--train_data'.";
            exit(1);
        }

        cactus::DataParser* parser = new cactus::DataParser();
        cactus::DMatrix train_data = parser->Load(FLAGS_train_data, "svm");
        VLOG(1) << "training dataset (" << train_data.num_rows() << ", "
            << train_data.num_cols() << ")";

        cactus::DMatrix test_data = cactus::DMatrix();
        if (FLAGS_test_data.compare("") != 0) {
            test_data = parser->Load(FLAGS_test_data, "svm");
            VLOG(1) << "testing dataset (" << test_data.num_rows() << ", "
                << test_data.num_cols() << ")";
        }

        cactus::Linear* linr = nullptr;
        if (FLAGS_learner.compare("lasso") == 0) {
            linr = new cactus::Linear(new cactus::ObjMse(),
                    new cactus::RegL1(FLAGS_coef_l1),
                    new cactus::OptSgd(FLAGS_rate));
        } else if (FLAGS_learner.compare("ridge") == 0) {
            linr = new cactus::Linear(new cactus::ObjMse(),
                    new cactus::RegL2(FLAGS_coef_l1),
                    new cactus::OptSgd(FLAGS_rate));
        } else if (FLAGS_learner.compare("elsnet") == 0) {
            linr = new cactus::Linear(new cactus::ObjMse(),
                    new cactus::RegL2(FLAGS_coef_l1),
                    new cactus::OptSgd(FLAGS_rate));
        } else {
            if (FLAGS_learner.compare("linear") != 0) {
                LOG(WARNING) << "Undefined learner, using 'linear' instead.";
            }
            linr = new cactus::Linear(new cactus::ObjMse(),
                    new cactus::RegL1(0),
                    new cactus::OptSgd(FLAGS_rate));
        }
        linr->TrainBatch(train_data, FLAGS_epoch);
        if (test_data.num_rows() > 0 && test_data.num_cols() > 0) {
        }

        if (FLAGS_model_out.compare("") != 0) {
        }
    } else if (FLAGS_task.compare("pred") == 0) {
        if (FLAGS_model_in.compare("") == 0) {
            LOG(ERROR) << "No linear model specified with '--model_in'.";
            exit(1);
        }
        if (FLAGS_pred_data.compare("") == 0) {
            LOG(ERROR) << "No predicting data specified with '--pred_data'.";
            exit(1);
        }

        cactus::DataParser* parser = new cactus::DataParser();
        cactus::DMatrix pred_data = parser->Load(FLAGS_pred_data, "svm");
        VLOG(1) << "predicting dataset (" << pred_data.num_rows() << ", "
            << pred_data.num_cols() << ")";
    }
    return 0;
}
