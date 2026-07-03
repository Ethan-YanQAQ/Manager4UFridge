/**
  ******************************************************************************
  * @file    network_data.h
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-07-03T19:11:41+0800
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef NETWORK_DATA_H
#define NETWORK_DATA_H

#include "network_config.h"
#include "network_data_params.h"

AI_DEPRECATED
#define AI_NETWORK_DATA_ACTIVATIONS(ptr_)  \
  ai_network_data_activations_buffer_get(AI_HANDLE_PTR(ptr_))

AI_DEPRECATED
#define AI_NETWORK_DATA_WEIGHTS(ptr_)  \
  ai_network_data_weights_buffer_get(AI_HANDLE_PTR(ptr_))


AI_API_DECLARE_BEGIN


extern const ai_u64 s_network__model_10_m_m_0_attn_MatMul_1_output_0_bias_array_u64[1];
extern const ai_u64 s_network__model_10_m_m_0_attn_MatMul_output_0_bias_array_u64[1];
extern const ai_u64 s_network__model_23_Constant_14_output_0_3D_array_u64[1];
extern const ai_u64 s_network__model_23_Constant_15_output_0_3D_array_u64[1050];
extern const ai_u64 s_network__model_0_conv_Conv_output_0_weights_array_u64[216];
extern const ai_u64 s_network__model_0_conv_Conv_output_0_bias_array_u64[8];
extern const ai_u64 s_network__model_1_conv_Conv_output_0_weights_array_u64[2304];
extern const ai_u64 s_network__model_1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_2_cv1_conv_Conv_output_0_weights_array_u64[512];
extern const ai_u64 s_network__model_2_cv1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_2_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_2_m_0_cv1_conv_Conv_output_0_weights_array_u64[576];
extern const ai_u64 s_network__model_2_m_0_cv1_conv_Conv_output_0_bias_array_u64[4];
extern const ai_u64 s_network__model_2_m_0_cv2_conv_Conv_output_0_weights_array_u64[576];
extern const ai_u64 s_network__model_2_m_0_cv2_conv_Conv_output_0_bias_array_u64[8];
extern const ai_u64 s_network__model_2_cv2_conv_Conv_output_0_weights_array_u64[1536];
extern const ai_u64 s_network__model_2_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_3_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_3_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_4_cv1_conv_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_4_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_4_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_4_m_0_cv1_conv_Conv_output_0_weights_array_u64[2304];
extern const ai_u64 s_network__model_4_m_0_cv1_conv_Conv_output_0_bias_array_u64[8];
extern const ai_u64 s_network__model_4_m_0_cv2_conv_Conv_output_0_weights_array_u64[2304];
extern const ai_u64 s_network__model_4_m_0_cv2_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_4_cv2_conv_Conv_output_0_weights_array_u64[6144];
extern const ai_u64 s_network__model_4_cv2_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_5_conv_Conv_output_0_weights_array_u64[73728];
extern const ai_u64 s_network__model_5_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_6_cv1_conv_Conv_output_0_weights_array_u64[8192];
extern const ai_u64 s_network__model_6_cv1_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_6_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_6_m_0_cv2_conv_Conv_output_0_weights_array_u64[1024];
extern const ai_u64 s_network__model_6_m_0_cv2_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_6_m_0_cv1_conv_Conv_output_0_weights_array_u64[1024];
extern const ai_u64 s_network__model_6_m_0_cv1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_6_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array_u64[4608];
extern const ai_u64 s_network__model_6_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_6_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array_u64[4608];
extern const ai_u64 s_network__model_6_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_6_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array_u64[4608];
extern const ai_u64 s_network__model_6_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_6_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array_u64[4608];
extern const ai_u64 s_network__model_6_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_6_m_0_cv3_conv_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_6_m_0_cv3_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_6_cv2_conv_Conv_output_0_weights_array_u64[12288];
extern const ai_u64 s_network__model_6_cv2_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_7_conv_Conv_output_0_weights_array_u64[147456];
extern const ai_u64 s_network__model_7_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_8_cv1_conv_Conv_output_0_weights_array_u64[32768];
extern const ai_u64 s_network__model_8_cv1_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_8_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_8_m_0_cv2_conv_Conv_output_0_weights_array_u64[4096];
extern const ai_u64 s_network__model_8_m_0_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_8_m_0_cv1_conv_Conv_output_0_weights_array_u64[4096];
extern const ai_u64 s_network__model_8_m_0_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_8_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_8_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_8_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_8_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_8_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_8_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_8_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_8_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_8_m_0_cv3_conv_Conv_output_0_weights_array_u64[8192];
extern const ai_u64 s_network__model_8_m_0_cv3_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_8_cv2_conv_Conv_output_0_weights_array_u64[49152];
extern const ai_u64 s_network__model_8_cv2_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_9_cv1_conv_Conv_output_0_weights_array_u64[16384];
extern const ai_u64 s_network__model_9_cv1_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_9_cv2_conv_Conv_output_0_weights_array_u64[65536];
extern const ai_u64 s_network__model_9_cv2_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_10_cv1_conv_Conv_output_0_weights_array_u64[32768];
extern const ai_u64 s_network__model_10_cv1_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_10_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_10_m_m_0_attn_qkv_conv_Conv_output_0_weights_array_u64[16384];
extern const ai_u64 s_network__model_10_m_m_0_attn_qkv_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_10_m_m_0_attn_Split_output_0_num_or_size_splits_array_u64[2];
extern const ai_u64 s_network__model_10_m_m_0_attn_Mul_output_0_scale_array_u64[1];
extern const ai_u64 s_network__model_10_m_m_0_attn_Mul_output_0_bias_array_u64[1];
extern const ai_u64 s_network__model_10_m_m_0_attn_pe_conv_Conv_output_0_weights_array_u64[576];
extern const ai_u64 s_network__model_10_m_m_0_attn_pe_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_10_m_m_0_attn_proj_conv_Conv_output_0_weights_array_u64[8192];
extern const ai_u64 s_network__model_10_m_m_0_attn_proj_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_weights_array_u64[16384];
extern const ai_u64 s_network__model_10_m_m_0_ffn_ffn_0_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_weights_array_u64[16384];
extern const ai_u64 s_network__model_10_m_m_0_ffn_ffn_1_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_10_cv2_conv_Conv_output_0_weights_array_u64[32768];
extern const ai_u64 s_network__model_10_cv2_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_13_cv1_conv_Conv_output_0_weights_array_u64[24576];
extern const ai_u64 s_network__model_13_cv1_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_13_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_13_m_0_cv1_conv_Conv_output_0_weights_array_u64[9216];
extern const ai_u64 s_network__model_13_m_0_cv1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_13_m_0_cv2_conv_Conv_output_0_weights_array_u64[9216];
extern const ai_u64 s_network__model_13_m_0_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_13_cv2_conv_Conv_output_0_weights_array_u64[12288];
extern const ai_u64 s_network__model_13_cv2_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_16_cv1_conv_Conv_output_0_weights_array_u64[8192];
extern const ai_u64 s_network__model_16_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_16_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_16_m_0_cv1_conv_Conv_output_0_weights_array_u64[2304];
extern const ai_u64 s_network__model_16_m_0_cv1_conv_Conv_output_0_bias_array_u64[8];
extern const ai_u64 s_network__model_16_m_0_cv2_conv_Conv_output_0_weights_array_u64[2304];
extern const ai_u64 s_network__model_16_m_0_cv2_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_16_cv2_conv_Conv_output_0_weights_array_u64[3072];
extern const ai_u64 s_network__model_16_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_weights_array_u64[288];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_0_cv3_0_0_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_weights_array_u64[288];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_1_cv3_0_1_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_2_Conv_output_0_weights_array_u64[896];
extern const ai_u64 s_network__model_23_cv3_0_cv3_0_2_Conv_output_0_bias_array_u64[14];
extern const ai_u64 s_network__model_23_cv2_0_cv2_0_0_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_23_cv2_0_cv2_0_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv2_0_cv2_0_1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_23_cv2_0_cv2_0_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv2_0_cv2_0_2_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv2_0_cv2_0_2_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_17_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_17_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_19_cv1_conv_Conv_output_0_weights_array_u64[12288];
extern const ai_u64 s_network__model_19_cv1_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_19_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_19_m_0_cv1_conv_Conv_output_0_weights_array_u64[9216];
extern const ai_u64 s_network__model_19_m_0_cv1_conv_Conv_output_0_bias_array_u64[16];
extern const ai_u64 s_network__model_19_m_0_cv2_conv_Conv_output_0_weights_array_u64[9216];
extern const ai_u64 s_network__model_19_m_0_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_19_cv2_conv_Conv_output_0_weights_array_u64[12288];
extern const ai_u64 s_network__model_19_cv2_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_weights_array_u64[576];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_0_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_weights_array_u64[4096];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_0_cv3_1_0_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_weights_array_u64[288];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_1_cv3_1_1_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_2_Conv_output_0_weights_array_u64[896];
extern const ai_u64 s_network__model_23_cv3_1_cv3_1_2_Conv_output_0_bias_array_u64[14];
extern const ai_u64 s_network__model_23_cv2_1_cv2_1_0_conv_Conv_output_0_weights_array_u64[36864];
extern const ai_u64 s_network__model_23_cv2_1_cv2_1_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv2_1_cv2_1_1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_23_cv2_1_cv2_1_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv2_1_cv2_1_2_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv2_1_cv2_1_2_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_20_conv_Conv_output_0_weights_array_u64[73728];
extern const ai_u64 s_network__model_20_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_22_cv1_conv_Conv_output_0_weights_array_u64[49152];
extern const ai_u64 s_network__model_22_cv1_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_22_Split_output_0_num_or_size_splits_array_u64[1];
extern const ai_u64 s_network__model_22_m_0_cv2_conv_Conv_output_0_weights_array_u64[4096];
extern const ai_u64 s_network__model_22_m_0_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_22_m_0_cv1_conv_Conv_output_0_weights_array_u64[4096];
extern const ai_u64 s_network__model_22_m_0_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_22_m_0_m_m_0_cv1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_22_m_0_m_m_0_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_22_m_0_m_m_0_cv2_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_22_m_0_m_m_0_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_22_m_0_m_m_1_cv1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_22_m_0_m_m_1_cv1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_22_m_0_m_m_1_cv2_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_22_m_0_m_m_1_cv2_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_22_m_0_cv3_conv_Conv_output_0_weights_array_u64[8192];
extern const ai_u64 s_network__model_22_m_0_cv3_conv_Conv_output_0_bias_array_u64[64];
extern const ai_u64 s_network__model_22_cv2_conv_Conv_output_0_weights_array_u64[49152];
extern const ai_u64 s_network__model_22_cv2_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_weights_array_u64[1152];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_0_conv_Conv_output_0_bias_array_u64[128];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_weights_array_u64[8192];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_0_cv3_2_0_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_weights_array_u64[288];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_1_cv3_2_1_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_2_Conv_output_0_weights_array_u64[896];
extern const ai_u64 s_network__model_23_cv3_2_cv3_2_2_Conv_output_0_bias_array_u64[14];
extern const ai_u64 s_network__model_23_cv2_2_cv2_2_0_conv_Conv_output_0_weights_array_u64[73728];
extern const ai_u64 s_network__model_23_cv2_2_cv2_2_0_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv2_2_cv2_2_1_conv_Conv_output_0_weights_array_u64[18432];
extern const ai_u64 s_network__model_23_cv2_2_cv2_2_1_conv_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_cv2_2_cv2_2_2_Conv_output_0_weights_array_u64[2048];
extern const ai_u64 s_network__model_23_cv2_2_cv2_2_2_Conv_output_0_bias_array_u64[32];
extern const ai_u64 s_network__model_23_dfl_conv_Conv_output_0_weights_array_u64[8];
extern const ai_u64 s_network__model_23_dfl_conv_Conv_output_0_bias_array_u64[1];
extern const ai_u64 s_network__model_23_Constant_13_output_0_array_u64[2100];
extern const ai_u64 s_network__model_23_Constant_12_output_0_array_u64[2100];



/*!
 * @brief Get network activations buffer initialized struct.
 * @ingroup network_data
 * @param[in] ptr a pointer to the activations array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_network_data_activations_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights buffer initialized struct.
 * @ingroup network_data
 * @param[in] ptr a pointer to the weights array storage area
 * @return an ai_buffer initialized struct
 */
AI_DEPRECATED
AI_API_ENTRY
ai_buffer ai_network_data_weights_buffer_get(const ai_handle ptr);

/*!
 * @brief Get network weights array pointer as a handle ptr.
 * @ingroup network_data
 * @return a ai_handle pointer to the weights array
 */
AI_DEPRECATED
AI_API_ENTRY
ai_handle ai_network_data_weights_get(void);


/*!
 * @brief Get network params configuration data structure.
 * @ingroup network_data
 * @return true if a valid configuration is present, false otherwise
 */
AI_API_ENTRY
ai_bool ai_network_data_params_get(ai_network_params* params);


AI_API_DECLARE_END

#endif /* NETWORK_DATA_H */

