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

#ifndef FMICPP_FMUINSTANCE_HPP
#define FMICPP_FMUINSTANCE_HPP

#include <vector>
#include "../xml/ModelDescription.hpp"
#include "../fmi2Functions.h"

using std::vector;

namespace fmicpp::fmi2::import {

    class FmuInstance {

    protected:
        
        double simulationTime = 0.0;

        bool instantiated = false;
        bool terminated = false;

        xml::ModelDescription& modelDescription;

    public:

        const xml::ModelDescription& getModelDescription() const {
            return modelDescription;
        }

        const double getSimulationTime() const {
            return simulationTime;
        }

        const bool isInstantiated() const {
            return instantiated;
        }

        const bool isTerminated() const {
            return terminated;
        }

        virtual void init(double start = 0, double stop = 0) = 0;

        virtual fmi2Status reset() = 0;

        virtual fmi2Status terminate() = 0;

        virtual bool canGetAndSetFMUstate() const = 0;

        virtual fmi2Status getFMUstate(fmi2FMUstate &state) = 0;

        virtual fmi2Status setFMUstate(const fmi2FMUstate state) = 0;

        virtual fmi2Status freeFMUstate(fmi2FMUstate &state) = 0;

        virtual bool canSerializeFmuState() const = 0;

        virtual fmi2Status serializeFMUstate(vector<fmi2Byte> &serializedState) = 0;

        virtual fmi2Status deSerializeFMUstate(const vector<fmi2Byte> &serializedState, fmi2FMUstate &state) = 0;

        virtual bool providesDirectionalDerivative() const = 0;

        virtual fmi2Status getDirectionalDerivative(
                const vector<fmi2ValueReference> &vUnkownRef,
                const vector<fmi2ValueReference > &vKnownRef,
                const vector<fmi2Real> &dvKnownRef,
                vector<fmi2Real> &dvUnknownRef) = 0;

        virtual ~FmuInstance(){};

    };

}

#endif //FMICPP_FMUINSTANCE_HPP
