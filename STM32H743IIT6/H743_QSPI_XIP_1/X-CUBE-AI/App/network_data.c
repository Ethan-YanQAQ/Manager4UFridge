/**
  ******************************************************************************
  * @file    network_data.c
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
#include "network_data.h"
#include "ai_platform_interface.h"

AI_API_DECLARE_BEGIN
ai_buffer g_network_data_map_activations[AI_NETWORK_DATA_ACTIVATIONS_COUNT] = {
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 6144000, 1, 1),
    6144000, NULL, NULL),    /* heap_overlay_pool */
  };
ai_buffer g_network_data_map_weights[AI_NETWORK_DATA_WEIGHTS_COUNT] = {
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_10_m_m_0_attn_MatMul_1_output_0_bias_array_u64),   /* _model_10_m_m_0_attn_MatMul_1_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_10_m_m_0_attn_MatMul_output_0_bias_array_u64),   /* _model_10_m_m_0_attn_MatMul_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_23_Constant_14_output_0_3D_array_u64),   /* _model_23_Constant_14_output_0_3D_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8400, 1, 1),
    8400, NULL, s_network__model_23_Constant_15_output_0_3D_array_u64),   /* _model_23_Constant_15_output_0_3D_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1728, 1, 1),
    1728, NULL, s_network__model_0_conv_Conv_output_0_weights_array_u64),   /* _model_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 64, 1, 1),
    64, NULL, s_network__model_0_conv_Conv_output_0_bias_array_u64),   /* _model_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 18432, 1, 1),
    18432, NULL, s_network__model_1_conv_Conv_output_0_weights_array_u64),   /* _model_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_1_conv_Conv_output_0_bias_array_u64),   /* _model_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4096, 1, 1),
    4096, NULL, s_network__model_2_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_2_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_2_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_2_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_2_Split_output_0_num_or_size_splits_array_u64),   /* _model_2_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4608, 1, 1),
    4608, NULL, s_network__model_2_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_2_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32, 1, 1),
    32, NULL, s_network__model_2_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_2_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4608, 1, 1),
    4608, NULL, s_network__model_2_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_2_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 64, 1, 1),
    64, NULL, s_network__model_2_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_2_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 12288, 1, 1),
    12288, NULL, s_network__model_2_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_2_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_2_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_2_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_3_conv_Conv_output_0_weights_array_u64),   /* _model_3_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_3_conv_Conv_output_0_bias_array_u64),   /* _model_3_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_4_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_4_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_4_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_4_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_4_Split_output_0_num_or_size_splits_array_u64),   /* _model_4_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 18432, 1, 1),
    18432, NULL, s_network__model_4_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_4_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 64, 1, 1),
    64, NULL, s_network__model_4_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_4_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 18432, 1, 1),
    18432, NULL, s_network__model_4_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_4_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_4_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_4_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 49152, 1, 1),
    49152, NULL, s_network__model_4_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_4_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_4_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_4_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 589824, 1, 1),
    589824, NULL, s_network__model_5_conv_Conv_output_0_weights_array_u64),   /* _model_5_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_5_conv_Conv_output_0_bias_array_u64),   /* _model_5_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 65536, 1, 1),
    65536, NULL, s_network__model_6_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_6_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_6_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_6_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_6_Split_output_0_num_or_size_splits_array_u64),   /* _model_6_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8192, 1, 1),
    8192, NULL, s_network__model_6_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_6_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8192, 1, 1),
    8192, NULL, s_network__model_6_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_6_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36864, 1, 1),
    36864, NULL, s_network__model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36864, 1, 1),
    36864, NULL, s_network__model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36864, 1, 1),
    36864, NULL, s_network__model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36864, 1, 1),
    36864, NULL, s_network__model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_6_m_0_cv3_conv_Conv_output_0_weights_array_u64),   /* _model_6_m_0_cv3_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_6_m_0_cv3_conv_Conv_output_0_bias_array_u64),   /* _model_6_m_0_cv3_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 98304, 1, 1),
    98304, NULL, s_network__model_6_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_6_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_6_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_6_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1179648, 1, 1),
    1179648, NULL, s_network__model_7_conv_Conv_output_0_weights_array_u64),   /* _model_7_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_7_conv_Conv_output_0_bias_array_u64),   /* _model_7_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 262144, 1, 1),
    262144, NULL, s_network__model_8_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_8_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_8_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_8_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_8_Split_output_0_num_or_size_splits_array_u64),   /* _model_8_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32768, 1, 1),
    32768, NULL, s_network__model_8_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_8_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32768, 1, 1),
    32768, NULL, s_network__model_8_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_8_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 65536, 1, 1),
    65536, NULL, s_network__model_8_m_0_cv3_conv_Conv_output_0_weights_array_u64),   /* _model_8_m_0_cv3_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_8_m_0_cv3_conv_Conv_output_0_bias_array_u64),   /* _model_8_m_0_cv3_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 393216, 1, 1),
    393216, NULL, s_network__model_8_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_8_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_8_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_8_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 131072, 1, 1),
    131072, NULL, s_network__model_9_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_9_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_9_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_9_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 524288, 1, 1),
    524288, NULL, s_network__model_9_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_9_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_9_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_9_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 262144, 1, 1),
    262144, NULL, s_network__model_10_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_10_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_10_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_10_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_10_Split_output_0_num_or_size_splits_array_u64),   /* _model_10_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 131072, 1, 1),
    131072, NULL, s_network__model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array_u64),   /* _model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array_u64),   /* _model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 12, 1, 1),
    12, NULL, s_network__model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array_u64),   /* _model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8, 1, 1),
    8, NULL, s_network__model_10_m_m_0_attn_Mul_output_0_scale_array_u64),   /* _model_10_m_m_0_attn_Mul_output_0_scale_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 8, 1, 1),
    8, NULL, s_network__model_10_m_m_0_attn_Mul_output_0_bias_array_u64),   /* _model_10_m_m_0_attn_Mul_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4608, 1, 1),
    4608, NULL, s_network__model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array_u64),   /* _model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array_u64),   /* _model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 65536, 1, 1),
    65536, NULL, s_network__model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array_u64),   /* _model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array_u64),   /* _model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 131072, 1, 1),
    131072, NULL, s_network__model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array_u64),   /* _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array_u64),   /* _model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 131072, 1, 1),
    131072, NULL, s_network__model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array_u64),   /* _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array_u64),   /* _model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 262144, 1, 1),
    262144, NULL, s_network__model_10_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_10_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_10_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_10_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 196608, 1, 1),
    196608, NULL, s_network__model_13_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_13_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_13_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_13_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_13_Split_output_0_num_or_size_splits_array_u64),   /* _model_13_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 73728, 1, 1),
    73728, NULL, s_network__model_13_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_13_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_13_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_13_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 73728, 1, 1),
    73728, NULL, s_network__model_13_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_13_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_13_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_13_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 98304, 1, 1),
    98304, NULL, s_network__model_13_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_13_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_13_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_13_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 65536, 1, 1),
    65536, NULL, s_network__model_16_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_16_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_16_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_16_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_16_Split_output_0_num_or_size_splits_array_u64),   /* _model_16_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 18432, 1, 1),
    18432, NULL, s_network__model_16_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_16_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 64, 1, 1),
    64, NULL, s_network__model_16_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_16_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 18432, 1, 1),
    18432, NULL, s_network__model_16_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_16_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_16_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_16_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 24576, 1, 1),
    24576, NULL, s_network__model_16_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_16_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_16_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_16_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 2304, 1, 1),
    2304, NULL, s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 2304, 1, 1),
    2304, NULL, s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 7168, 1, 1),
    7168, NULL, s_network__model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array_u64),   /* _model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 112, 1, 1),
    112, NULL, s_network__model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array_u64),   /* _model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array_u64),   /* _model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array_u64),   /* _model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_17_conv_Conv_output_0_weights_array_u64),   /* _model_17_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_17_conv_Conv_output_0_bias_array_u64),   /* _model_17_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 98304, 1, 1),
    98304, NULL, s_network__model_19_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_19_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_19_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_19_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_19_Split_output_0_num_or_size_splits_array_u64),   /* _model_19_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 73728, 1, 1),
    73728, NULL, s_network__model_19_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_19_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 128, 1, 1),
    128, NULL, s_network__model_19_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_19_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 73728, 1, 1),
    73728, NULL, s_network__model_19_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_19_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_19_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_19_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 98304, 1, 1),
    98304, NULL, s_network__model_19_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_19_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_19_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_19_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4608, 1, 1),
    4608, NULL, s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32768, 1, 1),
    32768, NULL, s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 2304, 1, 1),
    2304, NULL, s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 7168, 1, 1),
    7168, NULL, s_network__model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array_u64),   /* _model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 112, 1, 1),
    112, NULL, s_network__model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array_u64),   /* _model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 294912, 1, 1),
    294912, NULL, s_network__model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array_u64),   /* _model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array_u64),   /* _model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 589824, 1, 1),
    589824, NULL, s_network__model_20_conv_Conv_output_0_weights_array_u64),   /* _model_20_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_20_conv_Conv_output_0_bias_array_u64),   /* _model_20_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 393216, 1, 1),
    393216, NULL, s_network__model_22_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_22_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_22_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_22_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_22_Split_output_0_num_or_size_splits_array_u64),   /* _model_22_Split_output_0_num_or_size_splits_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32768, 1, 1),
    32768, NULL, s_network__model_22_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_22_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 32768, 1, 1),
    32768, NULL, s_network__model_22_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_22_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 65536, 1, 1),
    65536, NULL, s_network__model_22_m_0_cv3_conv_Conv_output_0_weights_array_u64),   /* _model_22_m_0_cv3_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 512, 1, 1),
    512, NULL, s_network__model_22_m_0_cv3_conv_Conv_output_0_bias_array_u64),   /* _model_22_m_0_cv3_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 393216, 1, 1),
    393216, NULL, s_network__model_22_cv2_conv_Conv_output_0_weights_array_u64),   /* _model_22_cv2_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_22_cv2_conv_Conv_output_0_bias_array_u64),   /* _model_22_cv2_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 9216, 1, 1),
    9216, NULL, s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1024, 1, 1),
    1024, NULL, s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 65536, 1, 1),
    65536, NULL, s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 2304, 1, 1),
    2304, NULL, s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 7168, 1, 1),
    7168, NULL, s_network__model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array_u64),   /* _model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 112, 1, 1),
    112, NULL, s_network__model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array_u64),   /* _model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 589824, 1, 1),
    589824, NULL, s_network__model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 147456, 1, 1),
    147456, NULL, s_network__model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array_u64),   /* _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array_u64),   /* _model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16384, 1, 1),
    16384, NULL, s_network__model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array_u64),   /* _model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 256, 1, 1),
    256, NULL, s_network__model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array_u64),   /* _model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 64, 1, 1),
    64, NULL, s_network__model_23_dfl_conv_Conv_output_0_weights_array_u64),   /* _model_23_dfl_conv_Conv_output_0_weights_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 4, 1, 1),
    4, NULL, s_network__model_23_dfl_conv_Conv_output_0_bias_array_u64),   /* _model_23_dfl_conv_Conv_output_0_bias_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16800, 1, 1),
    16800, NULL, s_network__model_23_Constant_13_output_0_array_u64),   /* _model_23_Constant_13_output_0_array */
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 16800, 1, 1),
    16800, NULL, s_network__model_23_Constant_12_output_0_array_u64),   /* _model_23_Constant_12_output_0_array */
  };


