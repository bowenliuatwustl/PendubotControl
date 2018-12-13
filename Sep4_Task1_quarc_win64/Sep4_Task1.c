/*
 * Sep4_Task1.c
 *
 * Code generation for model "Sep4_Task1".
 *
 * Model version              : 1.7
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Tue Sep 11 17:35:42 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Sep4_Task1.h"
#include "Sep4_Task1_private.h"
#include "Sep4_Task1_dt.h"

/* Block signals (auto storage) */
BlockIO_Sep4_Task1 Sep4_Task1_B;

/* Block states (auto storage) */
D_Work_Sep4_Task1 Sep4_Task1_DWork;

/* Real-time model */
RT_MODEL_Sep4_Task1 Sep4_Task1_M_;
RT_MODEL_Sep4_Task1 *const Sep4_Task1_M = &Sep4_Task1_M_;

/* Model step function */
void Sep4_Task1_step(void)
{
  /* local block i/o variables */
  real_T rtb_Saturation;

  /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

  /* S-Function Block: Sep4_Task1/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(Sep4_Task1_DWork.HILInitialize_Card,
      &Sep4_Task1_P.HILReadEncoder_Channels, 1,
      &Sep4_Task1_DWork.HILReadEncoder_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
    } else {
      rtb_Saturation = Sep4_Task1_DWork.HILReadEncoder_Buffer;
    }
  }

  /* Gain: '<Root>/Gain' */
  Sep4_Task1_B.signal1 = Sep4_Task1_P.Gain_Gain * rtb_Saturation;

  /* Memory: '<Root>/Memory' */
  rtb_Saturation = Sep4_Task1_DWork.Memory_PreviousInput;

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S2>/Constant'
   *  RelationalOperator: '<S1>/Compare'
   *  RelationalOperator: '<S2>/Compare'
   */
  if (rtb_Saturation > Sep4_Task1_P.Switch1_Threshold) {
    Sep4_Task1_B.Switch1 = (Sep4_Task1_B.signal1 > Sep4_Task1_P.Constant_Value_p);
  } else {
    Sep4_Task1_B.Switch1 = (Sep4_Task1_B.signal1 >= Sep4_Task1_P.Constant_Value);
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   */
  if (Sep4_Task1_B.Switch1) {
    Sep4_Task1_B.Switch = Sep4_Task1_P.Constant_Value_f;
  } else {
    Sep4_Task1_B.Switch = Sep4_Task1_P.Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Saturate: '<Root>/Saturation' */
  if (Sep4_Task1_B.Switch >= Sep4_Task1_P.Saturation_UpperSat) {
    rtb_Saturation = Sep4_Task1_P.Saturation_UpperSat;
  } else if (Sep4_Task1_B.Switch <= Sep4_Task1_P.Saturation_LowerSat) {
    rtb_Saturation = Sep4_Task1_P.Saturation_LowerSat;
  } else {
    rtb_Saturation = Sep4_Task1_B.Switch;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: Sep4_Task1/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(Sep4_Task1_DWork.HILInitialize_Card,
      &Sep4_Task1_P.HILWriteAnalog_Channels, 1, &rtb_Saturation);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
    }
  }

  /* Update for Memory: '<Root>/Memory' */
  Sep4_Task1_DWork.Memory_PreviousInput = Sep4_Task1_B.Switch;

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.002s, 0.0s] */
    rtExtModeUpload(0, Sep4_Task1_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.002s, 0.0s] */
    if ((rtmGetTFinal(Sep4_Task1_M)!=-1) &&
        !((rtmGetTFinal(Sep4_Task1_M)-Sep4_Task1_M->Timing.taskTime0) >
          Sep4_Task1_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(Sep4_Task1_M, "Simulation finished");
    }

    if (rtmGetStopRequested(Sep4_Task1_M)) {
      rtmSetErrorStatus(Sep4_Task1_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Sep4_Task1_M->Timing.clockTick0)) {
    ++Sep4_Task1_M->Timing.clockTickH0;
  }

  Sep4_Task1_M->Timing.taskTime0 = Sep4_Task1_M->Timing.clockTick0 *
    Sep4_Task1_M->Timing.stepSize0 + Sep4_Task1_M->Timing.clockTickH0 *
    Sep4_Task1_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void Sep4_Task1_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Sep4_Task1_M, 0,
                sizeof(RT_MODEL_Sep4_Task1));
  rtmSetTFinal(Sep4_Task1_M, -1);
  Sep4_Task1_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  Sep4_Task1_M->Sizes.checksums[0] = (4039315625U);
  Sep4_Task1_M->Sizes.checksums[1] = (3372337190U);
  Sep4_Task1_M->Sizes.checksums[2] = (1355606481U);
  Sep4_Task1_M->Sizes.checksums[3] = (438804003U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    Sep4_Task1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Sep4_Task1_M->extModeInfo,
      &Sep4_Task1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Sep4_Task1_M->extModeInfo, Sep4_Task1_M->Sizes.checksums);
    rteiSetTPtr(Sep4_Task1_M->extModeInfo, rtmGetTPtr(Sep4_Task1_M));
  }

  /* block I/O */
  (void) memset(((void *) &Sep4_Task1_B), 0,
                sizeof(BlockIO_Sep4_Task1));

  /* states (dwork) */
  (void) memset((void *)&Sep4_Task1_DWork, 0,
                sizeof(D_Work_Sep4_Task1));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Sep4_Task1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Sep4_Task1/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &Sep4_Task1_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Sep4_Task1_DWork.HILInitialize_Card,
      "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Sep4_Task1_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
      return;
    }

    if ((Sep4_Task1_P.HILInitialize_AIPStart && !is_switching) ||
        (Sep4_Task1_P.HILInitialize_AIPEnter && is_switching)) {
      Sep4_Task1_DWork.HILInitialize_AIMinimums[0] =
        Sep4_Task1_P.HILInitialize_AILow;
      Sep4_Task1_DWork.HILInitialize_AIMinimums[1] =
        Sep4_Task1_P.HILInitialize_AILow;
      Sep4_Task1_DWork.HILInitialize_AIMaximums[0] =
        Sep4_Task1_P.HILInitialize_AIHigh;
      Sep4_Task1_DWork.HILInitialize_AIMaximums[1] =
        Sep4_Task1_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(Sep4_Task1_DWork.HILInitialize_Card,
        Sep4_Task1_P.HILInitialize_AIChannels, 2U,
        &Sep4_Task1_DWork.HILInitialize_AIMinimums[0],
        &Sep4_Task1_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
        return;
      }
    }

    if ((Sep4_Task1_P.HILInitialize_AOPStart && !is_switching) ||
        (Sep4_Task1_P.HILInitialize_AOPEnter && is_switching)) {
      Sep4_Task1_DWork.HILInitialize_AOMinimums[0] =
        Sep4_Task1_P.HILInitialize_AOLow;
      Sep4_Task1_DWork.HILInitialize_AOMinimums[1] =
        Sep4_Task1_P.HILInitialize_AOLow;
      Sep4_Task1_DWork.HILInitialize_AOMaximums[0] =
        Sep4_Task1_P.HILInitialize_AOHigh;
      Sep4_Task1_DWork.HILInitialize_AOMaximums[1] =
        Sep4_Task1_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(Sep4_Task1_DWork.HILInitialize_Card,
        Sep4_Task1_P.HILInitialize_AOChannels, 2U,
        &Sep4_Task1_DWork.HILInitialize_AOMinimums[0],
        &Sep4_Task1_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
        return;
      }
    }

    if ((Sep4_Task1_P.HILInitialize_AOStart && !is_switching) ||
        (Sep4_Task1_P.HILInitialize_AOEnter && is_switching)) {
      Sep4_Task1_DWork.HILInitialize_AOVoltages[0] =
        Sep4_Task1_P.HILInitialize_AOInitial;
      Sep4_Task1_DWork.HILInitialize_AOVoltages[1] =
        Sep4_Task1_P.HILInitialize_AOInitial;
      result = hil_write_analog(Sep4_Task1_DWork.HILInitialize_Card,
        Sep4_Task1_P.HILInitialize_AOChannels, 2U,
        &Sep4_Task1_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
        return;
      }
    }

    if (Sep4_Task1_P.HILInitialize_AOReset) {
      Sep4_Task1_DWork.HILInitialize_AOVoltages[0] =
        Sep4_Task1_P.HILInitialize_AOWatchdog;
      Sep4_Task1_DWork.HILInitialize_AOVoltages[1] =
        Sep4_Task1_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (Sep4_Task1_DWork.HILInitialize_Card,
         Sep4_Task1_P.HILInitialize_AOChannels, 2U,
         &Sep4_Task1_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
        return;
      }
    }

    if ((Sep4_Task1_P.HILInitialize_EIPStart && !is_switching) ||
        (Sep4_Task1_P.HILInitialize_EIPEnter && is_switching)) {
      Sep4_Task1_DWork.HILInitialize_QuadratureModes[0] =
        Sep4_Task1_P.HILInitialize_EIQuadrature;
      Sep4_Task1_DWork.HILInitialize_QuadratureModes[1] =
        Sep4_Task1_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (Sep4_Task1_DWork.HILInitialize_Card,
         Sep4_Task1_P.HILInitialize_EIChannels, 2U, (t_encoder_quadrature_mode *)
         &Sep4_Task1_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
        return;
      }
    }

    if ((Sep4_Task1_P.HILInitialize_EIStart && !is_switching) ||
        (Sep4_Task1_P.HILInitialize_EIEnter && is_switching)) {
      Sep4_Task1_DWork.HILInitialize_InitialEICounts[0] =
        Sep4_Task1_P.HILInitialize_EIInitial;
      Sep4_Task1_DWork.HILInitialize_InitialEICounts[1] =
        Sep4_Task1_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(Sep4_Task1_DWork.HILInitialize_Card,
        Sep4_Task1_P.HILInitialize_EIChannels, 2U,
        &Sep4_Task1_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for Memory: '<Root>/Memory' */
  Sep4_Task1_DWork.Memory_PreviousInput = Sep4_Task1_P.Memory_X0;
}

/* Model terminate function */
void Sep4_Task1_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Sep4_Task1/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(Sep4_Task1_DWork.HILInitialize_Card);
    hil_monitor_stop_all(Sep4_Task1_DWork.HILInitialize_Card);
    is_switching = false;
    if ((Sep4_Task1_P.HILInitialize_AOTerminate && !is_switching) ||
        (Sep4_Task1_P.HILInitialize_AOExit && is_switching)) {
      Sep4_Task1_DWork.HILInitialize_AOVoltages[0] =
        Sep4_Task1_P.HILInitialize_AOFinal;
      Sep4_Task1_DWork.HILInitialize_AOVoltages[1] =
        Sep4_Task1_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(Sep4_Task1_DWork.HILInitialize_Card,
        Sep4_Task1_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &Sep4_Task1_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Sep4_Task1_M, _rt_error_message);
      }
    }

    hil_task_delete_all(Sep4_Task1_DWork.HILInitialize_Card);
    hil_monitor_delete_all(Sep4_Task1_DWork.HILInitialize_Card);
    hil_close(Sep4_Task1_DWork.HILInitialize_Card);
    Sep4_Task1_DWork.HILInitialize_Card = NULL;
  }
}
