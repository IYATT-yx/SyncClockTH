/**
 * @file      RtcModule.hpp
 * @brief     实时时钟模块
 * @author    IYATT-yx
 * @copyright Copyright (c) 2026 IYATT-yx.
 *            Licensed under the MIT License. See LICENSE file in the project root for full license information.
 */
#ifndef RTC_MODULE_HPP
#define RTC_MODULE_HPP

/**
 * @brief 将 ESP32 的本地系统时间同步写入到 DS1302 硬件芯片中
 * @return true 同步成功，false 获取系统时间失败
 */
bool syncTimeEsp32ToRtc();

/**
 * @brief 从 DS1302 硬件芯片读取时间，并更新设置给 ESP32 的内部系统时钟
 * @return true 设置成功，false 硬件未启动
 */
bool syncTimeRtcToEsp32();

#endif