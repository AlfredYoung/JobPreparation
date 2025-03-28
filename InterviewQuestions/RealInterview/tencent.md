1. new 和 malloc 的区别？

|特性| new/delete | malloc/free |
|--|--|--|
|**语言支持**|C++| C/C++|
|**返回类型**|类型指针，自动转换|void*，需要手动转换|
|**初始化**|自动调用构造函数并初始化|不调用构造函数，需手动初始化|
|**释放内存**|`delete` / `delete[]`|`free()`|
|**异常处理**|内存不足抛出 `std::bad_alloc`|返回 `nullptr`，需手动检查|
2. free 可以对对象使用吗？
答：**不可以**，不会调用析构函数，如果你用 new 创建了一个类对象，free() 只会回收内存，但不会调用对象的**析构函数**，可能会导致资源泄露（如文件、网络、内存未释放）。此外，内存管理方式不一致new 依赖于 C++ 的内存管理系统，通过 operator new 分配内存。malloc/free 属于 C 标准库，依赖于 C 的堆分配方式。这两种方式的实现可能使用了不同的堆分配机制，混用可能导致 未定义行为（UB, Undefined Behavior）。


3. malloc和new分配的地址是虚拟地址还是物理地址，它们是怎么做转换的？
答：在现代操作系统（如 Linux、Windows、macOS）中，`malloc` 和 `new` 分配的地址是虚拟地址，而非物理地址。程序运行时，访问的都是虚拟地址，操作系统和硬件（MMU，内存管理单元）负责将虚拟地址映射到实际的物理地址。CPU 取指令或数据时，访问虚拟地址。MMU 通过页表找到虚拟地址对应的物理地址。若找到映射，直接访问物理内存（TLB 命中）。若未找到映射，触发 缺页异常，OS 分配新页并更新页表。

4. 进程和线程分别共享哪些资源？
答：
- 全局变量和静态变量；
- 堆内存
- 文件描述符
- 进程资源
  - 地址空间
  - 代码段
  - 静态资源

5. 堆区栈区访问速度对比？

答： 

|特性|栈区(Stack)|堆区(Heap)|
|--|--|--|
|**内存分配方式**|**顺序分配**，栈指针移动，O(1)|**动态分配**，复杂算法，O(log n)|
|**访问速度**|快|慢|
|**管理方式**|**自动**管理，函数退出自动释放|**手动**管理，需 malloc/free|
|**CPU寄存器**|直接基于栈指针，访问开销低|依赖指针，需多级间接寻址|
|**碎片化**|无|有|
|**缓存利用**|	好，数据连续性强|差，随机分布，缓存利用率低|
|**使用场景**|局部变量、函数调用栈|动态分配、生命周期不定的对象|

6. 内存布局
答 ：

| **区域**               | **存放内容**                        | **特点**                              |
|----------------------|--------------------------------|--------------------------------|
| **代码段 (.text)**    | 可执行代码                        | 只读，可共享                      |
| **已初始化数据段 (.data)** | 已初始化的全局/静态变量                | 进程生命周期内有效                  |
| **未初始化数据段 (.bss)**  | 未初始化的全局/静态变量                | 自动初始化为 0                    |
| **堆 (Heap)**        | 动态分配的内存 (`malloc/new`)  | 需手动释放，向上增长                |
| **栈 (Stack)**       | 局部变量、函数调用信息                | 自动管理，向下增长                  |
| **共享库映射区**        | 动态链接库 (`.so/.dll`)         | 可共享                          |
| **内核空间**          | 操作系统核心代码                    | 需系统调用访问                    |

7. 介绍伙伴系统？

答：

- 伙伴系统是一种 **基于二的幂次方** 的内存分配策略，核心是 **拆分**（Split）和**合并**（Merge） 机制。它能减少外部碎片，适用于 操作系统的物理内存管理，如 Linux 的 page_alloc.c。
- malloc/free 通常基于**堆** 管理，使用 **链表或二叉树** 分配，而伙伴系统主要用于 **内核的页管理**，适用于 固定大小的块，并支持 快速合并和拆分。


8. 内核态和用户态内存申请的区别？
答： 
- 用户态 使用 `malloc()` / `mmap()`，需要 系统调用，只能访问 虚拟地址。
- 内核态 使用 `kmalloc()` / `vmalloc()`，直接操作 物理内存，无须系统调用。
- `kmalloc()` 适合小块物理连续内存，`vmalloc()` 适合大块非连续内存。
- 内核管理物理内存（`伙伴系统` / `SLAB`），保证高效分配和释放。

9. RPC协议的报文格式：
答：

RPC 协议的报文格式通常由 **消息头（Header）** 和 **消息体（Body）** 组成：  

1. 消息头（固定长度）  
- **魔数（Magic Number）**：用于协议识别，防止误解析。  
- **版本号（Version）**：标识协议版本，确保兼容性。  
- **请求 ID（Request ID）**：唯一标识请求，便于匹配响应。  
- **序列化方式**：如 Protobuf、JSON、Hessian 等。  
- **压缩方式**：是否启用 gzip、snappy 等压缩。  
- **消息类型**：区分请求、响应或心跳。  
- **消息长度**：标识消息体大小，方便解析。  

1. 消息体（可变长度）  
- **方法名称**：调用的远程方法名。  
- **请求参数**：序列化后的参数数据。  
- **响应数据**：执行结果，格式与请求参数类似。  
- **错误信息**：失败时返回的错误描述。  

不同 RPC 框架（如 gRPC、Thrift、Dubbo）实现细节有所不同，例如 gRPC 基于 HTTP/2，使用 Protobuf 进行序列化，并采用 **Length-Prefixed Message** 格式。

10. 已经有HTTP协议为什么还需要RPC协议？

1. **高效的通信**  
   - RPC 通常基于二进制协议（如 Protobuf、Thrift），相比 HTTP 的文本格式（JSON、XML），序列化体积更小，解析更快。  
   - 采用长连接（如 gRPC 基于 HTTP/2 的多路复用），减少连接建立的开销。  

2. **简化调用方式**  
   - RPC 使远程调用像本地函数调用一样，无需手动构造 HTTP 请求。  
   - 提供自动代码生成（如 gRPC 的代码生成工具），减少开发工作量。  

3. **更好的错误处理和流控**  
   - gRPC 等 RPC 框架提供内建的错误码、重试机制和超时控制。  
   - 具备流式传输能力，适用于大数据或实时通信场景。  

4. **服务治理能力**  
   - RPC 框架通常内置负载均衡、服务注册发现、监控等能力，而 HTTP 需要额外组件支持。

11. 