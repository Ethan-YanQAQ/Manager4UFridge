/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-07-03T19:11:41+0800
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0x40ab45c0d0d518b5e7e9a9a5d8fb5e96"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2026-07-03T19:11:41+0800"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[194] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  images_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 307200, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  images_Transpose_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 307200, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _model_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _model_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _model_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _model_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 307200, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  _model_3_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  _model_3_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 153600, AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(
  _model_5_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(
  _model_5_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#63 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#64 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#65 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#66 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#67 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#68 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#69 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#70 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#71 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#72 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#73 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#74 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#75 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 76800, AI_STATIC)

/* Array#76 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#77 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#78 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#79 */
AI_ARRAY_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#80 */
AI_ARRAY_OBJ_DECLARE(
  _model_7_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#81 */
AI_ARRAY_OBJ_DECLARE(
  _model_7_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#82 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#83 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#84 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#85 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#86 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#87 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#88 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#89 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#90 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#91 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#92 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#93 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#94 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#95 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#96 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#97 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#98 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#99 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#100 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#101 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#102 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#103 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#104 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#105 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#106 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#107 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#108 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#109 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#110 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#111 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 38400, AI_STATIC)

/* Array#112 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#113 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#114 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#115 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#116 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_m_MaxPool_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#117 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_m_1_MaxPool_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#118 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_m_2_MaxPool_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#119 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#120 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#121 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#122 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#123 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#124 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#125 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#126 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#127 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#128 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#129 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#130 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#131 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#132 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#133 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_output2_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#134 */
AI_ARRAY_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#135 */
AI_ARRAY_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#136 */
AI_ARRAY_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#137 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20000, AI_STATIC)

/* Array#138 */
AI_ARRAY_OBJ_DECLARE(
  transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20000, AI_STATIC)

/* Array#139 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20000, AI_STATIC)

/* Array#140 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Softmax_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20000, AI_STATIC)

/* Array#141 */
AI_ARRAY_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 20000, AI_STATIC)

/* Array#142 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#143 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#144 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#145 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#146 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#147 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#148 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#149 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#150 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#151 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#152 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#153 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#154 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_Add_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#155 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#156 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#157 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#158 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#159 */
AI_ARRAY_OBJ_DECLARE(
  _model_11_Resize_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#160 */
AI_ARRAY_OBJ_DECLARE(
  _model_12_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 153600, AI_STATIC)

/* Array#161 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#162 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#163 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#164 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#165 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#166 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#167 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#168 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#169 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#170 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#171 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#172 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#173 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 76800, AI_STATIC)

/* Array#174 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#175 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#176 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#177 */
AI_ARRAY_OBJ_DECLARE(
  _model_14_Resize_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 204800, AI_STATIC)

/* Array#178 */
AI_ARRAY_OBJ_DECLARE(
  _model_15_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 409600, AI_STATIC)

/* Array#179 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#180 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#181 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#182 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#183 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#184 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#185 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#186 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#187 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#188 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#189 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#190 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#191 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 153600, AI_STATIC)

/* Array#192 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#193 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#194 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#195 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#196 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#197 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#198 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#199 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#200 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#201 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#202 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#203 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#204 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#205 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#206 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#207 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 44800, AI_STATIC)

/* Array#208 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#209 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#210 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#211 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#212 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#213 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#214 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 102400, AI_STATIC)

/* Array#215 */
AI_ARRAY_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#216 */
AI_ARRAY_OBJ_DECLARE(
  _model_17_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#217 */
AI_ARRAY_OBJ_DECLARE(
  _model_17_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#218 */
AI_ARRAY_OBJ_DECLARE(
  _model_18_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 76800, AI_STATIC)

/* Array#219 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#220 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#221 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#222 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#223 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#224 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#225 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#226 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#227 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#228 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#229 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#230 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#231 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 76800, AI_STATIC)

/* Array#232 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#233 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#234 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#235 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#236 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#237 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 51200, AI_STATIC)

/* Array#238 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#239 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#240 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#241 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#242 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#243 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#244 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#245 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#246 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#247 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 11200, AI_STATIC)

/* Array#248 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#249 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#250 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#251 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#252 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#253 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#254 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#255 */
AI_ARRAY_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#256 */
AI_ARRAY_OBJ_DECLARE(
  _model_20_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#257 */
AI_ARRAY_OBJ_DECLARE(
  _model_20_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#258 */
AI_ARRAY_OBJ_DECLARE(
  _model_21_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 38400, AI_STATIC)

/* Array#259 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#260 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#261 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#262 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_Split_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#263 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_Split_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#264 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#265 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#266 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#267 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#268 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#269 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#270 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#271 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#272 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#273 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#274 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#275 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#276 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#277 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#278 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#279 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#280 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#281 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#282 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#283 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_Add_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#284 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#285 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#286 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#287 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#288 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 38400, AI_STATIC)

/* Array#289 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#290 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv2_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#291 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv2_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#292 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#293 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#294 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#295 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#296 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#297 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#298 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#299 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#300 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#301 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#302 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#303 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#304 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2800, AI_STATIC)

/* Array#305 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Concat_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 58800, AI_STATIC)

/* Array#306 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 58800, AI_STATIC)

/* Array#307 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#308 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#309 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#310 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#311 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#312 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Mul_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#313 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6400, AI_STATIC)

/* Array#314 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Concat_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 134400, AI_STATIC)

/* Array#315 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_Reshape_output_0_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 134400, AI_STATIC)

/* Array#316 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_Transpose_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 134400, AI_STATIC)

/* Array#317 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_Softmax_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 134400, AI_STATIC)

/* Array#318 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8400, AI_STATIC)

/* Array#319 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chlast_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8400, AI_STATIC)

/* Array#320 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chfirst_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8400, AI_STATIC)

/* Array#321 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Slice_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#322 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Slice_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#323 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Add_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#324 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Sub_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#325 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Sub_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#326 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Add_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#327 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Div_1_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#328 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Concat_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8400, AI_STATIC)

/* Array#329 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Mul_2_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8400, AI_STATIC)

/* Array#330 */
AI_ARRAY_OBJ_DECLARE(
  output0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 67200, AI_STATIC)

/* Array#331 */
AI_ARRAY_OBJ_DECLARE(
  output0_Transpose_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 67200, AI_STATIC)

/* Array#332 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#333 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#334 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Constant_14_output_0_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#335 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Constant_15_output_0_3D_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2100, AI_STATIC)

/* Array#336 */
AI_ARRAY_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 432, AI_STATIC)

/* Array#337 */
AI_ARRAY_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#338 */
AI_ARRAY_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4608, AI_STATIC)

/* Array#339 */
AI_ARRAY_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#340 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1024, AI_STATIC)

/* Array#341 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#342 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#343 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#344 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8, AI_STATIC)

/* Array#345 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#346 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#347 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3072, AI_STATIC)

/* Array#348 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#349 */
AI_ARRAY_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#350 */
AI_ARRAY_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#351 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#352 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#353 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#354 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4608, AI_STATIC)

/* Array#355 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#356 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4608, AI_STATIC)

/* Array#357 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#358 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12288, AI_STATIC)

/* Array#359 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#360 */
AI_ARRAY_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 147456, AI_STATIC)

/* Array#361 */
AI_ARRAY_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#362 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#363 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#364 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#365 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#366 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#367 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2048, AI_STATIC)

/* Array#368 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#369 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#370 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#371 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#372 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#373 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#374 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#375 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#376 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#377 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#378 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#379 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 24576, AI_STATIC)

/* Array#380 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#381 */
AI_ARRAY_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 294912, AI_STATIC)

/* Array#382 */
AI_ARRAY_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#383 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 65536, AI_STATIC)

/* Array#384 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#385 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#386 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8192, AI_STATIC)

/* Array#387 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#388 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8192, AI_STATIC)

/* Array#389 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#390 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#391 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#392 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#393 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#394 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#395 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#396 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#397 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#398 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#399 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#400 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 98304, AI_STATIC)

/* Array#401 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#402 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32768, AI_STATIC)

/* Array#403 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#404 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 131072, AI_STATIC)

/* Array#405 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#406 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 65536, AI_STATIC)

/* Array#407 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#408 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#409 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32768, AI_STATIC)

/* Array#410 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#411 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 3, AI_STATIC)

/* Array#412 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)

/* Array#413 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2, AI_STATIC)

/* Array#414 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#415 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#416 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#417 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#418 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32768, AI_STATIC)

/* Array#419 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#420 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32768, AI_STATIC)

/* Array#421 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#422 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 65536, AI_STATIC)

/* Array#423 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#424 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 49152, AI_STATIC)

/* Array#425 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#426 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#427 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)

/* Array#428 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#429 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)

/* Array#430 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#431 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 24576, AI_STATIC)

/* Array#432 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#433 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#434 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#435 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#436 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4608, AI_STATIC)

/* Array#437 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#438 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4608, AI_STATIC)

/* Array#439 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#440 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 6144, AI_STATIC)

/* Array#441 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#442 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#443 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#444 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#445 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#446 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#447 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#448 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#449 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#450 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1792, AI_STATIC)

/* Array#451 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 28, AI_STATIC)

/* Array#452 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#453 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#454 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#455 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#456 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#457 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#458 */
AI_ARRAY_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#459 */
AI_ARRAY_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#460 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 24576, AI_STATIC)

/* Array#461 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#462 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#463 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)

/* Array#464 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#465 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)

/* Array#466 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#467 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 24576, AI_STATIC)

/* Array#468 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#469 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#470 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#471 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8192, AI_STATIC)

/* Array#472 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#473 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#474 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#475 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#476 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#477 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1792, AI_STATIC)

/* Array#478 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 28, AI_STATIC)

/* Array#479 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 73728, AI_STATIC)

/* Array#480 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#481 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#482 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#483 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#484 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#485 */
AI_ARRAY_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 147456, AI_STATIC)

/* Array#486 */
AI_ARRAY_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#487 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 98304, AI_STATIC)

/* Array#488 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#489 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_Split_output_0_num_or_size_splits_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#490 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8192, AI_STATIC)

/* Array#491 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#492 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 8192, AI_STATIC)

/* Array#493 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#494 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#495 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#496 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#497 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#498 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#499 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#500 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#501 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#502 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#503 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#504 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 98304, AI_STATIC)

/* Array#505 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#506 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2304, AI_STATIC)

/* Array#507 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#508 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#509 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#510 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#511 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#512 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#513 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#514 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1792, AI_STATIC)

/* Array#515 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 28, AI_STATIC)

/* Array#516 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 147456, AI_STATIC)

/* Array#517 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#518 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864, AI_STATIC)

/* Array#519 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#520 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4096, AI_STATIC)

/* Array#521 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#522 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/* Array#523 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)

/* Array#524 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Constant_13_output_0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#525 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_Constant_12_output_0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4200, AI_STATIC)

/* Array#526 */
AI_ARRAY_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 27, AI_STATIC)

/* Array#527 */
AI_ARRAY_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)

/* Array#528 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#529 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)

/* Array#530 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 72, AI_STATIC)

/* Array#531 */
AI_ARRAY_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 48, AI_STATIC)

/* Array#532 */
AI_ARRAY_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#533 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#534 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#535 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)

/* Array#536 */
AI_ARRAY_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 96, AI_STATIC)

/* Array#537 */
AI_ARRAY_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#538 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#539 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#540 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#541 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#542 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#543 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#544 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#545 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#546 */
AI_ARRAY_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 192, AI_STATIC)

/* Array#547 */
AI_ARRAY_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#548 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#549 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#550 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#551 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#552 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#553 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#554 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#555 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#556 */
AI_ARRAY_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 384, AI_STATIC)

/* Array#557 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#558 */
AI_ARRAY_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 512, AI_STATIC)

/* Array#559 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#560 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#561 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#562 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#563 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#564 */
AI_ARRAY_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#565 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 384, AI_STATIC)

/* Array#566 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#567 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#568 */
AI_ARRAY_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 192, AI_STATIC)

/* Array#569 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#570 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#571 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 144, AI_STATIC)

/* Array#572 */
AI_ARRAY_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 96, AI_STATIC)

/* Array#573 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#574 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#575 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#576 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#577 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#578 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#579 */
AI_ARRAY_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#580 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 192, AI_STATIC)

/* Array#581 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#582 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#583 */
AI_ARRAY_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 192, AI_STATIC)

/* Array#584 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#585 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#586 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#587 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#588 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#589 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#590 */
AI_ARRAY_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1152, AI_STATIC)

/* Array#591 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 384, AI_STATIC)

/* Array#592 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#593 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#594 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#595 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#596 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#597 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#598 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128, AI_STATIC)

/* Array#599 */
AI_ARRAY_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 384, AI_STATIC)

/* Array#600 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#601 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#602 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#603 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2304, AI_STATIC)

/* Array#604 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576, AI_STATIC)

/* Array#605 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#606 */
AI_ARRAY_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _model_0_act_Mul_output_0_output, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 160, 160), AI_STRIDE_INIT(4, 4, 4, 64, 10240),
  1, &_model_0_act_Mul_output_0_output_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _model_0_act_Sigmoid_output_0_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 160, 160), AI_STRIDE_INIT(4, 4, 4, 64, 10240),
  1, &_model_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_bias, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_model_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 160, 160), AI_STRIDE_INIT(4, 4, 4, 64, 10240),
  1, &_model_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_scratch0, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 3), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &_model_0_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_weights, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 16), AI_STRIDE_INIT(4, 4, 12, 192, 576),
  1, &_model_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_Concat_output_0_output, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_Concat_output_0_output_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_Split_output_0_num_or_size_splits, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_10_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_Split_output_0_output0, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_Split_output_0_output0_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_Split_output_0_output1, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_Split_output_0_output1_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv1_act_Mul_output_0_output, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_bias, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_output, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_weights, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 256), AI_STRIDE_INIT(4, 4, 1024, 262144, 262144),
  1, &_model_10_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv2_act_Mul_output_0_output, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_bias, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_weights, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 256), AI_STRIDE_INIT(4, 4, 1024, 262144, 262144),
  1, &_model_10_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_Add_1_output_0_output, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_Add_1_output_0_output_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_Add_output_0_output, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_Add_output_0_output_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Add_output_0_output, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_attn_Add_output_0_output_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_bias, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_10_m_m_0_attn_MatMul_1_output_0_bias_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_output, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 64, 2), AI_STRIDE_INIT(4, 4, 4, 400, 25600),
  1, &_model_10_m_m_0_attn_MatMul_1_output_0_output_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_output0, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 10, 128), AI_STRIDE_INIT(4, 4, 4, 40, 400),
  1, &_model_10_m_m_0_attn_MatMul_1_output_0_output_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_output_0_bias, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_10_m_m_0_attn_MatMul_output_0_bias_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_output_0_output, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 100, 2), AI_STRIDE_INIT(4, 4, 4, 400, 40000),
  1, &_model_10_m_m_0_attn_MatMul_output_0_output_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_bias, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_10_m_m_0_attn_Mul_output_0_bias_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_output, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 100), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &_model_10_m_m_0_attn_Mul_output_0_output_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_scale, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_10_m_m_0_attn_Mul_output_0_scale_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output, AI_STATIC,
  35, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 64, 2), AI_STRIDE_INIT(4, 4, 4, 400, 25600),
  1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output0, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 10, 128), AI_STRIDE_INIT(4, 4, 4, 40, 400),
  1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output, AI_STATIC,
  37, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 128), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &_model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output_array, NULL)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chlast_output, AI_STATIC,
  38, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 10, 256), AI_STRIDE_INIT(4, 4, 4, 40, 400),
  1, &_model_10_m_m_0_attn_Reshape_output_0_to_chlast_output_array, NULL)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chlast_output0, AI_STATIC,
  39, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 128, 2), AI_STRIDE_INIT(4, 4, 4, 400, 51200),
  1, &_model_10_m_m_0_attn_Reshape_output_0_to_chlast_output_array, NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Softmax_output_0_output, AI_STATIC,
  40, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 100), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &_model_10_m_m_0_attn_Softmax_output_0_output_array, NULL)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_num_or_size_splits, AI_STATIC,
  41, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &_model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_output0, AI_STATIC,
  42, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 32), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &_model_10_m_m_0_attn_Split_output_0_output0_array, NULL)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_output1, AI_STATIC,
  43, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 32), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &_model_10_m_m_0_attn_Split_output_0_output1_array, NULL)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_output2, AI_STATIC,
  44, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 64), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &_model_10_m_m_0_attn_Split_output_0_output2_array, NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_bias, AI_STATIC,
  45, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array, NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_output, AI_STATIC,
  46, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_output_array, NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_weights, AI_STATIC,
  47, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 128), AI_STRIDE_INIT(4, 1, 128, 128, 128),
  1, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array, NULL)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_bias, AI_STATIC,
  48, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array, NULL)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_output, AI_STATIC,
  49, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_output_array, NULL)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_scratch0, AI_STATIC,
  50, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_weights, AI_STATIC,
  51, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 128), AI_STRIDE_INIT(4, 4, 512, 65536, 65536),
  1, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array, NULL)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias, AI_STATIC,
  52, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array, NULL)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_output, AI_STATIC,
  53, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_output_array, NULL)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_scratch0, AI_STATIC,
  54, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights, AI_STATIC,
  55, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 256), AI_STRIDE_INIT(4, 4, 512, 131072, 131072),
  1, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array, NULL)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output, AI_STATIC,
  56, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output_array, NULL)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output, AI_STATIC,
  57, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias, AI_STATIC,
  58, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output, AI_STATIC,
  59, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_scratch0, AI_STATIC,
  60, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights, AI_STATIC,
  61, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 256), AI_STRIDE_INIT(4, 4, 512, 131072, 131072),
  1, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias, AI_STATIC,
  62, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #63 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output, AI_STATIC,
  63, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #64 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_scratch0, AI_STATIC,
  64, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #65 */
AI_TENSOR_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights, AI_STATIC,
  65, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 128), AI_STRIDE_INIT(4, 4, 1024, 131072, 131072),
  1, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #66 */
AI_TENSOR_OBJ_DECLARE(
  _model_11_Resize_output_0_output, AI_STATIC,
  66, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 20, 20), AI_STRIDE_INIT(4, 4, 4, 1024, 20480),
  1, &_model_11_Resize_output_0_output_array, NULL)

/* Tensor #67 */
AI_TENSOR_OBJ_DECLARE(
  _model_12_Concat_output_0_output, AI_STATIC,
  67, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 20, 20), AI_STRIDE_INIT(4, 4, 4, 1536, 30720),
  1, &_model_12_Concat_output_0_output_array, NULL)

