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

init() {
    Score=0
    Tips=""
    test_flag=1
    filename="my_ls.c"
    execname="./my_ls"
    exec_program=$execname
}

return_value(){
    ans=$1
    correct_ans=$2
    tips=$3
    score=$4
    if [[ "$ans" != "$correct_ans" ]];then
        Tips=${Tips}$tips
    else
        Score=`expr $score + $Score`
    fi
}

re_init(){
    test_dir=$1
    test_flag=$2
    exec_program=$3
}

add_flag(){
    lv=$1
    rv=$2
    if [[ $lv == $rv ]];then
        test_flag=$[$test_flag+1];
    fi
}

grep_file(){
    file_name=$1
    $exec_program $test_dir 2>/dev/null | grep $file_name 2>/dev/null 1>/dev/null
    exist=$?
    add_flag $exist 0
}

check_adjoin(){
    file1=$1
    file2=$2

    echo "$f_or_d" | grep $file1 2>/dev/null 1>/dev/null
    exist=$?
    if [[ $exist == 0 ]];then
        pos=$i;
    fi
    echo "$f_or_d" | grep $file2 2>/dev/null 1>/dev/null
    exist=$?
    if [[ $exist == 0 && $[$pos+1] == $i ]];then
        test_flag=$[$test_flag+1];
    fi
}

simple_sort() {
    i=$1
    for f_or_d in `$exec_program $test_dir 2>/dev/null | cut -d " " -f 1-1 2>/dev/null`
    do
        i=$[$i+1];
        check_adjoin cat cow
        check_adjoin hhh horse
    done
}

test_l(){
    $exec_program $test_dir | grep cat >test3.log
    mode=`awk -F" " '{ print $1 }' test3.log`
    link_num=`awk -F" " '{ print $2 }' test3.log`
    username=`whoami`
    get_username=`awk -F" " '{ print $3 }' test3.log`
    add_flag "$mode" "-rw-r--r--"
    add_flag "$link_num" 1
    add_flag "$username" "$get_username"
}

# 变量初始化

init

# 文件是否存在

ls | grep $filename 2>/dev/null 1>/dev/null
file_exist=$?
if [[ $file_exist == 1 ]];then
    Tips=${Tips}"File 'my_ls.c' not exists; "
    test_flag=0;
fi

# 文件是否可编译

if [[ $test_flag  == 1 ]]; then
    gcc -D _CHECK -o $exec_program $filename 2>/dev/null 1>/dev/null 
    compile_result=$?
    if [[ $compile_result == 1 ]];then
        Tips=${Tips}"Compile error; "
        test_flag=0;
    fi
fi


# 文件存在且可编译

if [[ $test_flag  == 1 ]]; then
    tar -zxvf kkb_ls_data.tar.gz 2>/dev/null 1>/dev/null
    
# 多个参数
    re_init "kkb_ls_data kkb_ls_data/b_dir kkb_ls_data/m_dir" 0 "$execname"
    grep_file bird
    grep_file tr.sh
    grep_file a_dir
    return_value $test_flag 3 "Multiple parameters are not supported; " 25

# 简单排序
    re_init "kkb_ls_data/m_dir" 0 "$execname"
    simple_sort 0
    return_value $test_flag 2 "Simple sorting is not supported; " 25

# ls -l
    re_init "kkb_ls_data/a_dir" 0 "$execname -l"
    test_l
    return_value $test_flag 3 "ls -l function is not supported; " 25

# ls -a
    re_init "kkb_ls_data/a_dir" 0 "$execname -a"
    grep_file pig
    grep_file dog
    return_value $test_flag 2 "ls -a function is not supported; " 25

# 删除用完的文件
    rm $execname 2>/dev/null
    rm -r kkb_ls_data 2>/dev/null
    rm test3.log 2>/dev/null

fi

rm kkb_ls_data.tar.gz 2>/dev/null

if [[ "$Tips" == "" ]]; then
    fruit 100 "JudgeMsg" "Success"
else
    fruit $Score "Tips" "${Tips}"
fi

