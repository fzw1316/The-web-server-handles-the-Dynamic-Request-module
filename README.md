该项目的实现基于TCP协议的Echo服务器，是一个扩展了一个 动态内容处理模块 来处理动态请求（如时间、系统状态等）的模块。当服务器接收到包含特定内容请求的消息时，动态内容处理模块会生成响应内容并返回给客户端。

本模块是针对没有后端Web服务的环境设计的，所有的动态内容都在服务器端直接生成。
* 动态内容处理模块概述

*.1 动态内容的类型
我们使用一个简单的模块来处理动态内容请求。以下是当前支持的动态内容类型：
时间戳：返回当前的系统时间。
系统状态：返回当前服务器的负载和连接数量等信息。

*.2 模块架构
DynamicContentHandler 类是本模块的核心。它根据客户端发送的请求（如时间请求或系统状态请求）生成并返回相应的动态内容。请求格式如下：
请求动态时间：GET /time
请求系统状态：GET /status
DynamicContentHandler 会解析请求内容并生成相应的动态响应。
