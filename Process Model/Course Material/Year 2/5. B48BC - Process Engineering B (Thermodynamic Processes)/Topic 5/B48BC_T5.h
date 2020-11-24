//
//  B48BC_T5.h
//  Process Model
//
//  Created by Matthew Cheung on 23/11/2020.
//

#ifndef B48BC_T5_h
#define B48BC_T5_h

/// This subroutine is used to guide the user through calculating the thermodynamic feasibility of a system undergoing an isobaric change.
void SteadyStateEntropyBalance(void);

/// This subroutine is used to guide the user through calculating the thermodynamic feasibility of a heat engine/pump with multiple hot and cold reservoirs.
void EngineEntropyBalance(void);

/// This subroutine is used to guide the user through estimating the entropy change of a system through the Gibbs-Duhem statement combined with the entropy Maxwell equation. This subroutine is not applicable where the working fluid changes phase between the two end-states.
void StateEntropyChange(void);

#endif /* B48BC_T5_h */
