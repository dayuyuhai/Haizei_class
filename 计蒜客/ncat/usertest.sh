cp -- src/* srctestbyscript
cd srctestbyscript
echo "> 编译自测"
if ! make ncat > /dev/null; then
	echo "> 编译失败"
elif ! make clean > /dev/null; then
	echo "> 编译清除失败"
elif ! make ncat > /dev/null; then
	echo "> 再次编译失败"
else
	R=0
	echo "> 编译未报错"
	echo "> 编译自测完毕"
	echo ""
	echo "测试运行结果"
	echo "================================================"
	if ./ncat -d < in > 1 && diff 1 d > /dev/null; then
		echo "测评用例 1 得分：[1 / 1]"
		let R=R+1
	else
		echo "测评用例 1 得分：[0 / 1]"
	fi
	echo "用例说明：阿拉伯数字标准输入输出"
	echo "---------------------------"
	if ./ncat -d in > 2 && diff 2 d > /dev/null; then
		echo "测评用例 2 得分：[1 / 1]"
		let R=R+1
	else
		echo "测评用例 2 得分：[0 / 1]"
	fi
	echo "用例说明：阿拉伯数字文件输入标准输出"
	echo "---------------------------"
	if ./ncat -d in 3 && diff 3 d > /dev/null 2>&1; then
		echo "测评用例 3 得分：[1 / 1]"
		let R=R+1
	else
		echo "测评用例 3 得分：[0 / 1]"
	fi
	echo "用例说明：阿拉伯数字文件输入输出"
	echo "---------------------------"
	if ./ncat -r < in > 4 && diff 4 r > /dev/null; then
		echo "测评用例 4 得分：[1 / 1]"
		let R=R+1
	else
		echo "测评用例 4 得分：[0 / 1]"
	fi
	echo "用例说明：罗马数字标准输入输出"
	echo "---------------------------"
	if ./ncat -r in > 5 && diff 5 r > /dev/null; then
		echo "测评用例 5 得分：[1 / 1]"
		let R=R+1
	else
		echo "测评用例 5 得分：[0 / 1]"
	fi
	echo "用例说明：罗马数字文件输入标准输出"
	echo "---------------------------"
	if ./ncat -r in 6 && diff 6 r > /dev/null 2>&1; then
		echo "测评用例 6 得分：[1 / 1]"
		let R=R+1
	else
		echo "测评用例 6 得分：[0 / 1]"
	fi
	echo "用例说明：罗马数字文件输入输出"
	echo "---------------------------"
    echo ""
	echo "本地非全部测评数据测评得分"
	echo "================================================"
    echo "编译未报错：[1 / 1]"
	echo "ncat 测试得分：[$R / 6]"
fi
