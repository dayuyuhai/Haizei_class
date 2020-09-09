if [ ! -d srctestbyscript ]; then
	mkdir srctestbyscript
fi
cp -- src/* srctestbyscript
cd srctestbyscript
if ! make angle > /dev/null; then
	echo "> angle.c 编译失败，请先确保可编译通过"
else
	echo "> angle.c 编译成功"
	echo ""
	echo "测试运行结果"
	echo "================================================"
	RA=0
	RAT=1
	if echo "65 72 97" | ./angle | grep "right" > /dev/null; then
		echo "测评用例 1 得分：[1 / 1]"
		let RA=RA+1
	else
		echo "测评用例 1 得分：[0 / 1]"
	fi
	echo "用例说明：三角形 - 输入 65 72 97"
	echo "---------------------------"
	if echo "55 73 48" | ./angle | grep "right" > /dev/null; then
		echo "测评用例 2 得分：[1 / 1]"
		let RA=RA+1
	else
		echo "测评用例 2 得分：[0 / 1]"
	fi
	echo "用例说明：三角形 - 输入 55 73 48"
	echo "---------------------------"
	if echo "5 4 3" | ./angle | grep "right" > /dev/null; then
	    echo "5 4 3" | ./angle | grep "obtuse" > /dev/null && let RAT=0
	    echo "5 4 3" | ./angle | grep "acute" > /dev/null && let RAT=0
	else
		RAT=0
	fi
	echo "测评用例 3 得分：[$RAT / 1]"
	echo "用例说明：三角形 - 输入 5 4 3"
	echo "---------------------------"
	let RA=RA+RAT
	echo "5 4 3" > in.txt
	./angle < in.txt > out.txt
	cp out.txt right.txt > /dev/null
	mv angle program > /dev/null
	echo ""
	if ! make oj > /dev/null; then
		echo "> oj.c 编译失败，请先确保可编译通过"
	else
		echo "> oj.c 编译成功"
		R=0
		if ./oj | grep "Accept" > /dev/null; then
			let R=R+1
			echo "测评用例 4 得分：[1 / 1]"
		else
			echo "测评用例 4 得分：[0 / 1]"
		fi
		echo "用例说明：一致的结果"
		echo "---------------------------"
		echo "" >> right.txt
		if ./oj | grep "Accept" > /dev/null; then
			let R=R+1
			echo "测评用例 5 得分：[1 / 1]"
		else
			echo "测评用例 5 得分：[0 / 1]"
		fi
		echo "用例说明：结尾相差一个换行"
		echo "---------------------------"
		echo "" >> right.txt
		if ./oj | grep "Wrong" > /dev/null; then
			let R=R+1
			echo "测评用例 6 得分：[1 / 1]"
		else
			echo "测评用例 6 得分：[0 / 1]"
		fi
		echo "用例说明：结尾相差多个换行"
	fi
	echo ""
	echo "本地非全部测评数据测评得分"
	echo "================================================"
	echo "angle 测试得分：[$RA / 3]"
	echo "oj 测试得分：[$R / 3]"
fi
