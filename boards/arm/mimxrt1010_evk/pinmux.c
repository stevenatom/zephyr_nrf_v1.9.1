/*
 * Copyright (c) 2019, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <fsl_iomuxc.h>
#include <fsl_gpio.h>

static int mimxrt1010_evk_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	CLOCK_EnableClock(kCLOCK_Iomuxc);
	CLOCK_EnableClock(kCLOCK_IomuxcSnvs);

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio1), okay)
	IOMUXC_SetPinMux(IOMUXC_GPIO_11_GPIOMUX_IO11, 0);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_11_GPIOMUX_IO11,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_PUE(1) |
				IOMUXC_SW_PAD_CTL_PAD_PUS(2) |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
	IOMUXC_GPR->GPR26 &= ~(IOMUXC_GPR_GPR26_GPIO_SEL(1 << 11));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio2), okay)
	IOMUXC_SetPinMux(IOMUXC_GPIO_SD_05_GPIO2_IO05, 0);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_05_GPIO2_IO05,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_PUE(1) |
				IOMUXC_SW_PAD_CTL_PAD_PUS(2) |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
#endif

/* MCUX SDK sets the drive strength of pins on RT1010 to 4 by default,
 * hence the difference between the drive strength selected here and in other
 * board pinmux files
 */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpuart1), okay) && CONFIG_SERIAL
	/* LPUART1 TX/RX */
	IOMUXC_SetPinMux(IOMUXC_GPIO_09_LPUART1_RXD, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_10_LPUART1_TXD, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_09_LPUART1_RXD,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_10_LPUART1_TXD,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpi2c1), okay) && CONFIG_I2C
	/* LPI2C1 SCL, SDA */
	IOMUXC_SetPinMux(IOMUXC_GPIO_01_LPI2C1_SDA, 1);
	IOMUXC_SetPinMux(IOMUXC_GPIO_02_LPI2C1_SCL, 1);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_02_LPI2C1_SCL,
				IOMUXC_SW_PAD_CTL_PAD_PUS(3) |
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_ODE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_01_LPI2C1_SDA,
				IOMUXC_SW_PAD_CTL_PAD_PUS(3) |
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_ODE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpspi1), okay) && CONFIG_SPI
	/* LPSPI1 CS, SDO, SDI, CLK exposed as pins 6, 8, 10, and 12 on J57 */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_03_LPSPI1_SDI, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_04_LPSPI1_SDO, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_05_LPSPI1_PCS0, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_06_LPSPI1_SCK, 0U);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_03_LPSPI1_SDI,
			IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			IOMUXC_SW_PAD_CTL_PAD_DSE(4));
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_04_LPSPI1_SDO,
			IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			IOMUXC_SW_PAD_CTL_PAD_DSE(4));
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_05_LPSPI1_PCS0,
			IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			IOMUXC_SW_PAD_CTL_PAD_DSE(4));
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_06_LPSPI1_SCK,
			IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			IOMUXC_SW_PAD_CTL_PAD_DSE(4));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(adc1), okay) && CONFIG_ADC
	/* ADC Channels 1 and 2, exposed as pins 10 and 12 on J26 of EVK */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_01_GPIOMUX_IO15, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_02_GPIOMUX_IO16, 0U);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_01_GPIOMUX_IO15,
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_02_GPIOMUX_IO16,
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
#endif

	return 0;
}

SYS_INIT(mimxrt1010_evk_init, PRE_KERNEL_1, 0);
