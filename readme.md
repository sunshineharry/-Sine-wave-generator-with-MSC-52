# 周期可调的正弦波发生器

## 项目简介
* 用89C52芯片控制DA转换器构成正弦波发生器，一个正弦周期使用100个采样点，周期在5ms-1000ms范围内可调。
  
* 右上角提供四个按钮，分别对正弦波周期+50ms，-50ms，-5ms，此外，还提供一个重启按钮，可以在波形错误时重启正弦波发生器。
  
* 具备串口通信功能，通过串口向外发送当前周期。
  
* LED显示屏同步显示当先正弦波周期。
  

## 设计思考
* **为什么使用周期而没有使用更常见的频率？**
  
  一个周期需要用100个采样点绘制，每个采样点之间的时差使用定时器控制。如果使用周期，则需要将频率一百分频后转换成定时，根据周期与频率的倒数关系，单片机需要计算除法，因此产生舍入误差。

  在一个周期内，舍入误差将被放大100倍，故直接使用周期控制效果更好。


* **为什么最小周期是5ms？**
  
  完成纯粹的一个DA输出至少25us，加上其他的运算与控制逻辑，所以两次DA输出的间隔至少50us。
  
  一个周期的正弦波需要100次DA输出控制，故最小周期是5ms。


* **为什么晶振使用22.1184MHz？**
  
  兼顾串口通信的同时，加快单片机的运行速度。

  根据资料，51系列单片机最高支持晶振40Hz，兼顾串口和常见的晶振频率，选择22.1184MHz。此时，使用串口需要设置波特率19200。

  
* **为什么当正弦周期比较小时LED显示不稳定？**
  
  当周期较小时，在定时器的中断服务函数中停留时间更长，从而影响显示的时序控制。
  

* **为什么控制周期的只有三个按钮？**
  
  最多只能使用三个按钮QwQ

  当中断较多时，无法使用正常消抖的方式检测按钮是否摁下，故只能将外中断设置成下降沿模式，使用查询的方式获取按钮信息。

  通过`74LS148`编码器，可以扩展一个按钮。

  此外，在这种模式下，必须手动清除中断标志位。