/* Tensor #68 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_Concat_output_0_output, AI_STATIC,
  68, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 20, 20), AI_STRIDE_INIT(4, 4, 4, 768, 15360),
  1, &_model_13_Concat_output_0_output_array, NULL)

/* Tensor #69 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_Split_output_0_num_or_size_splits, AI_STATIC,
  69, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_13_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #70 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_Split_output_0_output0, AI_STATIC,
  70, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_13_Split_output_0_output0_array, NULL)

/* Tensor #71 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_Split_output_0_output1, AI_STATIC,
  71, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_13_Split_output_0_output1_array, NULL)

/* Tensor #72 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv1_act_Mul_output_0_output, AI_STATIC,
  72, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_13_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #73 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  73, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_13_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #74 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_bias, AI_STATIC,
  74, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_13_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #75 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_output, AI_STATIC,
  75, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_13_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #76 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  76, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1536, 1536),
  1, &_model_13_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #77 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_weights, AI_STATIC,
  77, 0x0,
  AI_SHAPE_INIT(4, 384, 1, 1, 128), AI_STRIDE_INIT(4, 4, 1536, 196608, 196608),
  1, &_model_13_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #78 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv2_act_Mul_output_0_output, AI_STATIC,
  78, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_13_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #79 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  79, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_13_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #80 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_bias, AI_STATIC,
  80, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_13_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #81 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_output, AI_STATIC,
  81, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_13_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #82 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  82, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 1, 1), AI_STRIDE_INIT(4, 4, 4, 768, 768),
  1, &_model_13_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #83 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_weights, AI_STATIC,
  83, 0x0,
  AI_SHAPE_INIT(4, 192, 1, 1, 128), AI_STRIDE_INIT(4, 4, 768, 98304, 98304),
  1, &_model_13_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #84 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_Add_output_0_output, AI_STATIC,
  84, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_13_m_0_Add_output_0_output_array, NULL)

/* Tensor #85 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  85, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_13_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #86 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  86, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_13_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #87 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  87, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_13_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #88 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  88, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_13_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #89 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  89, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_13_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #90 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  90, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 32), AI_STRIDE_INIT(4, 4, 256, 8192, 24576),
  1, &_model_13_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #91 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  91, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_13_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #92 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  92, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_13_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #93 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  93, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_13_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #94 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  94, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_13_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #95 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  95, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_13_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #96 */
AI_TENSOR_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  96, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 4, 128, 8192, 24576),
  1, &_model_13_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #97 */
AI_TENSOR_OBJ_DECLARE(
  _model_14_Resize_output_0_output, AI_STATIC,
  97, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 40, 40), AI_STRIDE_INIT(4, 4, 4, 512, 20480),
  1, &_model_14_Resize_output_0_output_array, NULL)

/* Tensor #98 */
AI_TENSOR_OBJ_DECLARE(
  _model_15_Concat_output_0_output, AI_STATIC,
  98, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 40, 40), AI_STRIDE_INIT(4, 4, 4, 1024, 40960),
  1, &_model_15_Concat_output_0_output_array, NULL)

/* Tensor #99 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_Concat_output_0_output, AI_STATIC,
  99, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 40, 40), AI_STRIDE_INIT(4, 4, 4, 384, 15360),
  1, &_model_16_Concat_output_0_output_array, NULL)

/* Tensor #100 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_Split_output_0_num_or_size_splits, AI_STATIC,
  100, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_16_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #101 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_Split_output_0_output0, AI_STATIC,
  101, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_16_Split_output_0_output0_array, NULL)

/* Tensor #102 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_Split_output_0_output1, AI_STATIC,
  102, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_16_Split_output_0_output1_array, NULL)

/* Tensor #103 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv1_act_Mul_output_0_output, AI_STATIC,
  103, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_16_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #104 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  104, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_16_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #105 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_bias, AI_STATIC,
  105, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_16_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #106 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_output, AI_STATIC,
  106, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_16_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #107 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  107, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_16_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #108 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_weights, AI_STATIC,
  108, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 64), AI_STRIDE_INIT(4, 4, 1024, 65536, 65536),
  1, &_model_16_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #109 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv2_act_Mul_output_0_output, AI_STATIC,
  109, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_16_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #110 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  110, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_16_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #111 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_bias, AI_STATIC,
  111, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_16_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #112 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_output, AI_STATIC,
  112, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_16_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #113 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  113, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 4, 4, 384, 384),
  1, &_model_16_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #114 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_weights, AI_STATIC,
  114, 0x0,
  AI_SHAPE_INIT(4, 96, 1, 1, 64), AI_STRIDE_INIT(4, 4, 384, 24576, 24576),
  1, &_model_16_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #115 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_Add_output_0_output, AI_STATIC,
  115, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_16_m_0_Add_output_0_output_array, NULL)

/* Tensor #116 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  116, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 40, 40), AI_STRIDE_INIT(4, 4, 4, 64, 2560),
  1, &_model_16_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #117 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  117, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 40, 40), AI_STRIDE_INIT(4, 4, 4, 64, 2560),
  1, &_model_16_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #118 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  118, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_model_16_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #119 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  119, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 40, 40), AI_STRIDE_INIT(4, 4, 4, 64, 2560),
  1, &_model_16_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #120 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  120, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_16_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #121 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  121, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 16), AI_STRIDE_INIT(4, 4, 128, 2048, 6144),
  1, &_model_16_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #122 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  122, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_16_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #123 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  123, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_16_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #124 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  124, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_16_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #125 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  125, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_16_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #126 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  126, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 3), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &_model_16_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #127 */
AI_TENSOR_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  127, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 4, 64, 2048, 6144),
  1, &_model_16_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #128 */
AI_TENSOR_OBJ_DECLARE(
  _model_17_act_Mul_output_0_output, AI_STATIC,
  128, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_17_act_Mul_output_0_output_array, NULL)

/* Tensor #129 */
AI_TENSOR_OBJ_DECLARE(
  _model_17_act_Sigmoid_output_0_output, AI_STATIC,
  129, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_17_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #130 */
AI_TENSOR_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_bias, AI_STATIC,
  130, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_17_conv_Conv_output_0_bias_array, NULL)

/* Tensor #131 */
AI_TENSOR_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_output, AI_STATIC,
  131, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_17_conv_Conv_output_0_output_array, NULL)

/* Tensor #132 */
AI_TENSOR_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_scratch0, AI_STATIC,
  132, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_17_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #133 */
AI_TENSOR_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_weights, AI_STATIC,
  133, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_17_conv_Conv_output_0_weights_array, NULL)

/* Tensor #134 */
AI_TENSOR_OBJ_DECLARE(
  _model_18_Concat_output_0_output, AI_STATIC,
  134, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 20, 20), AI_STRIDE_INIT(4, 4, 4, 768, 15360),
  1, &_model_18_Concat_output_0_output_array, NULL)

/* Tensor #135 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_Concat_output_0_output, AI_STATIC,
  135, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 20, 20), AI_STRIDE_INIT(4, 4, 4, 768, 15360),
  1, &_model_19_Concat_output_0_output_array, NULL)

/* Tensor #136 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_Split_output_0_num_or_size_splits, AI_STATIC,
  136, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_19_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #137 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_Split_output_0_output0, AI_STATIC,
  137, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_19_Split_output_0_output0_array, NULL)

/* Tensor #138 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_Split_output_0_output1, AI_STATIC,
  138, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_19_Split_output_0_output1_array, NULL)

/* Tensor #139 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv1_act_Mul_output_0_output, AI_STATIC,
  139, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_19_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #140 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  140, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_19_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #141 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_bias, AI_STATIC,
  141, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_19_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #142 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_output, AI_STATIC,
  142, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_19_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #143 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  143, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 1, 1), AI_STRIDE_INIT(4, 4, 4, 768, 768),
  1, &_model_19_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #144 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_weights, AI_STATIC,
  144, 0x0,
  AI_SHAPE_INIT(4, 192, 1, 1, 128), AI_STRIDE_INIT(4, 4, 768, 98304, 98304),
  1, &_model_19_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #145 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv2_act_Mul_output_0_output, AI_STATIC,
  145, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_19_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #146 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  146, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_19_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #147 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_bias, AI_STATIC,
  147, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_19_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #148 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_output, AI_STATIC,
  148, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_19_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #149 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  149, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 1, 1), AI_STRIDE_INIT(4, 4, 4, 768, 768),
  1, &_model_19_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #150 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_weights, AI_STATIC,
  150, 0x0,
  AI_SHAPE_INIT(4, 192, 1, 1, 128), AI_STRIDE_INIT(4, 4, 768, 98304, 98304),
  1, &_model_19_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #151 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_Add_output_0_output, AI_STATIC,
  151, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_19_m_0_Add_output_0_output_array, NULL)

/* Tensor #152 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  152, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_19_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #153 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  153, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_19_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #154 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  154, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_19_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #155 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  155, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_19_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #156 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  156, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_19_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #157 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  157, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 32), AI_STRIDE_INIT(4, 4, 256, 8192, 24576),
  1, &_model_19_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #158 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  158, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_19_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #159 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  159, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_19_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #160 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  160, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_19_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #161 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  161, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_19_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #162 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  162, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_19_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #163 */
AI_TENSOR_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  163, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 4, 128, 8192, 24576),
  1, &_model_19_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #164 */
AI_TENSOR_OBJ_DECLARE(
  _model_1_act_Mul_output_0_output, AI_STATIC,
  164, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 80, 80), AI_STRIDE_INIT(4, 4, 4, 128, 10240),
  1, &_model_1_act_Mul_output_0_output_array, NULL)

/* Tensor #165 */
AI_TENSOR_OBJ_DECLARE(
  _model_1_act_Sigmoid_output_0_output, AI_STATIC,
  165, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 80, 80), AI_STRIDE_INIT(4, 4, 4, 128, 10240),
  1, &_model_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #166 */
AI_TENSOR_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_bias, AI_STATIC,
  166, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #167 */
AI_TENSOR_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_output, AI_STATIC,
  167, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 80, 80), AI_STRIDE_INIT(4, 4, 4, 128, 10240),
  1, &_model_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #168 */
AI_TENSOR_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_scratch0, AI_STATIC,
  168, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 3), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &_model_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #169 */
AI_TENSOR_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_weights, AI_STATIC,
  169, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 4, 64, 2048, 6144),
  1, &_model_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #170 */
AI_TENSOR_OBJ_DECLARE(
  _model_20_act_Mul_output_0_output, AI_STATIC,
  170, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_20_act_Mul_output_0_output_array, NULL)

/* Tensor #171 */
AI_TENSOR_OBJ_DECLARE(
  _model_20_act_Sigmoid_output_0_output, AI_STATIC,
  171, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_20_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #172 */
AI_TENSOR_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_bias, AI_STATIC,
  172, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_20_conv_Conv_output_0_bias_array, NULL)

/* Tensor #173 */
AI_TENSOR_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_output, AI_STATIC,
  173, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_20_conv_Conv_output_0_output_array, NULL)

/* Tensor #174 */
AI_TENSOR_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_scratch0, AI_STATIC,
  174, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 3, 3), AI_STRIDE_INIT(4, 4, 4, 512, 1536),
  1, &_model_20_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #175 */
AI_TENSOR_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_weights, AI_STATIC,
  175, 0x0,
  AI_SHAPE_INIT(4, 128, 3, 3, 128), AI_STRIDE_INIT(4, 4, 512, 65536, 196608),
  1, &_model_20_conv_Conv_output_0_weights_array, NULL)

/* Tensor #176 */
AI_TENSOR_OBJ_DECLARE(
  _model_21_Concat_output_0_output, AI_STATIC,
  176, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1536, 15360),
  1, &_model_21_Concat_output_0_output_array, NULL)

/* Tensor #177 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_Concat_output_0_output, AI_STATIC,
  177, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1536, 15360),
  1, &_model_22_Concat_output_0_output_array, NULL)

/* Tensor #178 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_Split_output_0_num_or_size_splits, AI_STATIC,
  178, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_22_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #179 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_Split_output_0_output0, AI_STATIC,
  179, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_22_Split_output_0_output0_array, NULL)

/* Tensor #180 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_Split_output_0_output1, AI_STATIC,
  180, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_22_Split_output_0_output1_array, NULL)

/* Tensor #181 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv1_act_Mul_output_0_output, AI_STATIC,
  181, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_22_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #182 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  182, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_22_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #183 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_bias, AI_STATIC,
  183, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_22_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #184 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_output, AI_STATIC,
  184, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_22_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #185 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  185, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1536, 1536),
  1, &_model_22_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #186 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_weights, AI_STATIC,
  186, 0x0,
  AI_SHAPE_INIT(4, 384, 1, 1, 256), AI_STRIDE_INIT(4, 4, 1536, 393216, 393216),
  1, &_model_22_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #187 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv2_act_Mul_output_0_output, AI_STATIC,
  187, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_22_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #188 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  188, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_22_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #189 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_bias, AI_STATIC,
  189, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_22_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #190 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_output, AI_STATIC,
  190, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_22_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #191 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  191, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1536, 1536),
  1, &_model_22_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #192 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_weights, AI_STATIC,
  192, 0x0,
  AI_SHAPE_INIT(4, 384, 1, 1, 256), AI_STRIDE_INIT(4, 4, 1536, 393216, 393216),
  1, &_model_22_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #193 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_Concat_output_0_output, AI_STATIC,
  193, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_22_m_0_Concat_output_0_output_array, NULL)

/* Tensor #194 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  194, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #195 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  195, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #196 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  196, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_22_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #197 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  197, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #198 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  198, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_22_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #199 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  199, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 64), AI_STRIDE_INIT(4, 4, 512, 32768, 32768),
  1, &_model_22_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #200 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  200, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #201 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  201, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #202 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  202, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_22_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #203 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  203, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #204 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  204, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_22_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #205 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  205, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 64), AI_STRIDE_INIT(4, 4, 512, 32768, 32768),
  1, &_model_22_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #206 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Mul_output_0_output, AI_STATIC,
  206, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_22_m_0_cv3_act_Mul_output_0_output_array, NULL)

/* Tensor #207 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Sigmoid_output_0_output, AI_STATIC,
  207, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_22_m_0_cv3_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #208 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_bias, AI_STATIC,
  208, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_22_m_0_cv3_conv_Conv_output_0_bias_array, NULL)

/* Tensor #209 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_output, AI_STATIC,
  209, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_22_m_0_cv3_conv_Conv_output_0_output_array, NULL)

/* Tensor #210 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_scratch0, AI_STATIC,
  210, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_22_m_0_cv3_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #211 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_weights, AI_STATIC,
  211, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 128), AI_STRIDE_INIT(4, 4, 512, 65536, 65536),
  1, &_model_22_m_0_cv3_conv_Conv_output_0_weights_array, NULL)

/* Tensor #212 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_Add_output_0_output, AI_STATIC,
  212, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_Add_output_0_output_array, NULL)

/* Tensor #213 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  213, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #214 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  214, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #215 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  215, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #216 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  216, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #217 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  217, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #218 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  218, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #219 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  219, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #220 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  220, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #221 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  221, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #222 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  222, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #223 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  223, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #224 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  224, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #225 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_Add_output_0_output, AI_STATIC,
  225, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_Add_output_0_output_array, NULL)

/* Tensor #226 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Mul_output_0_output, AI_STATIC,
  226, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #227 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  227, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #228 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias, AI_STATIC,
  228, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #229 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output, AI_STATIC,
  229, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #230 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  230, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #231 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights, AI_STATIC,
  231, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #232 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Mul_output_0_output, AI_STATIC,
  232, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #233 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  233, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #234 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias, AI_STATIC,
  234, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #235 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output, AI_STATIC,
  235, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #236 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  236, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #237 */
AI_TENSOR_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights, AI_STATIC,
  237, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #238 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Add_1_output_0_output, AI_STATIC,
  238, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Add_1_output_0_output_array, NULL)

