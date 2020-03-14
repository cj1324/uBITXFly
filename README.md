# uBITXFly

通过 STM32F0 芯片，扩展 uBIXT  Raduino 的功能，包括按钮， 电源电压，信号强度等。

# 主控 STM32F0

  原设计是 STM32F030F4P6 考虑到容量 实际使用了引脚基本兼容的 STM32F070F6P6 作为主控。


  优点

    + 廉价 2-3元（人民币）一片
    + 易于焊接 TSSOP20 封装
    + 高性能 32 位 ，32kb flash, 48MHz 时钟
 

# 硬件资源

  + I2C 加用 5V 的电平转换，用来链接 Raduino。
  + 额外一个 5V 的引脚，用来做 Raduino 中断。
  + 电源 ADC, 最大 15V (电阻按实际情况焊接，非原理图标注值)
  + 音频 ADC, 链接运放 LM321 计划代替 S 表
  + PCB 上内置 两个按钮，两个 LED.
  + 通过 USB 接口或 2.54 接口供电 带有 3.3V LDO 芯片
  + 提供 3.3V UART 接口，可以用来编程 （配套 BOOT0 开关）
  + 预留 SWD 接口, 可以选择链接两个外部按钮
  + PA7 / PA5 可以链接两个外部按钮。

# 软件 (In Progress)

  + 项目模板参考 https://github.com/cj1324/STM32F030F4-GCC-Template


# LICENSE

[BSD 2-Clause "Simplified" License](/LICENSE)
