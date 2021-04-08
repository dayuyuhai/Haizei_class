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
    filename=$1
    cnt=0
}

del() {
    rm ans.out 2>/dev/null 1>/dev/null
    rm -r data 2>/dev/null 1>/dev/null
    rm data.tar.gz 2>/dev/null 1>/dev/null
}

num_of_line=`ls data/input/ | sort -n | wc -l`
unit_score=$[100/$num_of_line]

init "ans.sh"

for ((i=1; i<=$num_of_line; i++)); 
do
    timeout 10 bash $filename < data/input/$i.in 1>ans.out 2>/dev/null
    com_res=$?
    if [[ $com_res -ne 0 ]]; then
        Tips=${Tips}"Compile error or time limit exceeded; "
        fruit 0 "Tips" "${Tips}"
        del
        exit
    fi
    diff data/output/$i.out ans.out -b 2>/dev/null 1>/dev/null
    cmp_res=$?
    if [[ $cmp_res -eq 0 ]] ;then
        Score=`expr $unit_score + $Score`
    else
        cnt=$[$cnt+1]
    fi
done

if [[ $cnt -ne 0  ]]; then
    Tips=${Tips}"$cnt"" use cases failed."
fi

del

if [[ "$Tips" == "" ]]; then
    fruit 100 "JudgeMsg" "Success"
else
    fruit $Score "Tips" "${Tips}"
fi

