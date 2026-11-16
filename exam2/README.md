# 考核二：ROS2 自定义话题 / 自定义服务 / launch + yaml

本目录是一个 ROS2 工作空间，里面有 4 个包，全部用 **C++（rclcpp）** 编写。

```
exam2/
├── robot_status_msg/     自定义消息接口（RobotStatus.msg）
├── add_two_ints_srv/     自定义服务接口（AddTwoInts.srv）
├── robot_status_node/    话题发布者 + 订阅者（C++）
├── service_node/         服务端 + 客户端（C++）
└── README.md
```

## 一、接口

`robot_status_msg/msg/RobotStatus.msg`

```
string robot_name
float32 speed
float32 position_x
float32 position_y
```

`add_two_ints_srv/srv/AddTwoInts.srv`

```
int64 a
int64 b
---
int64 sum
```

## 二、编译

```bash
cd exam2
colcon build --symlink-install
source install/setup.bash
```

编译成功会看到：

```
Summary: 4 packages finished
```

## 三、第一题：自定义话题通信

开两个终端（都要先 `source install/setup.bash`）：

```bash
# 终端 A
ros2 run robot_status_node publisher

# 终端 B
ros2 run robot_status_node subscriber
```

发布者每秒发一条：

```
[INFO] [robot_status_publisher]: 发布者已启动：话题 robot_status，频率 1.0 Hz
[INFO] [robot_status_publisher]: 发布：atil_1 速度 0.50 坐标 (0.50, 0.25)
```

订阅者收到并打印：

```
[INFO] [robot_status_subscriber]: 订阅者已启动：话题 robot_status
[INFO] [robot_status_subscriber]: 收到：atil_1 速度 0.50 坐标 (0.50, 0.25)
```

检查命令：

```bash
ros2 topic list                 # 能看到 /robot_status
ros2 topic info /robot_status   # Publisher count: 1, Subscription count: 1
ros2 topic hz /robot_status     # average rate: 1.000
ros2 interface show robot_status_msg/msg/RobotStatus
```

## 四、第二题：自定义服务通信

```bash
# 终端 A：先启动服务端
ros2 run service_node server

# 终端 B：再启动客户端
ros2 run service_node client
```

```
[INFO] [add_two_ints_client]: 发送请求：3 + 5
[INFO] [add_two_ints_server]: 收到请求：3 + 5 = 8
[INFO] [add_two_ints_client]: 收到响应：3 + 5 = 8
```

检查命令：

```bash
ros2 service list
ros2 service type /add_two_ints
ros2 service call /add_two_ints add_two_ints_srv/srv/AddTwoInts "{a: 10, b: 20}"
```

`ros2 service call` 的返回：

```
response:
add_two_ints_srv.srv.AddTwoInts_Response(sum=30)
```

## 五、第三题：launch 一键启动 + yaml 参数

```bash
ros2 launch robot_status_node exam2.launch.py
```

一条命令启动 4 个节点，统一命名空间 `robot1`，统一 `output="screen"`：

```bash
ros2 node list
/robot1/atil_1
/robot1/atil_1_client
/robot1/atil_1_server
/robot1/atil_1_subscriber
```

参数确实是从 `params.yaml` 读的（不是代码里的默认值）：

```bash
ros2 param get /robot1/atil_1 topic_name       # /robot_status
ros2 param get /robot1/atil_1 publish_rate     # 1.0
ros2 param get /robot1/atil_1_client a         # 3
```

## 六、几个容易搞错的地方

### 1. 参数文件的键名要写全

`params.yaml` 里必须写 `/robot1/atil_1`，不能只写 `atil_1`。
因为 launch 里设置了 `namespace="robot1"`，节点的完整名字已经变成 `/robot1/atil_1`，
只写短名字 ROS2 匹配不上，**参数不会报错，但也不会生效**，节点会继续用代码里的默认值。

### 2. 话题名、服务名前面要加 /

节点被放进 `robot1` 命名空间后，如果参数里写的是相对名字 `robot_status`，
实际话题会变成 `/robot1/robot_status`。题目要求是 `/robot_status`，
所以 yaml 里写 `/robot_status` 和 `/add_two_ints`，用全局名字。

### 3. 四个节点不能都叫 atil_1

题目要求用 `name` 重命名节点（重命名为 atil_1）。但 4 个节点在同一个命名空间里，
如果都叫 `atil_1` 就重名了，`ros2 node list` 分不清，参数也会互相覆盖。
所以发布者叫 `atil_1`，其它三个加后缀（`atil_1_subscriber` 等）。

### 4. 为什么客户端发完请求不退出

客户端的 `main()` 里发完请求、打印结果后继续 `rclcpp::spin(node)`，
这样节点会一直活着，launch 启动后 `ros2 node list` 才能看到 4 个节点。
不想让它一直跑，按 Ctrl+C 就行。
