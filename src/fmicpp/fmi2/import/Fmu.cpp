/*
 * The MIT License
 *
 * Copyright 2017-2018 Norwegian University of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <zip.h>
#include <fmicpp/fmi2/import/Fmu.hpp>
#include <fmicpp/fmi2/import/CoSimulationSlaveBuilder.hpp>

using namespace std;
using namespace fmicpp::fmi2::import;

Fmu::Fmu(const std::string fmu_file): fmu_file_(fmu_file) {

    this->tmp_path_ = fs::temp_directory_path() /= fs::path(fmu_file).stem();
    create_directories(tmp_path_);

    extractFmu();

    string modelDescriptionPath = tmp_path_.string() + "/modelDescription.xml";

    this->modelDescription_ = make_unique<ModelDescription>(ModelDescription());
    this->modelDescription_->load(modelDescriptionPath);

    ifstream t(modelDescriptionPath);
    this->model_description_xml_ = string((istreambuf_iterator<char>(t)),
                                          istreambuf_iterator<char>());

}

const ModelDescription &Fmu::getModelDescription() const {
    return *modelDescription_;
}

const string &Fmu::getModelDescriptionXml() const {
    return model_description_xml_;
}

unique_ptr<CoSimulationSlaveBuilder> Fmu::asCoSimulationFmu() {
    return unique_ptr<CoSimulationSlaveBuilder>(new CoSimulationSlaveBuilder(*this));
}


bool Fmu::extractFmu() {
    int* err;
    zip* za = zip_open(fmu_file_.c_str(), 0, err);
    if (za == nullptr) {
        return false;
    }

    struct zip_file *zf;
    struct zip_stat sb;
    for (int i = 0; i < zip_get_num_entries(za, 0); i++) {
        if (zip_stat_index(za, i, 0, &sb) == 0) {

            if (sb.size == 0) {
                fs::create_directories(tmp_path_ / sb.name);
            } else {
                zf = zip_fopen_index(za, i, 0);
                char* contents = new char[sb.size];
                zip_fread(zf, contents, 0);
                if (!ofstream ((tmp_path_ / sb.name).c_str()).write(contents, sb.size)) {
                    return false;
                }
                zip_fclose(zf);
            }

        }
    }

    zip_close(za);

}


Fmu::~Fmu() {

    for (const shared_ptr<FmuInstance>& instance : instances_) {
        if (!instance->isTerminated()) {
            instance->terminate();
        }
    }

    remove_all(this->tmp_path_);
}
