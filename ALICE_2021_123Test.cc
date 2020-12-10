// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/UnstableParticles.hh"

namespace Rivet {


  /// @brief Add a short analysis description here
  class ALICE_2021_123Test : public Analysis {
  public:

    /// Constructor
    DEFAULT_RIVET_ANALYSIS_CTOR(ALICE_2021_123Test);

    /// @name Analysis methods
    ///@{

    /// Book histograms and initialise projections before the run
    void init() {
        
        // Initialise and register projections
        declare( UnstableParticles( Cuts::absrap < 0.5 ), "AnalysisCuts");
        
        // Book histograms
        book(_H2["PhiMeson_Plot"], "PhiMeson_Plot", fArrNtup, fArrMult);
    }

    /// Perform the per-event analysis
    void analyze(const Event& event) {
        
        // Phi Meson Analysis
        const UnstableParticles &_EventParticles = apply<UnstableParticles>(event, "AnalysisCuts");
        
        int nPhi = 0;
        int nPrt = 0;
        for ( const Particle& Current_Particle : _EventParticles.particles() ) {
            
            // Filling pT spectrum for Phi Meson
            if ( Current_Particle.abspid() == 333 ) {
                ++nPhi;
            }
            
            // Evalutating multiplicity
            if ( Current_Particle.isStable() && Current_Particle.isCharged() )  {
                ++nPrt;
            }
        }
        _H2["PhiMeson_Plot"]->fill(double(nPhi),nPrt);
    }

    /// Normalise histograms etc., after the run
    void finalize() {
        
        scale(_H2["PhiMeson_Plot"], 1./sumW());

    }

    ///@}

    /// @name Histograms
    ///@{
      map<string, Histo1DPtr> _H1;
      map<string, Histo2DPtr> _H2;
      map<string, Scatter2DPtr> _S2;
    ///@}
      
      const std::vector<double> fArrMult = {0.0,42.,46.,52.,57.,72.,94.,120.,156.,208.,500.};
      const std::vector<double> fArrNtup = {-0.5,0.5,1.5,2.5,3.5,4.5};
      
  };


  DECLARE_RIVET_PLUGIN(ALICE_2021_123Test);

}
