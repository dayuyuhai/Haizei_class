#!/bin/bash
#!/bin/bash
max=0
goal=
str=
line=

function findMax(){

    if [[ $# -eq 0 ]];then
        local arg="."
    else
         local arg=${1}
    fi

    local c=${arg}${2}
    #echo "${arg}  ${2}"
    file ${c} | grep -q  "ASCII text"
    if [[ $? -eq 0 ]]; then
        #echo "判断文件内容${c}"
        for j in `cat ${c} | tr -c "a-zA-Z" " "`;do
            local temp=`echo $j | wc -L`
                if [[ ${max} -lt ${temp} ]];then
                    line=`grep -n ${j} ${c}`        
                

                    max=${temp}
                
                    goal=${c}
                    str=${j}
                fi
            done
    else
        file ${c} | grep -q "directory"
        
        if [[ $? -eq 0 ]];then
        
            #echo "进入目录${c}"
            for i in `ls -A ${c}`;do
                findMax ${c}/ ${i}
            done
        fi
    fi
    return
}


findMax $1
#echo "--------------结果------------------"
line=`echo ${line} | cut -d ':' -f 1`
echo "${goal}:${max}:${str}:${line}"

