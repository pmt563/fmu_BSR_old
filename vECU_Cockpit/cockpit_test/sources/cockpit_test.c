/* ---------------------------------------------------------------------------*
 * Implementation of Cockpit_ECU in Co-Simulation mode
 * Inputs:
 *  In_UserConfirmAirbagState           (integer): User confirmation of airbag state
 *  In_PassengerAirbagDisableLamp_bo    (boolean): Disable lamp input
 *  In_PassengerAirbagEnableLamp_bo     (boolean): Enable lamp input
 *  In_PassengerAirbagWarningState_se   (integer): Warning state input
 * Outputs:
 *  Out_UserConfirmAirbagState_se       (integer): Confirmed airbag state
 *  Out_PassengerAirbagWarningState_se  (integer): Warning state output
 *  Out_PassengerAirbagDisableLamp_bo   (boolean): Disable lamp output
 * Logic:
 *  Out_UserConfirmAirbagState_se = In_UserConfirmAirbagState
 *  Out_PassengerAirbagWarningState_se = In_PassengerAirbagWarningState_se
 *  Out_PassengerAirbagDisableLamp_bo = In_PassengerAirbagDisableLamp_bo && !In_PassengerAirbagEnableLamp_bo
 * ---------------------------------------------------------------------------*/

// Define class name and unique id
#define MODEL_IDENTIFIER cockpit_test
#define MODEL_GUID "{f1e2d3c4-b5a6-7890-abcd-1234567890ef}"

// Define model size
#define NUMBER_OF_REALS             0        
#define NUMBER_OF_INTEGERS          4
#define NUMBER_OF_BOOLEANS          3
#define NUMBER_OF_STRINGS           0
#define NUMBER_OF_STATES            0       
#define NUMBER_OF_EVENT_INDICATORS  0

// Include FMU header files, typedefs, and macros
#include "fmuTemplate.h"

// Define all model variables and their value references
#define In_UserConfirmAirbagState           0  // input
#define In_PassengerAirbagDisableLamp_bo    0  // input
#define In_PassengerAirbagEnableLamp_bo     1  // input
#define In_PassengerAirbagWarningState_se   1  // input
#define Out_UserConfirmAirbagState_se       2  // output
#define Out_PassengerAirbagWarningState_se  3  // output
#define Out_PassengerAirbagDisableLamp_bo   2  // output

// Called by fmi2Instantiate
void setStartValues(ModelInstance *comp) {
    // input
    i(In_UserConfirmAirbagState)            = 0;         // Initial input value
    b(In_PassengerAirbagDisableLamp_bo)     = fmi2True;  // Initial input value
    b(In_PassengerAirbagEnableLamp_bo)      = fmi2True;  // Initial input value
    i(In_PassengerAirbagWarningState_se)    = 0;         // Initial input value
    // output
    i(Out_UserConfirmAirbagState_se)        = 0;         // Initial output value
    i(Out_PassengerAirbagWarningState_se)   = 0;         // Initial output value
    b(In_PassengerAirbagEnableLamp_bo)      = fmi2False; // Initial output value
}

// Called by fmi2GetReal, fmi2GetInteger, fmi2GetBoolean, fmi2GetString, fmi2ExitInitialization
// Compute output based on input at every access
void calculateValues(ModelInstance *comp) {
    i(Out_PassengerAirbagWarningState_se)   = i(In_PassengerAirbagWarningState_se);
    i(Out_UserConfirmAirbagState_se)        = i(In_UserConfirmAirbagState);
    b(In_PassengerAirbagEnableLamp_bo)      = b(In_PassengerAirbagDisableLamp_bo) && !b(In_PassengerAirbagEnableLamp_bo);
}

// Called by fmi2GetInteger to return integer values
fmi2Integer getInteger(ModelInstance* comp, fmi2ValueReference vr) {
    switch (vr) {
        case In_UserConfirmAirbagState:          return i(In_UserConfirmAirbagState);
        case In_PassengerAirbagWarningState_se:  return i(In_PassengerAirbagWarningState_se);
        case Out_UserConfirmAirbagState_se:      return i(Out_UserConfirmAirbagState_se);
        case Out_PassengerAirbagWarningState_se: return i(Out_PassengerAirbagWarningState_se);
        default: return 0;
    }
}

// Called by fmi2GetBoolean to return boolean values
fmi2Boolean getBoolean(ModelInstance* comp, fmi2ValueReference vr) {
    switch (vr) {
        case In_PassengerAirbagDisableLamp_bo:   return b(In_PassengerAirbagDisableLamp_bo);
        case In_PassengerAirbagEnableLamp_bo:    return b(In_PassengerAirbagEnableLamp_bo);
        case Out_PassengerAirbagDisableLamp_bo:  return b(Out_PassengerAirbagDisableLamp_bo);
        default: return fmi2False;
    }
}

// Called by fmi2SetInteger to set integer inputs
fmi2Status setInteger(ModelInstance* comp, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer value[]) {
    for (size_t i = 0; i < nvr; i++) {
        switch (vr[i]) {
            case In_UserConfirmAirbagState:          i(In_UserConfirmAirbagState)           = value[i]; break;
            case In_PassengerAirbagWarningState_se:  i(In_PassengerAirbagWarningState_se)   = value[i]; break;
            case Out_UserConfirmAirbagState_se:      i(Out_UserConfirmAirbagState_se)       = value[i]; break;  // Optional
            case Out_PassengerAirbagWarningState_se: i(Out_PassengerAirbagWarningState_se)  = value[i]; break;  // Optional
            default: return fmi2Error;
        }
    }
    calculateValues(comp);  // Update output after setting input
    return fmi2OK;
}

// Called by fmi2SetBoolean to set boolean inputs
fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean value[]) {
    for (size_t i = 0; i < nvr; i++) {
        switch (vr[i]) {
            case In_PassengerAirbagDisableLamp_bo:   b(In_PassengerAirbagDisableLamp_bo)    = value[i]; break;
            case In_PassengerAirbagEnableLamp_bo:    b(In_PassengerAirbagEnableLamp_bo)     = value[i]; break;
            case Out_PassengerAirbagDisableLamp_bo:  b(Out_PassengerAirbagDisableLamp_bo)   = value[i]; break;  // Optional
            default: return fmi2Error;
        }
    }
    calculateValues(comp);  // Update output after setting input
    return fmi2OK;
}

// No event indicators
fmi2Real getEventIndicator(ModelInstance* comp, int z) {
    return 0;  // Not used
}

// No events to handle
void eventUpdate(ModelInstance *comp, fmi2EventInfo *eventInfo, int isTimeEvent, int isNewEventIteration) {
    eventInfo->newDiscreteStatesNeeded              = fmi2False;
    eventInfo->terminateSimulation                  = fmi2False;
    eventInfo->nominalsOfContinuousStatesChanged    = fmi2False;
    eventInfo->valuesOfContinuousStatesChanged      = fmi2False;
    eventInfo->nextEventTimeDefined                 = fmi2False;
}

// Indicate Co-Simulation mode and include the template
#define FMI_COSIMULATION
#include "fmuTemplate.c"