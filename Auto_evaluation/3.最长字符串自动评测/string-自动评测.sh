#!/bin/bash

help() {
    echo 'Usage: score(int) YourJudgeMsg(string) YourTips(string)'
    echo 'Or You Can Usage: score(int) JudgeMsg/Tips(string) Yourmsg(string)'
}

fruit() {
    num=$#
    #parameter judgement
    if [[ $num -ne 1 && $num -ne 3 ]]; then
        echo 'Parameter number error'
        exit 2
    fi

    #get statu
    score=$1
    if [[ score -eq 0 ]]; then
        statu=Failed
    elif [[ score -eq 100 ]]; then
        statu=Successed
    else
        statu=PartialSuccessed
    fi

    if [[ $num -eq 1 ]]; then
        msg='{"JudgeStatus": "'${statu}'", "JudgeMsg": "None", "Tips": "None", "Score": '${score}'}'
    elif [[ $num -eq 3 ]]; then
        key=$2
        value=$3
        if [[ $key == 'JudgeMsg' ]]; then
            msg='{"JudgeStatus": "'${statu}'", "JudgeMsg": "'${value}'", "Tips": "None", "Score": '${score}'}'
        elif [[ $key == 'Tips' ]]; then
            msg='{"JudgeStatus": "'${statu}'", "JudgeMsg": "None", "'${key}'": "'${value}'", "Score": '${score}'}'
        else
            msg='{"JudgeStatus": "'${statu}'", "JudgeMsg": "'$2'", "Tips": "'$3'", "Score": '${score}'}'
        fi
    fi
    echo $msg
}

judge_file(){
    tips=$1
    Tips=${Tips}$tips
    test_flag=0
}

init() {
    Score=0
    Tips=""
    filename=$1
    test_flag=1
    test_dir="kkb_string_data/a_dir kkb_string_data/m_Dir kkb_string_data/test"
    #ans_log="ans.log"
}

judge_str_fn() {
    string=$1
    correct_string=$2
    tips=$3
    score=$4
    if [[ "$string" == "$correct_string" ]];then
        Tips=${Tips}$tips
        Score=$score
    fi
}

init "string.sh"

# 文件是否存在
ls | grep $filename 2>/dev/null 1>/dev/null
file_exist=$?
if [[ $file_exist -ne 0 ]];then
    judge_file "File 'string.sh' not exists; "
fi

# 文件是否为脚本
if [[ $test_flag  == 1 ]];then
    first_line=`head -n 1 $filename | tr -d " "` 2>/dev/null
    if [[ "$first_line" != "#!/bin/bash" ]];then
        judge_file "This is not a shell script; "
    fi
fi

# 文件编译
if [[ $test_flag  == 1 ]]; then
    tar -zxvf kkb_string_data.tar.gz 2>/dev/null 1>/dev/null
    #bash $filename $test_dir 2>/dev/null 1>$ans_log
    bash $filename $test_dir 2>/dev/null 1>/dev/null
    compile_result=$?
    if [[ $compile_result -ne 0 ]];then
        judge_file "Compile error; "
    fi

fi

# 是否有冗余输出
# if [[ $test_flag == 1 ]];then
#    num_of_line=`awk 'END{print NR}' $ans_log 2>/dev/null`
#    if [[ $num_of_line -ne 1  ]]; then
#        judge_file "Redundant output(more than one line); "
#    fi
# fi

# 格式错误
#if [[ $test_flag == 1 ]];then
#    test_str=`awk -F":" '{ print $4 }' $ans_log`
#    if [[ -z "$test_str" ]]; then
#        judge_file "Wrong format or missing elements; "
#    fi
#fi


if [[ $test_flag == 1 ]];then
    ans=`bash $filename $test_dir 2>/dev/null`

    # 不支持多个参数
    judge_str_fn "$ans" "kkb_string_data/a_dir/deep1/deep2/.test2:21:AaQQaQQaQQaQQaQQaQQaQ:22" "Multiple parameters are not supported; " 50
    # 不支持递归
    judge_str_fn "$ans" "kkb_string_data/m_Dir/.test2:21:BaQQaQQaQQaQQaQQaQQaQ:7" "Directory recursion are not supported; " 50
    # 不支持隐藏文件
    judge_str_fn "$ans" "kkb_string_data/m_Dir/deep1/deep2/test1:21:CaQQaQQaQQaQQaQQaQQaQ:16" "Hidden files are not supported" 50
    # 未输出第一个符合条件的答案
    judge_str_fn "$ans" "kkb_string_data/m_Dir/deep1/deep2/.test2:27:QaQQaQQaQQaQQaQQaQQaQQaQQaW:21" "The output string does not match for the first time" 80
    # 都支持
    judge_str_fn "$ans" "kkb_string_data/m_Dir/deep1/deep2/.test2:27:QaQQaQQaQQaQQaQQaQQaQQaQQaQ:19" "" 100

    if [[ $Score -eq 0 ]]; then
        Tips="Wrong answer or wrong format; "
    fi

fi

# 删除文件
rm -r kkb_string_data 2>/dev/null
#rm $ans_log 2>/dev/null
rm kkb_string_data.tar.gz 2>/dev/null

if [[ "$Tips" == "" ]]; then
    fruit 100 "JudgeMsg" "Success"
else
    fruit $Score "Tips" "${Tips}"
fi