/* Tensor #239 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Add_2_output_0_output, AI_STATIC,
  239, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Add_2_output_0_output_array, NULL)

/* Tensor #240 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Concat_1_output_0_output, AI_STATIC,
  240, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_Concat_1_output_0_output_array, NULL)

/* Tensor #241 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Concat_2_output_0_output, AI_STATIC,
  241, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_model_23_Concat_2_output_0_output_array, NULL)

/* Tensor #242 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Concat_output_0_output, AI_STATIC,
  242, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_Concat_output_0_output_array, NULL)

/* Tensor #243 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Constant_12_output_0, AI_STATIC,
  243, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Constant_12_output_0_array, NULL)

/* Tensor #244 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Constant_13_output_0, AI_STATIC,
  244, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Constant_13_output_0_array, NULL)

/* Tensor #245 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Constant_14_output_0_3D, AI_STATIC,
  245, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_23_Constant_14_output_0_3D_array, NULL)

/* Tensor #246 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Constant_15_output_0_3D, AI_STATIC,
  246, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_23_Constant_15_output_0_3D_array, NULL)

/* Tensor #247 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Div_1_output_0_output, AI_STATIC,
  247, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Div_1_output_0_output_array, NULL)

/* Tensor #248 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Mul_2_output_0_output, AI_STATIC,
  248, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_model_23_Mul_2_output_0_output_array, NULL)

/* Tensor #249 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Sigmoid_output_0_output, AI_STATIC,
  249, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_Sigmoid_output_0_output_array, NULL)

/* Tensor #250 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Slice_1_output_0_output, AI_STATIC,
  250, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Slice_1_output_0_output_array, NULL)

/* Tensor #251 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Slice_output_0_output, AI_STATIC,
  251, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Slice_output_0_output_array, NULL)

/* Tensor #252 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Sub_1_output_0_output, AI_STATIC,
  252, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Sub_1_output_0_output_array, NULL)

/* Tensor #253 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_Sub_output_0_output, AI_STATIC,
  253, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &_model_23_Sub_output_0_output_array, NULL)

/* Tensor #254 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Mul_output_0_output, AI_STATIC,
  254, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_0_act_Mul_output_0_output_array, NULL)

/* Tensor #255 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output, AI_STATIC,
  255, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #256 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias, AI_STATIC,
  256, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #257 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output, AI_STATIC,
  257, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #258 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_scratch0, AI_STATIC,
  258, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #259 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights, AI_STATIC,
  259, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #260 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Mul_output_0_output, AI_STATIC,
  260, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_1_act_Mul_output_0_output_array, NULL)

/* Tensor #261 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output, AI_STATIC,
  261, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #262 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias, AI_STATIC,
  262, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #263 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output, AI_STATIC,
  263, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #264 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_scratch0, AI_STATIC,
  264, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #265 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights, AI_STATIC,
  265, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #266 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_bias, AI_STATIC,
  266, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array, NULL)

/* Tensor #267 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_output, AI_STATIC,
  267, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv2_0_cv2_0_2_Conv_output_0_output_array, NULL)

/* Tensor #268 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_output0, AI_STATIC,
  268, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1600), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_0_cv2_0_2_Conv_output_0_output_array, NULL)

/* Tensor #269 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_scratch0, AI_STATIC,
  269, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_0_cv2_0_2_Conv_output_0_scratch0_array, NULL)

/* Tensor #270 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_weights, AI_STATIC,
  270, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array, NULL)

/* Tensor #271 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Mul_output_0_output, AI_STATIC,
  271, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_0_act_Mul_output_0_output_array, NULL)

/* Tensor #272 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output, AI_STATIC,
  272, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #273 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias, AI_STATIC,
  273, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #274 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output, AI_STATIC,
  274, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #275 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_scratch0, AI_STATIC,
  275, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 3, 3), AI_STRIDE_INIT(4, 4, 4, 512, 1536),
  1, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #276 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights, AI_STATIC,
  276, 0x0,
  AI_SHAPE_INIT(4, 128, 3, 3, 64), AI_STRIDE_INIT(4, 4, 512, 32768, 98304),
  1, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #277 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Mul_output_0_output, AI_STATIC,
  277, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_1_act_Mul_output_0_output_array, NULL)

/* Tensor #278 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output, AI_STATIC,
  278, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #279 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias, AI_STATIC,
  279, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #280 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output, AI_STATIC,
  280, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #281 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_scratch0, AI_STATIC,
  281, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #282 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights, AI_STATIC,
  282, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #283 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_bias, AI_STATIC,
  283, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array, NULL)

/* Tensor #284 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_output, AI_STATIC,
  284, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv2_1_cv2_1_2_Conv_output_0_output_array, NULL)

/* Tensor #285 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_output0, AI_STATIC,
  285, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 400), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_1_cv2_1_2_Conv_output_0_output_array, NULL)

/* Tensor #286 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_scratch0, AI_STATIC,
  286, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_1_cv2_1_2_Conv_output_0_scratch0_array, NULL)

/* Tensor #287 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_weights, AI_STATIC,
  287, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array, NULL)

/* Tensor #288 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Mul_output_0_output, AI_STATIC,
  288, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_0_act_Mul_output_0_output_array, NULL)

/* Tensor #289 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output, AI_STATIC,
  289, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #290 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias, AI_STATIC,
  290, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #291 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output, AI_STATIC,
  291, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #292 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_scratch0, AI_STATIC,
  292, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 3, 3), AI_STRIDE_INIT(4, 4, 4, 1024, 3072),
  1, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #293 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights, AI_STATIC,
  293, 0x0,
  AI_SHAPE_INIT(4, 256, 3, 3, 64), AI_STRIDE_INIT(4, 4, 1024, 65536, 196608),
  1, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #294 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Mul_output_0_output, AI_STATIC,
  294, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_1_act_Mul_output_0_output_array, NULL)

/* Tensor #295 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output, AI_STATIC,
  295, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #296 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias, AI_STATIC,
  296, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #297 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output, AI_STATIC,
  297, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #298 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_scratch0, AI_STATIC,
  298, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #299 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights, AI_STATIC,
  299, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #300 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_bias, AI_STATIC,
  300, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array, NULL)

/* Tensor #301 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_output, AI_STATIC,
  301, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv2_2_cv2_2_2_Conv_output_0_output_array, NULL)

/* Tensor #302 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_output0, AI_STATIC,
  302, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 100), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_2_cv2_2_2_Conv_output_0_output_array, NULL)

/* Tensor #303 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_scratch0, AI_STATIC,
  303, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv2_2_cv2_2_2_Conv_output_0_scratch0_array, NULL)

/* Tensor #304 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_weights, AI_STATIC,
  304, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array, NULL)

/* Tensor #305 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output, AI_STATIC,
  305, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output_array, NULL)

/* Tensor #306 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output, AI_STATIC,
  306, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #307 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias, AI_STATIC,
  307, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #308 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output, AI_STATIC,
  308, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #309 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights, AI_STATIC,
  309, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 1, 64, 64, 64),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #310 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output, AI_STATIC,
  310, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output_array, NULL)

/* Tensor #311 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output, AI_STATIC,
  311, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #312 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias, AI_STATIC,
  312, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #313 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output, AI_STATIC,
  313, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #314 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_scratch0, AI_STATIC,
  314, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #315 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights, AI_STATIC,
  315, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #316 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output, AI_STATIC,
  316, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output_array, NULL)

/* Tensor #317 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output, AI_STATIC,
  317, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #318 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias, AI_STATIC,
  318, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #319 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output, AI_STATIC,
  319, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #320 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights, AI_STATIC,
  320, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 1, 64, 64, 64),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #321 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output, AI_STATIC,
  321, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output_array, NULL)

/* Tensor #322 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output, AI_STATIC,
  322, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #323 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias, AI_STATIC,
  323, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #324 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output, AI_STATIC,
  324, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #325 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_scratch0, AI_STATIC,
  325, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #326 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights, AI_STATIC,
  326, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #327 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_bias, AI_STATIC,
  327, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 1), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array, NULL)

/* Tensor #328 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_output, AI_STATIC,
  328, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 40, 40), AI_STRIDE_INIT(4, 4, 4, 112, 4480),
  1, &_model_23_cv3_0_cv3_0_2_Conv_output_0_output_array, NULL)

/* Tensor #329 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_output0, AI_STATIC,
  329, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 1600), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_cv3_0_cv3_0_2_Conv_output_0_output_array, NULL)

/* Tensor #330 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_scratch0, AI_STATIC,
  330, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_0_cv3_0_2_Conv_output_0_scratch0_array, NULL)

/* Tensor #331 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_weights, AI_STATIC,
  331, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 28), AI_STRIDE_INIT(4, 4, 256, 7168, 7168),
  1, &_model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array, NULL)

/* Tensor #332 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output, AI_STATIC,
  332, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output_array, NULL)

/* Tensor #333 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output, AI_STATIC,
  333, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #334 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias, AI_STATIC,
  334, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #335 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output, AI_STATIC,
  335, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #336 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights, AI_STATIC,
  336, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 128), AI_STRIDE_INIT(4, 1, 128, 128, 128),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #337 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output, AI_STATIC,
  337, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output_array, NULL)

/* Tensor #338 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output, AI_STATIC,
  338, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #339 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias, AI_STATIC,
  339, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #340 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output, AI_STATIC,
  340, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #341 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_scratch0, AI_STATIC,
  341, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #342 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights, AI_STATIC,
  342, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 64), AI_STRIDE_INIT(4, 4, 512, 32768, 32768),
  1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #343 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output, AI_STATIC,
  343, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output_array, NULL)

/* Tensor #344 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output, AI_STATIC,
  344, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #345 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias, AI_STATIC,
  345, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #346 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output, AI_STATIC,
  346, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #347 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights, AI_STATIC,
  347, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 1, 64, 64, 64),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #348 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output, AI_STATIC,
  348, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output_array, NULL)

/* Tensor #349 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output, AI_STATIC,
  349, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #350 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias, AI_STATIC,
  350, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #351 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output, AI_STATIC,
  351, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #352 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_scratch0, AI_STATIC,
  352, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #353 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights, AI_STATIC,
  353, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #354 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_bias, AI_STATIC,
  354, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 1), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array, NULL)

/* Tensor #355 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_output, AI_STATIC,
  355, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 20, 20), AI_STRIDE_INIT(4, 4, 4, 112, 2240),
  1, &_model_23_cv3_1_cv3_1_2_Conv_output_0_output_array, NULL)

/* Tensor #356 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_output0, AI_STATIC,
  356, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 400), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_cv3_1_cv3_1_2_Conv_output_0_output_array, NULL)

/* Tensor #357 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_scratch0, AI_STATIC,
  357, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_1_cv3_1_2_Conv_output_0_scratch0_array, NULL)

/* Tensor #358 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_weights, AI_STATIC,
  358, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 28), AI_STRIDE_INIT(4, 4, 256, 7168, 7168),
  1, &_model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array, NULL)

/* Tensor #359 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output, AI_STATIC,
  359, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output_array, NULL)

/* Tensor #360 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output, AI_STATIC,
  360, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #361 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias, AI_STATIC,
  361, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #362 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output, AI_STATIC,
  362, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #363 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights, AI_STATIC,
  363, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 256), AI_STRIDE_INIT(4, 1, 256, 256, 256),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #364 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output, AI_STATIC,
  364, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output_array, NULL)

/* Tensor #365 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output, AI_STATIC,
  365, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #366 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias, AI_STATIC,
  366, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #367 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output, AI_STATIC,
  367, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #368 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_scratch0, AI_STATIC,
  368, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #369 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights, AI_STATIC,
  369, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 64), AI_STRIDE_INIT(4, 4, 1024, 65536, 65536),
  1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #370 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output, AI_STATIC,
  370, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output_array, NULL)

/* Tensor #371 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output, AI_STATIC,
  371, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #372 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias, AI_STATIC,
  372, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array, NULL)

/* Tensor #373 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output, AI_STATIC,
  373, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output_array, NULL)

/* Tensor #374 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights, AI_STATIC,
  374, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 64), AI_STRIDE_INIT(4, 1, 64, 64, 64),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array, NULL)

/* Tensor #375 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output, AI_STATIC,
  375, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output_array, NULL)

/* Tensor #376 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output, AI_STATIC,
  376, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #377 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias, AI_STATIC,
  377, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #378 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output, AI_STATIC,
  378, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output_array, NULL)

/* Tensor #379 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_scratch0, AI_STATIC,
  379, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #380 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights, AI_STATIC,
  380, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #381 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_bias, AI_STATIC,
  381, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 1), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array, NULL)

/* Tensor #382 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_output, AI_STATIC,
  382, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 10, 10), AI_STRIDE_INIT(4, 4, 4, 112, 1120),
  1, &_model_23_cv3_2_cv3_2_2_Conv_output_0_output_array, NULL)

/* Tensor #383 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_output0, AI_STATIC,
  383, 0x0,
  AI_SHAPE_INIT(4, 1, 28, 1, 100), AI_STRIDE_INIT(4, 4, 4, 112, 112),
  1, &_model_23_cv3_2_cv3_2_2_Conv_output_0_output_array, NULL)

/* Tensor #384 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_scratch0, AI_STATIC,
  384, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_23_cv3_2_cv3_2_2_Conv_output_0_scratch0_array, NULL)

/* Tensor #385 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_weights, AI_STATIC,
  385, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 28), AI_STRIDE_INIT(4, 4, 256, 7168, 7168),
  1, &_model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array, NULL)

/* Tensor #386 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chfirst_output, AI_STATIC,
  386, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &_model_23_dfl_Reshape_1_output_0_to_chfirst_output_array, NULL)

/* Tensor #387 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chlast_output, AI_STATIC,
  387, 0x0,
  AI_SHAPE_INIT(4, 1, 2100, 4, 1), AI_STRIDE_INIT(4, 4, 4, 8400, 33600),
  1, &_model_23_dfl_Reshape_1_output_0_to_chlast_output_array, NULL)

/* Tensor #388 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chlast_output0, AI_STATIC,
  388, 0x0,
  AI_SHAPE_INIT(4, 1, 2100, 1, 4), AI_STRIDE_INIT(4, 4, 4, 8400, 8400),
  1, &_model_23_dfl_Reshape_1_output_0_to_chlast_output_array, NULL)

/* Tensor #389 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Reshape_output_0_to_chlast_output, AI_STATIC,
  389, 0x0,
  AI_SHAPE_INIT(4, 1, 2100, 1, 64), AI_STRIDE_INIT(4, 4, 4, 8400, 8400),
  1, &_model_23_dfl_Reshape_output_0_to_chlast_output_array, NULL)

/* Tensor #390 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Reshape_output_0_to_chlast_output0, AI_STATIC,
  390, 0x0,
  AI_SHAPE_INIT(4, 1, 2100, 16, 4), AI_STRIDE_INIT(4, 4, 4, 8400, 134400),
  1, &_model_23_dfl_Reshape_output_0_to_chlast_output_array, NULL)

/* Tensor #391 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Softmax_output_0_output, AI_STATIC,
  391, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 2100, 4), AI_STRIDE_INIT(4, 4, 4, 64, 134400),
  1, &_model_23_dfl_Softmax_output_0_output_array, NULL)

/* Tensor #392 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_Transpose_output_0_output, AI_STATIC,
  392, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 2100, 4), AI_STRIDE_INIT(4, 4, 4, 64, 134400),
  1, &_model_23_dfl_Transpose_output_0_output_array, NULL)

/* Tensor #393 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_bias, AI_STATIC,
  393, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_23_dfl_conv_Conv_output_0_bias_array, NULL)

/* Tensor #394 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_output, AI_STATIC,
  394, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 2100, 4), AI_STRIDE_INIT(4, 4, 4, 4, 8400),
  1, &_model_23_dfl_conv_Conv_output_0_output_array, NULL)

/* Tensor #395 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_scratch0, AI_STATIC,
  395, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_model_23_dfl_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #396 */
AI_TENSOR_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_weights, AI_STATIC,
  396, 0x0,
  AI_SHAPE_INIT(4, 16, 1, 1, 1), AI_STRIDE_INIT(4, 4, 64, 64, 64),
  1, &_model_23_dfl_conv_Conv_output_0_weights_array, NULL)

/* Tensor #397 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_Concat_output_0_output, AI_STATIC,
  397, 0x0,
  AI_SHAPE_INIT(4, 1, 48, 80, 80), AI_STRIDE_INIT(4, 4, 4, 192, 15360),
  1, &_model_2_Concat_output_0_output_array, NULL)

/* Tensor #398 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_Split_output_0_num_or_size_splits, AI_STATIC,
  398, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_2_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #399 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_Split_output_0_output0, AI_STATIC,
  399, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 80, 80), AI_STRIDE_INIT(4, 4, 4, 64, 5120),
  1, &_model_2_Split_output_0_output0_array, NULL)

/* Tensor #400 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_Split_output_0_output1, AI_STATIC,
  400, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 80, 80), AI_STRIDE_INIT(4, 4, 4, 64, 5120),
  1, &_model_2_Split_output_0_output1_array, NULL)

/* Tensor #401 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv1_act_Mul_output_0_output, AI_STATIC,
  401, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 80, 80), AI_STRIDE_INIT(4, 4, 4, 128, 10240),
  1, &_model_2_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #402 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  402, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 80, 80), AI_STRIDE_INIT(4, 4, 4, 128, 10240),
  1, &_model_2_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #403 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_bias, AI_STATIC,
  403, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_2_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #404 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_output, AI_STATIC,
  404, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 80, 80), AI_STRIDE_INIT(4, 4, 4, 128, 10240),
  1, &_model_2_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #405 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  405, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_2_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #406 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_weights, AI_STATIC,
  406, 0x0,
  AI_SHAPE_INIT(4, 32, 1, 1, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 4096),
  1, &_model_2_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #407 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv2_act_Mul_output_0_output, AI_STATIC,
  407, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 80, 80), AI_STRIDE_INIT(4, 4, 4, 256, 20480),
  1, &_model_2_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #408 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  408, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 80, 80), AI_STRIDE_INIT(4, 4, 4, 256, 20480),
  1, &_model_2_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #409 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_bias, AI_STATIC,
  409, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_2_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #410 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_output, AI_STATIC,
  410, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 80, 80), AI_STRIDE_INIT(4, 4, 4, 256, 20480),
  1, &_model_2_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #411 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  411, 0x0,
  AI_SHAPE_INIT(4, 1, 48, 1, 1), AI_STRIDE_INIT(4, 4, 4, 192, 192),
  1, &_model_2_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #412 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_weights, AI_STATIC,
  412, 0x0,
  AI_SHAPE_INIT(4, 48, 1, 1, 64), AI_STRIDE_INIT(4, 4, 192, 12288, 12288),
  1, &_model_2_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #413 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_Add_output_0_output, AI_STATIC,
  413, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 80, 80), AI_STRIDE_INIT(4, 4, 4, 64, 5120),
  1, &_model_2_m_0_Add_output_0_output_array, NULL)

/* Tensor #414 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  414, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 80, 80), AI_STRIDE_INIT(4, 4, 4, 32, 2560),
  1, &_model_2_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #415 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  415, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 80, 80), AI_STRIDE_INIT(4, 4, 4, 32, 2560),
  1, &_model_2_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #416 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  416, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &_model_2_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #417 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  417, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 80, 80), AI_STRIDE_INIT(4, 4, 4, 32, 2560),
  1, &_model_2_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #418 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  418, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 3), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &_model_2_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #419 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  419, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 8), AI_STRIDE_INIT(4, 4, 64, 512, 1536),
  1, &_model_2_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #420 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  420, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 80, 80), AI_STRIDE_INIT(4, 4, 4, 64, 5120),
  1, &_model_2_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #421 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  421, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 80, 80), AI_STRIDE_INIT(4, 4, 4, 64, 5120),
  1, &_model_2_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #422 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  422, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_model_2_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #423 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  423, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 80, 80), AI_STRIDE_INIT(4, 4, 4, 64, 5120),
  1, &_model_2_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #424 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  424, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 3, 3), AI_STRIDE_INIT(4, 4, 4, 32, 96),
  1, &_model_2_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #425 */
AI_TENSOR_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  425, 0x0,
  AI_SHAPE_INIT(4, 8, 3, 3, 16), AI_STRIDE_INIT(4, 4, 32, 512, 1536),
  1, &_model_2_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #426 */
AI_TENSOR_OBJ_DECLARE(
  _model_3_act_Mul_output_0_output, AI_STATIC,
  426, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_3_act_Mul_output_0_output_array, NULL)

/* Tensor #427 */
AI_TENSOR_OBJ_DECLARE(
  _model_3_act_Sigmoid_output_0_output, AI_STATIC,
  427, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_3_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #428 */
AI_TENSOR_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_bias, AI_STATIC,
  428, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_3_conv_Conv_output_0_bias_array, NULL)

/* Tensor #429 */
AI_TENSOR_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_output, AI_STATIC,
  429, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_3_conv_Conv_output_0_output_array, NULL)

/* Tensor #430 */
AI_TENSOR_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_scratch0, AI_STATIC,
  430, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_3_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #431 */
AI_TENSOR_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_weights, AI_STATIC,
  431, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_3_conv_Conv_output_0_weights_array, NULL)

/* Tensor #432 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_Concat_output_0_output, AI_STATIC,
  432, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 40, 40), AI_STRIDE_INIT(4, 4, 4, 384, 15360),
  1, &_model_4_Concat_output_0_output_array, NULL)

/* Tensor #433 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_Split_output_0_num_or_size_splits, AI_STATIC,
  433, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_4_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #434 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_Split_output_0_output0, AI_STATIC,
  434, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_4_Split_output_0_output0_array, NULL)

/* Tensor #435 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_Split_output_0_output1, AI_STATIC,
  435, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_4_Split_output_0_output1_array, NULL)

/* Tensor #436 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv1_act_Mul_output_0_output, AI_STATIC,
  436, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_4_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #437 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  437, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_4_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #438 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_bias, AI_STATIC,
  438, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_4_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #439 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_output, AI_STATIC,
  439, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 40, 40), AI_STRIDE_INIT(4, 4, 4, 256, 10240),
  1, &_model_4_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #440 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  440, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_4_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #441 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_weights, AI_STATIC,
  441, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_4_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #442 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv2_act_Mul_output_0_output, AI_STATIC,
  442, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 40, 40), AI_STRIDE_INIT(4, 4, 4, 512, 20480),
  1, &_model_4_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #443 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  443, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 40, 40), AI_STRIDE_INIT(4, 4, 4, 512, 20480),
  1, &_model_4_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #444 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_bias, AI_STATIC,
  444, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_4_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #445 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_output, AI_STATIC,
  445, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 40, 40), AI_STRIDE_INIT(4, 4, 4, 512, 20480),
  1, &_model_4_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #446 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  446, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 4, 4, 384, 384),
  1, &_model_4_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #447 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_weights, AI_STATIC,
  447, 0x0,
  AI_SHAPE_INIT(4, 96, 1, 1, 128), AI_STRIDE_INIT(4, 4, 384, 49152, 49152),
  1, &_model_4_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #448 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_Add_output_0_output, AI_STATIC,
  448, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_4_m_0_Add_output_0_output_array, NULL)

/* Tensor #449 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  449, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 40, 40), AI_STRIDE_INIT(4, 4, 4, 64, 2560),
  1, &_model_4_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #450 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  450, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 40, 40), AI_STRIDE_INIT(4, 4, 4, 64, 2560),
  1, &_model_4_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #451 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  451, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &_model_4_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #452 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  452, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 40, 40), AI_STRIDE_INIT(4, 4, 4, 64, 2560),
  1, &_model_4_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #453 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  453, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_4_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #454 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  454, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 16), AI_STRIDE_INIT(4, 4, 128, 2048, 6144),
  1, &_model_4_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #455 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  455, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_4_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #456 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  456, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_4_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #457 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  457, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_4_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #458 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  458, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 40, 40), AI_STRIDE_INIT(4, 4, 4, 128, 5120),
  1, &_model_4_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #459 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  459, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 3, 3), AI_STRIDE_INIT(4, 4, 4, 64, 192),
  1, &_model_4_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #460 */
