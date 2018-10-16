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

#include <fmi4cpp/fmi2/xml/DefaultExperiment.hpp>

using fmi4cpp::fmi2::DefaultExperiment;

fmi4cpp::fmi2::DefaultExperiment::DefaultExperiment() {}

DefaultExperiment::DefaultExperiment(const std::optional<double> &startTime, const std::optional<double> &stopTime,
                                     const std::optional<double> &stepSize, const std::optional<double> &tolerance)
        : startTime_(startTime), stopTime_(stopTime), stepSize_(stepSize), tolerance_(tolerance) {}


std::optional<double> fmi4cpp::fmi2::DefaultExperiment::startTime() const {
    return startTime_;
}

std::optional<double> fmi4cpp::fmi2::DefaultExperiment::stopTime() const {
    return stopTime_;
}

std::optional<double> fmi4cpp::fmi2::DefaultExperiment::stepSize() const {
    return stepSize_;
}

std::optional<double> fmi4cpp::fmi2::DefaultExperiment::tolerance() const {
    return tolerance_;
}
