# C编译器功能TODO

Note: ccc is no longer an active project. The successor is
[subc-llvm](https://github.com/iiicp/subc-llvm).

# 声明

- [ ]  存储类声明说明符(`extern`、`static`、`auto`、`register`、`typedef`)
- [ ]  类型限定符(`const`、`volatile`、`restrict`)
- [x]  声明说明符(`char`、`short`、`int`、`long`)
- [x]  指针说明符(`*`)
- [x]  直接说明符(`[]`、`()`)
- [x]  结构体说明符(`struct or union {struct-declaration*}、struct or union tag{struct-declaration*}`)
- [ ]  枚举说明符
- [ ]  函数声明符(`inline`)

# 语句

- [x]  if-else
- [x]  switch-case-default
- [x]  while
- [x]  do-while
- [x]  for
- [x]  goto-label
- [x]  break
- [x]  continue
- [x]  blockStmt

# 表达式

- [ ]  逗号表达式(`,`)
- [x]  赋值表达式(`=`)
- [ ]  赋值表达式(`+=`、`-=`、`*=`、`/=` 、`%=`、`<<=`、`>>=`、`&=`、`|=`、`^=`)
- [ ]  条件表达式(`?:`)
- [ ]  逻辑或表达式(`||`)
- [ ]  逻辑与表达式(`&&`)
- [ ]  按位或表达式(`|`)
- [ ]  按位异或表达式(`^`)
- [ ]  按位与表达式(`&`)
- [x]  相等表达式(`==`、`!=`)
- [x]  关系表达式(`>`、`>=`、`<`、`<=`)
- [ ]  移位表达式(`<<`、`>>`)
- [x]  加法表达式(`+`、`-`)
- [x]  乘法表达式(`*`、`/`)
- [ ]  乘法表达式(`%`)
- [ ]  case表达式 (`(type-name) unary-expression`)
- [x]  一元表达式(`+`、`-`、`&`、`*`)
- [ ]  一元表达式(`++`、`- -`)
- [ ]  一元表达式(`~`、`!`)
- [x]  一元表达式(`sizeof unary-expression`)
- [ ]  一元表达式(`sizeof (type-name)`)
- [x]  后缀表达式(`[ ]`、`( )`、`.`、`→`)
- [ ]  后缀表达式(`++`、 `- -`)
- [x]  基本表达式(`id`、`num`、(`Expr`)、`StmtExpr`)

# 词素

- [ ]  整数解析（八进制、十进制、十六进制、后缀）
- [ ]  浮点数解析 （后缀）
- [ ]  字符解析（包含转义字符）
- [ ]  字符串解析（包含转义字符）
- [ ]  标识符（包含关键字）
- [ ]  运算符、标点符号、分界符

# 操作系统平台

- [x]  Linux
- [x]  MacOSX

# 指令集

- [x]  X86-64
