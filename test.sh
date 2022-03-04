#!/bin/bash

test_number=1

test_in[0]='read_test1.txt'
test_in[1]='read_test2.txt'
test_in[2]='read_test3.txt'
test_in[3]='read_test4.txt'
test_in[4]='read_test5.txt'
test_in[5]='read_test6.txt'
test_in[6]='read_test7.txt'
test_in[7]='read_test8.txt'
test_in[8]='read_test9.txt'
test_in[9]='read_test10.txt'
test_in[10]='read_test11.txt'
test_in[11]='read_test12.txt'

test_out[0]=exp_write1.txt
test_out[1]=exp_write2.txt
test_out[2]=exp_write3.txt
test_out[3]=exp_write4.txt
test_out[4]=exp_write5.txt
test_out[5]=exp_write6.txt
test_out[6]=exp_write7.txt
test_out[7]=exp_write8.txt
test_out[8]=exp_write9.txt
test_out[9]=exp_write10.txt
test_out[10]=exp_write11.txt
test_out[11]=exp_write12.txt

for ((i = 0; i < 12; i++))
do
	echo "Test $test_number"
	test_number=$(($test_number + 1))
	./app.exe < ${test_in[i]}

	if (cmp -s write.txt ${test_out[i]})
	then echo "OK"
	else echo "Error"
	fi
done
