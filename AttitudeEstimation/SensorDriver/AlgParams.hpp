#pragma once

/**
 * @brief algorithm parameters for the complementary filter
*/
#define COMP_FILTER_ALPHA_GAIN 0.9

/**
 * @brief algorithm parameters for the Madgwick Filter
*/
#define BETA_GAIN (0.866*0.05)

/**
 * @brief algorithm parameters for the Mahony Filter
*/
#define KI 0.1
#define KP 1.0