AI_TENSOR_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  460, 0x0,
  AI_SHAPE_INIT(4, 16, 3, 3, 32), AI_STRIDE_INIT(4, 4, 64, 2048, 6144),
  1, &_model_4_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #461 */
AI_TENSOR_OBJ_DECLARE(
  _model_5_act_Mul_output_0_output, AI_STATIC,
  461, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_5_act_Mul_output_0_output_array, NULL)

/* Tensor #462 */
AI_TENSOR_OBJ_DECLARE(
  _model_5_act_Sigmoid_output_0_output, AI_STATIC,
  462, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_5_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #463 */
AI_TENSOR_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_bias, AI_STATIC,
  463, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_5_conv_Conv_output_0_bias_array, NULL)

/* Tensor #464 */
AI_TENSOR_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_output, AI_STATIC,
  464, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_5_conv_Conv_output_0_output_array, NULL)

/* Tensor #465 */
AI_TENSOR_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_scratch0, AI_STATIC,
  465, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 3, 3), AI_STRIDE_INIT(4, 4, 4, 512, 1536),
  1, &_model_5_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #466 */
AI_TENSOR_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_weights, AI_STATIC,
  466, 0x0,
  AI_SHAPE_INIT(4, 128, 3, 3, 128), AI_STRIDE_INIT(4, 4, 512, 65536, 196608),
  1, &_model_5_conv_Conv_output_0_weights_array, NULL)

/* Tensor #467 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_Concat_output_0_output, AI_STATIC,
  467, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 20, 20), AI_STRIDE_INIT(4, 4, 4, 768, 15360),
  1, &_model_6_Concat_output_0_output_array, NULL)

/* Tensor #468 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_Split_output_0_num_or_size_splits, AI_STATIC,
  468, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_6_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #469 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_Split_output_0_output0, AI_STATIC,
  469, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_6_Split_output_0_output0_array, NULL)

/* Tensor #470 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_Split_output_0_output1, AI_STATIC,
  470, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_6_Split_output_0_output1_array, NULL)

/* Tensor #471 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv1_act_Mul_output_0_output, AI_STATIC,
  471, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_6_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #472 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  472, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_6_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #473 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_bias, AI_STATIC,
  473, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_6_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #474 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_output, AI_STATIC,
  474, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_6_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #475 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  475, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_6_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #476 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_weights, AI_STATIC,
  476, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 128), AI_STRIDE_INIT(4, 4, 512, 65536, 65536),
  1, &_model_6_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #477 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv2_act_Mul_output_0_output, AI_STATIC,
  477, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_6_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #478 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  478, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_6_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #479 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_bias, AI_STATIC,
  479, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_6_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #480 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_output, AI_STATIC,
  480, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 20, 20), AI_STRIDE_INIT(4, 4, 4, 512, 10240),
  1, &_model_6_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #481 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  481, 0x0,
  AI_SHAPE_INIT(4, 1, 192, 1, 1), AI_STRIDE_INIT(4, 4, 4, 768, 768),
  1, &_model_6_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #482 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_weights, AI_STATIC,
  482, 0x0,
  AI_SHAPE_INIT(4, 192, 1, 1, 128), AI_STRIDE_INIT(4, 4, 768, 98304, 98304),
  1, &_model_6_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #483 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_Concat_output_0_output, AI_STATIC,
  483, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_6_m_0_Concat_output_0_output_array, NULL)

/* Tensor #484 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  484, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #485 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  485, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #486 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  486, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_6_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #487 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  487, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #488 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  488, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_6_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #489 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  489, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 32), AI_STRIDE_INIT(4, 4, 256, 8192, 8192),
  1, &_model_6_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #490 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  490, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #491 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  491, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #492 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  492, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_6_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #493 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  493, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #494 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  494, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_6_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #495 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  495, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 32), AI_STRIDE_INIT(4, 4, 256, 8192, 8192),
  1, &_model_6_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #496 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Mul_output_0_output, AI_STATIC,
  496, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_6_m_0_cv3_act_Mul_output_0_output_array, NULL)

/* Tensor #497 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Sigmoid_output_0_output, AI_STATIC,
  497, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_6_m_0_cv3_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #498 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_bias, AI_STATIC,
  498, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_6_m_0_cv3_conv_Conv_output_0_bias_array, NULL)

/* Tensor #499 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_output, AI_STATIC,
  499, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 20, 20), AI_STRIDE_INIT(4, 4, 4, 256, 5120),
  1, &_model_6_m_0_cv3_conv_Conv_output_0_output_array, NULL)

/* Tensor #500 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_scratch0, AI_STATIC,
  500, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_6_m_0_cv3_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #501 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_weights, AI_STATIC,
  501, 0x0,
  AI_SHAPE_INIT(4, 64, 1, 1, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 16384),
  1, &_model_6_m_0_cv3_conv_Conv_output_0_weights_array, NULL)

/* Tensor #502 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_Add_output_0_output, AI_STATIC,
  502, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_Add_output_0_output_array, NULL)

/* Tensor #503 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  503, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #504 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  504, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #505 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  505, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #506 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  506, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #507 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  507, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #508 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  508, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #509 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  509, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #510 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  510, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #511 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  511, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #512 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  512, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #513 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  513, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #514 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  514, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #515 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_Add_output_0_output, AI_STATIC,
  515, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_Add_output_0_output_array, NULL)

/* Tensor #516 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Mul_output_0_output, AI_STATIC,
  516, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #517 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  517, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #518 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias, AI_STATIC,
  518, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #519 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output, AI_STATIC,
  519, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #520 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  520, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #521 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights, AI_STATIC,
  521, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #522 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Mul_output_0_output, AI_STATIC,
  522, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #523 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  523, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #524 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias, AI_STATIC,
  524, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #525 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output, AI_STATIC,
  525, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #526 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  526, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #527 */
AI_TENSOR_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights, AI_STATIC,
  527, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #528 */
AI_TENSOR_OBJ_DECLARE(
  _model_7_act_Mul_output_0_output, AI_STATIC,
  528, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_7_act_Mul_output_0_output_array, NULL)

/* Tensor #529 */
AI_TENSOR_OBJ_DECLARE(
  _model_7_act_Sigmoid_output_0_output, AI_STATIC,
  529, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_7_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #530 */
AI_TENSOR_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_bias, AI_STATIC,
  530, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_7_conv_Conv_output_0_bias_array, NULL)

/* Tensor #531 */
AI_TENSOR_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_output, AI_STATIC,
  531, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_7_conv_Conv_output_0_output_array, NULL)

/* Tensor #532 */
AI_TENSOR_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_scratch0, AI_STATIC,
  532, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 3, 3), AI_STRIDE_INIT(4, 4, 4, 512, 1536),
  1, &_model_7_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #533 */
AI_TENSOR_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_weights, AI_STATIC,
  533, 0x0,
  AI_SHAPE_INIT(4, 128, 3, 3, 256), AI_STRIDE_INIT(4, 4, 512, 131072, 393216),
  1, &_model_7_conv_Conv_output_0_weights_array, NULL)

/* Tensor #534 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_Concat_output_0_output, AI_STATIC,
  534, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1536, 15360),
  1, &_model_8_Concat_output_0_output_array, NULL)

/* Tensor #535 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_Split_output_0_num_or_size_splits, AI_STATIC,
  535, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_model_8_Split_output_0_num_or_size_splits_array, NULL)

/* Tensor #536 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_Split_output_0_output0, AI_STATIC,
  536, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_8_Split_output_0_output0_array, NULL)

/* Tensor #537 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_Split_output_0_output1, AI_STATIC,
  537, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_8_Split_output_0_output1_array, NULL)

/* Tensor #538 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv1_act_Mul_output_0_output, AI_STATIC,
  538, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_8_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #539 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  539, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_8_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #540 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_bias, AI_STATIC,
  540, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_8_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #541 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_output, AI_STATIC,
  541, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_8_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #542 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  542, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_8_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #543 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_weights, AI_STATIC,
  543, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 256), AI_STRIDE_INIT(4, 4, 1024, 262144, 262144),
  1, &_model_8_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #544 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv2_act_Mul_output_0_output, AI_STATIC,
  544, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_8_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #545 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  545, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_8_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #546 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_bias, AI_STATIC,
  546, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_8_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #547 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_output, AI_STATIC,
  547, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_8_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #548 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  548, 0x0,
  AI_SHAPE_INIT(4, 1, 384, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1536, 1536),
  1, &_model_8_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #549 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_weights, AI_STATIC,
  549, 0x0,
  AI_SHAPE_INIT(4, 384, 1, 1, 256), AI_STRIDE_INIT(4, 4, 1536, 393216, 393216),
  1, &_model_8_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #550 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_Concat_output_0_output, AI_STATIC,
  550, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_8_m_0_Concat_output_0_output_array, NULL)

/* Tensor #551 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  551, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #552 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  552, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #553 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  553, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_8_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #554 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  554, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #555 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  555, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_8_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #556 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  556, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 64), AI_STRIDE_INIT(4, 4, 512, 32768, 32768),
  1, &_model_8_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #557 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  557, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #558 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  558, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #559 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  559, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_8_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #560 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  560, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #561 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  561, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_8_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #562 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  562, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 64), AI_STRIDE_INIT(4, 4, 512, 32768, 32768),
  1, &_model_8_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #563 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Mul_output_0_output, AI_STATIC,
  563, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_8_m_0_cv3_act_Mul_output_0_output_array, NULL)

/* Tensor #564 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Sigmoid_output_0_output, AI_STATIC,
  564, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_8_m_0_cv3_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #565 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_bias, AI_STATIC,
  565, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_8_m_0_cv3_conv_Conv_output_0_bias_array, NULL)

/* Tensor #566 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_output, AI_STATIC,
  566, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_8_m_0_cv3_conv_Conv_output_0_output_array, NULL)

/* Tensor #567 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_scratch0, AI_STATIC,
  567, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_8_m_0_cv3_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #568 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_weights, AI_STATIC,
  568, 0x0,
  AI_SHAPE_INIT(4, 128, 1, 1, 128), AI_STRIDE_INIT(4, 4, 512, 65536, 65536),
  1, &_model_8_m_0_cv3_conv_Conv_output_0_weights_array, NULL)

/* Tensor #569 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_Add_output_0_output, AI_STATIC,
  569, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_Add_output_0_output_array, NULL)

/* Tensor #570 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Mul_output_0_output, AI_STATIC,
  570, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #571 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  571, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #572 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias, AI_STATIC,
  572, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #573 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output, AI_STATIC,
  573, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #574 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  574, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #575 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights, AI_STATIC,
  575, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #576 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Mul_output_0_output, AI_STATIC,
  576, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #577 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  577, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #578 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias, AI_STATIC,
  578, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #579 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output, AI_STATIC,
  579, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #580 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  580, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #581 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights, AI_STATIC,
  581, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #582 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_Add_output_0_output, AI_STATIC,
  582, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_Add_output_0_output_array, NULL)

/* Tensor #583 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Mul_output_0_output, AI_STATIC,
  583, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_cv1_act_Mul_output_0_output_array, NULL)

/* Tensor #584 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output, AI_STATIC,
  584, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #585 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias, AI_STATIC,
  585, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #586 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output, AI_STATIC,
  586, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #587 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  587, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #588 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights, AI_STATIC,
  588, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #589 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Mul_output_0_output, AI_STATIC,
  589, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #590 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  590, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #591 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias, AI_STATIC,
  591, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #592 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output, AI_STATIC,
  592, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 10, 10), AI_STRIDE_INIT(4, 4, 4, 256, 2560),
  1, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #593 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  593, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 3, 3), AI_STRIDE_INIT(4, 4, 4, 256, 768),
  1, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #594 */
AI_TENSOR_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights, AI_STATIC,
  594, 0x0,
  AI_SHAPE_INIT(4, 64, 3, 3, 64), AI_STRIDE_INIT(4, 4, 256, 16384, 49152),
  1, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #595 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_Concat_output_0_output, AI_STATIC,
  595, 0x0,
  AI_SHAPE_INIT(4, 1, 512, 10, 10), AI_STRIDE_INIT(4, 4, 4, 2048, 20480),
  1, &_model_9_Concat_output_0_output_array, NULL)

/* Tensor #596 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_bias, AI_STATIC,
  596, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 1, 1), AI_STRIDE_INIT(4, 4, 4, 512, 512),
  1, &_model_9_cv1_conv_Conv_output_0_bias_array, NULL)

/* Tensor #597 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_output, AI_STATIC,
  597, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_9_cv1_conv_Conv_output_0_output_array, NULL)

/* Tensor #598 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_scratch0, AI_STATIC,
  598, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_9_cv1_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #599 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_weights, AI_STATIC,
  599, 0x0,
  AI_SHAPE_INIT(4, 256, 1, 1, 128), AI_STRIDE_INIT(4, 4, 1024, 131072, 131072),
  1, &_model_9_cv1_conv_Conv_output_0_weights_array, NULL)

/* Tensor #600 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv2_act_Mul_output_0_output, AI_STATIC,
  600, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_9_cv2_act_Mul_output_0_output_array, NULL)

/* Tensor #601 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv2_act_Sigmoid_output_0_output, AI_STATIC,
  601, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_9_cv2_act_Sigmoid_output_0_output_array, NULL)

/* Tensor #602 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_bias, AI_STATIC,
  602, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_model_9_cv2_conv_Conv_output_0_bias_array, NULL)

/* Tensor #603 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_output, AI_STATIC,
  603, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 10, 10), AI_STRIDE_INIT(4, 4, 4, 1024, 10240),
  1, &_model_9_cv2_conv_Conv_output_0_output_array, NULL)

/* Tensor #604 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_scratch0, AI_STATIC,
  604, 0x0,
  AI_SHAPE_INIT(4, 1, 512, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2048, 2048),
  1, &_model_9_cv2_conv_Conv_output_0_scratch0_array, NULL)

/* Tensor #605 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_weights, AI_STATIC,
  605, 0x0,
  AI_SHAPE_INIT(4, 512, 1, 1, 256), AI_STRIDE_INIT(4, 4, 2048, 524288, 524288),
  1, &_model_9_cv2_conv_Conv_output_0_weights_array, NULL)

/* Tensor #606 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_m_1_MaxPool_output_0_output, AI_STATIC,
  606, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_9_m_1_MaxPool_output_0_output_array, NULL)

/* Tensor #607 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_m_2_MaxPool_output_0_output, AI_STATIC,
  607, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_9_m_2_MaxPool_output_0_output_array, NULL)

/* Tensor #608 */
AI_TENSOR_OBJ_DECLARE(
  _model_9_m_MaxPool_output_0_output, AI_STATIC,
  608, 0x0,
  AI_SHAPE_INIT(4, 1, 128, 10, 10), AI_STRIDE_INIT(4, 4, 4, 512, 5120),
  1, &_model_9_m_MaxPool_output_0_output_array, NULL)

/* Tensor #609 */
AI_TENSOR_OBJ_DECLARE(
  images_Transpose_output, AI_STATIC,
  609, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 320, 320), AI_STRIDE_INIT(4, 4, 4, 12, 3840),
  1, &images_Transpose_output_array, NULL)

/* Tensor #610 */
AI_TENSOR_OBJ_DECLARE(
  images_output, AI_STATIC,
  610, 0x0,
  AI_SHAPE_INIT(4, 1, 320, 320, 3), AI_STRIDE_INIT(4, 4, 4, 1280, 409600),
  1, &images_output_array, NULL)

/* Tensor #611 */
AI_TENSOR_OBJ_DECLARE(
  output0_Transpose_0_output, AI_STATIC,
  611, 0x0,
  AI_SHAPE_INIT(4, 1, 2100, 1, 32), AI_STRIDE_INIT(4, 4, 4, 8400, 8400),
  1, &output0_Transpose_0_output_array, NULL)

/* Tensor #612 */
AI_TENSOR_OBJ_DECLARE(
  output0_output, AI_STATIC,
  612, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 2100), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &output0_output_array, NULL)

/* Tensor #613 */
AI_TENSOR_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output, AI_STATIC,
  613, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 64, 2), AI_STRIDE_INIT(4, 4, 4, 400, 25600),
  1, &transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array, NULL)

/* Tensor #614 */
AI_TENSOR_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output, AI_STATIC,
  614, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 100, 2), AI_STRIDE_INIT(4, 4, 4, 128, 12800),
  1, &transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output_array, NULL)

/* Tensor #615 */
AI_TENSOR_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output, AI_STATIC,
  615, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 100, 2), AI_STRIDE_INIT(4, 4, 4, 400, 40000),
  1, &transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array, NULL)

/* Tensor #616 */
AI_TENSOR_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output, AI_STATIC,
  616, 0x0,
  AI_SHAPE_INIT(4, 1, 100, 32, 2), AI_STRIDE_INIT(4, 4, 4, 400, 12800),
  1, &transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output_array, NULL)

/* Tensor #617 */
AI_TENSOR_OBJ_DECLARE(
  transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output, AI_STATIC,
  617, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 100, 100), AI_STRIDE_INIT(4, 4, 4, 8, 800),
  1, &transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output0_Transpose_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output0_Transpose_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output0_Transpose_0_layer, 1,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &output0_Transpose_0_chain,
  NULL, &output0_Transpose_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_WIDTH, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  output0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Mul_2_output_0_output, &_model_23_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output0_layer, 318,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &output0_chain,
  NULL, &output0_Transpose_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Mul_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Concat_2_output_0_output, &_model_23_Constant_15_output_0_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Mul_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Mul_2_output_0_layer, 317,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_Mul_2_output_0_chain,
  NULL, &output0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Concat_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Div_1_output_0_output, &_model_23_Sub_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Concat_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Concat_2_output_0_layer, 316,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_23_Concat_2_output_0_chain,
  NULL, &_model_23_Mul_2_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Div_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Add_2_output_0_output, &_model_23_Constant_14_output_0_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Div_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Div_1_output_0_layer, 315,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_Div_1_output_0_chain,
  NULL, &_model_23_Concat_2_output_0_layer, AI_STATIC, 
  .operation = ai_div_f32, 
  .buffer_operation = ai_div_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Add_2_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Sub_output_0_output, &_model_23_Add_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Add_2_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Add_2_output_0_layer, 313,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_Add_2_output_0_chain,
  NULL, &_model_23_Div_1_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Sub_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Add_1_output_0_output, &_model_23_Sub_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Sub_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Sub_1_output_0_layer, 314,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_Sub_1_output_0_chain,
  NULL, &_model_23_Add_2_output_0_layer, AI_STATIC, 
  .operation = ai_sub_f32, 
  .buffer_operation = ai_sub_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Sub_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Constant_12_output_0, &_model_23_Slice_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Sub_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Sub_output_0_layer, 311,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_Sub_output_0_chain,
  NULL, &_model_23_Sub_1_output_0_layer, AI_STATIC, 
  .operation = ai_sub_f32, 
  .buffer_operation = ai_sub_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Add_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_Constant_13_output_0, &_model_23_Slice_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Add_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Add_1_output_0_layer, 312,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_Add_1_output_0_chain,
  NULL, &_model_23_Sub_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)


