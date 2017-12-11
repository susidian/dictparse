模块介绍
-----------------------------------
通用的词表解析读取工具类，能解析并读取如下形式的词表：

   <col1>\t<col2>\t...\t<coln>

每一行都是一条记录，每一列可能的类型包括：

   * int
   * float
   * char *
   * 形如num:item1,item2,item3的数组（可以理解为T[num]的数组，T是用户给出某种build-in类型）
   * uint32_t
   * uint64_t
   * 其他用户自定义类型

每一列的数据中均不包含\t字符，每一行以\n结尾。


程序运行
-----------------------------------
生成静态库parser
    1.执行命令 make clean (清理之前的lib)
    2.执行命令 make  (生成在output/lib下)

运行demo
    1.执行命令 make clean (清理之前的demo) 
    2.执行命令 make  (生成在output/bin下)
    3.执行命令 ./demo -f test.dict

运行单测
    1.执行命令 make clean (清理之前的用例)
    2.执行命令 make (生成在unittest/output/bin下)
    3.执行命令 ./unittest_parser
