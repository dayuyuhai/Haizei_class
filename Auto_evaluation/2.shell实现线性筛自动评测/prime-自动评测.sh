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


init "prime.sh"

# 文件是否存在

ls | grep $filename 2>/dev/null 1>/dev/null
file_exist=$?
if [[ $file_exist -ne 0 ]];then
    judge_file "File 'prime.sh' not exists; "
fi

# 文件是否为脚本

if [[ $test_flag  == 1 ]];then
    #first_line=`head -n 1 $filename | tr -d " "` 2>/dev/null
    first_line=`head -n 1 $filename` 2>/dev/null
    if [[ "$first_line" != "#!/bin/bash" ]];then
        judge_file "This is not a shell script; "
    fi
fi

# 文件是否超过5行

if [[ $test_flag  == 1 ]]; then
    num_of_line=`awk 'END{print NR}' $filename 2>/dev/null`
    if [[ $num_of_line -le 5 ]];then
        judge_file "The file is less than 5 lines; "
    fi
fi

# 文件是否可编译

if [[ $test_flag  == 1 ]]; then
    bash $filename 2>/dev/null 1>/dev/null
    compile_result=$?
    if [[ $compile_result -ne 0 ]];then
        judge_file "Compile error; "
    fi
fi


# 文件正常

if [[ $test_flag  == 1 ]]; then

    ans=`bash prime.sh 2>/dev/null`
    if [[ $ans -ne 5736396 ]];then
        judge_file "Wrong answer; "
    fi

fi

if [[ "$Tips" == "" ]]; then
    fruit 100 "JudgeMsg" "Success"
else
    fruit $Score "Tips" "${Tips}"
fi


