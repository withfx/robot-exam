# C++ 与 ROS2 考核项目（robot-exam）

> **作者**：冯翔 ｜ **班级**：26 级 地理信息科学 2 班
> **仓库地址**：<https://github.com/withfx/robot-exam>

这个仓库是三次考核的作业：

| 考核 | 内容 | 语言 |
| --- | --- | --- |
| 考核一 | 成绩排序、Book 类、字符串统计 | C++ |
| 考核二 | 自定义话题、自定义服务、launch + yaml | C++（rclcpp） |
| 考核三 | Git 与 GitHub 的使用 | — |

## 一、目录结构

```
robot-exam/
├── exam1/                        # 考核一：C++ 代码能力
│   ├── question1/                # 第一题：成绩降序排序
│   │   ├── main.cpp
│   │   └── README.md
│   ├── question2/                # 第二题：Book 类
│   │   ├── main.cpp
│   │   └── README.md
│   └── question3/                # 第三题：字符串统计
│       ├── main.cpp
│       └── README.md
├── exam2/                        # 考核二：ROS2
│   ├── robot_status_msg/         # 自定义消息接口
│   ├── add_two_ints_srv/         # 自定义服务接口
│   ├── robot_status_node/        # 话题发布者 + 订阅者 + launch + params.yaml
│   ├── service_node/             # 服务端 + 客户端
│   └── README.md
├── .gitignore
└── README.md
```

## 二、运行环境

| 软件 | 版本 |
| --- | --- |
| 系统 | Ubuntu 22.04 |
| ROS2 | Humble |
| g++ | 支持 C++17 |
| Python | 3.10（launch 文件用） |

考核一只要 g++ 就能跑；考核二需要先装好 ROS2 Humble。

## 三、考核一：C++ 代码能力

### 第一题：成绩降序排序

读入 10 个成绩，用 `sort` + `greater<int>()` 从大到小排序后输出。

```bash
cd exam1/question1
g++ -std=c++17 main.cpp -o main
./main
```

```
请输入10名同学的成绩：成绩从高到低排序结果：
100 95 92 88 85 82 78 70 65 60
```

### 第二题：Book 类

私有成员 `title` / `price` / `stock`，公有的构造函数、析构函数、`input()`、`display()`，
`main()` 里 `new` 一个对象、用指针调用、最后 `delete`。

```bash
cd exam1/question2
g++ -std=c++17 main.cpp -o main
./main
# 依次输入：C++入门 / 45.5 / 20
```

```
书名：C++入门
价格：45.5
库存：20
Book 对象已销毁
```

### 第三题：字符串统计

用 `getline` 读一整行，遍历每个字符，用 `isalpha` / `isdigit` 分类计数。

```bash
cd exam1/question3
g++ -std=c++17 main.cpp -o main
./main
# 输入：Hello, ROS2 2024!
```

```
英文字母个数：8
数字个数：5
其他字符个数：4
```

## 四、考核二：ROS2（C++）

4 个包：两个接口包（msg / srv），两个节点包（话题 / 服务）。

```bash
cd exam2
colcon build --symlink-install
source install/setup.bash

# 第一题：话题
ros2 run robot_status_node publisher     # 终端 A
ros2 run robot_status_node subscriber    # 终端 B

# 第二题：服务
ros2 run service_node server             # 终端 A
ros2 run service_node client             # 终端 B

# 第三题：launch + yaml 一键启动 4 个节点
ros2 launch robot_status_node exam2.launch.py
ros2 node list
```

`ros2 node list` 应该看到：

```
/robot1/atil_1
/robot1/atil_1_client
/robot1/atil_1_server
/robot1/atil_1_subscriber
```

详细的验证命令和踩坑记录写在 [`exam2/README.md`](exam2/README.md)。

几个关键点：

1. **节点重命名**：4 个节点在同一个命名空间里不能都叫 `atil_1`，否则重名，
   所以发布者叫 `atil_1`，其它三个加后缀；
2. **话题/服务用全局名**：节点进了 `robot1` 命名空间后，相对话题会变成
   `/robot1/robot_status`，所以在 yaml 里写 `/robot_status`、`/add_two_ints`；
