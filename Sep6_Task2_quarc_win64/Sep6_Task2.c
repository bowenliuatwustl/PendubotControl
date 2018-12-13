/*
 * Sep6_Task2.c
 *
 * Code generation for model "Sep6_Task2".
 *
 * Model version              : 1.10
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Thu Sep 06 17:02:34 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Sep6_Task2.h"
#include "Sep6_Task2_private.h"
#include "Sep6_Task2_dt.h"

/* Block signals (auto storage) */
BlockIO_Sep6_Task2 Sep6_Task2_B;

/* Continuous states */
ContinuousStates_Sep6_Task2 Sep6_Task2_X;

/* Block states (auto storage) */
D_Work_Sep6_Task2 Sep6_Task2_DWork;

/* Real-time model */
RT_MODEL_Sep6_Task2 Sep6_Task2_M_;
RT_MODEL_Sep6_Task2 *const Sep6_Task2_M = &Sep6_Task2_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  Sep6_Task2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Sep6_Task2_step(void)
{
  /* local block i/o variables */
  real_T rtb_D;
  real_T rtb_HILReadEncoder;
  real_T rtb_Derivative;
  real_T temp;
  if (rtmIsMajorTimeStep(Sep6_Task2_M)) {
    /* set solver stop time */
    if (!(Sep6_Task2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Sep6_Task2_M->solverInfo,
                            ((Sep6_Task2_M->Timing.clockTickH0 + 1) *
        Sep6_Task2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Sep6_Task2_M->solverInfo,
                            ((Sep6_Task2_M->Timing.clockTick0 + 1) *
        Sep6_Task2_M->Timing.stepSize0 + Sep6_Task2_M->Timing.clockTickH0 *
        Sep6_Task2_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Sep6_Task2_M)) {
    Sep6_Task2_M->Timing.t[0] = rtsiGetT(&Sep6_Task2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Sep6_Task2_M)) {
    /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

    /* S-Function Block: Sep6_Task2/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(Sep6_Task2_DWork.HILInitialize_Card,
        &Sep6_Task2_P.HILReadEncoder_Channels, 1,
        &Sep6_Task2_DWork.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder = Sep6_Task2_DWork.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<Root>/Gain' */
    Sep6_Task2_B.signal1 = Sep6_Task2_P.Gain_Gain * rtb_HILReadEncoder;
  }

  /* SignalGenerator: '<Root>/Signal Generator' */
  temp = Sep6_Task2_P.SignalGenerator_Frequency * Sep6_Task2_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    Sep6_Task2_B.SignalGenerator = Sep6_Task2_P.SignalGenerator_Amplitude;
  } else {
    Sep6_Task2_B.SignalGenerator = -Sep6_Task2_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Sum: '<Root>/Add1' */
  Sep6_Task2_B.Add1 = Sep6_Task2_B.signal1 - Sep6_Task2_B.SignalGenerator;

  /* Gain: '<Root>/D' */
  rtb_D = Sep6_Task2_P.D_Gain * Sep6_Task2_B.Add1;

  /* Derivative: '<Root>/Derivative' */
  {
    real_T t = Sep6_Task2_M->Timing.t[0];
    real_T timeStampA = Sep6_Task2_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = Sep6_Task2_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &Sep6_Task2_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      rtb_Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &Sep6_Task2_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &Sep6_Task2_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      rtb_Derivative = (rtb_D - *lastU++) / deltaT;
    }
  }

  /* Sum: '<Root>/Add' incorporates:
   *  Gain: '<Root>/P'
   *  Integrator: '<Root>/Integrator'
   */
  Sep6_Task2_B.Add = (Sep6_Task2_P.P_Gain * Sep6_Task2_B.Add1 + rtb_Derivative)
    + Sep6_Task2_X.Integrator_CSTATE;

  /* Saturate: '<Root>/Saturation' */
  if (Sep6_Task2_B.Add >= Sep6_Task2_P.Saturation_UpperSat) {
    Sep6_Task2_B.Saturation = Sep6_Task2_P.Saturation_UpperSat;
  } else if (Sep6_Task2_B.Add <= Sep6_Task2_P.Saturation_LowerSat) {
    Sep6_Task2_B.Saturation = Sep6_Task2_P.Saturation_LowerSat;
  } else {
    Sep6_Task2_B.Saturation = Sep6_Task2_B.Add;
  }

  /* End of Saturate: '<Root>/Saturation' */
  if (rtmIsMajorTimeStep(Sep6_Task2_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: Sep6_Task2/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(Sep6_Task2_DWork.HILInitialize_Card,
        &Sep6_Task2_P.HILWriteAnalog_Channels, 1, &Sep6_Task2_B.Saturation);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<Root>/I' */
  Sep6_Task2_B.I = Sep6_Task2_P.I_Gain * Sep6_Task2_B.Add1;
  if (rtmIsMajorTimeStep(Sep6_Task2_M)) {
    /* Update for Derivative: '<Root>/Derivative' */
    {
      real_T timeStampA = Sep6_Task2_DWork.Derivative_RWORK.TimeStampA;
      real_T timeStampB = Sep6_Task2_DWork.Derivative_RWORK.TimeStampB;
      real_T* lastTime = &Sep6_Task2_DWork.Derivative_RWORK.TimeStampA;
      real_T* lastU = &Sep6_Task2_DWork.Derivative_RWORK.LastUAtTimeA;
      if (timeStampA != rtInf) {
        if (timeStampB == rtInf) {
          lastTime = &Sep6_Task2_DWork.Derivative_RWORK.TimeStampB;
          lastU = &Sep6_Task2_DWork.Derivative_RWORK.LastUAtTimeB;
        } else if (timeStampA >= timeStampB) {
          lastTime = &Sep6_Task2_DWork.Derivative_RWORK.TimeStampB;
          lastU = &Sep6_Task2_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      }

      *lastTime = Sep6_Task2_M->Timing.t[0];
      *lastU++ = rtb_D;
    }

    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, Sep6_Task2_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(Sep6_Task2_M)) {/* Sample time: [0.002s, 0.0s] */
      rtExtModeUpload(1, (((Sep6_Task2_M->Timing.clockTick1+
                            Sep6_Task2_M->Timing.clockTickH1* 4294967296.0)) *
                          0.002));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Sep6_Task2_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Sep6_Task2_M)!=-1) &&
          !((rtmGetTFinal(Sep6_Task2_M)-(((Sep6_Task2_M->Timing.clockTick1+
               Sep6_Task2_M->Timing.clockTickH1* 4294967296.0)) * 0.002)) >
            (((Sep6_Task2_M->Timing.clockTick1+Sep6_Task2_M->Timing.clockTickH1*
               4294967296.0)) * 0.002) * (DBL_EPSILON))) {
        rtmSetErrorStatus(Sep6_Task2_M, "Simulation finished");
      }

      if (rtmGetStopRequested(Sep6_Task2_M)) {
        rtmSetErrorStatus(Sep6_Task2_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Sep6_Task2_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Sep6_Task2_M->Timing.clockTick0)) {
      ++Sep6_Task2_M->Timing.clockTickH0;
    }

    Sep6_Task2_M->Timing.t[0] = rtsiGetSolverStopTime(&Sep6_Task2_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.002s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.002, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Sep6_Task2_M->Timing.clockTick1++;
      if (!Sep6_Task2_M->Timing.clockTick1) {
        Sep6_Task2_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Sep6_Task2_derivatives(void)
{
  /* Derivatives for Integrator: '<Root>/Integrator' */
  ((StateDerivatives_Sep6_Task2 *) Sep6_Task2_M->ModelData.derivs)
    ->Integrator_CSTATE = Sep6_Task2_B.I;
}

/* Model initialize function */
void Sep6_Task2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Sep6_Task2_M, 0,
                sizeof(RT_MODEL_Sep6_Task2));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Sep6_Task2_M->solverInfo,
                          &Sep6_Task2_M->Timing.simTimeStep);
    rtsiSetTPtr(&Sep6_Task2_M->solverInfo, &rtmGetTPtr(Sep6_Task2_M));
    rtsiSetStepSizePtr(&Sep6_Task2_M->solverInfo,
                       &Sep6_Task2_M->Timing.stepSize0);
    rtsiSetdXPtr(&Sep6_Task2_M->solverInfo, &Sep6_Task2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&Sep6_Task2_M->solverInfo,
                         &Sep6_Task2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&Sep6_Task2_M->solverInfo,
      &Sep6_Task2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&Sep6_Task2_M->solverInfo, (&rtmGetErrorStatus
      (Sep6_Task2_M)));
    rtsiSetRTModelPtr(&Sep6_Task2_M->solverInfo, Sep6_Task2_M);
  }

  rtsiSetSimTimeStep(&Sep6_Task2_M->solverInfo, MAJOR_TIME_STEP);
  Sep6_Task2_M->ModelData.intgData.f[0] = Sep6_Task2_M->ModelData.odeF[0];
  Sep6_Task2_M->ModelData.contStates = ((real_T *) &Sep6_Task2_X);
  rtsiSetSolverData(&Sep6_Task2_M->solverInfo, (void *)
                    &Sep6_Task2_M->ModelData.intgData);
  rtsiSetSolverName(&Sep6_Task2_M->solverInfo,"ode1");
  rtmSetTPtr(Sep6_Task2_M, &Sep6_Task2_M->Timing.tArray[0]);
  rtmSetTFinal(Sep6_Task2_M, -1);
  Sep6_Task2_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  Sep6_Task2_M->Sizes.checksums[0] = (4020583363U);
  Sep6_Task2_M->Sizes.checksums[1] = (199543928U);
  Sep6_Task2_M->Sizes.checksums[2] = (1984320943U);
  Sep6_Task2_M->Sizes.checksums[3] = (3726749242U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Sep6_Task2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Sep6_Task2_M->extModeInfo,
      &Sep6_Task2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Sep6_Task2_M->extModeInfo, Sep6_Task2_M->Sizes.checksums);
    rteiSetTPtr(Sep6_Task2_M->extModeInfo, rtmGetTPtr(Sep6_Task2_M));
  }

  /* block I/O */
  (void) memset(((void *) &Sep6_Task2_B), 0,
                sizeof(BlockIO_Sep6_Task2));

  /* states (continuous) */
  {
    (void) memset((void *)&Sep6_Task2_X, 0,
                  sizeof(ContinuousStates_Sep6_Task2));
  }

  /* states (dwork) */
  (void) memset((void *)&Sep6_Task2_DWork, 0,
                sizeof(D_Work_Sep6_Task2));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Sep6_Task2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Sep6_Task2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &Sep6_Task2_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Sep6_Task2_DWork.HILInitialize_Card,
      "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Sep6_Task2_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
      return;
    }

    if ((Sep6_Task2_P.HILInitialize_AIPStart && !is_switching) ||
        (Sep6_Task2_P.HILInitialize_AIPEnter && is_switching)) {
      Sep6_Task2_DWork.HILInitialize_AIMinimums[0] =
        Sep6_Task2_P.HILInitialize_AILow;
      Sep6_Task2_DWork.HILInitialize_AIMinimums[1] =
        Sep6_Task2_P.HILInitialize_AILow;
      Sep6_Task2_DWork.HILInitialize_AIMaximums[0] =
        Sep6_Task2_P.HILInitialize_AIHigh;
      Sep6_Task2_DWork.HILInitialize_AIMaximums[1] =
        Sep6_Task2_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(Sep6_Task2_DWork.HILInitialize_Card,
        Sep6_Task2_P.HILInitialize_AIChannels, 2U,
        &Sep6_Task2_DWork.HILInitialize_AIMinimums[0],
        &Sep6_Task2_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
        return;
      }
    }

    if ((Sep6_Task2_P.HILInitialize_AOPStart && !is_switching) ||
        (Sep6_Task2_P.HILInitialize_AOPEnter && is_switching)) {
      Sep6_Task2_DWork.HILInitialize_AOMinimums[0] =
        Sep6_Task2_P.HILInitialize_AOLow;
      Sep6_Task2_DWork.HILInitialize_AOMinimums[1] =
        Sep6_Task2_P.HILInitialize_AOLow;
      Sep6_Task2_DWork.HILInitialize_AOMaximums[0] =
        Sep6_Task2_P.HILInitialize_AOHigh;
      Sep6_Task2_DWork.HILInitialize_AOMaximums[1] =
        Sep6_Task2_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(Sep6_Task2_DWork.HILInitialize_Card,
        Sep6_Task2_P.HILInitialize_AOChannels, 2U,
        &Sep6_Task2_DWork.HILInitialize_AOMinimums[0],
        &Sep6_Task2_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
        return;
      }
    }

    if ((Sep6_Task2_P.HILInitialize_AOStart && !is_switching) ||
        (Sep6_Task2_P.HILInitialize_AOEnter && is_switching)) {
      Sep6_Task2_DWork.HILInitialize_AOVoltages[0] =
        Sep6_Task2_P.HILInitialize_AOInitial;
      Sep6_Task2_DWork.HILInitialize_AOVoltages[1] =
        Sep6_Task2_P.HILInitialize_AOInitial;
      result = hil_write_analog(Sep6_Task2_DWork.HILInitialize_Card,
        Sep6_Task2_P.HILInitialize_AOChannels, 2U,
        &Sep6_Task2_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
        return;
      }
    }

    if (Sep6_Task2_P.HILInitialize_AOReset) {
      Sep6_Task2_DWork.HILInitialize_AOVoltages[0] =
        Sep6_Task2_P.HILInitialize_AOWatchdog;
      Sep6_Task2_DWork.HILInitialize_AOVoltages[1] =
        Sep6_Task2_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (Sep6_Task2_DWork.HILInitialize_Card,
         Sep6_Task2_P.HILInitialize_AOChannels, 2U,
         &Sep6_Task2_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
        return;
      }
    }

    if ((Sep6_Task2_P.HILInitialize_EIPStart && !is_switching) ||
        (Sep6_Task2_P.HILInitialize_EIPEnter && is_switching)) {
      Sep6_Task2_DWork.HILInitialize_QuadratureModes[0] =
        Sep6_Task2_P.HILInitialize_EIQuadrature;
      Sep6_Task2_DWork.HILInitialize_QuadratureModes[1] =
        Sep6_Task2_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (Sep6_Task2_DWork.HILInitialize_Card,
         Sep6_Task2_P.HILInitialize_EIChannels, 2U, (t_encoder_quadrature_mode *)
         &Sep6_Task2_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
        return;
      }
    }

    if ((Sep6_Task2_P.HILInitialize_EIStart && !is_switching) ||
        (Sep6_Task2_P.HILInitialize_EIEnter && is_switching)) {
      Sep6_Task2_DWork.HILInitialize_InitialEICounts[0] =
        Sep6_Task2_P.HILInitialize_EIInitial;
      Sep6_Task2_DWork.HILInitialize_InitialEICounts[1] =
        Sep6_Task2_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(Sep6_Task2_DWork.HILInitialize_Card,
        Sep6_Task2_P.HILInitialize_EIChannels, 2U,
        &Sep6_Task2_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  Sep6_Task2_DWork.Derivative_RWORK.TimeStampA = rtInf;
  Sep6_Task2_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  Sep6_Task2_X.Integrator_CSTATE = Sep6_Task2_P.Integrator_IC;
}

/* Model terminate function */
void Sep6_Task2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Sep6_Task2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(Sep6_Task2_DWork.HILInitialize_Card);
    hil_monitor_stop_all(Sep6_Task2_DWork.HILInitialize_Card);
    is_switching = false;
    if ((Sep6_Task2_P.HILInitialize_AOTerminate && !is_switching) ||
        (Sep6_Task2_P.HILInitialize_AOExit && is_switching)) {
      Sep6_Task2_DWork.HILInitialize_AOVoltages[0] =
        Sep6_Task2_P.HILInitialize_AOFinal;
      Sep6_Task2_DWork.HILInitialize_AOVoltages[1] =
        Sep6_Task2_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(Sep6_Task2_DWork.HILInitialize_Card,
        Sep6_Task2_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &Sep6_Task2_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep6_Task2_M, _rt_error_message);
      }
    }

    hil_task_delete_all(Sep6_Task2_DWork.HILInitialize_Card);
    hil_monitor_delete_all(Sep6_Task2_DWork.HILInitialize_Card);
    hil_close(Sep6_Task2_DWork.HILInitialize_Card);
    Sep6_Task2_DWork.HILInitialize_Card = NULL;
  }
}
