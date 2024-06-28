// main01.cc is a part of the PYTHIA event generator.
// Copyright (C) 2023 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Keywords: basic usage; charged multiplicity;

// This is a simple test program. It fits on one slide in a talk.
// It studies the charged multiplicity distribution at the LHC.

#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
  pythia.readString("Beams:eCM = 8000.");
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 50.");
  pythia.readString("PartonLevel:all=off");
  pythia.readString("HadronLevel:all=off");
  pythia.readString("PhaseSpace:bias2Selection=on");
  pythia.readString("PhaseSpace:bias2SelectionPow=6.");
  pythia.readString("PhaseSpace:bias2SelectionRef=50.");
  pythia.init();
  Hist mult("charged multiplicity", 100, -0.5, 799.5);
  Hist pTevent("Hard-process-pT", 100, 0., 1000.);
  Hist pTweighted("Weighted -hard-process -pT", 100, 0., 1000.);
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < 100; ++iEvent) {
    if (!pythia.next()) continue;
    // Find number of all final charged particles and fill histogram.
    int nCharged = 0;
    for (int i = 0; i < pythia.event.size(); ++i)
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged())
        ++nCharged;
    mult.fill( nCharged );
    double pTnow = pythia.info.pTHat();
    double weight = pythia.info.weight();
    pTweighted.fill(pTnow ,weight);
    pTevent.fill(pTnow);
  // End of event loop. Statistics. Histogram. Done.
  }
  pythia.stat();
  cout << pTevent << pTweighted;
  return 0;
}
