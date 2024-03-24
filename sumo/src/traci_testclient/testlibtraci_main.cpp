/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
// Copyright (C) 2001-2023 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    testlibtraci_main.cpp
/// @author  Michael Behrisch
/// @date    Tue, 20 Nov 2001
///
// Testing libtraci for C++
/****************************************************************************/
#ifdef _MSC_VER
// Avoid some noisy warnings with Visual Studio
#pragma warning(disable:4820 4514 5045 4668 4710)
#endif

#include <iostream>
#include <libsumo/libtraci.h>


// ===========================================================================
// main function
// ===========================================================================
int
main(int argc, char** argv) {
    std::vector<std::string> options;
    for (int i = 1; i < argc; i++) {
        options.push_back(argv[i]);
    }
    try {
        libtraci::Simulation::start(options);
        // libtraci::Simulation::init(3000);
        std::cout << "Simulation started\n";
        for (int i = 0; i < 50; i++) {
            libtraci::Simulation::step();
        }
        libtraci::Simulation::close();
    } catch (const std::runtime_error& e) {
        std::cerr << "Could not start simulation: " << e.what() << "\n";
    }
}


/****************************************************************************/
