/**
 *  @author:    Qsionc
 *  @date:      03/08/2021
 *  @file:      logger_settings.h
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_LOGGER_SETTINGS_H
#define SMOL_LOGGER_LOGGER_SETTINGS_H

namespace smol::settings {
    constexpr char info_prefix[] = "[INFO]\t";
    constexpr char warning_prefix[] = "[WARNING]\t";
    constexpr char error_prefix[] = "[ERROR] \t";
    constexpr char fatal_prefix[] = "[FATAL]\t";
}

#endif //SMOL_LOGGER_LOGGER_SETTINGS_H
