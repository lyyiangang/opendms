# 简介
opendms是一个定位在嵌入式平台运行的DMS(driver monitor system)系统, 提供了一下feature。
- 人脸检测
- 人脸landmark检测
- 人脸6DOF姿态检测
- 以及基于上述基础功能获取的驾驶员疲劳，分心等信息。
由于定位在较低资源的设备上运行，所以使用的模型都比较精简。

## 环境搭建
1. clone代码

    ```bash
    git clone https://github.com/lyyiangang/opendms.git
    ``` 

2. 创建docker镜像
 
    ```bash
    cd opendms
    docker build -f Dockerfile.txt -t opendms . 
    ```
    这个dockerfile里面包含了OpenCV，MNN, 以及arm的交叉编译环境配置,由于github访问太慢，所以里面的OpenCV以及MNN等库是从gitee上拉下来的。

3. 编译

- 编译x86程序
    编译x86平台程序，主要用来功能验证以及调试。
    ```bash
    mkdir build &&cd build 
    cmake .. && make -j
    ```
    接下来可以启动demo程序
    ```bash
    ./demo.out ../data/test.mp4
    ```

- 编译arm程序
    ```bash
    mkdir build &&cd build 
    cmake .. -DPLATFORM=aarch64 && make -j
    ```
    编译完成后，需要手动将下列文件复制到目标平台，比如树莓派。

    ```bash
    # 第三方库
    build/install_aarch64/lib
    # 编译的可执行程序
    build/demo.out
    build/libdms.so
    # 配置文件
    cfg.json
    # 模型
    models/
    ```

    当然也可以修改script/sync_to_pi.sh里的配置后使用命令自动复制过去。

## 示例

编译完成后就可以启动demo程序
```bash
cd build && ./demo.out ../data/test.mp4
```
可以得到类似下图的结果：
![](doc/imgs/2021-07-10-17-58-13.png)
**cfg.json**为配置文件，目前只能设置模型路径等参数，将会支持更多设置。

## TODO

- [ ] face track

- [ ] 更好的face detector
- [ ] 更好的face landmark detector
- [ ] 视线估计

## 感谢
[MNN](https://github.com/alibaba/MNN)

[Ultra-Light-Fast-Generic-Face-Detector-1MB](https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB)

[PFLD](https://github.com/guoqiangqi/PFLD.git)