3. **参数文件的键要写全**：必须写 `/robot1/atil_1`，只写 `atil_1` 匹配不上，
   参数不会生效（这个坑我踩过，查了很久）。

## 五、考核三：Git 与 GitHub 学习报告

### 5.1 为什么要用 Git

一开始我保存代码的方式是"复制一份文件夹，改名叫最终版、最终版2"，
结果文件越来越多，也不知道哪一次改了什么。Git 能记录每一次修改，
改坏了可以退回去，还能把代码传到 GitHub 上，换台电脑也能继续写。

### 5.2 三个区域

```
工作区（改代码的地方） --git add--> 暂存区 --git commit--> 本地仓库 --git push--> GitHub
```

### 5.3 常用命令

```bash
git init                    # 在当前文件夹创建仓库
git status                  # 看哪些文件改了
git add .                   # 把改动放进暂存区
git commit -m "说明"         # 提交到本地仓库
git log --oneline           # 看提交记录
git remote add origin 地址   # 关联远程仓库
git push -u origin main     # 推送到 GitHub
git pull                    # 把 GitHub 上的更新拉下来
git clone 地址               # 把仓库下载到本地
```

### 5.4 把项目传到 GitHub 的步骤

1. 在 GitHub 网页点 `New repository`，名字填 `robot-exam`，选 **Public**，
   **不要**勾选 "Add a README file"（本地已经有 README，勾了会冲突）；
2. 在本地项目文件夹里打开终端：

```bash
cd robot-exam
git init
git add .
git commit -m "完成 C++ 与 ROS2 考核作业"
git branch -M main
git remote add origin https://github.com/withfx/robot-exam.git
git push -u origin main
```

3. 推送时如果让输密码，不能输 GitHub 登录密码，要用 **Personal Access Token**：
   GitHub → Settings → Developer settings → Personal access tokens → Generate new token，
   勾上 `repo` 权限，复制出来的 token 当密码用；
4. 刷新仓库页面，能看到代码和 README 就成功了。

### 5.5 GitHub Desktop

不想敲命令可以装 GitHub Desktop：

1. 登录账号 → `File` → `Add local repository`，选中 `robot-exam` 文件夹；
2. 左边 `Changes` 会列出改动的文件，勾选要提交的；
3. 左下角填 Summary（相当于提交说明），点 `Commit to main`；
4. 点右上角 `Publish repository` / `Push origin` 推送到 GitHub。

### 5.6 提交前检查

- [x] 仓库是 Public（别人不登录也能看）
- [x] 没有提交 `build/`、`install/`、`log/`、`__pycache__`、`.exe` 这些编译产物
      （用 `.gitignore` 排除）
- [x] README 写清楚项目是什么、怎么编译、怎么运行
- [x] 提交说明写清楚改了什么，不是一堆 `update`

### 5.7 踩过的坑

| 问题 | 原因 | 解决 |
| --- | --- | --- |
| `fatal: not a git repository` | 当前目录不是仓库 | `cd` 到项目文件夹再执行 |
| `Updates were rejected` | GitHub 上有本地没有的提交 | 先 `git pull` 再 `git push` |
| `Authentication failed` | 用了登录密码 | 改用 Personal Access Token |
| 误把 `build/` 提交了 | 忘了写 `.gitignore` | `git rm -r --cached build` 后再提交 |

### 5.8 我的仓库

<https://github.com/withfx/robot-exam>（Public）

## 六、学习总结

- 第一题让我知道了 `sort` 默认是升序，要降序得传 `greater<int>()`，还要包含 `<functional>`；
- 第二题最大的收获是 `cin.ignore()` 不能乱加，它会吃掉一个字符，
  我的书名一开始就少了第一个字，查了半天才发现；
- 第三题知道了 `cin >>` 遇到空格会停，读一整行要用 `getline`；
- ROS2 里"名字"特别重要：节点名、命名空间、话题名、参数文件的键名，
  有一个对不上就可能不生效，而且不报错，只能自己用 `ros2 param get`、`ros2 topic list` 去查。

## 七、提交说明

- 压缩包：`26-地信2-冯翔.zip`
- 邮箱：1219921425@qq.com
- 正文写仓库链接：<https://github.com/withfx/robot-exam>