/*!
 * @brief Get network activations buffer initialized struct.
 * @ingroup network_data
 * @param[in] ptr a pointer to the activations array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_network_data_activations_buffer_get(const ai_handle ptr)
{
  ai_buffer buf = AI_BUFFER_INIT(
    AI_FLAG_NONE, AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, AI_NETWORK_DATA_ACTIVATIONS_SIZE, 1, AI_NETWORK_DATA_ACTIVATIONS_COUNT),
    AI_NETWORK_DATA_ACTIVATIONS_SIZE,
    NULL, ptr);
  return buf;
}

/*!
 * @brief Get network weights buffer initialized struct.
 * @ingroup network_data
 * @param[in] ptr a pointer to the weights array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_network_data_weights_buffer_get(const ai_handle ptr)
{
  ai_buffer buf = AI_BUFFER_INIT(
    AI_FLAG_NONE, AI_BUFFER_FORMAT_U8|AI_BUFFER_FMT_FLAG_CONST,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, AI_NETWORK_DATA_WEIGHTS_SIZE, 1, AI_NETWORK_DATA_WEIGHTS_COUNT),
    AI_NETWORK_DATA_WEIGHTS_SIZE,
    NULL, ptr);
  return buf;
}


/*!
 * @brief Get network weights array pointer as a handle ptr.
 * @ingroup network_data
 * @return a ai_handle pointer to the weights array
 */
AI_DEPRECATED
AI_API_ENTRY
ai_handle ai_network_data_weights_get(void)
{
  return AI_HANDLE_PTR(g_network_weights_table);

}


/*!
 * @brief Get network params configuration data structure.
 * @ingroup network_data
 * @return true if a valid configuration is present, false otherwise
 */
AI_API_ENTRY
ai_bool ai_network_data_params_get(ai_network_params* params)
{
  if (!params) return false;
  
  const ai_buffer_array map_activations = 
    AI_BUFFER_ARRAY_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_DATA_ACTIVATIONS_COUNT, g_network_data_map_activations);
  
  const ai_buffer_array map_weights = 
    AI_BUFFER_ARRAY_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_DATA_WEIGHTS_COUNT, g_network_data_map_weights);

  return ai_platform_bind_network_params(params, &map_weights, &map_activations);
}


AI_API_DECLARE_END