AI_STATIC_CONST ai_u8 _model_23_Slice_output_0_axes_data[] = { 2 };
AI_ARRAY_OBJ_DECLARE(
    _model_23_Slice_output_0_axes, AI_ARRAY_FORMAT_U8,
    _model_23_Slice_output_0_axes_data, _model_23_Slice_output_0_axes_data, 1, AI_STATIC_CONST)

AI_STATIC_CONST ai_i16 _model_23_Slice_output_0_starts_data[] = { 0 };
AI_ARRAY_OBJ_DECLARE(
    _model_23_Slice_output_0_starts, AI_ARRAY_FORMAT_S16,
    _model_23_Slice_output_0_starts_data, _model_23_Slice_output_0_starts_data, 1, AI_STATIC_CONST)

AI_STATIC_CONST ai_i16 _model_23_Slice_output_0_ends_data[] = { 2 };
AI_ARRAY_OBJ_DECLARE(
    _model_23_Slice_output_0_ends, AI_ARRAY_FORMAT_S16,
    _model_23_Slice_output_0_ends_data, _model_23_Slice_output_0_ends_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Slice_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_1_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Slice_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Slice_output_0_layer, 308,
  SLICE_TYPE, 0x0, NULL,
  slice, forward_slice,
  &_model_23_Slice_output_0_chain,
  NULL, &_model_23_Add_1_output_0_layer, AI_STATIC, 
  .axes = &_model_23_Slice_output_0_axes, 
  .starts = &_model_23_Slice_output_0_starts, 
  .ends = &_model_23_Slice_output_0_ends, 
)


AI_STATIC_CONST ai_u8 _model_23_Slice_1_output_0_axes_data[] = { 2 };
AI_ARRAY_OBJ_DECLARE(
    _model_23_Slice_1_output_0_axes, AI_ARRAY_FORMAT_U8,
    _model_23_Slice_1_output_0_axes_data, _model_23_Slice_1_output_0_axes_data, 1, AI_STATIC_CONST)

AI_STATIC_CONST ai_i16 _model_23_Slice_1_output_0_starts_data[] = { 2 };
AI_ARRAY_OBJ_DECLARE(
    _model_23_Slice_1_output_0_starts, AI_ARRAY_FORMAT_S16,
    _model_23_Slice_1_output_0_starts_data, _model_23_Slice_1_output_0_starts_data, 1, AI_STATIC_CONST)

AI_STATIC_CONST ai_i16 _model_23_Slice_1_output_0_ends_data[] = { 4 };
AI_ARRAY_OBJ_DECLARE(
    _model_23_Slice_1_output_0_ends, AI_ARRAY_FORMAT_S16,
    _model_23_Slice_1_output_0_ends_data, _model_23_Slice_1_output_0_ends_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Slice_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_1_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Slice_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Slice_1_output_0_layer, 309,
  SLICE_TYPE, 0x0, NULL,
  slice, forward_slice,
  &_model_23_Slice_1_output_0_chain,
  NULL, &_model_23_Slice_output_0_layer, AI_STATIC, 
  .axes = &_model_23_Slice_1_output_0_axes, 
  .starts = &_model_23_Slice_1_output_0_starts, 
  .ends = &_model_23_Slice_1_output_0_ends, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chfirst_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_1_output_0_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_1_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chfirst_layer, 306,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_23_dfl_Reshape_1_output_0_to_chfirst_chain,
  NULL, &_model_23_Slice_1_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_WIDTH, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_1_output_0_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_dfl_Reshape_1_output_0_to_chlast_layer, 306,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_23_dfl_Reshape_1_output_0_to_chlast_chain,
  NULL, &_model_23_dfl_Reshape_1_output_0_to_chfirst_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Softmax_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_dfl_conv_Conv_output_0_weights, &_model_23_dfl_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_dfl_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_dfl_conv_Conv_output_0_layer, 304,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_dfl_conv_Conv_output_0_chain,
  NULL, &_model_23_dfl_Reshape_1_output_0_to_chlast_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_dfl_Softmax_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Transpose_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Softmax_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_dfl_Softmax_output_0_layer, 302,
  SM_TYPE, 0x0, NULL,
  sm, forward_sm,
  &_model_23_dfl_Softmax_output_0_chain,
  NULL, &_model_23_dfl_conv_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_dfl_Transpose_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_output_0_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Transpose_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_dfl_Transpose_output_0_layer, 300,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_23_dfl_Transpose_output_0_chain,
  NULL, &_model_23_dfl_Softmax_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_dfl_Reshape_output_0_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_dfl_Reshape_output_0_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_dfl_Reshape_output_0_to_chlast_layer, 298,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_23_dfl_Reshape_output_0_to_chlast_chain,
  NULL, &_model_23_dfl_Transpose_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_WIDTH, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_0_cv2_0_2_Conv_output_0_output0, &_model_23_cv2_1_cv2_1_2_Conv_output_0_output0, &_model_23_cv2_2_cv2_2_2_Conv_output_0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Concat_output_0_layer, 295,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_23_Concat_output_0_chain,
  NULL, &_model_23_dfl_Reshape_output_0_to_chlast_layer, AI_STATIC, 
  .axis = AI_SHAPE_HEIGHT, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_2_cv2_2_2_Conv_output_0_weights, &_model_23_cv2_2_cv2_2_2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_2_cv2_2_2_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_2_Conv_output_0_layer, 291,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_2_cv2_2_2_Conv_output_0_chain,
  NULL, &_model_23_Concat_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output, &_model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Mul_output_0_layer, 289,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv2_2_cv2_2_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_2_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_layer, 287,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_layer, 285,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output, &_model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Mul_output_0_layer, 283,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv2_2_cv2_2_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_layer, 281,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_layer, 279,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Concat_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Sigmoid_output_0_layer, 310,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_2_cv2_2_0_conv_Conv_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_Concat_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_0_cv3_0_2_Conv_output_0_output0, &_model_23_cv3_1_cv3_1_2_Conv_output_0_output0, &_model_23_cv3_2_cv3_2_2_Conv_output_0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_Concat_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_Concat_1_output_0_layer, 307,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_23_Concat_1_output_0_chain,
  NULL, &_model_23_Sigmoid_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_HEIGHT, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_2_cv3_2_2_Conv_output_0_weights, &_model_23_cv3_2_cv3_2_2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_2_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_2_Conv_output_0_layer, 303,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_2_cv3_2_2_Conv_output_0_chain,
  NULL, &_model_23_Concat_1_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_layer, 301,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_2_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_layer, 299,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_layer, 297,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_layer, 296,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_layer, 294,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_layer, 292,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 64, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_layer, 290,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_layer, 288,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_layer, 286,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_layer, 284,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_layer, 282,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_layer, 280,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 256, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_cv2_conv_Conv_output_0_output, &_model_22_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_cv2_act_Mul_output_0_layer, 278,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_cv2_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_cv2_act_Sigmoid_output_0_layer, 277,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_22_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_cv2_conv_Conv_output_0_weights, &_model_22_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_cv2_conv_Conv_output_0_layer, 276,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_cv2_conv_Conv_output_0_chain,
  NULL, &_model_22_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_Split_output_0_output0, &_model_22_Split_output_0_output1, &_model_22_m_0_cv3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_Concat_output_0_layer, 275,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_22_Concat_output_0_chain,
  NULL, &_model_22_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv3_conv_Conv_output_0_output, &_model_22_m_0_cv3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Mul_output_0_layer, 274,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_cv3_act_Mul_output_0_chain,
  NULL, &_model_22_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv3_act_Sigmoid_output_0_layer, 273,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_cv3_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_cv3_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_cv3_conv_Conv_output_0_weights, &_model_22_m_0_cv3_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv3_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv3_conv_Conv_output_0_layer, 272,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_cv3_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_cv3_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_1_Add_output_0_output, &_model_22_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_Concat_output_0_layer, 271,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_22_m_0_Concat_output_0_chain,
  NULL, &_model_22_m_0_cv3_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_0_Add_output_0_output, &_model_22_m_0_m_m_1_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_Add_output_0_layer, 270,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_m_m_1_Add_output_0_chain,
  NULL, &_model_22_m_0_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output, &_model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Mul_output_0_layer, 269,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_m_m_1_cv2_act_Mul_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_layer, 268,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_layer, 267,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output, &_model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Mul_output_0_layer, 266,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_m_m_1_cv1_act_Mul_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_layer, 265,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_layer, 264,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv1_act_Mul_output_0_output, &_model_22_m_0_m_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_Add_output_0_layer, 263,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_m_m_0_Add_output_0_chain,
  NULL, &_model_22_m_0_m_m_1_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output, &_model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Mul_output_0_layer, 262,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_m_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_layer, 261,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_layer, 260,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output, &_model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Mul_output_0_layer, 258,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_m_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_layer, 256,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_layer, 254,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv1_conv_Conv_output_0_output, &_model_22_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Mul_output_0_layer, 251,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_22_m_0_m_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv1_act_Sigmoid_output_0_layer, 248,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_cv1_conv_Conv_output_0_weights, &_model_22_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv1_conv_Conv_output_0_layer, 245,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv2_conv_Conv_output_0_output, &_model_22_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Mul_output_0_layer, 252,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_22_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv2_act_Sigmoid_output_0_layer, 249,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_22_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_m_0_cv2_conv_Conv_output_0_weights, &_model_22_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_m_0_cv2_conv_Conv_output_0_layer, 246,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_22_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_Split_output_0_output0, &_model_22_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_Split_output_0_layer, 242,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_22_Split_output_0_chain,
  NULL, &_model_22_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 100, 
  .outer_elems_stride = 1024, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_cv1_conv_Conv_output_0_output, &_model_22_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_cv1_act_Mul_output_0_layer, 239,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_22_cv1_act_Mul_output_0_chain,
  NULL, &_model_22_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_22_cv1_act_Sigmoid_output_0_layer, 236,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_22_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_22_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_21_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_22_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_22_cv1_conv_Conv_output_0_weights, &_model_22_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_22_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_22_cv1_conv_Conv_output_0_layer, 233,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_22_cv1_conv_Conv_output_0_chain,
  NULL, &_model_22_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_21_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_20_act_Mul_output_0_output, &_model_10_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_21_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_21_Concat_output_0_layer, 230,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_21_Concat_output_0_chain,
  NULL, &_model_22_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_20_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_20_conv_Conv_output_0_output, &_model_20_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_20_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_20_act_Mul_output_0_layer, 227,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_20_act_Mul_output_0_chain,
  NULL, &_model_21_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_20_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_20_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_20_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_20_act_Sigmoid_output_0_layer, 224,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_20_act_Sigmoid_output_0_chain,
  NULL, &_model_20_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_20_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_20_conv_Conv_output_0_weights, &_model_20_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_20_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_20_conv_Conv_output_0_layer, 221,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_20_conv_Conv_output_0_chain,
  NULL, &_model_20_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_1_cv2_1_2_Conv_output_0_weights, &_model_23_cv2_1_cv2_1_2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_1_cv2_1_2_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_2_Conv_output_0_layer, 240,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_1_cv2_1_2_Conv_output_0_chain,
  NULL, &_model_20_conv_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output, &_model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Mul_output_0_layer, 237,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv2_1_cv2_1_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_2_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_layer, 234,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_layer, 231,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output, &_model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Mul_output_0_layer, 228,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv2_1_cv2_1_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_layer, 225,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_layer, 222,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_1_cv3_1_2_Conv_output_0_weights, &_model_23_cv3_1_cv3_1_2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_2_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_2_Conv_output_0_layer, 257,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_1_cv3_1_2_Conv_output_0_chain,
  NULL, &_model_23_cv2_1_cv2_1_0_conv_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_layer, 255,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_2_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_layer, 253,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_layer, 250,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_layer, 247,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_layer, 244,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_layer, 241,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 64, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_layer, 238,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_layer, 235,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_layer, 232,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_layer, 229,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_layer, 226,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_layer, 223,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 128, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_cv2_conv_Conv_output_0_output, &_model_19_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_cv2_act_Mul_output_0_layer, 220,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_19_cv2_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_cv2_act_Sigmoid_output_0_layer, 219,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_19_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_19_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_19_cv2_conv_Conv_output_0_weights, &_model_19_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_19_cv2_conv_Conv_output_0_layer, 218,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_19_cv2_conv_Conv_output_0_chain,
  NULL, &_model_19_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_19_Split_output_0_output0, &_model_19_Split_output_0_output1, &_model_19_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_Concat_output_0_layer, 217,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_19_Concat_output_0_chain,
  NULL, &_model_19_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_Split_output_0_output1, &_model_19_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_Add_output_0_layer, 216,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_19_m_0_Add_output_0_chain,
  NULL, &_model_19_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_m_0_cv2_conv_Conv_output_0_output, &_model_19_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Mul_output_0_layer, 214,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_19_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_19_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_cv2_act_Sigmoid_output_0_layer, 212,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_19_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_19_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_19_m_0_cv2_conv_Conv_output_0_weights, &_model_19_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_cv2_conv_Conv_output_0_layer, 210,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_19_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_19_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_m_0_cv1_conv_Conv_output_0_output, &_model_19_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Mul_output_0_layer, 208,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_19_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_19_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_cv1_act_Sigmoid_output_0_layer, 206,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_19_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_19_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_19_m_0_cv1_conv_Conv_output_0_weights, &_model_19_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_19_m_0_cv1_conv_Conv_output_0_layer, 204,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_19_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_19_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_Split_output_0_output0, &_model_19_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_Split_output_0_layer, 201,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_19_Split_output_0_chain,
  NULL, &_model_19_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 400, 
  .outer_elems_stride = 512, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_cv1_conv_Conv_output_0_output, &_model_19_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_cv1_act_Mul_output_0_layer, 198,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_19_cv1_act_Mul_output_0_chain,
  NULL, &_model_19_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_19_cv1_act_Sigmoid_output_0_layer, 195,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_19_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_19_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_18_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_19_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_19_cv1_conv_Conv_output_0_weights, &_model_19_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_19_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_19_cv1_conv_Conv_output_0_layer, 192,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_19_cv1_conv_Conv_output_0_chain,
  NULL, &_model_19_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_18_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_17_act_Mul_output_0_output, &_model_13_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_18_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_18_Concat_output_0_layer, 189,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_18_Concat_output_0_chain,
  NULL, &_model_19_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_17_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_17_conv_Conv_output_0_output, &_model_17_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_17_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_17_act_Mul_output_0_layer, 186,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_17_act_Mul_output_0_chain,
  NULL, &_model_18_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_17_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_17_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_17_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_17_act_Sigmoid_output_0_layer, 183,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_17_act_Sigmoid_output_0_chain,
  NULL, &_model_17_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_17_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_17_conv_Conv_output_0_weights, &_model_17_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_17_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_17_conv_Conv_output_0_layer, 180,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_17_conv_Conv_output_0_chain,
  NULL, &_model_17_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_0_cv2_0_2_Conv_output_0_weights, &_model_23_cv2_0_cv2_0_2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_0_cv2_0_2_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_2_Conv_output_0_layer, 199,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_0_cv2_0_2_Conv_output_0_chain,
  NULL, &_model_17_conv_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output, &_model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Mul_output_0_layer, 196,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv2_0_cv2_0_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_2_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_layer, 193,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_layer, 190,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output, &_model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Mul_output_0_layer, 187,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv2_0_cv2_0_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_layer, 184,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_layer, 181,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_2_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_0_cv3_0_2_Conv_output_0_weights, &_model_23_cv3_0_cv3_0_2_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_2_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_2_Conv_output_0_layer, 213,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_0_cv3_0_2_Conv_output_0_chain,
  NULL, &_model_23_cv2_0_cv2_0_0_conv_Conv_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_layer, 211,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_2_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_layer, 209,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_layer, 207,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_layer, 205,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_layer, 203,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_layer, 200,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 64, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_layer, 197,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_layer, 194,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_layer, 191,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_layer, 188,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_layer, 185,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_layer, 182,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 64, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_cv2_conv_Conv_output_0_output, &_model_16_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_cv2_act_Mul_output_0_layer, 179,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_16_cv2_act_Mul_output_0_chain,
  NULL, &_model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_cv2_act_Sigmoid_output_0_layer, 178,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_16_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_16_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_16_cv2_conv_Conv_output_0_weights, &_model_16_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_16_cv2_conv_Conv_output_0_layer, 177,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_16_cv2_conv_Conv_output_0_chain,
  NULL, &_model_16_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_16_Split_output_0_output0, &_model_16_Split_output_0_output1, &_model_16_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_Concat_output_0_layer, 176,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_16_Concat_output_0_chain,
  NULL, &_model_16_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_Split_output_0_output1, &_model_16_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_Add_output_0_layer, 175,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_16_m_0_Add_output_0_chain,
  NULL, &_model_16_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_m_0_cv2_conv_Conv_output_0_output, &_model_16_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Mul_output_0_layer, 174,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_16_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_16_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_cv2_act_Sigmoid_output_0_layer, 173,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_16_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_16_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_16_m_0_cv2_conv_Conv_output_0_weights, &_model_16_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_cv2_conv_Conv_output_0_layer, 172,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_16_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_16_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_m_0_cv1_conv_Conv_output_0_output, &_model_16_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Mul_output_0_layer, 171,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_16_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_16_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_cv1_act_Sigmoid_output_0_layer, 170,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_16_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_16_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_16_m_0_cv1_conv_Conv_output_0_weights, &_model_16_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_16_m_0_cv1_conv_Conv_output_0_layer, 169,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_16_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_16_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_Split_output_0_output0, &_model_16_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_Split_output_0_layer, 168,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_16_Split_output_0_chain,
  NULL, &_model_16_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 1600, 
  .outer_elems_stride = 256, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_cv1_conv_Conv_output_0_output, &_model_16_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_cv1_act_Mul_output_0_layer, 167,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_16_cv1_act_Mul_output_0_chain,
  NULL, &_model_16_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_16_cv1_act_Sigmoid_output_0_layer, 166,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_16_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_16_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_15_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_16_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_16_cv1_conv_Conv_output_0_weights, &_model_16_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_16_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_16_cv1_conv_Conv_output_0_layer, 165,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_16_cv1_conv_Conv_output_0_chain,
  NULL, &_model_16_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_15_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_14_Resize_output_0_output, &_model_4_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_15_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_15_Concat_output_0_layer, 164,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_15_Concat_output_0_chain,
  NULL, &_model_16_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)


