
####  <font size = 4>一、说明：</font>
> <font size = 3>本程序是模仿泡泡堂游戏功能的Demo，使用DirectX11图形库和C++语言，v1.0在VS2010环境下编译，v1.2以后再VS2015环境下编译。</font>

####  <font size = 4>二、程序运行环境：</font>
> <font size = 3>WIN7以上系统，64/32位均可，DirectX版本需要在11以上。</font>

####  <font size = 4>三、搭建编译环境：</font>
> <font size = 3>右击项目-点击属性：
1.在常规页面，字符集修改为“使用多字节字符集”
2.在链接器-输入页的附加依赖项添加：
dxguid.lib;dinput8.lib;dxerr.lib;d3d11.lib;d3dx11.lib;d3dcompiler.lib;
<font color = red>（以下两项因为不同电脑的DirectX11图形库路径不同，需要重新设置目录路径）
3.在VC++目录页的包含目录添加DirectX11图形库头文件目录：如：
C:\Users\Administrator\Desktop\泡泡堂Demo V1.0\源代码\DirectX11图形库\Microsoft DirectX SDK (June 2010)\Include;
4/在VC++目录页的库目录添加DirectX11图形库Lib文件目录，如：
C:\Users\Administrator\Desktop\泡泡堂Demo V1.0\源代码\DirectX11图形库\Microsoft DirectX SDK (June 2010)\Lib\x86;</font></font>

####  <font size = 4>四、程序运行截图：</font>
![截图1](http://img.blog.csdn.net/20150906141825934)

![截图2](http://img.blog.csdn.net/20150906141839704)

![截图3](http://img.blog.csdn.net/20150906141851190)

V1.2：（新增AI）
![这里写图片描述](http://img.blog.csdn.net/20160814081756525)

####  <font size = 4>五、总结</font>
> 
<font size = 3>第一次用DirectX11做游戏，主要是为了复习和熟练DirectX11知识。这个做游戏的过程复习还有学习了很多有趣的东西，用到比较好玩的技术有：</font>
> 
* <font size = 3>脏矩形：优化2D游戏，使得程序不必每次都渲染所有精灵图片，而只要渲染改变的那部分矩形。本来FPS最高才10多20，使用了脏矩形技术，FPS飙得非常高，不过为了玩起来游戏平滑，要设置固定FPS。</font>
> 
* <font size = 3>有限状态机：使得游戏对象可以在不同的状态进行切换，但是同时又使得代码非常整洁，避免使用了过多的if else减低程序可维护度。</font>
> 
* <font size = 3>消息功能：封装一个电报消息，使得游戏对象直接可以发送消息，也可以设置消息立即执行还是过多久才执行，如游戏的泡泡爆炸是设置了数秒后向泡泡发送爆炸的消息。</font>
> 
* <font size = 3>碰撞检测：这个游戏的碰撞检测有一点不同，当游戏角色碰到方块的边缘时，要让它平滑地“漂移”才能够拐弯。不然是无法刚刚进入一个大小刚刚好的方块的。</font>
> 

####  <font size = 4>六、泡泡堂DirectX11完整项目源代码下载地址（无需积分）：</font>
> v1.0更新内容：
> 
* 人物按方向键移动
* 人物按空格释放泡泡
* 泡泡可炸墙
* 墙内含有属性道具
* 人物捡起道具可获得属性增强

> v1.0下载地址：
>http://download.csdn.net/detail/sinat_24229853/9082187

> 
v1.2更新内容：
> 
* 增加电脑AI自动寻路算法演示
* 优化脏矩形算法
* 将游戏自身与游戏引擎分离
> 
v1.2 下载地址：
> https://github.com/ljcduo/CrazyArcade
> 
> 注意：由于本人要开展新的项目，此Demo已不再维护。

本人博客：http://blog.csdn.net/sinat_24229853