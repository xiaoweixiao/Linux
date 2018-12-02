#	makefile编写规则
# 		 目标对象：依赖对象
# 		 [制表符]如何通过依赖对象生成目标对象的编译命令
#Makefile中有几个预定义变量
#	$@ 代表目标对象
#	$^ 代表所有依赖对象
#	$< 代表所有以来对象的中的第一个
all:test test1 

.PHONY:test test1
test:test.c tmp.c
	gcc $^ -o $@
#在makefile当中，永远只生成第一个对象，生成后则退出
#因此要生成多个对象，就要在前面定义一个对象包含所有欲生成的对象
#声明伪对象强制生成对象
test1:test.c  tmp.c
	gcc $^ -o $@
clean:
	rm -f test test1