AI_STATIC_CONST ai_float _model_14_Resize_output_0_scales_data[] = { 2.0, 2.0, 1.0, 1.0 };
AI_ARRAY_OBJ_DECLARE(
    _model_14_Resize_output_0_scales, AI_ARRAY_FORMAT_FLOAT,
    _model_14_Resize_output_0_scales_data, _model_14_Resize_output_0_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_14_Resize_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_14_Resize_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_14_Resize_output_0_layer, 163,
  UPSAMPLE_TYPE, 0x0, NULL,
  upsample, forward_upsample_nearest,
  &_model_14_Resize_output_0_chain,
  NULL, &_model_15_Concat_output_0_layer, AI_STATIC, 
  .scales = &_model_14_Resize_output_0_scales, 
  .center = false, 
  .mode = AI_UPSAMPLE_NEAREST, 
  .nearest_mode = AI_ROUND_FLOOR, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_cv2_conv_Conv_output_0_output, &_model_13_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_cv2_act_Mul_output_0_layer, 162,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_13_cv2_act_Mul_output_0_chain,
  NULL, &_model_14_Resize_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_cv2_act_Sigmoid_output_0_layer, 161,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_13_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_13_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_13_cv2_conv_Conv_output_0_weights, &_model_13_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_13_cv2_conv_Conv_output_0_layer, 160,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_13_cv2_conv_Conv_output_0_chain,
  NULL, &_model_13_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_13_Split_output_0_output0, &_model_13_Split_output_0_output1, &_model_13_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_Concat_output_0_layer, 159,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_13_Concat_output_0_chain,
  NULL, &_model_13_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_Split_output_0_output1, &_model_13_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_Add_output_0_layer, 158,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_13_m_0_Add_output_0_chain,
  NULL, &_model_13_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_m_0_cv2_conv_Conv_output_0_output, &_model_13_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Mul_output_0_layer, 157,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_13_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_13_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_cv2_act_Sigmoid_output_0_layer, 156,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_13_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_13_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_13_m_0_cv2_conv_Conv_output_0_weights, &_model_13_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_cv2_conv_Conv_output_0_layer, 155,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_13_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_13_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_m_0_cv1_conv_Conv_output_0_output, &_model_13_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Mul_output_0_layer, 154,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_13_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_13_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_cv1_act_Sigmoid_output_0_layer, 153,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_13_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_13_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_13_m_0_cv1_conv_Conv_output_0_weights, &_model_13_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_13_m_0_cv1_conv_Conv_output_0_layer, 152,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_13_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_13_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_Split_output_0_output0, &_model_13_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_Split_output_0_layer, 151,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_13_Split_output_0_chain,
  NULL, &_model_13_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 400, 
  .outer_elems_stride = 512, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_cv1_conv_Conv_output_0_output, &_model_13_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_cv1_act_Mul_output_0_layer, 150,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_13_cv1_act_Mul_output_0_chain,
  NULL, &_model_13_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_13_cv1_act_Sigmoid_output_0_layer, 149,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_13_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_13_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_12_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_13_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_13_cv1_conv_Conv_output_0_weights, &_model_13_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_13_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_13_cv1_conv_Conv_output_0_layer, 148,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_13_cv1_conv_Conv_output_0_chain,
  NULL, &_model_13_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_12_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_11_Resize_output_0_output, &_model_6_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_12_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_12_Concat_output_0_layer, 147,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_12_Concat_output_0_chain,
  NULL, &_model_13_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)


