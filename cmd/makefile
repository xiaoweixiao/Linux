.PHONY:test
	#声明一个伪对象，强制生成
	#Makefile文件编写规则：
	#对象名称：依赖对象名称

	#$^是一个预定义变量，冒号右边的所有依赖文件
	#$@是一个预定义变量，冒号左边要生成的文件对象
test:test.c tmp.c
	gcc $^ -o $@ 
	#gcc test.c tmp.c -o test
test1:test.o tmp.o
	gcc test.o tmp.o -o test
test.o:test.c
	gcc -c test.c -o test.o
tmp.o:tmp.c 
	gcc -ctmp.c -o tmp.o


#因为makefile规定说永远只生成第一个对象，因此，在生成了test之后
#就不会在继续往下执行，因此不会再次为了生成clean而执行删除操作
#这个clean是为了专门在外边调用 make clean来手动清理文件的

clear:
	rm -f test.o tmp.o test