AI_STATIC_CONST ai_float _model_11_Resize_output_0_scales_data[] = { 2.0, 2.0, 1.0, 1.0 };
AI_ARRAY_OBJ_DECLARE(
    _model_11_Resize_output_0_scales, AI_ARRAY_FORMAT_FLOAT,
    _model_11_Resize_output_0_scales_data, _model_11_Resize_output_0_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_11_Resize_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_11_Resize_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_11_Resize_output_0_layer, 146,
  UPSAMPLE_TYPE, 0x0, NULL,
  upsample, forward_upsample_nearest,
  &_model_11_Resize_output_0_chain,
  NULL, &_model_12_Concat_output_0_layer, AI_STATIC, 
  .scales = &_model_11_Resize_output_0_scales, 
  .center = false, 
  .mode = AI_UPSAMPLE_NEAREST, 
  .nearest_mode = AI_ROUND_FLOOR, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_cv2_conv_Conv_output_0_output, &_model_10_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_cv2_act_Mul_output_0_layer, 145,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_10_cv2_act_Mul_output_0_chain,
  NULL, &_model_11_Resize_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_cv2_act_Sigmoid_output_0_layer, 144,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_10_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_10_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_cv2_conv_Conv_output_0_weights, &_model_10_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_10_cv2_conv_Conv_output_0_layer, 143,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_10_cv2_conv_Conv_output_0_chain,
  NULL, &_model_10_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_Split_output_0_output0, &_model_10_m_m_0_Add_1_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_Concat_output_0_layer, 142,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_10_Concat_output_0_chain,
  NULL, &_model_10_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_Add_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_Add_output_0_output, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_Add_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_Add_1_output_0_layer, 141,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_10_m_m_0_Add_1_output_0_chain,
  NULL, &_model_10_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_layer, 140,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_chain,
  NULL, &_model_10_m_m_0_Add_1_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output, &_model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_layer, 139,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_chain,
  NULL, &_model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_layer, 138,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_chain,
  NULL, &_model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_layer, 137,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_chain,
  NULL, &_model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_Split_output_0_output1, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_Add_output_0_layer, 136,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_10_m_m_0_Add_output_0_chain,
  NULL, &_model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_weights, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_proj_conv_Conv_output_0_layer, 135,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_10_m_m_0_attn_proj_conv_Conv_output_0_chain,
  NULL, &_model_10_m_m_0_Add_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Add_output_0_layer, 134,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_10_m_m_0_attn_Add_output_0_chain,
  NULL, &_model_10_m_m_0_attn_proj_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_weights, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_pe_conv_Conv_output_0_layer, 128,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_dw_if32of32wf32,
  &_model_10_m_m_0_attn_pe_conv_Conv_output_0_chain,
  NULL, &_model_10_m_m_0_attn_Add_output_0_layer, AI_STATIC, 
  .groups = 128, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_layer, 126,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_chain,
  NULL, &_model_10_m_m_0_attn_pe_conv_Conv_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Split_output_0_output2),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_layer, 126,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_chain,
  NULL, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_MatMul_1_output_0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_layer, 133,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_chain,
  NULL, &_model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output, &transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output, &_model_10_m_m_0_attn_MatMul_1_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_MatMul_1_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_1_output_0_layer, 132,
  MATMUL_TYPE, 0x0, NULL,
  matmul, forward_matmul,
  &_model_10_m_m_0_attn_MatMul_1_output_0_chain,
  NULL, &_model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_layer, AI_STATIC, 
  .alpha = 1.0, 
  .beta = 1.0, 
  .tA = 0, 
  .tB = 0, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Softmax_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_layer, 132,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_chain,
  NULL, &_model_10_m_m_0_attn_MatMul_1_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_WIDTH, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Softmax_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Softmax_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Softmax_output_0_layer, 130,
  SM_TYPE, 0x0, NULL,
  sm, forward_sm,
  &_model_10_m_m_0_attn_Softmax_output_0_chain,
  NULL, &transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_layer, AI_STATIC, 
  .nl_params = NULL, 
  .axis = AI_SHAPE_WIDTH, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_attn_Mul_output_0_scale, &_model_10_m_m_0_attn_Mul_output_0_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Mul_output_0_layer, 129,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &_model_10_m_m_0_attn_Mul_output_0_chain,
  NULL, &_model_10_m_m_0_attn_Softmax_output_0_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_layer, 127,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_chain,
  NULL, &_model_10_m_m_0_attn_Mul_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output, &transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output, &_model_10_m_m_0_attn_MatMul_output_0_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_MatMul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_MatMul_output_0_layer, 127,
  MATMUL_TYPE, 0x0, NULL,
  matmul, forward_matmul,
  &_model_10_m_m_0_attn_MatMul_output_0_chain,
  NULL, &transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_layer, AI_STATIC, 
  .alpha = 1.0, 
  .beta = 1.0, 
  .tA = 0, 
  .tB = 0, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_layer, 127,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_chain,
  NULL, &_model_10_m_m_0_attn_MatMul_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Split_output_0_output2),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_layer, 132,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_chain,
  NULL, &transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Split_output_0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_layer, 127,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_chain,
  NULL, &transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_WIDTH, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_m_m_0_attn_Split_output_0_output0, &_model_10_m_m_0_attn_Split_output_0_output1, &_model_10_m_m_0_attn_Split_output_0_output2),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Split_output_0_layer, 124,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_10_m_m_0_attn_Split_output_0_chain,
  NULL, &transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_layer, AI_STATIC, 
  .outer_elems = 1, 
  .outer_elems_stride = 102400, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chfirst_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_output_0_to_chlast_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chfirst_layer, 123,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_10_m_m_0_attn_Reshape_output_0_to_chfirst_chain,
  NULL, &_model_10_m_m_0_attn_Split_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chlast_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_Reshape_output_0_to_chlast_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_Reshape_output_0_to_chlast_layer, 123,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &_model_10_m_m_0_attn_Reshape_output_0_to_chlast_chain,
  NULL, &_model_10_m_m_0_attn_Reshape_output_0_to_chfirst_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_10_m_m_0_attn_qkv_conv_Conv_output_0_layer, 122,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_chain,
  NULL, &_model_10_m_m_0_attn_Reshape_output_0_to_chlast_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_Split_output_0_output0, &_model_10_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_Split_output_0_layer, 121,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_10_Split_output_0_chain,
  NULL, &_model_10_m_m_0_attn_qkv_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 100, 
  .outer_elems_stride = 1024, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_cv1_conv_Conv_output_0_output, &_model_10_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_cv1_act_Mul_output_0_layer, 120,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_10_cv1_act_Mul_output_0_chain,
  NULL, &_model_10_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_10_cv1_act_Sigmoid_output_0_layer, 119,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_10_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_10_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_10_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_10_cv1_conv_Conv_output_0_weights, &_model_10_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_10_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_10_cv1_conv_Conv_output_0_layer, 118,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_10_cv1_conv_Conv_output_0_chain,
  NULL, &_model_10_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_9_cv2_conv_Conv_output_0_output, &_model_9_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_9_cv2_act_Mul_output_0_layer, 117,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_9_cv2_act_Mul_output_0_chain,
  NULL, &_model_10_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_9_cv2_act_Sigmoid_output_0_layer, 116,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_9_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_9_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_9_cv2_conv_Conv_output_0_weights, &_model_9_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_9_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_9_cv2_conv_Conv_output_0_layer, 115,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_9_cv2_conv_Conv_output_0_chain,
  NULL, &_model_9_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 4, &_model_9_cv1_conv_Conv_output_0_output, &_model_9_m_MaxPool_output_0_output, &_model_9_m_1_MaxPool_output_0_output, &_model_9_m_2_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_9_Concat_output_0_layer, 114,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_9_Concat_output_0_chain,
  NULL, &_model_9_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_m_2_MaxPool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_m_1_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_m_2_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_9_m_2_MaxPool_output_0_layer, 113,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &_model_9_m_2_MaxPool_output_0_chain,
  NULL, &_model_9_Concat_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(5, 5), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_m_1_MaxPool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_m_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_m_1_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_9_m_1_MaxPool_output_0_layer, 112,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &_model_9_m_1_MaxPool_output_0_chain,
  NULL, &_model_9_m_2_MaxPool_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(5, 5), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_m_MaxPool_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_m_MaxPool_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_9_m_MaxPool_output_0_layer, 111,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp,
  &_model_9_m_MaxPool_output_0_chain,
  NULL, &_model_9_m_1_MaxPool_output_0_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(5, 5), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_9_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_9_cv1_conv_Conv_output_0_weights, &_model_9_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_9_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_9_cv1_conv_Conv_output_0_layer, 110,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_9_cv1_conv_Conv_output_0_chain,
  NULL, &_model_9_m_MaxPool_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_cv2_conv_Conv_output_0_output, &_model_8_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_cv2_act_Mul_output_0_layer, 109,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_cv2_act_Mul_output_0_chain,
  NULL, &_model_9_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_cv2_act_Sigmoid_output_0_layer, 108,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_8_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_cv2_conv_Conv_output_0_weights, &_model_8_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_cv2_conv_Conv_output_0_layer, 107,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_cv2_conv_Conv_output_0_chain,
  NULL, &_model_8_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_Split_output_0_output0, &_model_8_Split_output_0_output1, &_model_8_m_0_cv3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_Concat_output_0_layer, 106,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_8_Concat_output_0_chain,
  NULL, &_model_8_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv3_conv_Conv_output_0_output, &_model_8_m_0_cv3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Mul_output_0_layer, 105,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_cv3_act_Mul_output_0_chain,
  NULL, &_model_8_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv3_act_Sigmoid_output_0_layer, 104,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_cv3_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_cv3_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_cv3_conv_Conv_output_0_weights, &_model_8_m_0_cv3_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv3_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv3_conv_Conv_output_0_layer, 103,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_cv3_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_cv3_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_1_Add_output_0_output, &_model_8_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_Concat_output_0_layer, 102,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_8_m_0_Concat_output_0_chain,
  NULL, &_model_8_m_0_cv3_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_0_Add_output_0_output, &_model_8_m_0_m_m_1_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_Add_output_0_layer, 101,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_m_m_1_Add_output_0_chain,
  NULL, &_model_8_m_0_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output, &_model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Mul_output_0_layer, 100,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_m_m_1_cv2_act_Mul_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_layer, 99,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_layer, 98,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output, &_model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Mul_output_0_layer, 97,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_m_m_1_cv1_act_Mul_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_layer, 96,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_layer, 95,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv1_act_Mul_output_0_output, &_model_8_m_0_m_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_Add_output_0_layer, 94,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_m_m_0_Add_output_0_chain,
  NULL, &_model_8_m_0_m_m_1_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output, &_model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Mul_output_0_layer, 93,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_m_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_layer, 92,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_layer, 91,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output, &_model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Mul_output_0_layer, 90,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_m_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_layer, 89,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_layer, 88,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv1_conv_Conv_output_0_output, &_model_8_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Mul_output_0_layer, 86,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_8_m_0_m_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv1_act_Sigmoid_output_0_layer, 84,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_cv1_conv_Conv_output_0_weights, &_model_8_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv1_conv_Conv_output_0_layer, 82,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv2_conv_Conv_output_0_output, &_model_8_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Mul_output_0_layer, 87,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_8_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv2_act_Sigmoid_output_0_layer, 85,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_8_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_m_0_cv2_conv_Conv_output_0_weights, &_model_8_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_m_0_cv2_conv_Conv_output_0_layer, 83,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_8_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_Split_output_0_output0, &_model_8_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_Split_output_0_layer, 81,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_8_Split_output_0_chain,
  NULL, &_model_8_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 100, 
  .outer_elems_stride = 1024, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_cv1_conv_Conv_output_0_output, &_model_8_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_cv1_act_Mul_output_0_layer, 80,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_8_cv1_act_Mul_output_0_chain,
  NULL, &_model_8_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_8_cv1_act_Sigmoid_output_0_layer, 79,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_8_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_8_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_7_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_8_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_8_cv1_conv_Conv_output_0_weights, &_model_8_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_8_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_8_cv1_conv_Conv_output_0_layer, 78,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_8_cv1_conv_Conv_output_0_chain,
  NULL, &_model_8_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_7_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_7_conv_Conv_output_0_output, &_model_7_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_7_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_7_act_Mul_output_0_layer, 77,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_7_act_Mul_output_0_chain,
  NULL, &_model_8_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_7_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_7_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_7_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_7_act_Sigmoid_output_0_layer, 76,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_7_act_Sigmoid_output_0_chain,
  NULL, &_model_7_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_7_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_7_conv_Conv_output_0_weights, &_model_7_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_7_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_7_conv_Conv_output_0_layer, 75,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_7_conv_Conv_output_0_chain,
  NULL, &_model_7_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_cv2_conv_Conv_output_0_output, &_model_6_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_cv2_act_Mul_output_0_layer, 74,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_cv2_act_Mul_output_0_chain,
  NULL, &_model_7_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_cv2_act_Sigmoid_output_0_layer, 73,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_6_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_cv2_conv_Conv_output_0_weights, &_model_6_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_cv2_conv_Conv_output_0_layer, 72,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_cv2_conv_Conv_output_0_chain,
  NULL, &_model_6_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_Split_output_0_output0, &_model_6_Split_output_0_output1, &_model_6_m_0_cv3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_Concat_output_0_layer, 71,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_6_Concat_output_0_chain,
  NULL, &_model_6_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv3_conv_Conv_output_0_output, &_model_6_m_0_cv3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Mul_output_0_layer, 70,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_cv3_act_Mul_output_0_chain,
  NULL, &_model_6_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv3_act_Sigmoid_output_0_layer, 69,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_cv3_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_cv3_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_cv3_conv_Conv_output_0_weights, &_model_6_m_0_cv3_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv3_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv3_conv_Conv_output_0_layer, 68,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_cv3_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_cv3_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_1_Add_output_0_output, &_model_6_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_Concat_output_0_layer, 67,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_6_m_0_Concat_output_0_chain,
  NULL, &_model_6_m_0_cv3_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_0_Add_output_0_output, &_model_6_m_0_m_m_1_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_Add_output_0_layer, 66,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_m_m_1_Add_output_0_chain,
  NULL, &_model_6_m_0_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output, &_model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Mul_output_0_layer, 65,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_m_m_1_cv2_act_Mul_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_layer, 64,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_layer, 63,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output, &_model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Mul_output_0_layer, 62,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_m_m_1_cv1_act_Mul_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_layer, 61,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_layer, 60,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv1_act_Mul_output_0_output, &_model_6_m_0_m_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_Add_output_0_layer, 59,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_m_m_0_Add_output_0_chain,
  NULL, &_model_6_m_0_m_m_1_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output, &_model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Mul_output_0_layer, 58,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_m_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_layer, 57,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_layer, 56,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output, &_model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Mul_output_0_layer, 55,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_m_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_layer, 54,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_layer, 53,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv1_conv_Conv_output_0_output, &_model_6_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Mul_output_0_layer, 51,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_6_m_0_m_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv1_act_Sigmoid_output_0_layer, 49,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_cv1_conv_Conv_output_0_weights, &_model_6_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv1_conv_Conv_output_0_layer, 47,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv2_conv_Conv_output_0_output, &_model_6_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Mul_output_0_layer, 52,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_6_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv2_act_Sigmoid_output_0_layer, 50,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_6_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_m_0_cv2_conv_Conv_output_0_weights, &_model_6_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_m_0_cv2_conv_Conv_output_0_layer, 48,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_6_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_Split_output_0_output0, &_model_6_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_Split_output_0_layer, 46,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_6_Split_output_0_chain,
  NULL, &_model_6_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 400, 
  .outer_elems_stride = 512, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_cv1_conv_Conv_output_0_output, &_model_6_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_cv1_act_Mul_output_0_layer, 45,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_6_cv1_act_Mul_output_0_chain,
  NULL, &_model_6_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_6_cv1_act_Sigmoid_output_0_layer, 44,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_6_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_6_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_5_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_6_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_6_cv1_conv_Conv_output_0_weights, &_model_6_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_6_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_6_cv1_conv_Conv_output_0_layer, 43,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_6_cv1_conv_Conv_output_0_chain,
  NULL, &_model_6_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_5_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_5_conv_Conv_output_0_output, &_model_5_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_5_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_5_act_Mul_output_0_layer, 42,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_5_act_Mul_output_0_chain,
  NULL, &_model_6_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_5_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_5_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_5_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_5_act_Sigmoid_output_0_layer, 41,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_5_act_Sigmoid_output_0_chain,
  NULL, &_model_5_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_5_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_5_conv_Conv_output_0_weights, &_model_5_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_5_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_5_conv_Conv_output_0_layer, 40,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_5_conv_Conv_output_0_chain,
  NULL, &_model_5_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_cv2_conv_Conv_output_0_output, &_model_4_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_cv2_act_Mul_output_0_layer, 39,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_4_cv2_act_Mul_output_0_chain,
  NULL, &_model_5_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_cv2_act_Sigmoid_output_0_layer, 38,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_4_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_4_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_4_cv2_conv_Conv_output_0_weights, &_model_4_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_4_cv2_conv_Conv_output_0_layer, 37,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_4_cv2_conv_Conv_output_0_chain,
  NULL, &_model_4_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_4_Split_output_0_output0, &_model_4_Split_output_0_output1, &_model_4_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_Concat_output_0_layer, 36,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_4_Concat_output_0_chain,
  NULL, &_model_4_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_Split_output_0_output1, &_model_4_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_Add_output_0_layer, 35,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_4_m_0_Add_output_0_chain,
  NULL, &_model_4_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_m_0_cv2_conv_Conv_output_0_output, &_model_4_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Mul_output_0_layer, 34,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_4_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_4_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_cv2_act_Sigmoid_output_0_layer, 33,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_4_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_4_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_4_m_0_cv2_conv_Conv_output_0_weights, &_model_4_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_cv2_conv_Conv_output_0_layer, 32,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_4_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_4_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_m_0_cv1_conv_Conv_output_0_output, &_model_4_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Mul_output_0_layer, 31,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_4_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_4_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_cv1_act_Sigmoid_output_0_layer, 30,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_4_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_4_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_4_m_0_cv1_conv_Conv_output_0_weights, &_model_4_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_4_m_0_cv1_conv_Conv_output_0_layer, 29,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_4_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_4_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_Split_output_0_output0, &_model_4_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_Split_output_0_layer, 28,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_4_Split_output_0_chain,
  NULL, &_model_4_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 1600, 
  .outer_elems_stride = 256, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_cv1_conv_Conv_output_0_output, &_model_4_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_cv1_act_Mul_output_0_layer, 27,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_4_cv1_act_Mul_output_0_chain,
  NULL, &_model_4_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_4_cv1_act_Sigmoid_output_0_layer, 26,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_4_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_4_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_4_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_4_cv1_conv_Conv_output_0_weights, &_model_4_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_4_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_4_cv1_conv_Conv_output_0_layer, 25,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_4_cv1_conv_Conv_output_0_chain,
  NULL, &_model_4_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_3_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_3_conv_Conv_output_0_output, &_model_3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_3_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_3_act_Mul_output_0_layer, 24,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_3_act_Mul_output_0_chain,
  NULL, &_model_4_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_3_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_3_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_3_act_Sigmoid_output_0_layer, 23,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_3_act_Sigmoid_output_0_chain,
  NULL, &_model_3_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_3_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_3_conv_Conv_output_0_weights, &_model_3_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_3_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_3_conv_Conv_output_0_layer, 22,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_3_conv_Conv_output_0_chain,
  NULL, &_model_3_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_cv2_conv_Conv_output_0_output, &_model_2_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_cv2_act_Mul_output_0_layer, 21,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_2_cv2_act_Mul_output_0_chain,
  NULL, &_model_3_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_cv2_act_Sigmoid_output_0_layer, 20,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_2_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_2_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_2_cv2_conv_Conv_output_0_weights, &_model_2_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_2_cv2_conv_Conv_output_0_layer, 19,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_2_cv2_conv_Conv_output_0_chain,
  NULL, &_model_2_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_Concat_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_2_Split_output_0_output0, &_model_2_Split_output_0_output1, &_model_2_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_Concat_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_Concat_output_0_layer, 18,
  CONCAT_TYPE, 0x0, NULL,
  concat, forward_concat,
  &_model_2_Concat_output_0_chain,
  NULL, &_model_2_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_Add_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_Split_output_0_output1, &_model_2_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_Add_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_Add_output_0_layer, 17,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_2_m_0_Add_output_0_chain,
  NULL, &_model_2_Concat_output_0_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_m_0_cv2_conv_Conv_output_0_output, &_model_2_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv2_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Mul_output_0_layer, 16,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_2_m_0_cv2_act_Mul_output_0_chain,
  NULL, &_model_2_m_0_Add_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv2_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_cv2_act_Sigmoid_output_0_layer, 15,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_2_m_0_cv2_act_Sigmoid_output_0_chain,
  NULL, &_model_2_m_0_cv2_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv2_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_2_m_0_cv2_conv_Conv_output_0_weights, &_model_2_m_0_cv2_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_m_0_cv2_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_cv2_conv_Conv_output_0_layer, 14,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_2_m_0_cv2_conv_Conv_output_0_chain,
  NULL, &_model_2_m_0_cv2_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_m_0_cv1_conv_Conv_output_0_output, &_model_2_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Mul_output_0_layer, 13,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_2_m_0_cv1_act_Mul_output_0_chain,
  NULL, &_model_2_m_0_cv2_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_cv1_act_Sigmoid_output_0_layer, 12,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_2_m_0_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_2_m_0_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_m_0_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_2_m_0_cv1_conv_Conv_output_0_weights, &_model_2_m_0_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_m_0_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_2_m_0_cv1_conv_Conv_output_0_layer, 11,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_2_m_0_cv1_conv_Conv_output_0_chain,
  NULL, &_model_2_m_0_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_Split_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_Split_output_0_output0, &_model_2_Split_output_0_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_Split_output_0_num_or_size_splits),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_Split_output_0_layer, 10,
  SPLIT_TYPE, 0x0, NULL,
  split, forward_split,
  &_model_2_Split_output_0_chain,
  NULL, &_model_2_m_0_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .outer_elems = 6400, 
  .outer_elems_stride = 128, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_cv1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_cv1_conv_Conv_output_0_output, &_model_2_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_cv1_act_Mul_output_0_layer, 9,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_2_cv1_act_Mul_output_0_chain,
  NULL, &_model_2_Split_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_cv1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_2_cv1_act_Sigmoid_output_0_layer, 8,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_2_cv1_act_Sigmoid_output_0_chain,
  NULL, &_model_2_cv1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_2_cv1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_2_cv1_conv_Conv_output_0_weights, &_model_2_cv1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_2_cv1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_2_cv1_conv_Conv_output_0_layer, 7,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_2_cv1_conv_Conv_output_0_chain,
  NULL, &_model_2_cv1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_1_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_1_conv_Conv_output_0_output, &_model_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_1_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_1_act_Mul_output_0_layer, 6,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_1_act_Mul_output_0_chain,
  NULL, &_model_2_cv1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_1_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_1_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_1_act_Sigmoid_output_0_layer, 5,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_1_act_Sigmoid_output_0_chain,
  NULL, &_model_1_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_1_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_1_conv_Conv_output_0_weights, &_model_1_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_1_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_1_conv_Conv_output_0_layer, 4,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_1_conv_Conv_output_0_chain,
  NULL, &_model_1_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_0_act_Mul_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_0_conv_Conv_output_0_output, &_model_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_0_act_Mul_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_0_act_Mul_output_0_layer, 3,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &_model_0_act_Mul_output_0_chain,
  NULL, &_model_1_conv_Conv_output_0_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_0_act_Sigmoid_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_0_act_Sigmoid_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _model_0_act_Sigmoid_output_0_layer, 2,
  NL_TYPE, 0x0, NULL,
  nl, forward_sigmoid,
  &_model_0_act_Sigmoid_output_0_chain,
  NULL, &_model_0_act_Mul_output_0_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &images_Transpose_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_model_0_conv_Conv_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_model_0_conv_Conv_output_0_weights, &_model_0_conv_Conv_output_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_model_0_conv_Conv_output_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  _model_0_conv_Conv_output_0_layer, 1,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &_model_0_conv_Conv_output_0_chain,
  NULL, &_model_0_act_Sigmoid_output_0_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  images_Transpose_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &images_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &images_Transpose_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  images_Transpose_layer, 2,
  TRANSPOSE_TYPE, 0x0, NULL,
  transpose, forward_transpose,
  &images_Transpose_chain,
  NULL, &_model_0_conv_Conv_output_0_layer, AI_STATIC, 
  .out_mapping = AI_SHAPE_INIT(6, AI_SHAPE_IN_CHANNEL, AI_SHAPE_HEIGHT, AI_SHAPE_CHANNEL, AI_SHAPE_WIDTH, AI_SHAPE_DEPTH, AI_SHAPE_EXTENSION), 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 10392528, 1, 1),
    10392528, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 6144000, 1, 1),
    6144000, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &images_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &output0_Transpose_0_output),
  &images_Transpose_layer, 0x840d0f3c, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 194,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 10392528, 1, 1),
      10392528, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 6144000, 1, 1),
      6144000, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &images_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &output0_Transpose_0_output),
  &images_Transpose_layer, 0x840d0f3c, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    images_output_array.data = AI_PTR(g_network_activations_map[0] + 835968);
    images_output_array.data_start = AI_PTR(g_network_activations_map[0] + 835968);
    images_Transpose_output_array.data = AI_PTR(g_network_activations_map[0] + 2064768);
    images_Transpose_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2064768);
    _model_0_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 835968);
    _model_0_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 835968);
    _model_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _model_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _model_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 576);
    _model_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 576);
    _model_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819776);
    _model_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819776);
    _model_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638976);
    _model_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638976);
    _model_2_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_2_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _model_2_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 128);
    _model_2_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 128);
    _model_2_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819328);
    _model_2_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819328);
    _model_2_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638528);
    _model_2_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638528);
    _model_2_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    _model_2_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    _model_2_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 409600);
    _model_2_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 409600);
    _model_2_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819776);
    _model_2_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819776);
    _model_2_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1024576);
    _model_2_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1024576);
    _model_2_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1229376);
    _model_2_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1229376);
    _model_2_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819488);
    _model_2_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819488);
    _model_2_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1229088);
    _model_2_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1229088);
    _model_2_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638688);
    _model_2_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638688);
    _model_2_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_2_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_2_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2457600);
    _model_2_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2457600);
    _model_2_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_2_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2457600);
    _model_2_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2457600);
    _model_3_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_3_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_3_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 821504);
    _model_3_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 821504);
    _model_3_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1231104);
    _model_3_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1231104);
    _model_3_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1640704);
    _model_3_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1640704);
    _model_4_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_4_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_4_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 819456);
    _model_4_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 819456);
    _model_4_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1229056);
    _model_4_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1229056);
    _model_4_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_4_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_4_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 819200);
    _model_4_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 819200);
    _model_4_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 1024000);
    _model_4_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 1024000);
    _model_4_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1229952);
    _model_4_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1229952);
    _model_4_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1332352);
    _model_4_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1332352);
    _model_4_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434752);
    _model_4_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434752);
    _model_4_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1229376);
    _model_4_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1229376);
    _model_4_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434176);
    _model_4_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434176);
    _model_4_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638976);
    _model_4_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638976);
    _model_4_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_4_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_4_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_4_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_4_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_4_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867200);
    _model_4_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867200);
    _model_5_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_5_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_5_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1233408);
    _model_5_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1233408);
    _model_5_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1438208);
    _model_5_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1438208);
    _model_5_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1643008);
    _model_5_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1643008);
    _model_6_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_6_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_6_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1229312);
    _model_6_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1229312);
    _model_6_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434112);
    _model_6_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434112);
    _model_6_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_6_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_6_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_6_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1228800);
    _model_6_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 1331200);
    _model_6_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 1331200);
    _model_6_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1433856);
    _model_6_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1433856);
    _model_6_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1485056);
    _model_6_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1485056);
    _model_6_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536256);
    _model_6_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536256);
    _model_6_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1433856);
    _model_6_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1433856);
    _model_6_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1485056);
    _model_6_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1485056);
    _model_6_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434752);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434752);
    _model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1689856);
    _model_6_m_0_m_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1689856);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434752);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434752);
    _model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1689856);
    _model_6_m_0_m_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1689856);
    _model_6_m_0_m_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_m_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_1_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_1_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_m_m_1_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_m_m_1_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_6_m_0_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587456);
    _model_6_m_0_cv3_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_cv3_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_m_0_cv3_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1433856);
    _model_6_m_0_cv3_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1433856);
    _model_6_m_0_cv3_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536256);
    _model_6_m_0_cv3_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536256);
    _model_6_m_0_cv3_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_m_0_cv3_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638656);
    _model_6_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1741056);
    _model_6_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1741056);
    _model_6_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_6_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434368);
    _model_6_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434368);
    _model_6_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1639168);
    _model_6_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1639168);
    _model_6_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1843968);
    _model_6_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1843968);
    _model_7_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_7_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_7_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1438208);
    _model_7_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1438208);
    _model_7_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1540608);
    _model_7_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1540608);
    _model_7_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1643008);
    _model_7_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1643008);
    _model_8_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_8_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_8_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1434624);
    _model_8_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1434624);
    _model_8_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1537024);
    _model_8_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1537024);
    _model_8_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1639424);
    _model_8_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1639424);
    _model_8_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_8_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1433600);
    _model_8_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_8_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 1484800);
    _model_8_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536512);
    _model_8_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536512);
    _model_8_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1562112);
    _model_8_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1562112);
    _model_8_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587712);
    _model_8_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587712);
    _model_8_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536512);
    _model_8_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536512);
    _model_8_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1562112);
    _model_8_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1562112);
    _model_8_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1538304);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1538304);
    _model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1664512);
    _model_8_m_0_m_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1664512);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1538304);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1538304);
    _model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1664512);
    _model_8_m_0_m_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1664512);
    _model_8_m_0_m_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_m_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_1_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_1_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_m_m_1_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_m_m_1_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1561600);
    _model_8_m_0_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1613312);
    _model_8_m_0_cv3_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_cv3_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_m_0_cv3_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536512);
    _model_8_m_0_cv3_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536512);
    _model_8_m_0_cv3_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587712);
    _model_8_m_0_cv3_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587712);
    _model_8_m_0_cv3_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_m_0_cv3_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_8_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1690112);
    _model_8_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1690112);
    _model_8_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_8_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1537536);
    _model_8_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1537536);
    _model_8_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1639936);
    _model_8_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1639936);
    _model_8_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_8_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_9_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_9_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_9_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1537024);
    _model_9_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1537024);
    _model_9_m_MaxPool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1588224);
    _model_9_m_MaxPool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1588224);
    _model_9_m_1_MaxPool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1639424);
    _model_9_m_1_MaxPool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1639424);
    _model_9_m_2_MaxPool_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1690624);
    _model_9_m_2_MaxPool_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1690624);
    _model_9_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_9_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_9_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_9_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_9_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1538048);
    _model_9_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1538048);
    _model_9_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1640448);
    _model_9_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1640448);
    _model_9_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_9_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1537024);
    _model_10_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1537024);
    _model_10_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1639424);
    _model_10_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1639424);
    _model_10_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_10_m_m_0_attn_Reshape_output_0_to_chlast_output_array.data = AI_PTR(g_network_activations_map[0] + 1741312);
    _model_10_m_m_0_attn_Reshape_output_0_to_chlast_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1741312);
    _model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_Reshape_output_0_to_chfirst_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_10_m_m_0_attn_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_10_m_m_0_attn_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 1766400);
    _model_10_m_m_0_attn_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 1766400);
    _model_10_m_m_0_attn_Split_output_0_output2_array.data = AI_PTR(g_network_activations_map[0] + 1792000);
    _model_10_m_m_0_attn_Split_output_0_output2_array.data_start = AI_PTR(g_network_activations_map[0] + 1792000);
    transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    transpose_a_model_10_m_m_0_attn_MatMul_output_0_out_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array.data = AI_PTR(g_network_activations_map[0] + 1664000);
    transpose_a_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1664000);
    transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output_array.data = AI_PTR(g_network_activations_map[0] + 1715200);
    transpose_b_model_10_m_m_0_attn_MatMul_output_0_out_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1715200);
    _model_10_m_m_0_attn_MatMul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_m_m_0_attn_MatMul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output_array.data = AI_PTR(g_network_activations_map[0] + 2128768);
    transpose_out_model_10_m_m_0_attn_MatMul_output_0_out_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2128768);
    _model_10_m_m_0_attn_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_m_m_0_attn_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_m_m_0_attn_Softmax_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2128768);
    _model_10_m_m_0_attn_Softmax_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2128768);
    transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    transpose_b_model_10_m_m_0_attn_MatMul_1_output_0_out_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_m_m_0_attn_MatMul_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1715200);
    _model_10_m_m_0_attn_MatMul_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1715200);
    _model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_Reshape_1_output_0_to_chfirst_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output_array.data = AI_PTR(g_network_activations_map[0] + 1689600);
    _model_10_m_m_0_attn_Reshape_2_output_0_to_chlast_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1689600);
    _model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_10_m_m_0_attn_Reshape_2_output_0_to_chfirst_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1689600);
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1689600);
    _model_10_m_m_0_attn_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_10_m_m_0_attn_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1638912);
    _model_10_m_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1690112);
    _model_10_m_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1690112);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587712);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587712);
    _model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1741312);
    _model_10_m_m_0_ffn_ffn_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1741312);
    _model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_m_m_0_ffn_ffn_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1588224);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1588224);
    _model_10_m_m_0_Add_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1741312);
    _model_10_m_m_0_Add_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1741312);
    _model_10_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1587200);
    _model_10_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1689600);
    _model_10_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1689600);
    _model_10_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_10_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_10_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048768);
    _model_11_Resize_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_11_Resize_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_12_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3686400);
    _model_12_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3686400);
    _model_13_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_13_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_13_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1537536);
    _model_13_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1537536);
    _model_13_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1742336);
    _model_13_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1742336);
    _model_13_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_13_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1536000);
    _model_13_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_13_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 1638400);
    _model_13_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1743104);
    _model_13_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1743104);
    _model_13_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1794304);
    _model_13_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1794304);
    _model_13_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1845504);
    _model_13_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1845504);
    _model_13_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1741952);
    _model_13_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1741952);
    _model_13_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1844352);
    _model_13_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1844352);
    _model_13_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_13_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1741568);
    _model_13_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1741568);
    _model_13_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_13_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2355968);
    _model_13_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2355968);
    _model_14_Resize_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3686400);
    _model_14_Resize_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3686400);
    _model_15_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 4505600);
    _model_15_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4505600);
    _model_16_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_16_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_16_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2970368);
    _model_16_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2970368);
    _model_16_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_16_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_16_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_16_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1740800);
    _model_16_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_16_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 2151168);
    _model_16_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2663168);
    _model_16_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2663168);
    _model_16_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2765568);
    _model_16_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2765568);
    _model_16_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2970368);
    _model_16_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2970368);
    _model_16_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2765568);
    _model_16_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2765568);
    _model_16_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_16_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_16_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_16_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_16_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2970368);
    _model_16_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2970368);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2560768);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv2_0_cv2_0_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv2_0_cv2_0_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 4199168);
    _model_23_cv2_0_cv2_0_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4199168);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv2_0_cv2_0_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv2_0_cv2_0_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 4199168);
    _model_23_cv2_0_cv2_0_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4199168);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_17_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_17_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_17_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_17_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_17_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_17_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_17_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_17_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_18_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_18_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_19_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_19_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_19_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2355968);
    _model_19_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2355968);
    _model_19_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_19_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_19_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_19_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 1945600);
    _model_19_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 2355968);
    _model_19_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 2355968);
    _model_19_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2460672);
    _model_19_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2460672);
    _model_19_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2791168);
    _model_19_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2791168);
    _model_19_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_19_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_19_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_19_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_19_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_19_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3047168);
    _model_19_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3047168);
    _model_19_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_19_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_19_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3149568);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3149568);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_1_cv2_1_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_1_cv2_1_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv2_1_cv2_1_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_1_cv2_1_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_1_cv2_1_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv2_1_cv2_1_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2739968);
    _model_20_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_20_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_20_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2507776);
    _model_20_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2507776);
    _model_20_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_20_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_20_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_20_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_21_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_21_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_22_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_22_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_22_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_22_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_Split_output_0_output0_array.data = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_22_Split_output_0_output0_array.data_start = AI_PTR(g_network_activations_map[0] + 2048000);
    _model_22_Split_output_0_output1_array.data = AI_PTR(g_network_activations_map[0] + 2099200);
    _model_22_Split_output_0_output1_array.data_start = AI_PTR(g_network_activations_map[0] + 2099200);
    _model_22_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_22_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_22_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_22_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_22_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2505472);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2505472);
    _model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_0_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_0_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_0_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2505472);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2505472);
    _model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_0_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_0_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_0_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_0_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_m_m_0_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_m_m_1_cv1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_m_m_1_cv1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_1_cv1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2531072);
    _model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_m_m_1_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_m_m_1_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_1_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_m_m_1_Add_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_m_m_1_Add_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_22_m_0_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_22_m_0_cv3_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_22_m_0_cv3_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_22_m_0_cv3_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_cv3_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_m_0_cv3_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_m_0_cv3_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_m_0_cv3_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_m_0_cv3_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2893568);
    _model_22_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_cv2_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_cv2_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_22_cv2_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_cv2_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_22_cv2_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_cv2_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_22_cv2_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3047168);
    _model_22_cv2_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3047168);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2944768);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3149568);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3149568);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2504192);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2504192);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2529792);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2529792);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2528768);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2503168);
    _model_23_Concat_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_Concat_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3789568);
    _model_23_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2702784);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2702784);
    _model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_2_cv2_2_0_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_2_cv2_2_0_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_23_cv2_2_cv2_2_0_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2695872);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2695872);
    _model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_2_cv2_2_1_act_Sigmoid_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_cv2_2_cv2_2_1_act_Mul_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_23_cv2_2_cv2_2_1_act_Mul_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2867968);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Concat_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_Concat_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2842368);
    _model_23_dfl_Reshape_output_0_to_chlast_output_array.data = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_dfl_Reshape_output_0_to_chlast_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3379968);
    _model_23_dfl_Transpose_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_dfl_Transpose_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_dfl_Softmax_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 3231168);
    _model_23_dfl_Softmax_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3231168);
    _model_23_dfl_conv_Conv_output_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_dfl_conv_Conv_output_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2150400);
    _model_23_dfl_conv_Conv_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_dfl_conv_Conv_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_dfl_Reshape_1_output_0_to_chlast_output_array.data = AI_PTR(g_network_activations_map[0] + 2727168);
    _model_23_dfl_Reshape_1_output_0_to_chlast_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2727168);
    _model_23_dfl_Reshape_1_output_0_to_chfirst_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_dfl_Reshape_1_output_0_to_chfirst_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Slice_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2727168);
    _model_23_Slice_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2727168);
    _model_23_Slice_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2743968);
    _model_23_Slice_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2743968);
    _model_23_Add_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Add_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Sub_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2710368);
    _model_23_Sub_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2710368);
    _model_23_Sub_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2727168);
    _model_23_Sub_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2727168);
    _model_23_Add_2_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2743968);
    _model_23_Add_2_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2743968);
    _model_23_Div_1_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Div_1_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Concat_2_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2743968);
    _model_23_Concat_2_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2743968);
    _model_23_Mul_2_output_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2693568);
    _model_23_Mul_2_output_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2693568);
    output0_output_array.data = AI_PTR(g_network_activations_map[0] + 2727168);
    output0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2727168);
    output0_Transpose_0_output_array.data = AI_PTR(g_network_activations_map[0] + 2458368);
    output0_Transpose_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2458368);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 194, params)) {
    /* Updating weights (byte) offsets */
    
    _model_10_m_m_0_attn_MatMul_1_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_MatMul_1_output_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 0);
    _model_10_m_m_0_attn_MatMul_1_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    _model_10_m_m_0_attn_MatMul_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_MatMul_output_0_bias_array.data = AI_PTR(g_network_weights_map[1] + 0);
    _model_10_m_m_0_attn_MatMul_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[1] + 0);
    _model_23_Constant_14_output_0_3D_array.format |= AI_FMT_FLAG_CONST;
    _model_23_Constant_14_output_0_3D_array.data = AI_PTR(g_network_weights_map[2] + 0);
    _model_23_Constant_14_output_0_3D_array.data_start = AI_PTR(g_network_weights_map[2] + 0);
    _model_23_Constant_15_output_0_3D_array.format |= AI_FMT_FLAG_CONST;
    _model_23_Constant_15_output_0_3D_array.data = AI_PTR(g_network_weights_map[3] + 0);
    _model_23_Constant_15_output_0_3D_array.data_start = AI_PTR(g_network_weights_map[3] + 0);
    _model_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[4] + 0);
    _model_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[4] + 0);
    _model_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[5] + 0);
    _model_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[5] + 0);
    _model_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[6] + 0);
    _model_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[6] + 0);
    _model_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[7] + 0);
    _model_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[7] + 0);
    _model_2_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_2_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[8] + 0);
    _model_2_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[8] + 0);
    _model_2_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_2_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[9] + 0);
    _model_2_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[9] + 0);
    _model_2_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_2_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[10] + 0);
    _model_2_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[10] + 0);
    _model_2_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_2_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[11] + 0);
    _model_2_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[11] + 0);
    _model_2_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_2_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[12] + 0);
    _model_2_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[12] + 0);
    _model_2_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_2_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[13] + 0);
    _model_2_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[13] + 0);
    _model_2_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_2_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[14] + 0);
    _model_2_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[14] + 0);
    _model_2_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_2_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[15] + 0);
    _model_2_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[15] + 0);
    _model_2_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_2_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[16] + 0);
    _model_2_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[16] + 0);
    _model_3_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_3_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[17] + 0);
    _model_3_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[17] + 0);
    _model_3_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_3_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[18] + 0);
    _model_3_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[18] + 0);
    _model_4_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_4_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[19] + 0);
    _model_4_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[19] + 0);
    _model_4_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_4_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[20] + 0);
    _model_4_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[20] + 0);
    _model_4_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_4_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[21] + 0);
    _model_4_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[21] + 0);
    _model_4_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_4_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[22] + 0);
    _model_4_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[22] + 0);
    _model_4_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_4_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[23] + 0);
    _model_4_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[23] + 0);
    _model_4_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_4_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[24] + 0);
    _model_4_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[24] + 0);
    _model_4_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_4_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[25] + 0);
    _model_4_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[25] + 0);
    _model_4_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_4_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[26] + 0);
    _model_4_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[26] + 0);
    _model_4_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_4_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[27] + 0);
    _model_4_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[27] + 0);
    _model_5_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_5_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[28] + 0);
    _model_5_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[28] + 0);
    _model_5_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_5_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[29] + 0);
    _model_5_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[29] + 0);
    _model_6_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[30] + 0);
    _model_6_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[30] + 0);
    _model_6_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[31] + 0);
    _model_6_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[31] + 0);
    _model_6_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_6_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[32] + 0);
    _model_6_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[32] + 0);
    _model_6_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[33] + 0);
    _model_6_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[33] + 0);
    _model_6_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[34] + 0);
    _model_6_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[34] + 0);
    _model_6_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[35] + 0);
    _model_6_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[35] + 0);
    _model_6_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[36] + 0);
    _model_6_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[36] + 0);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[37] + 0);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[37] + 0);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[38] + 0);
    _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[38] + 0);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[39] + 0);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[39] + 0);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[40] + 0);
    _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[40] + 0);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[41] + 0);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[41] + 0);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[42] + 0);
    _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[42] + 0);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[43] + 0);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[43] + 0);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[44] + 0);
    _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[44] + 0);
    _model_6_m_0_cv3_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_cv3_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[45] + 0);
    _model_6_m_0_cv3_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[45] + 0);
    _model_6_m_0_cv3_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_m_0_cv3_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[46] + 0);
    _model_6_m_0_cv3_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[46] + 0);
    _model_6_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_6_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[47] + 0);
    _model_6_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[47] + 0);
    _model_6_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_6_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[48] + 0);
    _model_6_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[48] + 0);
    _model_7_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_7_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[49] + 0);
    _model_7_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[49] + 0);
    _model_7_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_7_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[50] + 0);
    _model_7_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[50] + 0);
    _model_8_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[51] + 0);
    _model_8_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[51] + 0);
    _model_8_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[52] + 0);
    _model_8_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[52] + 0);
    _model_8_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_8_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[53] + 0);
    _model_8_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[53] + 0);
    _model_8_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[54] + 0);
    _model_8_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[54] + 0);
    _model_8_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[55] + 0);
    _model_8_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[55] + 0);
    _model_8_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[56] + 0);
    _model_8_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[56] + 0);
    _model_8_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[57] + 0);
    _model_8_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[57] + 0);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[58] + 0);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[58] + 0);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[59] + 0);
    _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[59] + 0);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[60] + 0);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[60] + 0);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[61] + 0);
    _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[61] + 0);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[62] + 0);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[62] + 0);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[63] + 0);
    _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[63] + 0);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[64] + 0);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[64] + 0);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[65] + 0);
    _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[65] + 0);
    _model_8_m_0_cv3_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_cv3_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[66] + 0);
    _model_8_m_0_cv3_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[66] + 0);
    _model_8_m_0_cv3_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_m_0_cv3_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[67] + 0);
    _model_8_m_0_cv3_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[67] + 0);
    _model_8_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_8_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[68] + 0);
    _model_8_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[68] + 0);
    _model_8_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_8_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[69] + 0);
    _model_8_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[69] + 0);
    _model_9_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_9_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[70] + 0);
    _model_9_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[70] + 0);
    _model_9_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_9_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[71] + 0);
    _model_9_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[71] + 0);
    _model_9_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_9_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[72] + 0);
    _model_9_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[72] + 0);
    _model_9_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_9_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[73] + 0);
    _model_9_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[73] + 0);
    _model_10_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[74] + 0);
    _model_10_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[74] + 0);
    _model_10_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[75] + 0);
    _model_10_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[75] + 0);
    _model_10_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_10_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[76] + 0);
    _model_10_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[76] + 0);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[77] + 0);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[77] + 0);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[78] + 0);
    _model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[78] + 0);
    _model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[79] + 0);
    _model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[79] + 0);
    _model_10_m_m_0_attn_Mul_output_0_scale_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_Mul_output_0_scale_array.data = AI_PTR(g_network_weights_map[80] + 0);
    _model_10_m_m_0_attn_Mul_output_0_scale_array.data_start = AI_PTR(g_network_weights_map[80] + 0);
    _model_10_m_m_0_attn_Mul_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_Mul_output_0_bias_array.data = AI_PTR(g_network_weights_map[81] + 0);
    _model_10_m_m_0_attn_Mul_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[81] + 0);
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[82] + 0);
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[82] + 0);
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[83] + 0);
    _model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[83] + 0);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[84] + 0);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[84] + 0);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[85] + 0);
    _model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[85] + 0);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[86] + 0);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[86] + 0);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[87] + 0);
    _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[87] + 0);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[88] + 0);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[88] + 0);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[89] + 0);
    _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[89] + 0);
    _model_10_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_10_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[90] + 0);
    _model_10_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[90] + 0);
    _model_10_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_10_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[91] + 0);
    _model_10_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[91] + 0);
    _model_13_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_13_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[92] + 0);
    _model_13_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[92] + 0);
    _model_13_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_13_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[93] + 0);
    _model_13_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[93] + 0);
    _model_13_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_13_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[94] + 0);
    _model_13_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[94] + 0);
    _model_13_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_13_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[95] + 0);
    _model_13_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[95] + 0);
    _model_13_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_13_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[96] + 0);
    _model_13_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[96] + 0);
    _model_13_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_13_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[97] + 0);
    _model_13_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[97] + 0);
    _model_13_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_13_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[98] + 0);
    _model_13_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[98] + 0);
    _model_13_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_13_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[99] + 0);
    _model_13_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[99] + 0);
    _model_13_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_13_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[100] + 0);
    _model_13_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[100] + 0);
    _model_16_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_16_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[101] + 0);
    _model_16_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[101] + 0);
    _model_16_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_16_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[102] + 0);
    _model_16_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[102] + 0);
    _model_16_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_16_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[103] + 0);
    _model_16_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[103] + 0);
    _model_16_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_16_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[104] + 0);
    _model_16_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[104] + 0);
    _model_16_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_16_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[105] + 0);
    _model_16_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[105] + 0);
    _model_16_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_16_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[106] + 0);
    _model_16_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[106] + 0);
    _model_16_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_16_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[107] + 0);
    _model_16_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[107] + 0);
    _model_16_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_16_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[108] + 0);
    _model_16_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[108] + 0);
    _model_16_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_16_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[109] + 0);
    _model_16_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[109] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[110] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[110] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[111] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[111] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[112] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[112] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[113] + 0);
    _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[113] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[114] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[114] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[115] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[115] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[116] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[116] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[117] + 0);
    _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[117] + 0);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[118] + 0);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[118] + 0);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[119] + 0);
    _model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[119] + 0);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[120] + 0);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[120] + 0);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[121] + 0);
    _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[121] + 0);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[122] + 0);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[122] + 0);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[123] + 0);
    _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[123] + 0);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[124] + 0);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[124] + 0);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[125] + 0);
    _model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[125] + 0);
    _model_17_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_17_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[126] + 0);
    _model_17_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[126] + 0);
    _model_17_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_17_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[127] + 0);
    _model_17_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[127] + 0);
    _model_19_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_19_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[128] + 0);
    _model_19_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[128] + 0);
    _model_19_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_19_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[129] + 0);
    _model_19_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[129] + 0);
    _model_19_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_19_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[130] + 0);
    _model_19_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[130] + 0);
    _model_19_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_19_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[131] + 0);
    _model_19_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[131] + 0);
    _model_19_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_19_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[132] + 0);
    _model_19_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[132] + 0);
    _model_19_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_19_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[133] + 0);
    _model_19_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[133] + 0);
    _model_19_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_19_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[134] + 0);
    _model_19_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[134] + 0);
    _model_19_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_19_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[135] + 0);
    _model_19_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[135] + 0);
    _model_19_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_19_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[136] + 0);
    _model_19_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[136] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[137] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[137] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[138] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[138] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[139] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[139] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[140] + 0);
    _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[140] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[141] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[141] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[142] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[142] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[143] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[143] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[144] + 0);
    _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[144] + 0);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[145] + 0);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[145] + 0);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[146] + 0);
    _model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[146] + 0);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[147] + 0);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[147] + 0);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[148] + 0);
    _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[148] + 0);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[149] + 0);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[149] + 0);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[150] + 0);
    _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[150] + 0);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[151] + 0);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[151] + 0);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[152] + 0);
    _model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[152] + 0);
    _model_20_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_20_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[153] + 0);
    _model_20_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[153] + 0);
    _model_20_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_20_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[154] + 0);
    _model_20_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[154] + 0);
    _model_22_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[155] + 0);
    _model_22_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[155] + 0);
    _model_22_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[156] + 0);
    _model_22_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[156] + 0);
    _model_22_Split_output_0_num_or_size_splits_array.format |= AI_FMT_FLAG_CONST;
    _model_22_Split_output_0_num_or_size_splits_array.data = AI_PTR(g_network_weights_map[157] + 0);
    _model_22_Split_output_0_num_or_size_splits_array.data_start = AI_PTR(g_network_weights_map[157] + 0);
    _model_22_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[158] + 0);
    _model_22_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[158] + 0);
    _model_22_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[159] + 0);
    _model_22_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[159] + 0);
    _model_22_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[160] + 0);
    _model_22_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[160] + 0);
    _model_22_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[161] + 0);
    _model_22_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[161] + 0);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[162] + 0);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[162] + 0);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[163] + 0);
    _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[163] + 0);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[164] + 0);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[164] + 0);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[165] + 0);
    _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[165] + 0);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[166] + 0);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[166] + 0);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[167] + 0);
    _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[167] + 0);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[168] + 0);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[168] + 0);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[169] + 0);
    _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[169] + 0);
    _model_22_m_0_cv3_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_cv3_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[170] + 0);
    _model_22_m_0_cv3_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[170] + 0);
    _model_22_m_0_cv3_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_m_0_cv3_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[171] + 0);
    _model_22_m_0_cv3_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[171] + 0);
    _model_22_cv2_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_22_cv2_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[172] + 0);
    _model_22_cv2_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[172] + 0);
    _model_22_cv2_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_22_cv2_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[173] + 0);
    _model_22_cv2_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[173] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[174] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[174] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[175] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[175] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[176] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[176] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[177] + 0);
    _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[177] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[178] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[178] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[179] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[179] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[180] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[180] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[181] + 0);
    _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[181] + 0);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[182] + 0);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[182] + 0);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[183] + 0);
    _model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[183] + 0);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[184] + 0);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[184] + 0);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[185] + 0);
    _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[185] + 0);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[186] + 0);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[186] + 0);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[187] + 0);
    _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[187] + 0);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[188] + 0);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[188] + 0);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[189] + 0);
    _model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[189] + 0);
    _model_23_dfl_conv_Conv_output_0_weights_array.format |= AI_FMT_FLAG_CONST;
    _model_23_dfl_conv_Conv_output_0_weights_array.data = AI_PTR(g_network_weights_map[190] + 0);
    _model_23_dfl_conv_Conv_output_0_weights_array.data_start = AI_PTR(g_network_weights_map[190] + 0);
    _model_23_dfl_conv_Conv_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _model_23_dfl_conv_Conv_output_0_bias_array.data = AI_PTR(g_network_weights_map[191] + 0);
    _model_23_dfl_conv_Conv_output_0_bias_array.data_start = AI_PTR(g_network_weights_map[191] + 0);
    _model_23_Constant_13_output_0_array.format |= AI_FMT_FLAG_CONST;
    _model_23_Constant_13_output_0_array.data = AI_PTR(g_network_weights_map[192] + 0);
    _model_23_Constant_13_output_0_array.data_start = AI_PTR(g_network_weights_map[192] + 0);
    _model_23_Constant_12_output_0_array.format |= AI_FMT_FLAG_CONST;
    _model_23_Constant_12_output_0_array.data = AI_PTR(g_network_weights_map[193] + 0);
    _model_23_Constant_12_output_0_array.data_start = AI_PTR(g_network_weights_map[193] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1132046565,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x840d0f3c,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1132046565,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x840d0f3c,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_data_params_get(&params) != true) {
    err = ai_network_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_init(*network, &params) != true) {
    err = ai_network_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

